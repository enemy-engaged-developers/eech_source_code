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

object_3d_instance
	*virtual_cockpit_inst3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	pilot_head_pitch_datum,
	co_pilot_head_pitch_datum;

cockpit_switch
	*engine_start_switch_animation_object,
	*apu_start_switch_animation_object,
	*apu_stop_switch_animation_object;

static vec3d
	gunship_periscope_position[NUM_GUNSHIP_TYPES][2];

light_colour
	cockpit_light_color_table[COCKPIT_LIGHT_LAST];
int
	cockpit_light_color_index[2];
cockpit_light_colors
	*cockpit_light_color_array;
light_3d_source
	*display_backlight,
	*cockpit_light[2];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pre_initialise_common_virtual_cockpit (void)
{
	engine_start_switch_animation_object = NULL;
	apu_start_switch_animation_object = NULL;
	apu_stop_switch_animation_object = NULL;
}

void initialise_common_virtual_cockpit (void)
{
	initialise_common_virtual_cockpit_wiper_and_rain_effect ();

	memset(gunship_periscope_position, 0, sizeof(gunship_periscope_position));
	gunship_periscope_position[GUNSHIP_TYPE_HOKUM][0].x = -0.05;
	gunship_periscope_position[GUNSHIP_TYPE_HOKUM][1].x =  0.05;
	gunship_periscope_position[GUNSHIP_TYPE_HOKUM][0].y = -0.05;
	gunship_periscope_position[GUNSHIP_TYPE_HOKUM][1].y =  0.05;
	gunship_periscope_position[GUNSHIP_TYPE_HOKUM][0].z = 0.275;
	gunship_periscope_position[GUNSHIP_TYPE_HOKUM][1].z = 1.00;

	gunship_periscope_position[GUNSHIP_TYPE_APACHE][0].x = -0.05;
	gunship_periscope_position[GUNSHIP_TYPE_APACHE][1].x =  0.05;
	gunship_periscope_position[GUNSHIP_TYPE_APACHE][0].y = -0.080;
	gunship_periscope_position[GUNSHIP_TYPE_APACHE][1].y = -0.020;
	gunship_periscope_position[GUNSHIP_TYPE_APACHE][0].z = 0.175;
	gunship_periscope_position[GUNSHIP_TYPE_APACHE][1].z = 1.00;
	
	cockpit_light_color_table[COCKPIT_LIGHT_NONE].red = 0.25;
	cockpit_light_color_table[COCKPIT_LIGHT_NONE].green = 0.25;
	cockpit_light_color_table[COCKPIT_LIGHT_NONE].blue = 0.25;
	cockpit_light_color_table[COCKPIT_LIGHT_YELLOW].red = 1.0;
	cockpit_light_color_table[COCKPIT_LIGHT_YELLOW].green = 1.0;
	cockpit_light_color_table[COCKPIT_LIGHT_YELLOW].blue = 0.3;
	cockpit_light_color_table[COCKPIT_LIGHT_RED].red = 1.0;
	cockpit_light_color_table[COCKPIT_LIGHT_RED].green = 0.2;
	cockpit_light_color_table[COCKPIT_LIGHT_RED].blue = 0.2;
	cockpit_light_color_table[COCKPIT_LIGHT_WHITE].red = 1.0;
	cockpit_light_color_table[COCKPIT_LIGHT_WHITE].green = 1.0;
	cockpit_light_color_table[COCKPIT_LIGHT_WHITE].blue = 1.0;
	cockpit_light_color_table[COCKPIT_LIGHT_BLUE].red = 0.2;
	cockpit_light_color_table[COCKPIT_LIGHT_BLUE].green = 0.2;
	cockpit_light_color_table[COCKPIT_LIGHT_BLUE].blue = 1.0;
	cockpit_light_color_table[COCKPIT_LIGHT_GREEN].red = 0.2;
	cockpit_light_color_table[COCKPIT_LIGHT_GREEN].green = 1.0;
	cockpit_light_color_table[COCKPIT_LIGHT_GREEN].blue = 0.2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_virtual_cockpit (void)
{
	deinitialise_common_virtual_cockpit_wiper_and_rain_effect ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_virtual_cockpit (void)
{
	update_common_virtual_cockpit_wiper_and_rain_effect ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int TIR_looking_in_periscope(void)
{
	gunship_types ship = get_global_gunship_type();

	float x, y, z;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) != CREW_ROLE_CO_PILOT)
		return FALSE;

	x = wide_cockpit_position[wide_cockpit_nr].c.x - current_custom_cockpit_viewpoint.x;
	y = wide_cockpit_position[wide_cockpit_nr].c.y - current_custom_cockpit_viewpoint.y;
	z = wide_cockpit_position[wide_cockpit_nr].c.z - current_custom_cockpit_viewpoint.z;

	if (pilot_head_heading < rad(-10.0) || pilot_head_heading > rad(10.0)
		|| pilot_head_pitch < rad(-30.0) || pilot_head_pitch > rad(10.0))
	{
		return FALSE;
	}

	if (gunship_periscope_position[ship][0].x < x &&
		gunship_periscope_position[ship][1].x > x &&
		gunship_periscope_position[ship][0].y < y &&
		gunship_periscope_position[ship][1].y > y &&
		gunship_periscope_position[ship][0].z < z &&
		gunship_periscope_position[ship][1].z > z)
	{
		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_virtual_cockpit_periscope_mask (int x_min, int x_max, int monoccular)
{
#ifndef OGRE_EE
	vertex
		quad[4];

	real_colour
		colour,
		specular;

	float
		x_texture_limit = 1.0,
		y_texture_limit = 0.0;

	if (monoccular)
	{
		x_texture_limit = 0.6;
		y_texture_limit = 0.15;
	}

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		colour.red		= 255;
		colour.green	= 255;
		colour.blue		= 255;
		colour.alpha	= 255;

		specular.red	= 0;
		specular.green	= 0;
		specular.blue	= 0;
		specular.alpha	= 255;

		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_culling (FALSE);

		set_d3d_texture_wrapping (0, FALSE);

		set_d3d_texture_filtering (FALSE);

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_HOKUM_COCKPIT_WSO_SCOPE_VIEW));

		////////////////////////////////////////
		//
		// top left
		//
		////////////////////////////////////////

		quad[0].i 				= x_min;
		quad[0].j  				= full_screen_y_min;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= 0.0;
		quad[0].v				= y_texture_limit;

		quad[1].i  				= full_screen_x_mid;
		quad[1].j  				= full_screen_y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= x_texture_limit;
		quad[1].v  				= y_texture_limit;

		quad[2].i				= full_screen_x_mid;
		quad[2].j  				= full_screen_y_mid;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= x_texture_limit;
		quad[2].v  				= 1.0;

		quad[3].i  				= x_min;
		quad[3].j  				= full_screen_y_mid;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= 1.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		////////////////////////////////////////
		//
		// bottom left
		//
		////////////////////////////////////////

		quad[0].i 				= x_min;
		quad[0].j  				= full_screen_y_mid;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= 0.0;
		quad[0].v				= 1.0;

		quad[1].i  				= full_screen_x_mid;
		quad[1].j  				= full_screen_y_mid;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= x_texture_limit;
		quad[1].v  				= 1.0;

		quad[2].i				= full_screen_x_mid;
		quad[2].j  				= full_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= x_texture_limit;
		quad[2].v  				= y_texture_limit;

		quad[3].i  				= x_min;
		quad[3].j  				= full_screen_y_max;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= y_texture_limit;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		////////////////////////////////////////
		//
		// top right
		//
		////////////////////////////////////////

		quad[0].i 				= full_screen_x_mid;
		quad[0].j  				= full_screen_y_min;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= x_texture_limit;
		quad[0].v				= y_texture_limit;

		quad[1].i  				= x_max;
		quad[1].j  				= full_screen_y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 0.0;
		quad[1].v  				= y_texture_limit;

		quad[2].i				= x_max;
		quad[2].j  				= full_screen_y_mid;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 0.0;
		quad[2].v  				= 1.0;

		quad[3].i  				= full_screen_x_mid;
		quad[3].j  				= full_screen_y_mid;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
		quad[3].u				= x_texture_limit;
		quad[3].v				= 1.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		////////////////////////////////////////
		//
		// bottom left
		//
		////////////////////////////////////////

		quad[0].i 				= full_screen_x_mid;
		quad[0].j  				= full_screen_y_mid;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= x_texture_limit;
		quad[0].v				= 1.0;

		quad[1].i  				= x_max;
		quad[1].j  				= full_screen_y_mid;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 0.0;
		quad[1].v  				= 1.0;

		quad[2].i				= x_max;
		quad[2].j  				= full_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 0.0;
		quad[2].v  				= y_texture_limit;

		quad[3].i  				= full_screen_x_mid;
		quad[3].j  				= full_screen_y_max;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
		quad[3].u				= x_texture_limit;
		quad[3].v				= y_texture_limit;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		////////////////////////////////////////

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		set_d3d_culling (TRUE);

		end_3d_scene ();
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_virtual_cockpit_periscope_filler (int x_min, int x_max)
{
#ifndef OGRE_EE
	vertex
		quad[4];

	real_colour
		colour,
		specular;

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		colour.red		= 0;
		colour.green	= 0;
		colour.blue		= 0;
		colour.alpha	= 255;

		specular.red	= 0;
		specular.green	= 0;
		specular.blue	= 0;
		specular.alpha	= 255;

		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_plain_renderstate ();

		set_d3d_culling (FALSE);

		quad[0].i 				= full_screen_x_min;
		quad[0].j  				= full_screen_y_min;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;

		quad[1].i  				= full_screen_x_min;
		quad[1].j  				= full_screen_y_max;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;

		quad[2].i				= x_min;
		quad[2].j  				= full_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;

		quad[3].i  				= x_min;
		quad[3].j  				= full_screen_y_min;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_plain_polygon (quad, colour, specular);

		quad[0].i 				= x_max;
		quad[0].j  				= full_screen_y_min;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;

		quad[1].i  				= x_max;
		quad[1].j  				= full_screen_y_max;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;

		quad[2].i				= full_screen_x_max;
		quad[2].j  				= full_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;

		quad[3].i  				= full_screen_x_max;
		quad[3].j  				= full_screen_y_min;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_plain_polygon (quad, colour, specular);
		
		////////////////////////////////////////

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		end_3d_scene ();
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_switch(cockpit_switch* swch, float* position, float depress_length, float depress_time, float delay)
{
	swch->position = position;
	swch->initial_position = *position;
	swch->depress_length = depress_length * 2.0 / depress_time;
	swch->depress_time = depress_time;
	swch->delay = delay;
	swch->timer = 0.0;
}

void press_switch(cockpit_switch* swch)
{
	if (swch->timer <= 0.0)
		swch->timer = swch->depress_time + swch->delay;
}

void animate_switch(cockpit_switch* swch)
{
	if (swch->timer <= 0.0)
		return;

	if (swch->timer < swch->depress_time)  // otherwise delay
	{
		float half_time = swch->depress_time / 2.0;

		if (swch->timer > half_time)  // pressing in
			*(swch->position) = swch->initial_position + (swch->depress_length * (swch->depress_time - swch->timer));
		else // rebounding out
			*(swch->position) = swch->initial_position + (swch->depress_length * swch->timer);
	}

	swch->timer -= get_delta_time();
}

void print_repairing_status (void) // by /thealx/
{
	char buffer[128];
	int string_length;
	float x, progress, length;

	if (current_flight_dynamics->repairing_damage != DYNAMICS_DAMAGE_NONE)
	{
		progress = 1 - current_flight_dynamics->damage_repair_time / damage_repair_time;
		sprintf (buffer, "Repairing: %s", dynamics_damage_database [repairing_damage_count].name);
	}
	else if (current_flight_dynamics->refueling)
	{
		progress = fabs(current_fuel_level - current_flight_dynamics->fuel_weight.value)/(available_fuel - current_fuel_level);
		sprintf (buffer, "Refueling");
	}
	else
		return;

	set_ui_font_type (UI_FONT_THICK_ARIAL_18);
	set_ui_font_colour (ui_colour_cyan);

	string_length = ui_get_string_length ( buffer );
	x = get_integer_screen_x_mid () - (string_length / 2);
	ui_display_text (buffer, x, full_screen_height * 1 / 5);

	sprintf (buffer, "%0.0f %%", progress * 100);
	string_length = ui_get_string_length ( buffer );
	x = get_integer_screen_x_mid () - (string_length / 2);
	ui_display_text (buffer, x, full_screen_height * 1 / 5 + 1.5 * ui_get_font_height ());

	for (length = 0; length <= 19; length++)
	{
		if ((length / 20) <= progress)
			sprintf (buffer, "!");
		else
			sprintf (buffer, ".");

		ui_display_text (".", get_integer_screen_x_mid () - 50 + 5 * length, full_screen_height * 1 / 5 + 1.5 * ui_get_font_height () + 14);
		ui_display_text (buffer, get_integer_screen_x_mid () - 50 + 5 * length, full_screen_height * 1 / 5 + 2.5 * ui_get_font_height ());
	}	
}

//VJ wideview mod, date: 18-mar-03
void print_edit_wide_cockpit (void)
{
	char
		buffer[128];

	if (edit_wide_cockpit)
	{
		sprintf(buffer, "%s wide cockpit mod edit (set freelook off):", wide_cockpit_position[wide_cockpit_nr].cockpit);
		ui_display_text (buffer, 10, 40);
		ui_display_text ("X: num1/3; Y: num 8/2; Z: num 4/6; pitch: num 7/9; Restore: num 0; Ctrl-\\ Leave edit", 10, 60);
		sprintf (buffer, "x=%.3f, y=%.3f, z=%.3f, pitch=%.3f", wide_cockpit_position[wide_cockpit_nr].c.x, wide_cockpit_position[wide_cockpit_nr].c.y, wide_cockpit_position[wide_cockpit_nr].c.z, wide_cockpit_position[wide_cockpit_nr].c.p);
		ui_display_text (buffer, 10, 100);
	}
}

void move_edit_wide_cockpit (void)
{
	////////////////////////////////////////
	//
	// wide cockpit position edit
	//
	////////////////////////////////////////

	if (edit_wide_cockpit)
	{
		if (check_key(DIK_NUMPAD7))
		{
			wide_cockpit_position[wide_cockpit_nr].c.p += 0.5;
		}
		if (check_key(DIK_NUMPAD9))
		{
			wide_cockpit_position[wide_cockpit_nr].c.p -= 0.5;
		}
		if (check_key(DIK_NUMPAD6))
		{
			wide_cockpit_position[wide_cockpit_nr].c.z += 0.01;
		}
		if (check_key(DIK_NUMPAD4))
		{
			wide_cockpit_position[wide_cockpit_nr].c.z -= 0.01;
		}
		if (check_key(DIK_NUMPAD8))
		{
			wide_cockpit_position[wide_cockpit_nr].c.y += 0.01;
		}
		if (check_key(DIK_NUMPAD2))
		{
			wide_cockpit_position[wide_cockpit_nr].c.y -= 0.01;
		}
		if (check_key(DIK_NUMPAD1))
		{
			wide_cockpit_position[wide_cockpit_nr].c.x -= 0.01;
		}
		if (check_key(DIK_NUMPAD3))
		{
			wide_cockpit_position[wide_cockpit_nr].c.x += 0.01;
		}
		if (check_key(DIK_NUMPAD0))
		{
			wide_cockpit_position[wide_cockpit_nr].c = wide_cockpit_position[wide_cockpit_nr].d;
		}
	}
}

//ATARIBABY 27/12/2008 move to target value by defined rate
float move_by_rate(float oldval, float newval, float rate)
{
  float changeval;
	float value = oldval;
  changeval = get_delta_time() * rate;
  if (value > newval)
	{
    value -= changeval;
    if (value <= newval) {
			value = newval;
		}
  }
  else if (value < newval)
  {
    value += changeval;
    if (value >= newval) {
			value = newval;
		}
  }
	return value;
}

vec3d get_cockpit_backlight_direction() {
	vec3d
		direction;
	matrix3x3
		m1,
		m2;

	get_3d_transformation_matrix (m1, rad (0.0), rad (- 25.0), rad (0.0));
	multiply_matrix3x3_matrix3x3 (m2, m1, virtual_cockpit_inst3d->vp.attitude);

	direction.x = m2[2][0];
	direction.y = m2[2][1];
	direction.z = m2[2][2];

	return direction;
}

vec3d get_cockpit_light_direction() {
	matrix3x3
		m1,
		m2;
	vec3d
		direction;

	get_3d_transformation_matrix (m1, rad (180), rad (45), 0.0);
	multiply_matrix3x3_matrix3x3 (m2, m1, virtual_cockpit_inst3d->vp.attitude);

	direction.x = m2[2][0];
	direction.y = m2[2][1];
	direction.z = m2[2][2];

	return direction;
}

void initialise_cockpit_lights(cockpit_light_colors colors[], int count) {
	int i;
	
	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE) != DAY_SEGMENT_TYPE_DAY && !command_line_dynamics_engine_startup)
		cockpit_light_color_index[0] = (int) colors[1];
	else
		cockpit_light_color_index[0] = (int) colors[0];

	cockpit_light_color_index[1] = count;
	cockpit_light_color_array = (cockpit_light_colors *) safe_malloc (sizeof (cockpit_light_colors) * cockpit_light_color_index[1]);
	memset (cockpit_light_color_array, 0, sizeof (cockpit_light_colors) * cockpit_light_color_index[1]);
	
	for(i = 0; i < count; i++) {
		cockpit_light_color_array[i] = colors[i];
	}
}

void deinitialise_cockpit_lights() {
	safe_free(cockpit_light_color_array);

	ASSERT(sizeof(cockpit_light_color_array) != 0);

	cockpit_light_color_array = NULL;
}
