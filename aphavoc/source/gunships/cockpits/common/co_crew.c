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

#define DEBUG_MODULE						0

#define DEBUG_MODULE_CREW_CAMERAS	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_pilot_virtual_cockpit_cameras,
	current_pilot_virtual_cockpit_camera,
	num_co_pilot_virtual_cockpit_cameras,
	current_co_pilot_virtual_cockpit_camera;

static object_3d_camera_index_numbers
	pilot_crew_camera_index,
	co_pilot_crew_camera_index;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CREW ROLE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

crew_roles get_crew_role (void)
{
	entity
		*en;

	en = get_pilot_entity ();

	ASSERT (en);

	return (get_local_entity_int_value (en, INT_TYPE_CREW_ROLE));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CREW MOTION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_motion_values (const char *filespec, int num_frames, motion_data *array)
{
	FILE
		*fp;

	char
		s[200];

	int
		num_frames_in_file,
		frame,
		i_value;

	float
		f_value;

	ASSERT (filespec);

	ASSERT (num_frames > 0);

	ASSERT (array);

	fp = safe_fopen (filespec, "r");

	//
	// check for 'LWMO' file
	//

	fscanf (fp, "%s", s);

	if (strcmp (s, "LWMO") != 0)
	{
		debug_fatal ("%s is not a Lightwave motion file", filespec);
	}

	//
	// read off unwanted values
	//

	fscanf (fp, "%d", &i_value);

	fscanf (fp, "%d", &i_value);

	//
	// check number of frames
	//

	fscanf (fp, "%d", &num_frames_in_file);

	if (num_frames_in_file != num_frames)
	{
		debug_fatal ("Incorrect number of frames in motion file %s (expected = %d, actual = %d)", num_frames, num_frames_in_file);
	}

	//
	// read motion values
	//

	for (frame = 0; frame < num_frames; frame++)
	{
		fscanf (fp, "%f %f %f %f %f %f %f %f %f", &array->x, &array->y, &array->z, &array->heading, &array->pitch, &array->roll, &f_value, &f_value, &f_value);

		array->heading = rad (array->heading);

		array->pitch = rad (array->pitch);

		array->roll = rad (array->roll);

		fscanf (fp, "%d %d %d %d %d", &i_value, &i_value, &i_value, &i_value, &i_value);

		array++;
	}

	safe_fclose (fp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void interpolate_motion_values (float x, float y, motion_data *array, int array_width, motion_data *result)
{
	int
		x_whole,
		y_whole,
		i1,
		i2;

	float
		x_fractional,
		y_fractional;

	motion_data
		y1,
		y2;

	ASSERT (array);

	ASSERT (array_width > 0);

	ASSERT (result);

	x_whole = floor (x);

	x_fractional = x - x_whole;

	y_whole = floor (y);

	y_fractional = y - y_whole;

	i1 = (y_whole * array_width) + x_whole;

	i2 = i1 + array_width;

	y1.x = array[i1].x + ((array[i2].x - array[i1].x) * y_fractional);
	y1.y = array[i1].y + ((array[i2].y - array[i1].y) * y_fractional);
	y1.z = array[i1].z + ((array[i2].z - array[i1].z) * y_fractional);
	y1.heading = array[i1].heading + ((array[i2].heading - array[i1].heading) * y_fractional);
	y1.pitch = array[i1].pitch + ((array[i2].pitch - array[i1].pitch) * y_fractional);
	y1.roll = array[i1].roll + ((array[i2].roll - array[i1].roll) * y_fractional);

	i1++;

	i2++;

	y2.x = array[i1].x + ((array[i2].x - array[i1].x) * y_fractional);
	y2.y = array[i1].y + ((array[i2].y - array[i1].y) * y_fractional);
	y2.z = array[i1].z + ((array[i2].z - array[i1].z) * y_fractional);
	y2.heading = array[i1].heading + ((array[i2].heading - array[i1].heading) * y_fractional);
	y2.pitch = array[i1].pitch + ((array[i2].pitch - array[i1].pitch) * y_fractional);
	y2.roll = array[i1].roll + ((array[i2].roll - array[i1].roll) * y_fractional);

	result->x = y1.x + ((y2.x - y1.x) * x_fractional);
	result->y = y1.y + ((y2.y - y1.y) * x_fractional);
	result->z = y1.z + ((y2.z - y1.z) * x_fractional);
	result->heading = y1.heading + ((y2.heading - y1.heading) * x_fractional);
	result->pitch = y1.pitch + ((y2.pitch - y1.pitch) * x_fractional);
	result->roll = y1.roll + ((y2.roll - y1.roll) * x_fractional);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CREW CAMERAS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_virtual_cockpit_cameras (void)
{
	#if DEBUG_MODULE_CREW_CAMERAS

	debug_colour_watch (DEBUG_COLOUR_AMBER, "pilot_crew_camera_index = %d", MT_INT, &pilot_crew_camera_index);
	debug_colour_watch (DEBUG_COLOUR_AMBER, "num_pilot_virtual_cockpit_cameras = %d", MT_INT, &num_pilot_virtual_cockpit_cameras);
	debug_colour_watch (DEBUG_COLOUR_AMBER, "current_pilot_virtual_cockpit_camera = %d", MT_INT, &current_pilot_virtual_cockpit_camera);

	debug_colour_watch (DEBUG_COLOUR_MAGENTA, "co_pilot_crew_camera_index = %d", MT_INT, &co_pilot_crew_camera_index);
	debug_colour_watch (DEBUG_COLOUR_MAGENTA, "num_co_pilot_virtual_cockpit_cameras = %d", MT_INT, &num_co_pilot_virtual_cockpit_cameras);
	debug_colour_watch (DEBUG_COLOUR_MAGENTA, "current_co_pilot_virtual_cockpit_camera = %d", MT_INT, &current_co_pilot_virtual_cockpit_camera);

	#endif

	////////////////////////////////////////
	//
	// pilot
	//
	////////////////////////////////////////

	if (virtual_cockpit_inst3d)
	{
		num_pilot_virtual_cockpit_cameras = get_number_of_3d_object_cameras (virtual_cockpit_inst3d, OBJECT_3D_CAMERA_VIEW_STATIC_PILOT);
	}
	else
	{
		num_pilot_virtual_cockpit_cameras = 0;
	}

	if (num_pilot_virtual_cockpit_cameras > 0)
	{
		current_pilot_virtual_cockpit_camera = 0;

		pilot_crew_camera_index = OBJECT_3D_CAMERA_VIEW_STATIC_PILOT;
	}
	else
	{
		current_pilot_virtual_cockpit_camera = INVALID_VIRTUAL_COCKPIT_CAMERA;

		pilot_crew_camera_index = OBJECT_3D_INVALID_CAMERA_INDEX;
	}

	////////////////////////////////////////
	//
	// co-pilot
	//
	////////////////////////////////////////

	if (virtual_cockpit_inst3d)
	{
		num_co_pilot_virtual_cockpit_cameras = get_number_of_3d_object_cameras (virtual_cockpit_inst3d, OBJECT_3D_CAMERA_VIEW_STATIC_WSO);
	}
	else
	{
		num_co_pilot_virtual_cockpit_cameras = 0;
	}

	if (num_co_pilot_virtual_cockpit_cameras > 0)
	{
		current_co_pilot_virtual_cockpit_camera = 0;

		co_pilot_crew_camera_index = OBJECT_3D_CAMERA_VIEW_STATIC_WSO;
	}
	else
	{
		current_co_pilot_virtual_cockpit_camera = INVALID_VIRTUAL_COCKPIT_CAMERA;

		co_pilot_crew_camera_index = OBJECT_3D_INVALID_CAMERA_INDEX;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_virtual_cockpit_cameras (void)
{
	pilot_crew_camera_index = OBJECT_3D_INVALID_CAMERA_INDEX;

	num_pilot_virtual_cockpit_cameras = 0;

	current_pilot_virtual_cockpit_camera = INVALID_VIRTUAL_COCKPIT_CAMERA;

	co_pilot_crew_camera_index = OBJECT_3D_INVALID_CAMERA_INDEX;

	num_co_pilot_virtual_cockpit_cameras = 0;

	current_co_pilot_virtual_cockpit_camera = INVALID_VIRTUAL_COCKPIT_CAMERA;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_num_virtual_cockpit_cameras (crew_roles role)
{
	int
		num_virtual_cockpit_cameras;

	if (role == CREW_ROLE_PILOT)
	{
		num_virtual_cockpit_cameras = num_pilot_virtual_cockpit_cameras;
	}
	else
	{
		num_virtual_cockpit_cameras = num_co_pilot_virtual_cockpit_cameras;
	}

	return (num_virtual_cockpit_cameras);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_current_virtual_cockpit_camera (crew_roles role)
{
	int
		current_virtual_cockpit_camera;

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_EJECTED))
	{
		if (role == CREW_ROLE_PILOT)
		{
			ASSERT (get_number_of_3d_object_cameras (virtual_cockpit_inst3d, OBJECT_3D_CAMERA_VIEW_STATIC_PILOT_EJECT) > 0);

			current_virtual_cockpit_camera = 0;
		}
		else
		{
			ASSERT (get_number_of_3d_object_cameras (virtual_cockpit_inst3d, OBJECT_3D_CAMERA_VIEW_STATIC_WSO_EJECT) > 0);

			current_virtual_cockpit_camera = 0;
		}
	}
	else
	{
		if (role == CREW_ROLE_PILOT)
		{
			current_virtual_cockpit_camera = current_pilot_virtual_cockpit_camera;
		}
		else
		{
			current_virtual_cockpit_camera = current_co_pilot_virtual_cockpit_camera;
		}
	}

	return (current_virtual_cockpit_camera);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_current_virtual_cockpit_camera (crew_roles role)
{
	if (role == CREW_ROLE_PILOT)
	{
		if (num_pilot_virtual_cockpit_cameras > 0)
		{
			current_pilot_virtual_cockpit_camera++;

			current_pilot_virtual_cockpit_camera %= num_pilot_virtual_cockpit_cameras;
		}
	}
	else
	{
		if (num_co_pilot_virtual_cockpit_cameras > 0)
		{
			current_co_pilot_virtual_cockpit_camera++;

			current_co_pilot_virtual_cockpit_camera %= num_co_pilot_virtual_cockpit_cameras;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_camera_index_numbers get_crew_camera_index (crew_roles role)
{
	object_3d_camera_index_numbers
		crew_camera_index;

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_EJECTED))
	{
		if (role == CREW_ROLE_PILOT)
		{
			crew_camera_index = OBJECT_3D_CAMERA_VIEW_STATIC_PILOT_EJECT;
		}
		else
		{
			crew_camera_index = OBJECT_3D_CAMERA_VIEW_STATIC_WSO_EJECT;
		}
	}
	else
	{
		if (role == CREW_ROLE_PILOT)
		{
			crew_camera_index = OBJECT_3D_CAMERA_VIEW_STATIC_PILOT;
		}
		else
		{
			crew_camera_index = OBJECT_3D_CAMERA_VIEW_STATIC_WSO;
		}
	}

	return (crew_camera_index);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CREW SKINS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define BITMAP_ID		(0x4D42)

#define BI_RGB        0L
#define BI_RLE8       1L
#define BI_RLE4       2L
#define BI_BITFIELDS  3L

typedef unsigned short int WORD;

typedef unsigned int DWORD;

typedef long LONG;

#pragma	pack (2)

typedef struct tagBITMAPFILEHEADER {
        WORD    bfType;
        DWORD   bfSize;
        WORD    bfReserved1;
        WORD    bfReserved2;
        DWORD   bfOffBits;
} BITMAPFILEHEADER;

#pragma	pack (4)

typedef struct tagBITMAPINFOHEADER{
        DWORD      biSize;
        LONG       biWidth;
        LONG       biHeight;
        WORD       biPlanes;
        WORD       biBitCount;
        DWORD      biCompression;
        DWORD      biSizeImage;
        LONG       biXPelsPerMeter;
        LONG       biYPelsPerMeter;
        DWORD      biClrUsed;
        DWORD      biClrImportant;
} BITMAPINFOHEADER;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void load_skin_bitmap (char *filespec, screen *texture, int size)
{
	FILE
		*fp;

	BITMAPFILEHEADER
		bmfh;

	BITMAPINFOHEADER
		bmih;

	char
		*buffer,
		*p;

	int
		buffer_size,
		x,
		y;

	rgb_colour
		col;

	ASSERT (filespec);

	ASSERT (texture);

	fp = safe_fopen (filespec, "rb");

	//
	// file header
	//

	fread (&bmfh, sizeof (bmfh), 1, fp);

	if (bmfh.bfType != BITMAP_ID)
	{
		safe_fclose (fp);

		debug_fatal ("%s is not a BMP file!", filespec);
	}

	//
	// info header
	//

	fread (&bmih, sizeof (bmih), 1, fp);

	if (bmih.biCompression != BI_RGB)
	{
		safe_fclose (fp);

		debug_fatal ("%s is not uncompressed RGB!", filespec);
	}

	if (bmih.biBitCount != 24)
	{
		safe_fclose (fp);

		debug_fatal ("%s is not 24 bit!", filespec);
	}

	if (bmih.biWidth != size)
	{
		safe_fclose (fp);

		debug_fatal ("%s is not %d pixels wide", filespec, size);
	}

	if (bmih.biHeight != size)
	{
		safe_fclose (fp);

		debug_fatal ("%s is not %d pixels high", filespec, size);
	}

	//
	// texture
	//

	buffer_size = size * size * 3;

	buffer = safe_malloc (buffer_size);

	fread (buffer, buffer_size, 1, fp);

	set_active_screen (texture);

	if (lock_screen (texture))
	{
		p = buffer;

		for (y = size - 1; y >= 0; y--)
		{
			for (x = 0; x < size; x++)
			{
				col.b = *p++;
				col.g = *p++;
				col.r = *p++;
				col.a = 255;

				set_pixel (x, y, col);
			}
		}

		unlock_screen (texture);
	}

	set_active_screen (video_screen);

	safe_free (buffer);

	safe_fclose (fp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HIGH_DETAIL_FACE_SIZE		(128)
#define LOW_DETAIL_FACE_SIZE		(32)
#define NECK_SIZE						(32)
#define HANDS_SIZE					(8)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static screen
	*us_pilot_high_detail_face,
	*us_pilot_low_detail_face,
	*us_pilot_neck,
	*us_pilot_hands,
	*us_co_pilot_high_detail_face,
	*us_co_pilot_low_detail_face,
	*us_co_pilot_neck,
	*us_co_pilot_hands,
	*russian_pilot_high_detail_face,
	*russian_pilot_low_detail_face,
	*russian_pilot_neck,
	*russian_pilot_hands,
	*russian_co_pilot_high_detail_face,
	*russian_co_pilot_low_detail_face,
	*russian_co_pilot_neck,
	*russian_co_pilot_hands;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_crew_skins (void)
{
	//
	// create textures
	//

	us_pilot_high_detail_face = create_user_texture_screen (HIGH_DETAIL_FACE_SIZE, HIGH_DETAIL_FACE_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	us_pilot_low_detail_face = create_user_texture_screen (LOW_DETAIL_FACE_SIZE, LOW_DETAIL_FACE_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	us_pilot_neck = create_user_texture_screen (NECK_SIZE, NECK_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	us_pilot_hands = create_user_texture_screen (HANDS_SIZE, HANDS_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	us_co_pilot_high_detail_face = create_user_texture_screen (HIGH_DETAIL_FACE_SIZE, HIGH_DETAIL_FACE_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	us_co_pilot_low_detail_face = create_user_texture_screen (LOW_DETAIL_FACE_SIZE, LOW_DETAIL_FACE_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	us_co_pilot_neck = create_user_texture_screen (NECK_SIZE, NECK_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	us_co_pilot_hands = create_user_texture_screen (HANDS_SIZE, HANDS_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);

	russian_pilot_high_detail_face = create_user_texture_screen (HIGH_DETAIL_FACE_SIZE, HIGH_DETAIL_FACE_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	russian_pilot_low_detail_face = create_user_texture_screen (LOW_DETAIL_FACE_SIZE, LOW_DETAIL_FACE_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	russian_pilot_neck = create_user_texture_screen (NECK_SIZE, NECK_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	russian_pilot_hands = create_user_texture_screen (HANDS_SIZE, HANDS_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	russian_co_pilot_high_detail_face = create_user_texture_screen (HIGH_DETAIL_FACE_SIZE, HIGH_DETAIL_FACE_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	russian_co_pilot_low_detail_face = create_user_texture_screen (LOW_DETAIL_FACE_SIZE, LOW_DETAIL_FACE_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	russian_co_pilot_neck = create_user_texture_screen (NECK_SIZE, NECK_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);
	russian_co_pilot_hands = create_user_texture_screen (HANDS_SIZE, HANDS_SIZE, SCREEN_FORMAT_TYPE_NOALPHA_NOPALETTE, 0);

	//
	// set texture screens
	//

	set_system_texture_screen (us_pilot_high_detail_face, TEXTURE_INDEX_US_PILOT_FACE_01);
	set_system_texture_screen (us_pilot_low_detail_face, TEXTURE_INDEX_US_PILOT_FACE_01_LOW_RES);
	set_system_texture_screen (us_pilot_neck, TEXTURE_INDEX_US_PILOT_NECK_01);
	set_system_texture_screen (us_pilot_hands, TEXTURE_INDEX_US_PILOT_SKIN);
	set_system_texture_screen (us_co_pilot_high_detail_face, TEXTURE_INDEX_US_WSO_FACE_01);
	set_system_texture_screen (us_co_pilot_low_detail_face, TEXTURE_INDEX_US_WSO_FACE_01_LOW_RES);
	set_system_texture_screen (us_co_pilot_neck, TEXTURE_INDEX_US_WSO_NECK_01);
	set_system_texture_screen (us_co_pilot_hands, TEXTURE_INDEX_US_WSO_SKIN);

	set_system_texture_screen (russian_pilot_high_detail_face, TEXTURE_INDEX_RUSSIAN_PILOT_FACE_01);
	set_system_texture_screen (russian_pilot_low_detail_face, TEXTURE_INDEX_RUSSIAN_PILOT_FACE_LOW_RES);
	set_system_texture_screen (russian_pilot_neck, TEXTURE_INDEX_RUSSIAN_PILOT_NECK_01);
	set_system_texture_screen (russian_pilot_hands, TEXTURE_INDEX_RUSSIAN_PILOT_SKIN);
	set_system_texture_screen (russian_co_pilot_high_detail_face, TEXTURE_INDEX_RUSSIAN_WSO_FACE_01);
	set_system_texture_screen (russian_co_pilot_low_detail_face, TEXTURE_INDEX_RUSSIAN_WSO_FACE_LOW_RES);
	set_system_texture_screen (russian_co_pilot_neck, TEXTURE_INDEX_RUSSIAN_WSO_NECK_01);
	set_system_texture_screen (russian_co_pilot_hands, TEXTURE_INDEX_RUSSIAN_WSO_SKIN);

	//
	// load BMPs
	//

	load_skin_bitmap ("GRAPHICS\\SKINS\\USA\\PILOT\\HI_FACE.BMP", us_pilot_high_detail_face, HIGH_DETAIL_FACE_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\USA\\PILOT\\LOW_FACE.BMP", us_pilot_low_detail_face, LOW_DETAIL_FACE_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\USA\\PILOT\\NECK.BMP", us_pilot_neck, NECK_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\USA\\PILOT\\HANDS.BMP", us_pilot_hands, HANDS_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\USA\\CPG\\HI_FACE.BMP", us_co_pilot_high_detail_face, HIGH_DETAIL_FACE_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\USA\\CPG\\LOW_FACE.BMP", us_co_pilot_low_detail_face, LOW_DETAIL_FACE_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\USA\\CPG\\NECK.BMP", us_co_pilot_neck, NECK_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\USA\\CPG\\HANDS.BMP", us_co_pilot_hands, HANDS_SIZE);

	load_skin_bitmap ("GRAPHICS\\SKINS\\RUSSIAN\\PILOT\\HI_FACE.BMP", russian_pilot_high_detail_face, HIGH_DETAIL_FACE_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\RUSSIAN\\PILOT\\LOW_FACE.BMP", russian_pilot_low_detail_face, LOW_DETAIL_FACE_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\RUSSIAN\\PILOT\\NECK.BMP", russian_pilot_neck, NECK_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\RUSSIAN\\PILOT\\HANDS.BMP", russian_pilot_hands, HANDS_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\RUSSIAN\\CPG\\HI_FACE.BMP", russian_co_pilot_high_detail_face, HIGH_DETAIL_FACE_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\RUSSIAN\\CPG\\LOW_FACE.BMP", russian_co_pilot_low_detail_face, LOW_DETAIL_FACE_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\RUSSIAN\\CPG\\NECK.BMP", russian_co_pilot_neck, NECK_SIZE);
	load_skin_bitmap ("GRAPHICS\\SKINS\\RUSSIAN\\CPG\\HANDS.BMP", russian_co_pilot_hands, HANDS_SIZE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_crew_skins (void)
{
	destroy_screen (us_pilot_high_detail_face);
	destroy_screen (us_pilot_low_detail_face);
	destroy_screen (us_pilot_neck);
	destroy_screen (us_pilot_hands);
	destroy_screen (us_co_pilot_high_detail_face);
	destroy_screen (us_co_pilot_low_detail_face);
	destroy_screen (us_co_pilot_neck);
	destroy_screen (us_co_pilot_hands);

	destroy_screen (russian_pilot_high_detail_face);
	destroy_screen (russian_pilot_low_detail_face);
	destroy_screen (russian_pilot_neck);
	destroy_screen (russian_pilot_hands);
	destroy_screen (russian_co_pilot_high_detail_face);
	destroy_screen (russian_co_pilot_low_detail_face);
	destroy_screen (russian_co_pilot_neck);
	destroy_screen (russian_co_pilot_hands);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
