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

// Whole file Retro 6Feb2005
// Manages movement of Pilothead, currently only for trackir vector

// todo
// ) still need a way to tell if this version of the TIR supports this (or if the axis are active)
// ) also need a good (faster ?) way to clip to cockpit limits
// ) make limits configurable

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

static float
	command_line_viewpoint_left_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25} },
	command_line_viewpoint_right_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25} },
	command_line_viewpoint_up_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25} },
	command_line_viewpoint_down_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25} },
	command_line_viewpoint_fore_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25}, {0.25, 0.25} },
	command_line_viewpoint_aft_limit[NUM_GUNSHIP_TYPES][NUM_CREW_ROLES] =	{ {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25}, {-0.25, -0.25} };

static float getMaxLeft()
{
	return command_line_viewpoint_left_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxRight()
{
	return command_line_viewpoint_right_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxForeward()
{
	return command_line_viewpoint_fore_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxBackward()
{
	return command_line_viewpoint_aft_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxUp()
{
	return command_line_viewpoint_up_limit[get_global_gunship_type ()][get_crew_role ()];
}

static float getMaxDown()
{
	return command_line_viewpoint_down_limit[get_global_gunship_type ()][get_crew_role ()];
}

float getViewpointOffsetX (float x)
{
	if ((command_line_TIR_6DOF == TRUE) && ( query_TIR_active () == TRUE ))
	{
		float tmp = TIR_GetX() / TIR_GetMaxXY();

		{ FILE* fp = fopen("vector.txt", "at"); fprintf(fp,"%f %f %f\n", TIR_GetX(), TIR_GetMaxXY(), tmp); fclose(fp); }
		if (tmp >= 0)
			x = tmp * getMaxLeft();
		else
			x = tmp * -getMaxRight();
	}
	else
	{
		x = bound ( x, getMaxRight(), getMaxLeft() );
	}

	return x;
}

float getViewpointOffsetY (float y)
{
	if ((command_line_TIR_6DOF == TRUE) && ( query_TIR_active () == TRUE ))
	{
		float tmp = TIR_GetY() / TIR_GetMaxXY();
		if (tmp >= 0)
			y = tmp * -getMaxUp();
		else
			y = tmp * getMaxDown();
	}
	else
	{
		y = bound ( y, getMaxDown(), getMaxUp() );
	}

	return y;
}

float getViewpointOffsetZ (float z)
{
	if ((command_line_TIR_6DOF == TRUE) && ( query_TIR_active () == TRUE ))
	{
		float tmp = TIR_GetZ() / 16383.;	// this value is fixed, as opposed to x and y
		if (tmp >= 0)
			z = tmp * getMaxForeward();
		else
			z = tmp * -getMaxBackward();
	}
	else
	{
		z = bound ( z, getMaxBackward(), getMaxForeward() );
	}

	return z;
}