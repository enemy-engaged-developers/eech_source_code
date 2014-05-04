// 
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
// 
// 	 Please see the document LICENSE.TXT for the full licence agreement
// 
// 2. LICENCE
//  2.1 	
//  	Subject to the provisions of this Agreement we now grant to you the 
//  	following rights in respect of the Source Code:
//   2.1.1 
//   	the non-exclusive right to Exploit  the Source Code and Executable 
//   	Code on any medium; and 
//   2.1.2 
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2 	
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1 
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
// 
// 3. GENERAL OBLIGATIONS
//  3.1 
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1 
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2 
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3 
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4 
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5 
// 	not to place any restrictions on the operability of the Source 
// 	Code;
//   3.1.6 
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7 
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
// 



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_SCREEN_SHOT_INDEX	(999)

#define LARGE_IMAGE_PATH		("SCRNSHOT\\LARGE\\")
#define SMALL_IMAGE_PATH		("SCRNSHOT\\SMALL\\")
#define VIEWPOINT_DATA_PATH	("SCRNSHOT\\")
#define WRITE_VIEWPOINT_DATA FALSE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	found_first_screen_shot_index = FALSE,
	screen_shot_index = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_screen_image_and_viewpoint_data (void)
{
	char
		filename[100],
		large_image_filename[100],
		small_image_filename[100],
		viewpoint_data_filename[100];

	//
	// find first screen shot index
	//

	if (!found_first_screen_shot_index)
	{
		while (TRUE)
		{
			sprintf (large_image_filename, "%sIMAGE%03d.TGA", LARGE_IMAGE_PATH, screen_shot_index);

			if (file_exist (large_image_filename))
			{
				screen_shot_index++;

				if (screen_shot_index == 1000)
				{
					break;
				}
			}
			else
			{
				found_first_screen_shot_index = TRUE;

				break;
			}
		}
	}

	//
	// write screen files and viewpoint data file
	//

	if (screen_shot_index <= MAX_SCREEN_SHOT_INDEX)
	{
		sprintf (filename, "IMAGE%03d", screen_shot_index);

		debug_log ("Saving screen image (%s)", filename);

		sprintf (large_image_filename, "%s%s.TGA", LARGE_IMAGE_PATH, filename);

		sprintf (small_image_filename, "%s%s.TGA", SMALL_IMAGE_PATH, filename);

		sprintf (viewpoint_data_filename, "%s%s.TXT", VIEWPOINT_DATA_PATH, filename);

		////////////////////////////////////////

		if (lock_screen (video_screen))
		{

			save_tga_screen (large_image_filename);

			unlock_screen (video_screen);
		}

		////////////////////////////////////////

#if WRITE_VIEWPOINT_DATA
		{
			FILE
				*fp;

			int
				x_sec,
				z_sec;

			fp = safe_fopen (viewpoint_data_filename, "w");

			fprintf (fp, "Image viewpoint data:\n\n");

			fprintf (fp, "Map           : unknown\n");

			fprintf (fp, "X             : %.2f\n", main_vp.x);
			fprintf (fp, "Y             : %.2f\n", main_vp.y);
			fprintf (fp, "Z             : %.2f\n", main_vp.z);

			get_terrain_3d_sector (main_vp.x, main_vp.z, &x_sec, &z_sec);

			fprintf (fp, "X sector (3D) : %d\n", x_sec);
			fprintf (fp, "Z sector (3D) : %d\n", z_sec);

			get_x_sector (x_sec, main_vp.x);
			get_z_sector (z_sec, main_vp.z);

			fprintf (fp, "X sector (AI) : %d\n", x_sec);
			fprintf (fp, "Z sector (AI) : %d\n", z_sec);

			fprintf (fp, "Heading (degs): %.2f\n", deg (get_heading_from_attitude_matrix (main_vp.attitude)));
			fprintf (fp, "Pitch (degs)  : %.2f\n", deg (get_pitch_from_attitude_matrix (main_vp.attitude)));
			fprintf (fp, "Roll (degs)   : %.2f\n", deg (get_roll_from_attitude_matrix (main_vp.attitude)));

			safe_fclose (fp);
		}
#endif
		////////////////////////////////////////

		screen_shot_index++;
	}
	else
	{
		debug_colour_log (DEBUG_COLOUR_RED, "Exceeded screen image limit");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_screen_image_and_viewpoint_data (void)
{
	char
		filename[100],
		large_image_filename[100],
		small_image_filename[100],
		viewpoint_data_filename[100];

	debug_colour_log (DEBUG_COLOUR_RED, "Deleting all screen images");

	for (screen_shot_index = 0; screen_shot_index < MAX_SCREEN_SHOT_INDEX; screen_shot_index++)
	{
		sprintf (filename, "IMAGE%03d", screen_shot_index);

		sprintf (large_image_filename, "%s%s.TGA", LARGE_IMAGE_PATH, filename);

		sprintf (small_image_filename, "%s%s.TGA", SMALL_IMAGE_PATH, filename);

		sprintf (viewpoint_data_filename, "%s%s.TXT", VIEWPOINT_DATA_PATH, filename);

		remove (large_image_filename);

		remove (small_image_filename);

		remove (viewpoint_data_filename);
	}

	found_first_screen_shot_index = TRUE;

	screen_shot_index = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void save_high_res_screen_image ( void )
{
	char
		filename[100],
		image_filename[100];

	int
		x,
		y,
		x_repeat,
		y_repeat,
		screen_width,
		screen_height,
		screen_pitch;

	unsigned short int
		*huge_screen_shot_memory;

	unsigned char
		*screen_data;

	x_repeat = 8;

	y_repeat = 8;

	screen_width = get_screen_width ( video_screen );

	screen_height = get_screen_height ( video_screen );

	huge_screen_shot_memory = ( unsigned short int * ) safe_malloc ( sizeof ( unsigned short int ) * screen_width * screen_height * x_repeat * y_repeat );

	for ( y = 0; y < y_repeat; y++ )
	{

		for ( x = 0; x < x_repeat; x++ )
		{

			unsigned short int
				*destination_ptr,
				*screen_line;

			int
				screen_y;

			//
			// Render the big views
			//

			draw_application_highres_screen ( x, y, x_repeat, y_repeat );

			if ( lock_screen ( video_screen ) )
			{
	
				screen_data = get_screen_data ( video_screen );
	
				screen_pitch = get_screen_pitch ( video_screen );
	
				destination_ptr = huge_screen_shot_memory + ( y * x_repeat * screen_width * screen_height ) + ( x * screen_width );
	
				for ( screen_y = 0; screen_y < screen_height; screen_y++ )
				{
	
					screen_line = ( unsigned short int * ) ( screen_data + ( screen_y * screen_pitch ) );
	
					memcpy ( destination_ptr, screen_line, screen_width * sizeof ( unsigned short int ) );
	
					destination_ptr += x_repeat * screen_width;
				}
	
				unlock_screen ( video_screen );
			}
		}
	}

	//
	// find first screen shot index
	//

	if (!found_first_screen_shot_index)
	{
		while (TRUE)
		{
			sprintf (image_filename, "%sIMAGE%03d.PSD", LARGE_IMAGE_PATH, screen_shot_index);

			if (file_exist (image_filename))
			{
				screen_shot_index++;

				if (screen_shot_index == 1000)
				{
					break;
				}
			}
			else
			{
				found_first_screen_shot_index = TRUE;

				break;
			}
		}
	}

	//
	// write screen files and viewpoint data file
	//

	if (screen_shot_index <= MAX_SCREEN_SHOT_INDEX)
	{
		sprintf (filename, "IMAGE%03d", screen_shot_index);

		debug_log ("Saving screen image (%s)", filename);

		sprintf (image_filename, "%s%s.PSD", LARGE_IMAGE_PATH, filename);

		write_psd_screen_file ( image_filename,
												screen_width * x_repeat,
												screen_height * y_repeat,
												screen_width * x_repeat * sizeof ( unsigned short int ),
												( unsigned char * ) huge_screen_shot_memory );

		screen_shot_index++;
	}
	else
	{
		debug_colour_log (DEBUG_COLOUR_RED, "Exceeded screen image limit");
	}

	safe_free ( huge_screen_shot_memory );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_high_res_screen_image_viewangle_1 ( void )
{

	full_screen_width_view_angle = rad ( 59.99 );

	full_screen_height_view_angle = rad ( 46.82 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_high_res_screen_image_viewangle_2 ( void )
{

	full_screen_width_view_angle = rad ( 90 );

	full_screen_height_view_angle = rad ( 73.74 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_high_res_screen_image_viewangle_3 ( void )
{

	full_screen_width_view_angle = rad ( 120 );

	full_screen_height_view_angle = rad ( 104.82 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_high_res_screen_image_viewangle_4 ( void )
{

	full_screen_width_view_angle = rad ( 20 );

	full_screen_height_view_angle = rad ( 15.6 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

