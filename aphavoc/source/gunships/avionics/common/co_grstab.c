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

float
	eo_ground_stabilisation_value_heading,
 	eo_ground_stabilisation_value_pitch,
	pitch,
	roll;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void toggle_ground_stabilisation (void)
{
	if (command_line_ground_stabilisation_available)
	{
		if (eo_ground_stabilised)
		{
			eo_ground_stabilised = 0;
		}
		else
		{
			matrix3x3
				attitude;

			eo_ground_stabilised = 1;

			get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

			eo_ground_stabilisation_value_heading = atan2 (attitude [2][0], attitude [2][2]);

			eo_ground_stabilisation_value_pitch = asin (attitude [2][1]);

//			eo_ground_stabilisation_value_roll = atan2 (-attitude [0][1], attitude [1][1]);
		}
	}
}


void handle_ground_stabilisation (void)
{

	// loke 030322
	// handle the ground stabilisation
	// improved stabilization thealx 130218

	if (eo_ground_stabilised)
	{
		matrix3x3
			attitude;
				
		float
			delta_pitch,
			delta_roll,
			heading,
			anglex,
			angley,
			correctionx;
				
		float
			horizontal_pan_offset,
			vertical_pan_offset;
						
		get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

		heading = atan2 (attitude [2][0], attitude [2][2]);

		delta_pitch = pitch - asin (attitude [2][1]);
		pitch = asin (attitude [2][1]);

		delta_roll = roll - atan2 (-attitude [0][1], attitude [1][1]);
		roll = atan2 (-attitude [0][1], attitude [1][1]);

		if (eo_azimuth > (PI / 2))
		{
			anglex = PI - eo_azimuth;
			correctionx = - cos (anglex);
		}
		else if (eo_azimuth < (- PI / 2))
		{
			anglex = - PI - eo_azimuth;
			correctionx = - cos (anglex);
		}
		else
		{
			anglex = eo_azimuth;
			correctionx = cos (anglex);
		}

		angley = eo_elevation;				
				 
		// GCsDriver start 180 deg. bug workaround

		// problem :
		// when crossing 180 deg stabilised view switches focus to 109 or 250 deg
		// crossing 0 / 360 deg is fine

		// solution : ?
		// sth like this should do but what`s the C equivalent ?
		// horizontal_pan_offset = mod((eo_ground_stabilisation_value_heading - heading), 2*pi);

		// workaround :
		// if we cross border we have to invert the rad
		// this gives just a little "glitch" when crossing 180 AND 0/360 deg
		// glitch width depends on turn rate (and distance centered point to 180/0 line)

		if ((eo_ground_stabilisation_value_heading > 0)&&(heading < 0))
		{
			eo_ground_stabilisation_value_heading *= -1;
			anglex *= -1;
 		}
		else if ((eo_ground_stabilisation_value_heading < 0)&&(heading > 0))
		{
			eo_ground_stabilisation_value_heading *= -1;
			anglex *= -1;
		}
				
		// GCsDriver end 180 deg. bug workaround
					
		horizontal_pan_offset = (eo_ground_stabilisation_value_heading - heading) * cos(angley) + delta_roll * sin(angley) * correctionx + sin(anglex) * sin(delta_pitch) * eo_elevation;
		
		vertical_pan_offset = (eo_ground_stabilisation_value_pitch - pitch) * correctionx - delta_roll * sin(anglex);

		eo_azimuth +=  horizontal_pan_offset;

		if (eo_azimuth > 0)
		{
			eo_azimuth = min (eo_azimuth, eo_max_azimuth);
		}
		else
		{
			eo_azimuth = max (eo_azimuth, eo_min_azimuth);
		}
				
		eo_elevation += vertical_pan_offset;

		if (vertical_pan_offset > 0)
		{
			eo_elevation = min (eo_elevation, eo_max_elevation);
		}
		else
		{
			eo_elevation = max (eo_elevation, eo_min_elevation);
		}

		eo_ground_stabilisation_value_heading = heading;

		eo_ground_stabilisation_value_pitch = pitch;
	}
}

