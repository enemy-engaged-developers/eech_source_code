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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	null_text_string[] = "NULL";
/*
static game_text_translation_type
	text_translation_list [] =
	{
		{
			WEAPON_DESCRIPTION_UNKNOWN_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"?",				 			0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"?",			 				0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"?",				 			0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"?",				 			0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"?",				 			0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_HEDP_ROUNDS_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"High explosive dual purpose rounds", 		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Hochexplosive Mehrzweck-Geschosse", 		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"High explosive dual purpose rounds", 		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"High explosive dual purpose rounds", 		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Cartuchos de doble propósito con alto explosivo", 		0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_TWO_BARREL_CANNON_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"Two-barreled cannon",				 			0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Doppelläufige Kanone",			 				0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"Two-barreled cannon",				 			0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"Two-barreled cannon",				 			0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Cañón de doble tubo",				 			0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_HE_ROUNDS_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"High explosive rounds",	 					0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Hochexplosive Geschosse",		 				0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"High explosive rounds",	 					0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"High explosive rounds",	 					0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Cartuchos de alto explosivo",	 			0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_AP_ROUNDS_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"Armour piercing rounds",						0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Panzerbrechende Geschosse",					0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"Armour piercing rounds",						0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"Armour piercing rounds",						0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Cartuchos de metralla",						0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_70MM_HE_ROCKET_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"70mm high explosive unguided rocket",					0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Ungelenkte 70-mm-Rakete mit Brisanzsprengstoff",	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"70mm high explosive unguided rocket",					0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"70mm high explosive unguided rocket",					0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Cohetes de 70 mm, sin guía y con alto explosivo",	0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_70MM_MP_ROCKET_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"70mm multi-purpose unguided rocket",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Ungelenkte 70-mm-Mehrzweckrakete",		  	0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"70mm multi-purpose unguided rocket",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"70mm multi-purpose unguided rocket",	 	0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Cohetes de 70 mm, sin guía y multi-propósito",		0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_80MM_ROCKET_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"80mm unguided rocket",				 			0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Ungelenkte 80-mm-Rakete",				 		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"80mm unguided rocket",				 			0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"80mm unguided rocket",				 			0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Cohetes de 80 mm sin guía",					0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_130MM_ROCKET_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"130mm unguided rocket",  	 					0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Ungelenkte 130-mm-Rakete",  	 				0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"130mm unguided rocket",  	 					0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"130mm unguided rocket",  	 					0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Cohetes de 130 mm sin guía",  				0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_IR_MISSILE_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"Infra-red guided air-to-air missile",		0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Infrarotgelenkte Luftkampfrakete",			0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"Infra-red guided air-to-air missile",		0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"Infra-red guided air-to-air missile",		0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Misil aire-aire guiado por infrarrojos",	0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_RADAR_HELLFIRE_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"Radar guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Radargelenkte Panzerabwehr-Rakete",		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"Radar guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"Radar guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Misil anti-carro guiado por radar",		0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_LASER_HELLFIRE_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"Laser guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Lasergelenkte Panzerabwehr-Rakete",		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"Laser guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"Laser guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Misil anti-carro guiado por láser",	 	0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_ATAKA_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"Radio command guided anti-tank missile", 	0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Über Funk gesteuerte Panzerabwehr-Rakete",  0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"Radio command guided anti-tank missile", 	0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"Radio command guided anti-tank missile", 	0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Misil anti-carro guiado por radio", 			0, 0,		0, 0 },
			}
		},

		{
			WEAPON_DESCRIPTION_VIKHR_TEXT,
			{
				{ LANGUAGE_ENGLISH, 	"Laser guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_GERMAN, 	"Lasergelenkte Panzerabwehr-Rakete",		0, 0,		0, 0 },
				{ LANGUAGE_FRENCH, 	"Laser guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_ITALIAN, 	"Laser guided anti-tank missile",		 	0, 0,		0, 0 },
				{ LANGUAGE_SPANISH, 	"Misil anti-carro guiado por láser",	 	0, 0,		0, 0 },
			}
		},
	};
	*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_weapon_description_text (int id)
{
	ASSERT ((id >= 0) && (id < NUM_WEAPON_DESCRIPTION_TEXT_ITEMS));

	return null_text_string;	//get_localisation_text (text_translation_list, id);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
