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

static int
	initialised = FALSE;

static gunship_types
	gunship_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_cockpits (void)
{
	ASSERT (!initialised);

	if (!get_gunship_entity ())
	{
		return;
	}

	initialised = TRUE;

	gunship_type = get_global_gunship_type ();

	switch (gunship_type)
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			initialise_common_cockpits ();

			initialise_apache_cockpits ();

			//
			// order is critical
			//

			initialise_apache_virtual_cockpit ();

			initialise_common_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			initialise_common_cockpits ();

			initialise_havoc_cockpits ();

			//
			// order is critical
			//

			initialise_havoc_virtual_cockpit ();

			initialise_common_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			initialise_common_cockpits ();

			initialise_comanche_cockpits ();

			//
			// order is critical
			//

			initialise_comanche_virtual_cockpit ();

			initialise_common_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			initialise_common_cockpits ();

			initialise_hokum_cockpits ();

			//
			// order is critical
			//

			initialise_hokum_virtual_cockpit ();

			initialise_common_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		////Moje 030518 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			initialise_common_cockpits ();

			initialise_blackhawk_cockpits ();

			//
			// order is critical
			//

			initialise_blackhawk_virtual_cockpit ();

			initialise_common_virtual_cockpit ();

			break;
		}
		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			initialise_common_cockpits ();

			initialise_hind_cockpits ();

			//
			// order is critical
			//

			initialise_hind_virtual_cockpit ();

			initialise_common_virtual_cockpit ();

			break;
		}
		////Moje 030612 End
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_cockpits (void)
{
	if (!initialised)
	{
		return;
	}

	initialised = FALSE;

	switch (gunship_type)
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			deinitialise_common_cockpits ();

			deinitialise_common_virtual_cockpit ();

			deinitialise_apache_cockpits ();

			deinitialise_apache_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			deinitialise_common_cockpits ();

			deinitialise_common_virtual_cockpit ();

			deinitialise_havoc_cockpits ();

			deinitialise_havoc_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			deinitialise_common_cockpits ();

			deinitialise_common_virtual_cockpit ();

			deinitialise_comanche_cockpits ();

			deinitialise_comanche_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			deinitialise_common_cockpits ();

			deinitialise_common_virtual_cockpit ();

			deinitialise_hokum_cockpits ();

			deinitialise_hokum_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		////Moje 030518 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			deinitialise_common_cockpits ();

			deinitialise_common_virtual_cockpit ();

			deinitialise_blackhawk_cockpits ();

			deinitialise_blackhawk_virtual_cockpit ();

			break;
		}
		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			deinitialise_common_cockpits ();
			deinitialise_common_virtual_cockpit ();
			deinitialise_hind_cockpits ();
			deinitialise_hind_virtual_cockpit ();

			break;
		}
		////Moje 030612 End
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_cockpits (void)
{
	if (!initialised)
	{
		return;
	}

	switch (gunship_type)
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			update_common_cockpits ();

			update_common_virtual_cockpit ();

			update_apache_cockpits ();

			update_apache_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			update_common_cockpits ();

			update_common_virtual_cockpit ();

			update_havoc_cockpits ();

			update_havoc_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			update_common_cockpits ();

			update_common_virtual_cockpit ();

			update_comanche_cockpits ();

			update_comanche_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			update_common_cockpits ();

			update_common_virtual_cockpit ();

			update_hokum_cockpits ();

			update_hokum_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		////Moje 030518 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			update_common_cockpits ();

			update_common_virtual_cockpit ();

			update_blackhawk_cockpits ();

			update_blackhawk_virtual_cockpit ();

			break;
		}
		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			update_common_cockpits ();

			update_common_virtual_cockpit ();

			update_hind_cockpits ();

			update_hind_virtual_cockpit ();

			break;
		}
		////Moje 030612 End
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_cockpit (cockpit_panels panel)
{
	ASSERT (initialised);

	ASSERT (get_gunship_entity ());

	switch (gunship_type)
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_apache_cockpit (panel);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_havoc_cockpit (panel);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			debug_fatal ("Attempted to draw Comanche fixed cockpit");

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			debug_fatal ("Attempted to draw Hokum fixed cockpit");

			break;
		}
		////////////////////////////////////////
		////Moje 030518 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_blackhawk_cockpit (panel);

			break;
		}
		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_hind_cockpit (panel);

			break;
		}
		////Moje 030612 End
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
