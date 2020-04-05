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


/*
#if 0
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum
{
	GRAPHICS_FILE_DIRECTORY,

	NUM_TRANSLATION_ITEMS
};
/*
static game_text_translation_type
	text_translation_list [] =
	{
		{ GRAPHICS_FILE_DIRECTORY,
			{
				{ LANGUAGE_ENGLISH,	"", 0, 0, 0, 0 },
				{ LANGUAGE_GERMAN,	"german\\", 0, 0, 0, 0 },
				{ LANGUAGE_FRENCH,	"french\\", 0, 0, 0, 0 },
				{ LANGUAGE_ITALIAN,	"italian\\", 0, 0, 0, 0 },
				{ LANGUAGE_SPANISH,	"spanish\\", 0, 0, 0, 0 },
			}
		}
	};
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const char
	*distribution_path_names[] =
	{
		"\\COHOKUM\\GRAPHICS\\COCKPITS\\",
#if 0
		"\\COHOKUM\\GRAPHICS\\COCKPITS\\APACHE\\LEVEL1\\",
		"\\COHOKUM\\GRAPHICS\\COCKPITS\\APACHE\\LEVEL2\\",
		"\\COHOKUM\\GRAPHICS\\COCKPITS\\APACHE\\LEVEL3\\",
		"\\COHOKUM\\GRAPHICS\\COCKPITS\\HAVOC\\LEVEL1\\",
		"\\COHOKUM\\GRAPHICS\\COCKPITS\\HAVOC\\LEVEL2\\",
		"\\COHOKUM\\GRAPHICS\\COCKPITS\\HAVOC\\LEVEL3\\",
		"\\COHOKUM\\GRAPHICS\\UI\\APACHE\\",
#endif
		"\\COHOKUM\\GRAPHICS\\UI\\COMMON\\",
#if 0
		"\\COHOKUM\\GRAPHICS\\UI\\HAVOC\\",
#endif
		"\\COMMON\\MAPS\\MAP1\\GRAPHICS\\",
		"\\COMMON\\MAPS\\MAP2\\GRAPHICS\\",
		"\\COMMON\\MAPS\\MAP3\\GRAPHICS\\",
		"\\COMMON\\MAPS\\MAP4\\GRAPHICS\\",
	};

static const char
	*installation_path_names[] =
	{
		"GRAPHICS\\COCKPITS\\",
#if 0
		"GRAPHICS\\COCKPITS\\APACHE\\LEVEL1\\",
		"GRAPHICS\\COCKPITS\\APACHE\\LEVEL2\\",
		"GRAPHICS\\COCKPITS\\APACHE\\LEVEL3\\",
		"GRAPHICS\\COCKPITS\\HAVOC\\LEVEL1\\",
		"GRAPHICS\\COCKPITS\\HAVOC\\LEVEL2\\",
		"GRAPHICS\\COCKPITS\\HAVOC\\LEVEL3\\",
		"GRAPHICS\\UI\\APACHE\\",
#endif
		"GRAPHICS\\UI\\COMMON\\",
#if 0
		"GRAPHICS\\UI\\HAVOC\\",
#endif
		"..\\COMMON\\MAPS\\MAP1\\GRAPHICS\\",
		"..\\COMMON\\MAPS\\MAP2\\GRAPHICS\\",
		"..\\COMMON\\MAPS\\MAP3\\GRAPHICS\\",
		"..\\COMMON\\MAPS\\MAP4\\GRAPHICS\\",
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

file_data
	graphics_files[] =
	{
		////////////////////////////////////////
		//
		// IMPORTANT! ORDER MUST MATCH GRAPHICS_FILE_SPECIFIERS (GFXFILES.H)
		//
		////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// FIRST PASS CONVERSIONS
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
		////////////////////////////////////////
		//
		// INIT SCREEN
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_APACHE,														// path_name
			"INIT",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"INIT",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
#endif

		////////////////////////////////////////
		//
		// UI\COMMON
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"POINTER",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB,                                         // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			TRUE,                                                       // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL22W",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIA22BK",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIA22DG",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL22B",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL22G",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL22O",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL22R",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL22Y",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL15W",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL15B",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL15R",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL15Y",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIA15GY",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL15O",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL15G",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL11W",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIA11BK",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIA11DG",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL11B",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL11G",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIA11GY",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL11O",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL11R",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL11Y",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIA11BK",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS11W",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS11Y",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS11GY",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS11B",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS11O",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS15W",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS15Y",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS15B",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS15O",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS22W",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS22Y",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS22B",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ADS22O",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"MONO7",                                                    // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL8W",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"ARIAL8Y",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// SECOND PASS CONVERSIONS
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//
		// COCKPITS
		//
		////////////////////////////////////////
		{
			GRAPHICS_COCKPITS,                                          // path_name
			"LOGO",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

#if 0
		////////////////////////////////////////
		//
		// COCKPITS\APACHE\LEVEL1
		//
		////////////////////////////////////////
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U40_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U40_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U40_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U40_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U40_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U40_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U40_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"U20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"LVL_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"LVL_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"LVL_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"LVL_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"LVL_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"LVL_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"LVL_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"D20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"D20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"D20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"D20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"D20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"D20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"D20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"LHS_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"RHS_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"MD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"MD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"MD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"MLHS_MFD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"MRHS_MFD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WU20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WU20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WLVL_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WLVL_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WLVL_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WPN_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL1,                            // path_name
			"WPN_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// COCKPITS\APACHE\LEVEL2
		//
		////////////////////////////////////////
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U40_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U40_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U40_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U40_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U40_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U40_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U40_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"U20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"LVL_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"LVL_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"LVL_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"LVL_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"LVL_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"LVL_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"LVL_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"D20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"D20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"D20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"D20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"D20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"D20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"D20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"LHS_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"RHS_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"MD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"MD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"MD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"MLHS_MFD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"MRHS_MFD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WU20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WU20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WLVL_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WLVL_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WLVL_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WPN_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL2,                            // path_name
			"WPN_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// COCKPITS\APACHE\LEVEL3
		//
		////////////////////////////////////////
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U40_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U40_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U40_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U40_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U40_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U40_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U40_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"U20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"LVL_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"LVL_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"LVL_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"LVL_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"LVL_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"LVL_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"LVL_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"D20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"D20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"D20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"D20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"D20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"D20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"D20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"LHS_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"RHS_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"MD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"MD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"MD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"MLHS_MFD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"MRHS_MFD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WU20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WU20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WLVL_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WLVL_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WLVL_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WPN_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_APACHE_LEVEL3,                            // path_name
			"WPN_MFD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// COCKPITS\HAVOC\LEVEL1
		//
		////////////////////////////////////////
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U40_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U40_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U40_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U40_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U40_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U40_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U40_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"U20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"LVL_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"LVL_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"LVL_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"LVL_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"LVL_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"LVL_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"LVL_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"D20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"D20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"D20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"D20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"D20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"D20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"D20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"CRT",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"HUD",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"MD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"MCRT",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WU40_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WU40_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WU20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WU20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WLVL_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WLVL_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WLVL_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"WHUD",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL1,                             // path_name
			"TWD",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			TRUE,                                                       // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// COCKPITS\HAVOC\LEVEL2
		//
		////////////////////////////////////////
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U40_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U40_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U40_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U40_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U40_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U40_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U40_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"U20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"LVL_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"LVL_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"LVL_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"LVL_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"LVL_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"LVL_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"LVL_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"D20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"D20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"D20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"D20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"D20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"D20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"D20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"CRT",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"HUD",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"MD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"MCRT",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WU40_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WU40_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WU20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WU20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WLVL_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WLVL_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WLVL_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"WHUD",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL2,                             // path_name
			"TWD",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			TRUE,                                                       // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// COCKPITS\HAVOC\LEVEL3
		//
		////////////////////////////////////////
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U40_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U40_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U40_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U40_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U40_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U40_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U40_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"U20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"LVL_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"LVL_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"LVL_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"LVL_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"LVL_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"LVL_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"LVL_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"D20_L90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"D20_L60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"D20_L30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"D20_AHD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"D20_R30",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"D20_R60",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"D20_R90",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"CRT",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"HUD",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"MD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"MCRT",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WU40_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WU40_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WU20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WU20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WLVL_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WLVL_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WLVL_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WD20_L30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WD20_AHD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WD20_R30",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"WHUD",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RLE",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RLE,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"SPRITES",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"MSK",                                                      // installation_extension
			CONVERT_PSD_TO_ALPHA_MASK,                                  // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_COCKPITS_HAVOC_LEVEL3,                             // path_name
			"TWD",                                                      // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			TRUE,                                                       // required_for_apache_havoc_cockpits
			TRUE,                                                       // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// UI\APACHE
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"CZONE",                                                    // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"EXIT",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"GAMEOP",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"LOADING",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"MAIN",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"MULTI",                                                    // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAYER",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"TITLE",                                                    // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_FIRST_PASS,                             // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"CAMPOVER",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"GUNSHIP",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"DEMO",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// MAIN SCREEN BUTTONS
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"MAINPLAY",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"MAINMULT",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"MAINOPTI",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"MAINCOMB",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"MAINEXIT",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"MAINDEMO",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// GAME OPTIONS SCREEN BUTTONS
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// COMBAT ZONE SCREEN BUTTONS
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"CZONE_N",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"CZONE_B",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// COMBAT MISSIONS SCREEN BUTTONS
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"COMBAT_B",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"COMBAT_N",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"COMBAT_M",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// GUNSHIPS SCREEN BUTTONS
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"GUNSHP_A",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"GUNSHP_H",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"GUNSHPAU",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"GUNSHPHU",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"GUNSHPBX",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// PLANNER SCREEN BUTTONS
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_BU",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_BS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_FU",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_FS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_ZIU",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_ZIS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_ZOU",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_ZOS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_GU",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_GS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_VU",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"PLAN_VS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// FARP SCREENS
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"AIRBASE",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"FARP",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"SHIP",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_APACHE,                                         // path_name
			"DYN_MIS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// UI\HAVOC
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"CZONE",                                                    // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"GAMEOP",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"LOADING",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"MAIN",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"TITLE",                                                    // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"CAMPOVER",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// MAIN SCREEN BUTTONS
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// GAME OPTIONS SCREEN BUTTONS
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// COMBAT ZONE SCREEN BUTTONS
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// COMBAT MISSIONS SCREEN BUTTONS
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// GUNSHIPS SCREEN BUTTONS
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// PLANNER SCREEN BUTTONS
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"AIRBASE",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"FARP",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"SHIP",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_HAVOC,                                          // path_name
			"DYN_MIS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
#endif

		////////////////////////////////////////
		//
		// UI\COMMON
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UA_BRIEF",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UA_BAL",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UA_GSHIP",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UA_TASKS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UA_VLINE",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"AIRPORT",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB_ALPHA,                          // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,														// path_name
			"AVAILS",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"AVAILG",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"AVAILGD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,														// path_name
			"US_AAA",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_APC",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_ARTL",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_BLD",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_HELI",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_FARP",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_FIXW",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_FMIS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_JET",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_LNDF",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_LNDR",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_LNDS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_PMIS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_RMIS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_RWAY",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_SAM",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_SHIP",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_SMIS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_SML4",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_SML8",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_TANK",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_TRCK",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_USER",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_WPNV",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_WPTG",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_WPAD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_WPNS",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_GFRP",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_GRWY",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_GSHP",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"US_MULT",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,														// path_name
			"CIS_AAA",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_APC",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_ARTL",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_BLD",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_HELI",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_FARP",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_FIXW",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_FMIS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_JET",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_LNDF",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_LNDR",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_LNDS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_PMIS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_RMIS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_RWAY",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_SAM",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_SHIP",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_SMIS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_SML4",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_SML8",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_TANK",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_TRCK",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_USER",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_WPNV",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_WPTG",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_WPAD",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_WPNS",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_GFRP",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_GRWY",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_GFRP",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"CIS_MULT",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,														// path_name
			"UP_ARR_U",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UP_ARR_S",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"DW_ARR_U",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"DW_ARR_S",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,														// path_name
			"UA_MPBAR",                                                 // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UA_V",                                                     // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UA_DTOP",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"UA_DLOW",                                                  // file_name
			"PSD",                                                      // distribution_extension
			"RGA",                                                      // installation_extension
			CONVERT_PSD_TO_RGB_ALPHA,                                   // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			TRUE,                                                       // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,                                                      // required_for_apache_havoc_cockpits_patched_versions
		},

		////////////////////////////////////////
		//
		// AITOOL GRAPHICS
		//
		////////////////////////////////////////
		{
			GRAPHICS_UI_COMMON,                                         // path_name
			"AITOOL",                                                   // file_name
			"PSD",                                                      // distribution_extension
			"RGB",                                                      // installation_extension
			CONVERT_PSD_TO_DITHERED_RGB,                                // graphics_conversion_type
			NULL,                                                       // data
			GRAPHICS_CONVERSION_SECOND_PASS,                            // first_pass_conversion
			FALSE,                                                      // required_for_demo
			FALSE,                                                      // required_for_comanche_hokum
			FALSE,                                                      // required_for_apache_havoc_cockpits
			FALSE,																		// required_for_apache_havoc_cockpits_patched_versions
		},
	};

#define NUM_FILES (sizeof (graphics_files) / sizeof (graphics_files[0]))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*static char *get_language_specific_distribution_file_specifier (char *file_specifier, file_data *file);

static char *get_language_specific_local_distribution_file_specifier (char *file_specifier, file_data *file);*/

static char *get_distribution_file_specifier (char *file_specifier, file_data *file);

static char *get_local_distribution_file_specifier (char *file_specifier, file_data *file);

static char *get_installation_file_specifier (char *file_specifier, file_data *file);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_file_required (int index)
{
	if (!graphics_files[index].required_for_comanche_hokum)
	{
		return (FALSE);
	}

	if (DEMO_VERSION)
	{
		return (graphics_files[index].required_for_demo);
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_uninstalled_graphics_file_count (int pass_conversion)
{
	char
		installation_file[200];

	int
		count,
		i;

	count = 0;

	for (i = 0; i < NUM_FILES; i++)
	{
		if (get_file_required (i))
		{
			if (graphics_files[i].first_pass_conversion == pass_conversion)
			{
				get_installation_file_specifier (installation_file, &graphics_files[i]);

				if (!file_exist (installation_file))
				{
					count ++;
				}
			}
		}
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int install_graphics_files (int pass_conversion)
{
	char
		distribution_file[200],
		installation_file[200];

	int
		all_files_converted,
		i;

	all_files_converted = TRUE;

	debug_log ("Installing graphics files on pass %d...", pass_conversion + 1);

	for (i = 0; i < NUM_FILES; i++)
	{
		if (get_file_required (i))
		{
			if (graphics_files[i].first_pass_conversion == pass_conversion)
			{
				get_installation_file_specifier (installation_file, &graphics_files[i]);

				if (!file_exist (installation_file))
				{
					all_files_converted = FALSE;

					get_local_distribution_file_specifier (distribution_file, &graphics_files[i]);
/*
					if (!file_exist (distribution_file))
					{
						get_language_specific_local_distribution_file_specifier (distribution_file, &graphics_files[i]);

						if (!file_exist (distribution_file))
						{
							get_language_specific_distribution_file_specifier (distribution_file, &graphics_files[i]);
						}
					}
*/
					if (!file_exist (distribution_file ))
					{
						get_distribution_file_specifier (distribution_file, &graphics_files[i]);
					}

					debug_log ("Converting file %s to %s", distribution_file, installation_file);

					add_file_to_uninstall_log (installation_file);

					switch (graphics_files[i].graphics_conversion_type)
					{
#if 0
						////////////////////////////////////////
						case CONVERT_TGA_TO_ALPHA_MASK:
						////////////////////////////////////////
						{
							convert_tga_to_alpha_mask (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_TGA_TO_RGB:
						////////////////////////////////////////
						{
							convert_tga_to_rgb (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_TGA_TO_RGB_ALPHA:
						////////////////////////////////////////
						{
							convert_tga_to_rgb_alpha (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_TGA_TO_RLE:
						////////////////////////////////////////
						{
							convert_tga_to_rle (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_PSD_TO_ALPHA_MASK:
						////////////////////////////////////////
						{
							convert_psd_to_alpha_mask (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_PSD_TO_RGB:
						////////////////////////////////////////
						{
							convert_psd_to_rgb (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_PSD_TO_RGB_ALPHA:
						////////////////////////////////////////
						{
							convert_psd_to_rgb_alpha (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_PSD_TO_RLE:
						////////////////////////////////////////
						{
							convert_psd_to_rle (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_PSD_TO_DITHERED_RGB:
						////////////////////////////////////////
						{
							convert_and_dither_psd_to_rgb (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_PSD_TO_DITHERED_RGB_ALPHA:
						////////////////////////////////////////
						{
							convert_and_dither_psd_to_rgb_alpha (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_PSD_TO_DITHERED_RLE:
						////////////////////////////////////////
						{
							convert_and_dither_psd_to_rle (distribution_file, installation_file);

							break;
						}
#else
						////////////////////////////////////////
						case CONVERT_PSD_TO_RGBX:
						////////////////////////////////////////
						{
							convert_psd_to_rgbx (distribution_file, installation_file);

							break;
						}
						////////////////////////////////////////
						case CONVERT_PSD_TO_RGBA:
						////////////////////////////////////////
						{
							convert_psd_to_rgba (distribution_file, installation_file);

							break;
						}
#endif
					}

					break;
				}
			}
		}
	}

	if ((all_files_converted) && (pass_conversion == GRAPHICS_CONVERSION_SECOND_PASS))
	{

		set_global_graphics_files_installed (TRUE);
	}

	return (all_files_converted);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void uninstall_graphics_files (void)
{
	char
		installation_file[200];

	int
		i,
		failed;

	debug_log ("Uninstalling graphics files ...");

	for (i = 0; i < NUM_FILES; i++)
	{
		if (get_file_required (i))
		{
			get_installation_file_specifier (installation_file, &graphics_files[i]);

			if (file_exist (installation_file))
			{
				failed = unlink (installation_file);

				// JB 030311 Enable running out of separate directories
				if (failed)
				{
					char fn[1024];
					fn[0] = 0;
					strcpy(fn, comanche_hokum_installation_path);
					strcat(fn, "\\cohokum\\");
					strcat(fn, installation_file);

					failed = unlink (fn);

					if (failed)
					{
						fn[0] = 0;
						strcpy(fn, comanche_hokum_installation_path);
						strcat(fn, "\\common\\");
						strcat(fn, installation_file);

						failed = unlink (fn);

						if (failed)
							debug_fatal ("Failed to delete %s", installation_file);
					}
				}
			}
		}
	}

	set_global_graphics_files_installed (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void mclose_pre_installed_apache_havoc_cockpit_graphics (void)
{
	int
		i;

	char
		installation_file[1024],
		apache_havoc_installation_file[2048];

// VJ 050118 aphavoc install hack
	debug_assert (get_global_apache_havoc_installed ());

	debug_assert (apache_havoc_installation_path_valid);

	debug_assert (strlen (apache_havoc_installation_path));

	for (i = 0; i < NUM_FILES; i++)
	{
		if (graphics_files[i].required_for_apache_havoc_cockpits)
		{
			get_installation_file_specifier (installation_file, &graphics_files[i]);

			strcpy (apache_havoc_installation_file, apache_havoc_installation_path);

			strcat (apache_havoc_installation_file, "\\aphavoc\\");

			strcat (apache_havoc_installation_file, installation_file);

			if (!file_exist (apache_havoc_installation_file))
			{
				debug_colour_log (DEBUG_COLOUR_AMBER, "MCLOSE: missing installed Apache Havoc file: %s", apache_havoc_installation_file);
			}
			else
			{
				safe_mclose (graphics_files[i].data);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void mopen_pre_installed_apache_havoc_cockpit_graphics (void)
{
	int
		i,
		failed;

	char
		installation_file[1024],
		apache_havoc_installation_file[2048];

	debug_assert (get_global_apache_havoc_installed ());

	debug_assert (apache_havoc_installation_path_valid);

	debug_assert (strlen (apache_havoc_installation_path));

	failed = FALSE;

	for (i = 0; i < NUM_FILES; i++)
	{
		if (graphics_files[i].required_for_apache_havoc_cockpits)
		{
			get_installation_file_specifier (installation_file, &graphics_files[i]);

			strcpy (apache_havoc_installation_file, apache_havoc_installation_path);

			strcat (apache_havoc_installation_file, "\\aphavoc\\");

			strcat (apache_havoc_installation_file, installation_file);

			if (!file_exist (apache_havoc_installation_file))
			{
				debug_colour_log (DEBUG_COLOUR_AMBER, "MOPEN: missing installed Apache Havoc file: %s", apache_havoc_installation_file);

				failed = TRUE;
			}
			else
			{
				graphics_files[i].data = ( rgb_data * ) safe_mopen (apache_havoc_installation_file);
			}
		}
	}

	if (failed)
	{
		mclose_pre_installed_apache_havoc_cockpit_graphics ();

		set_global_apache_havoc_installed (FALSE);

		debug_colour_log (DEBUG_COLOUR_AMBER, "Apache Havoc is NOT installed");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mopen_all_graphics_files (int pass_conversion)
{
	char
		installation_file[200];

	int
		i;

	for (i = 0; i < NUM_FILES; i++)
	{
		if (get_file_required (i))
		{
			if (graphics_files[i].first_pass_conversion == pass_conversion)
			{
				get_installation_file_specifier (installation_file, &graphics_files[i]);

				graphics_files[i].data = ( rgb_data * ) safe_mopen (installation_file);
			}
		}
	}

	if (pass_conversion == GRAPHICS_CONVERSION_SECOND_PASS)
	{
		if (get_global_apache_havoc_installed ())
		{
			mopen_pre_installed_apache_havoc_cockpit_graphics ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mclose_all_graphics_files (void)
{
	int
		i;

	for (i = 0; i < NUM_FILES; i++)
	{
		if (get_file_required (i))
		{
			safe_mclose (graphics_files[i].data);
		}
	}

	if (get_global_apache_havoc_installed ())
	{
		mclose_pre_installed_apache_havoc_cockpit_graphics ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
char *get_language_specific_distribution_file_specifier (char *file_specifier, file_data *file)
{

	file_specifier[0] = cdrom_drive_letter;
	file_specifier[1] = ':';
	file_specifier[2] = '\0';

	file_specifier = strcat (file_specifier, distribution_path_names[file->path_name]);

	file_specifier = strcat (file_specifier, get_localisation_text (text_translation_list, GRAPHICS_FILE_DIRECTORY));

	file_specifier = strcat (file_specifier, file->file_name);

	file_specifier = strcat (file_specifier, ".");

	file_specifier = strcat (file_specifier, file->distribution_extension);

	return (file_specifier);
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
char *get_language_specific_local_distribution_file_specifier (char *file_specifier, file_data *file)
{

	file_specifier = strcpy (file_specifier, installation_path_names[file->path_name]);

	file_specifier = strcat (file_specifier, get_localisation_text (text_translation_list, GRAPHICS_FILE_DIRECTORY));

	file_specifier = strcat (file_specifier, file->file_name);

	file_specifier = strcat (file_specifier, ".");

	file_specifier = strcat (file_specifier, file->distribution_extension);

	return (file_specifier);
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *get_distribution_file_specifier (char *file_specifier, file_data *file)
{
	file_specifier[0] = cdrom_drive_letter;
	file_specifier[1] = ':';
	file_specifier[2] = '\0';

	file_specifier = strcat (file_specifier, distribution_path_names[file->path_name]);

	file_specifier = strcat (file_specifier, file->file_name);

	file_specifier = strcat (file_specifier, ".");

	file_specifier = strcat (file_specifier, file->distribution_extension);

	return (file_specifier);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *get_local_distribution_file_specifier (char *file_specifier, file_data *file)
{
	file_specifier = strcpy (file_specifier, installation_path_names[file->path_name]);

	file_specifier = strcat (file_specifier, file->file_name);

	file_specifier = strcat (file_specifier, ".");

	file_specifier = strcat (file_specifier, file->distribution_extension);

	return (file_specifier);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char *get_installation_file_specifier (char *file_specifier, file_data *file)
{
	file_specifier = strcpy (file_specifier, installation_path_names[file->path_name]);

	file_specifier = strcat (file_specifier, file->file_name);

	file_specifier = strcat (file_specifier, ".");

	file_specifier = strcat (file_specifier, file->installation_extension);

	return (file_specifier);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
*/