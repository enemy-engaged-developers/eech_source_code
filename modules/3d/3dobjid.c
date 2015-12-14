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

#include	"3d.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_information
	*object_3d_information_database = NULL;

char
	**object_3d_enumeration_names = NULL,
	**object_3d_sub_object_names = NULL,
	**object_3d_camoflage_set_names = NULL,
	**object_3d_camera_names = NULL,
	**texture_animation_names = NULL,
	**displacement_animation_names = NULL;

texture_animation_information
	*texture_animations = NULL,
	*displacement_animations = NULL;


int
	object_3d_number_of_scene_names = 0,
	object_3d_number_of_sub_object_names = 0,
	object_3d_number_of_camoflage_set_names = 0,
	object_3d_number_of_camera_names = 0,
	number_of_texture_animations = 0,
	number_of_displacement_animations = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// JB 030311 Enable running out of separate directories
extern char comanche_hokum_installation_path[];

#define TEXTURE_ANIMATION_DECLARATION(x)
#define TEXTURE_ANIMATION_INDEX(x) #x,
#define TEXTURE_ANIMATION_INDEX_(x) NULL
const char* texture_animation_names_[] = {
#include "textanim.h"
};
#undef TEXTURE_ANIMATION_DECLARATION
#undef TEXTURE_ANIMATION_INDEX
#undef TEXTURE_ANIMATION_INDEX_

void initialise_3d_objects_info ( const char *directory )
{

	int
		length,
		count;

	FILE
		*fp;

	char
		filename[1024];

	char
		*ptr;

	sprintf ( filename, "%s\\bininfo.bin", directory );

	fp = fopen ( filename, "rb" );

	// JB 030311 Enable running out of separate directories
	if (!fp)
	{
		char fn[1024];
		fn[0] = 0;
		strcpy(fn, comanche_hokum_installation_path);
		strcat(fn, "\\cohokum\\");
		strcat(fn, filename);

		fp = fopen ( fn, "rb" );
	}

	ASSERT ( fp );

	ptr = NULL;

	//
	// Read in scene names
	//

	fread ( &object_3d_number_of_scene_names, sizeof ( int ), 1, fp );

	ASSERT ( object_3d_number_of_scene_names == OBJECT_3D_OLD_LAST );

	if ( object_3d_number_of_scene_names )
	{
		const char
			* const object_invalid_index = "OBJECT_INVALID_INDEX";

		fread ( &length, sizeof ( int ), 1, fp );

		length += strlen ( object_invalid_index ) + 1;

		ptr = ( char * ) safe_malloc ( length * sizeof ( char ) );

		object_3d_information_database = ( object_3d_information * ) safe_malloc ( OBJECT_3D_LAST * sizeof ( object_3d_information ) );
		object_3d_enumeration_names = ( char * * ) safe_malloc ( OBJECT_3D_LAST * sizeof ( char * ) );

		object_3d_enumeration_names[0] = ptr;
		object_3d_information_database[0].name = ptr;

		strcpy ( ptr, object_invalid_index );
		ptr += strlen ( ptr ) + 1;

		for ( count = 1; count < object_3d_number_of_scene_names; count++ )
		{

			fread ( &length, sizeof ( int ), 1, fp );

			object_3d_enumeration_names[count] = ptr;

			object_3d_information_database[count].name = ptr;

			fread ( ptr, length, 1, fp );

			ASSERT ( !strcmp ( object_3d_enumeration_names[count], object_3d_scene_names[count] ) );

			fread ( &object_3d_information_database[count].maximum_distance, sizeof ( float ), 1, fp );

			ptr += length;
		}

		for ( ; count < OBJECT_3D_LAST; count++ )
		{
			object_3d_enumeration_names[count] = ( char * ) object_3d_scene_names[count];
			object_3d_information_database[count].name = ( char * ) object_3d_scene_names[count];
			object_3d_information_database[count].maximum_distance = 4000.0;
		}

		object_3d_number_of_scene_names = OBJECT_3D_LAST;

		ptr = NULL;
	}

	//
	// Read in sub object names
	//

	fread ( &object_3d_number_of_sub_object_names, sizeof ( int ), 1, fp );

	ASSERT ( object_3d_number_of_sub_object_names == OBJECT_3D_SUB_OBJECT_OLD_LAST );

	if ( object_3d_number_of_sub_object_names )
	{

		object_3d_sub_object_names = ( char * * ) safe_malloc ( OBJECT_3D_SUB_OBJECT_LAST * sizeof ( char * ) );

		fread ( &length, sizeof ( int ), 1, fp );

		length += strlen ( "INVALID_SUB_OBJECT_INDEX" ) + 1;

		ptr = ( char * ) safe_malloc ( length * sizeof ( char ) );

		object_3d_sub_object_names[0] = ptr;

		sprintf ( ptr, "INVALID_SUB_OBJECT_INDEX" );

		ptr += strlen ( "INVALID_SUB_OBJECT_INDEX" ) + 1;

		for ( count = 1; count < object_3d_number_of_sub_object_names; count++ )
		{

			fread ( &length, sizeof ( int ), 1, fp );

			object_3d_sub_object_names[count] = ptr;

			fread ( ptr, length, 1, fp );

			ASSERT ( !strcmp ( object_3d_sub_object_names[count], object_3d_subobject_names[count] ) );

			ptr += length;
		}

		for ( ; count < OBJECT_3D_SUB_OBJECT_LAST; count++ )
		{
			object_3d_sub_object_names[count] = ( char * ) object_3d_subobject_names[count];
		}

		object_3d_number_of_sub_object_names = OBJECT_3D_SUB_OBJECT_LAST;

		ptr = NULL;
	}

	//
	// Read in camera names
	//

	fread ( &object_3d_number_of_camera_names, sizeof ( int ), 1, fp );

	if ( object_3d_number_of_camera_names )
	{

		object_3d_camera_names = ( char * * ) safe_malloc ( object_3d_number_of_camera_names * sizeof ( char * ) );

		fread ( &length, sizeof ( int ), 1, fp );

		length += strlen ( "INVALID_CAMERA_INDEX" ) + 1;

		ptr = ( char * ) safe_malloc ( length * sizeof ( char ) );

		object_3d_camera_names[0] = ptr;

		sprintf ( ptr, "INVALID_CAMERA_INDEX" );

		ptr += strlen ( "INVALID_CAMERA_INDEX" ) + 1;

		for ( count = 1; count < object_3d_number_of_camera_names; count++ )
		{

			fread ( &length, sizeof ( int ), 1, fp );

			object_3d_camera_names[count] = ptr;

			fread ( ptr, length, 1, fp );

			ptr += length;
		}

		ptr = NULL;
	}

	//
	// Read in camoflage texture sets
	//

	fread ( &object_3d_number_of_camoflage_set_names, sizeof ( int ), 1, fp );

	if ( object_3d_number_of_camoflage_set_names )
	{

		object_3d_camoflage_set_names = ( char * * ) safe_malloc ( object_3d_number_of_camoflage_set_names * sizeof ( char * ) );

		fread ( &length, sizeof ( int ), 1, fp );

		ptr = ( char * ) safe_malloc ( length * sizeof ( char ) );

		for ( count = 0; count < object_3d_number_of_camoflage_set_names; count++ )
		{

			fread ( &length, sizeof ( int ), 1, fp );

			object_3d_camoflage_set_names[count] = ptr;

			fread ( ptr, length, 1, fp );

			ptr += length;
		}

		ptr = NULL;
	}

	//
	// Read in the texture animation names
	//

	fread ( &number_of_texture_animations, sizeof ( int ), 1, fp );

	ASSERT ( number_of_texture_animations == TEXTURE_ANIMATION_INDEX_OLD_LAST );

	if ( number_of_texture_animations )
	{

		texture_animations = ( texture_animation_information * ) safe_malloc ( sizeof ( texture_animation_information ) * TEXTURE_ANIMATION_INDEX_LAST );

		texture_animation_names = ( char * * ) safe_malloc ( sizeof ( char * ) * TEXTURE_ANIMATION_INDEX_LAST );

		fread ( &length, sizeof ( int ), 1, fp );

		ptr = ( char * ) safe_malloc ( length * sizeof ( char ) );

		for ( count = 0; count < number_of_texture_animations; count++ )
		{

			int
				temp,
				number_of_frames;

			texture_animation_names[count] = ptr;

			fread ( &length, sizeof ( int ), 1, fp );

			fread ( ptr, length, 1, fp );

			ASSERT ( !strcmp ( texture_animation_names[count], texture_animation_names_[count] ) );

			ptr += length;

			fread ( &number_of_frames, sizeof ( int ), 1, fp );

			texture_animations[count].number_of_frames = number_of_frames;
			texture_animations[count].current_frame = 0;
			texture_animations[count].texture_indices = ( int * ) safe_malloc ( sizeof ( int ) * number_of_frames );

			for ( temp = 0; temp < number_of_frames; temp++ )
			{

				fread ( &texture_animations[count].texture_indices[temp], sizeof ( int ), 1, fp );
			}
		}

		for ( ; count < TEXTURE_ANIMATION_INDEX_KNOWN_LAST; count++ )
		{
			length = strlen ( texture_animation_names_[count] ) + 1;

			ptr = ( char * ) safe_malloc ( length * sizeof ( char ) );

			memcpy ( ptr, texture_animation_names_[count], length );

			texture_animation_names[count] = ptr;

			texture_animations[count].number_of_frames = 0;
			texture_animations[count].current_frame = 0;
			texture_animations[count].texture_indices = NULL;
		}

		for ( ; count < TEXTURE_ANIMATION_INDEX_LAST; count++ )
		{
			texture_animation_names[count] = NULL;

			texture_animations[count].number_of_frames = 0;
			texture_animations[count].current_frame = 0;
			texture_animations[count].texture_indices = NULL;
		}

		ptr = NULL;
	}

	number_of_texture_animations = TEXTURE_ANIMATION_INDEX_KNOWN_LAST;

	//
	// Read in the displacement animations
	//

	fread ( &number_of_displacement_animations, sizeof ( int ), 1, fp );

	if ( number_of_displacement_animations )
	{

		displacement_animations = ( texture_animation_information * ) safe_malloc ( sizeof ( texture_animation_information ) * number_of_displacement_animations );

		displacement_animation_names = ( char * * ) safe_malloc ( sizeof ( char * ) * number_of_displacement_animations );

		fread ( &length, sizeof ( int ), 1, fp );

		ptr = ( char * ) safe_malloc ( length * sizeof ( char ) );

		for ( count = 0; count < number_of_displacement_animations; count++ )
		{

			int
				temp,
				number_of_frames;

			fread ( &length, sizeof ( int ), 1, fp );

			displacement_animation_names[count] = ptr;

			fread ( ptr, length, 1, fp );

			fread ( &number_of_frames, sizeof ( int ), 1, fp );

			displacement_animations[count].number_of_frames = number_of_frames;
			displacement_animations[count].current_frame = 0;
			displacement_animations[count].texture_indices = ( int * ) safe_malloc ( sizeof ( int ) * number_of_frames );

			for ( temp = 0; temp < number_of_frames; temp++ )
			{

				fread ( &displacement_animations[count].texture_indices[temp], sizeof ( int ), 1, fp );
			}
		}
	}

	fclose ( fp );

	// 12NOV10 Casm Loading custom textures animation BEGIN
	{
		int
			rc;
		long
			handle;
		struct _finddata_t
			fi;

		sprintf ( filename, "%s\\..\\GRAPHICS\\TEXTURES\\ANIMATION\\*.TXT", directory );
		for ( rc = handle = _findfirst ( filename, &fi ); rc != -1; rc = _findnext ( handle, &fi ) )
		{
			int
				texture_animation_index;

			if ( fi.attrib & _A_SUBDIR )
				continue;

			fi.name[strlen(fi.name) - 4] = '\0';
			strupr ( fi.name );

			texture_animation_index = get_object_3d_texture_animation_index_from_name ( fi.name );
			if ( texture_animation_index < 0 )
			{
				size_t
					length;
				char
					*ptr;

				ASSERT ( number_of_texture_animations < TEXTURE_ANIMATION_INDEX_LAST );
				texture_animation_index = number_of_texture_animations++;
				length = strlen ( fi.name ) + 1;
				ptr = ( char * ) safe_malloc ( length );
				memcpy ( ptr, fi.name, length );
				texture_animation_names[texture_animation_index] = ptr;
			}

			sprintf ( filename, "%s\\..\\GRAPHICS\\TEXTURES\\ANIMATION\\%s.TXT", directory, fi.name );

			{
				FILE*
					file;
				texture_animation_information
					texture_animation;
				char
					line[1024];

				texture_animation.number_of_frames = texture_animation.current_frame = 0;
				texture_animation.texture_indices = NULL;
				file = safe_fopen ( filename, "r" );
				while ( fgets ( line, sizeof ( line ), file ) && *line )
				{
					char
						*last;
					last = line + strlen ( line ) - 1;
					if ( *last == '\n' )
						*last = '\0';
					if ( !*line )
						break;
					if ( texture_animation.number_of_frames == texture_animation.current_frame )
					{
						int
							*new_texture_indices;

						texture_animation.current_frame = texture_animation.current_frame ? texture_animation.current_frame * 2 : 8;
						new_texture_indices = ( int * ) safe_malloc ( texture_animation.current_frame * sizeof ( int ) );
						if ( texture_animation.texture_indices )
						{
							memcpy ( new_texture_indices, texture_animation.texture_indices, texture_animation.number_of_frames * sizeof ( int ) );
							safe_free ( texture_animation.texture_indices );
						}
						texture_animation.texture_indices = new_texture_indices;
					}
					texture_animation.texture_indices[texture_animation.number_of_frames++] = add_new_texture ( line, filename );
				}
				safe_fclose ( file );

				texture_animation.current_frame = 0;
				if ( texture_animations[texture_animation_index].texture_indices )
				{
					safe_free ( texture_animations[texture_animation_index].texture_indices );
				}
				texture_animations[texture_animation_index] = texture_animation;
			}
		}
		_findclose ( handle );
	}
	// 12NOV10 Casm Loading custom textures animation END
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_3d_objects_info ( void )
{
	int
		count;

	if ( displacement_animation_names )
	{
		if ( displacement_animation_names[0] )
		{
			safe_free ( displacement_animation_names[0] );
		}
		safe_free ( displacement_animation_names );
	}

	if ( displacement_animations )
	{
		for ( count = 0; count < number_of_displacement_animations; count++ )
		{
			if ( displacement_animations[count].texture_indices )
			{
				safe_free ( displacement_animations[count].texture_indices );
			}
		}
		safe_free ( displacement_animations );
	}

	if ( texture_animation_names )
	{
		if ( texture_animation_names[0] )
		{
			safe_free ( texture_animation_names[0] );
		}
		for ( count = TEXTURE_ANIMATION_INDEX_OLD_LAST; count < TEXTURE_ANIMATION_INDEX_LAST; count++ )
		{
			if ( texture_animation_names[count] )
			{
				safe_free ( texture_animation_names[count] );
			}
		}
		safe_free ( texture_animation_names );
	}

	if ( texture_animations )
	{
		for ( count = 0; count < number_of_texture_animations; count++ )
		{
			if ( texture_animations[count].texture_indices )
			{
				safe_free ( texture_animations[count].texture_indices );
			}
		}
		safe_free ( texture_animations );
	}

	if ( object_3d_camoflage_set_names )
	{
		if ( object_3d_camoflage_set_names[0] )
		{
			safe_free ( object_3d_camoflage_set_names[0] );
		}
		safe_free ( object_3d_camoflage_set_names );
	}

	if ( object_3d_camera_names )
	{
		if ( object_3d_camera_names[0] )
		{
			safe_free ( object_3d_camera_names[0] );
		}
		safe_free ( object_3d_camera_names );
	}

	if ( object_3d_sub_object_names )
	{
		if ( object_3d_sub_object_names[0] )
		{
			safe_free ( object_3d_sub_object_names[0] );
		}
		safe_free ( object_3d_sub_object_names );
	}

	if ( object_3d_enumeration_names )
	{
		if ( object_3d_enumeration_names[0] )
		{
			safe_free ( object_3d_enumeration_names[0] );
		}
		safe_free ( object_3d_enumeration_names );
	}

	if ( object_3d_information_database )
	{
		safe_free ( object_3d_information_database );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_index_from_name ( char *name )
{

	int
		count;

	for ( count = 1; count < object_3d_number_of_scene_names; count++ )
	{

		if ( stricmp ( name, object_3d_enumeration_names[count] ) == 0 )
		{

			return ( count );
		}
	}

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_sub_index_from_name ( char *name )
{

	int
		count;

	for ( count = 1; count < object_3d_number_of_sub_object_names; count++ )
	{

		if ( stricmp ( name, object_3d_sub_object_names[count] ) == 0 )
		{

			return ( count );
		}
	}

	return ( 0 );
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_camoflage_index_from_name ( char *name )
{

	int
		count;

	for ( count = 0; count < object_3d_number_of_camoflage_set_names; count++ )
	{

		if ( stricmp ( name, object_3d_camoflage_set_names[count] ) == 0 )
		{

			return ( count );
		}
	}

	return ( -1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_camera_index_from_name ( char *name )
{

	int
		count;

	for ( count = 1; count < object_3d_number_of_camera_names; count++ )
	{

		if ( stricmp ( name, object_3d_camera_names [count] ) == 0 )
		{

			return ( count );
		}
	}

	return ( 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_texture_animation_index_from_name ( char *name )
{

	int
		count;

	for ( count = 0; count < number_of_texture_animations; count++ )
	{

		if ( stricmp ( name, texture_animation_names[count] ) == 0 )
		{

			return ( count );
		}
	}

	return ( -1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_displacement_animation_index_from_name ( char *name )
{

	int
		count;

	for ( count = 0; count < number_of_displacement_animations; count++ )
	{

		if ( stricmp ( name, displacement_animation_names[count] ) == 0 )
		{

			return ( count );
		}
	}

	return ( -1 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_instance *construct_3d_object_by_name ( char *name )
{

	int
		index;

	index = get_object_3d_index_from_name ( name );

	if ( index )
	{

		return ( construct_3d_object ( index ) );
	}
	else
	{

		debug_fatal ( "Unable to construct object: %s", name );

		return ( NULL );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_object_3d_texture_camoflage_by_name ( char *name )
{

	int
		index;

	index = get_object_3d_camoflage_index_from_name ( name );

	if ( index != -1 )
	{

		set_texture_camoflage ( index );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Casm 24JAN09 Adding textures animation loading for objects
int add_new_animation(char* animation_name)
{
	int
		texture_animation;

	texture_animation = get_object_3d_texture_animation_index_from_name ( animation_name );
	if ( texture_animation < 0 )
	{
		debug_fatal ( "FAILED to find texture animation '%s'", animation_name );
	}

	return texture_animation;
}
