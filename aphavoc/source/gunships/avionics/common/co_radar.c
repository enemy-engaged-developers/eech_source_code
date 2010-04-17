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

#define DEBUG_MODULE								0

#define DEBUG_MODULE_BEST_TARGET_SCORING	0

#define DEBUG_MODULE_DISABLE_OBJECT_LOS	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND AND AIR RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define TERRAIN_LOS_MARKER_SCALE						(0.5)

#define TERRAIN_LOS_MARKER_LIFETIME					(3.0)

#define TERRAIN_LOS_MARKER_LARGE_STEP_3D_OBJECT	(OBJECT_3D_INTERCEPT_POINT_RED)

#define TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT	(OBJECT_3D_INTERCEPT_POINT_WHITE)

#define RADAR_RETURN_WIDTH_SAMPLE_POINTS 255
#define ZOOMED_RADAR_RETURN_WIDTH_SAMPLE_POINTS 159
#define RADAR_RETURN_DISTANCE_SAMPLE_POINTS 100
//#define RADAR_RETURN_WIDTH_SAMPLE_POINTS 51
//#define RADAR_RETURN_DISTANCE_SAMPLE_POINTS 10
#define RADAR_RETURN_CENTRE_SAMPLE_POINT_INDEX (RADAR_RETURN_WIDTH_SAMPLE_POINTS / 2)

#define RADAR_BAR_COVERAGE_ANGLE (rad(5.0))

#define ZOOMED_RADAR_RADIUS 350.0

#define GROUND_RADAR_MIN_SCAN_ANGLE rad(-45.0)
#define GROUND_RADAR_MAX_SCAN_ANGLE rad(45.0)

#define FCR_POWERUP_TIME (180.0)

#define MAX_RADAR_CONTACTS (1 << (NUM_GUNSHIP_RADAR_TARGET_INDEX_BITS - 1))

#define use_separate_radar_target_list() (get_global_avionics_realism() == AVIONICS_DETAIL_REALISTIC && get_global_gunship_type() == GUNSHIP_TYPE_APACHE)

// time before target where contact is lost is removed from the radar
#define GROUND_TARGET_LIFETIME (60.0)
#define AIR_TARGET_LIFETIME (10.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	draw_radar_sweep = FALSE,
	draw_radar_terrain_los_markers = FALSE;

radar_params
	tpm_radar,
	zoomed_radar,
	ground_radar,
	air_radar;

static radar_modes
	radar_mode;

static int
	num_tpm_profile_lines;

static float
	fcr_power_up_timer,
	tpm_clearance_height = feet_to_metres(200.0);

static radar_tpm_profile_modes
	tpm_profile_mode;

vec3d
	zoomed_radar_centre_pos,
	zoomed_radar_relative_pos;

static unsigned
	fcr_powered,
	rfi_powered,
	mma_pinned,
	auto_pan_scan_datum,
	rfi_show_hostile_only,
	radar_zoomed,
	radar_active,
	radar_terrain_sensivity;  // 0 = Auto sensivity

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* radar_elevation_mode_names[] = {
	"MAN",
	"AUTO",
	"BELOW",
	"NEAR",
	"FAR",
	"ABOVE"
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int
	radar_clutter_hatch_pattern[32] =
	{
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
		0x88888888, 0x22222222,
	};

static rgb_colour radar_return_palette[16];

static radar_contact radar_contacts[MAX_RADAR_CONTACTS];
static unsigned nradar_contacts;

static signed char terrain_radar_return[RADAR_RETURN_WIDTH_SAMPLE_POINTS][RADAR_RETURN_DISTANCE_SAMPLE_POINTS];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	float
		distance,
		elevation;

	vec3d
		position;

	unsigned
		age : 2,
		bar : 2;
} radar_profile_information;

static float profile_sample_ranges[NUM_TPM_PROFILE_LINES];
static radar_profile_information highest_elevation_in_range[RADAR_RETURN_WIDTH_SAMPLE_POINTS][NUM_TPM_PROFILE_LINES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_best_air_radar_target (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_radar_returns_pallette_colours(void)
{
	int i;
	int last_colour_index = ARRAY_LENGTH(radar_return_palette) - 1;
	rgb_colour brightest;
	float luminocity_step = (1.0 - 0.2) / ARRAY_LENGTH(radar_return_palette);
	float luminocity = 1.0 - luminocity_step;

	float sensivity = ((radar_terrain_sensivity ? radar_terrain_sensivity : 4) * 0.1) + 0.4;

	set_rgb_colour(brightest, (int)(30 * sensivity), (int)(190 * sensivity), (int)(10 * sensivity), 255);
	radar_return_palette[last_colour_index] = brightest;

	for (i = last_colour_index - 1; i >= 0 ; i--, luminocity -= luminocity_step)
	{
		radar_return_palette[i].r = (int)(brightest.r * luminocity);
		radar_return_palette[i].g = (int)(brightest.g * luminocity);
		radar_return_palette[i].b = (int)(brightest.b * luminocity);
		radar_return_palette[i].a = 255;
	}
}

unsigned get_radar_terrain_sensivity()
{
	return radar_terrain_sensivity;
}

void set_radar_terrain_sensivity(unsigned sensivity)
{
	radar_terrain_sensivity = sensivity;
	set_radar_returns_pallette_colours();
}

static void clear_terrain_return_data(void)
{
	memset(terrain_radar_return, -1, sizeof(terrain_radar_return));
	memset(highest_elevation_in_range, 0, sizeof(highest_elevation_in_range));
}

void initialise_common_radar (void)
{
	radar_active = FALSE;
	clear_terrain_return_data();
	set_radar_returns_pallette_colours();

	radar_zoomed = FALSE;
	radar_mode = RADAR_MODE_NONE;

	set_tpm_profile_mode(RADAR_TPM_PROFILE_ARITH);
	num_tpm_profile_lines = 4;
	tpm_clearance_height = feet_to_metres(200.0);

	radar_terrain_sensivity = 0;
	auto_pan_scan_datum = FALSE;
	fcr_power_up_timer = 0.0;

	memset(radar_contacts, 0, sizeof(radar_contacts));
	nradar_contacts = 0;

	if (get_global_gunship_type() == GUNSHIP_TYPE_APACHE && get_global_avionics_realism() == AVIONICS_DETAIL_REALISTIC && command_line_dynamics_engine_startup)
	{
		fcr_powered = rfi_powered = FALSE;
		mma_pinned = TRUE;
		rfi_show_hostile_only = FALSE;
	}
	else
	{
		fcr_powered = rfi_powered = TRUE;
		mma_pinned = FALSE;
		rfi_show_hostile_only = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_radar (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

radar_params* get_current_radar_params(void)
{
	if (radar_mode == RADAR_MODE_ATM)
		return &air_radar;
	else if (radar_mode == RADAR_MODE_TPM)
		return &tpm_radar;
	else if (radar_zoomed)
		return &zoomed_radar;
	else
		return &ground_radar;
}

radar_modes get_radar_mode(void)
{
	return radar_mode;
}

void set_radar_mode(radar_modes mode)
{
	if (mode != radar_mode)
	{
		radar_mode = mode;
		if (mode == RADAR_MODE_RMAP || mode == RADAR_MODE_TPM)
			clear_terrain_return_data();
	}
}

unsigned get_radar_active(void)
{
	return radar_active && fcr_powered && !mma_pinned;
}

void set_radar_active(unsigned active)
{
	radar_active = active && fcr_powered;
}

void toggle_single_scan_active(void)
{
	radar_params* radar = get_current_radar_params();

	radar_active = !radar_active && fcr_powered;

	if (radar_active)
	{
		radar->sweep_mode = RADAR_SWEEP_MODE_SINGLE;
		radar->sweep_offset = -0.5 * radar->scan_arc_size;
		radar->sweep_direction = RADAR_SWEEP_CW;
		radar->bar = 0;
	}
}

void toggle_continuous_radar_active(void)
{
	radar_params* radar = get_current_radar_params();

	radar->sweep_mode = RADAR_SWEEP_MODE_CONTINUOUS;
	radar_active = !radar_active;
}

void set_air_radar_is_active(int active)
{
	if (active && fcr_powered)
	{
		radar_mode = RADAR_MODE_ATM;
		radar_active = TRUE;
	}
	else
		radar_active = FALSE;
}

void set_ground_radar_is_active(int active)
{
	radar_mode = (active && fcr_powered) ? RADAR_MODE_GTM : RADAR_MODE_NONE;
}

void activate_common_radar (void)
{
	radar_active = fcr_powered;

	if (radar_mode == RADAR_MODE_NONE)
		radar_mode = RADAR_MODE_GTM;
}

void deactivate_common_radar (void)
{
	radar_active = FALSE;
}

void toggle_common_radar_active(void)
{
	radar_active = !radar_active && fcr_powered;

	if (radar_mode == RADAR_MODE_NONE)
	{
		ASSERT(FALSE);
		radar_mode = RADAR_MODE_GTM;
	}
}

void set_radar_zoomed(unsigned zoomed)
{
	if (radar_mode == RADAR_MODE_RMAP && zoomed != radar_zoomed)
		clear_terrain_return_data();

	if (zoomed && get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET))
		radar_zoomed = TRUE;
	else
		radar_zoomed = FALSE;
}

unsigned get_radar_zoomed(void)
{
	return radar_zoomed;
}

void rotate_radar_scan_datum(float amount)
{
	radar_params* radar = get_current_radar_params();

	amount = bound(amount, GROUND_RADAR_MIN_SCAN_ANGLE + (radar->scan_arc_size * 0.5) - radar->scan_datum, GROUND_RADAR_MAX_SCAN_ANGLE - (radar->scan_arc_size * 0.5) - radar->scan_datum);

	radar->scan_datum += amount;
	radar->sweep_offset -= amount;
}

void pan_radar_elevation(float amount)
{
	radar_params* radar = get_current_radar_params();

	amount = bound(amount, MIN_RADAR_ELEVATION_ANGLE - radar->elevation, MAX_RADAR_ELEVATION_ANGLE - radar->elevation);

	radar->elevation += amount;
}

void set_radar_elevation_mode(radar_elevations mode)
{
	get_current_radar_params()->elevation_mode = mode;
}

radar_elevations get_radar_elevation_mode(void)
{
	return get_current_radar_params()->elevation_mode;
}

const char* get_radar_elevation_mode_name(void)
{
	return radar_elevation_mode_names[get_current_radar_params()->elevation_mode];
}

void toggle_radar_auto_pan_scan_datum(void)
{
	auto_pan_scan_datum = !auto_pan_scan_datum;
}

unsigned get_radar_auto_pan_scan_datum(void)
{
	return auto_pan_scan_datum;
}

unsigned get_fcr_powered(void)
{
	return fcr_powered;
}

unsigned fcr_being_powered_up(void)
{
	return fcr_power_up_timer > 0.0;
}

void toggle_fcr_power(void)
{
	if (!fcr_powered && fcr_power_up_timer <= 0.0)
		fcr_power_up_timer = FCR_POWERUP_TIME;
	else
	{
		fcr_powered = FALSE;
		fcr_power_up_timer = 0.0;
	}
}

unsigned get_rfi_powered(void)
{
	return rfi_powered;
}

void toggle_rfi_power(void)
{
	rfi_powered = !rfi_powered;
}

unsigned get_radar_mma_pinned(void)
{
	return mma_pinned;
}

void toggle_radar_mma_pinned(void)
{
	mma_pinned = !mma_pinned;
}

unsigned get_rfi_show_hostile_only(void)
{
	return rfi_show_hostile_only;
}

void toggle_rfi_show_hostile_only(void)
{
	rfi_show_hostile_only = !rfi_show_hostile_only;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const char* tpm_profile_mode_names[] =
{
	"GEOM",
	"ARITH",
	"TEST"
};

radar_tpm_profile_modes get_tpm_profile_mode(void)
{
	return tpm_profile_mode;
}

const char* get_tpm_profile_mode_name(void)
{
	return tpm_profile_mode_names[tpm_profile_mode];
}

void set_tpm_profile_mode(radar_tpm_profile_modes mode)
{
	tpm_profile_mode = mode;

	if (mode == RADAR_TPM_PROFILE_GEOM)
	{
		profile_sample_ranges[0] = 200.0;
		profile_sample_ranges[1] = 400.0;
		profile_sample_ranges[2] = 800.0;
		profile_sample_ranges[3] = 1600.0;
		profile_sample_ranges[4] = 2500.0;
	}
	else
	{
		profile_sample_ranges[0] = 500.0;
		profile_sample_ranges[1] = 1000.0;
		profile_sample_ranges[2] = 1500.0;
		profile_sample_ranges[3] = 2000.0;
		profile_sample_ranges[4] = 2500.0;
	}
}

unsigned get_tpm_profile_lines(void)
{
	return num_tpm_profile_lines;
}

void set_tpm_profile_lines(unsigned lines)
{
	num_tpm_profile_lines = lines;
}

float get_tpm_profile_range(unsigned index)
{
	if (index < NUM_TPM_PROFILE_LINES)
		return profile_sample_ranges[index];

	return 0.0;
}

void set_tpm_clearance_height(float height)
{
	tpm_clearance_height = height;
}

float get_tpm_clearance_height(void)
{
	return tpm_clearance_height;
}

void toggle_radar_tpm_far_near_mode(void)
{
	tpm_radar.elevation_mode = (tpm_radar.elevation_mode == RADAR_ELEVATION_NEAR) ? RADAR_ELEVATION_FAR : RADAR_ELEVATION_FAR;
}

unsigned get_radar_tpm_near_mode(void)
{
	return tpm_radar.elevation_mode == RADAR_ELEVATION_NEAR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void limit_radar_sweep (radar_params *radar)
{
	float
		sweep_min_limit,
		sweep_max_limit;

	ASSERT (radar);

	if (radar->scan_arc_size != RADAR_SCAN_ARC_SIZE_360)
	{
		sweep_min_limit = radar->scan_arc_size * -0.5;

		sweep_max_limit = radar->scan_arc_size * 0.5;

		if (radar->sweep_offset < sweep_min_limit)
		{
			radar->sweep_offset = sweep_min_limit;

			radar->sweep_direction = RADAR_SWEEP_CW;

			if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE)
				radar_active = FALSE;
		}
		else if (radar->sweep_offset > sweep_max_limit)
		{
			radar->sweep_offset = sweep_max_limit;

			radar->sweep_direction = RADAR_SWEEP_CCW;

			if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE)
				radar_active = FALSE;
		}

		//
		// if single sweep inactive then ensure that the sweep offset is kept to the sweep limit (when scan arc size is increased)
		//

		if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE && !radar_active)
		{
			if (radar->sweep_offset <= rad (0.0))
			{
				radar->sweep_offset = sweep_min_limit;
			}
			else
			{
				radar->sweep_offset = sweep_max_limit;
			}
		}
	}
	else
	{
		if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE && !radar_active)
		{
			radar->sweep_offset = rad (0.0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_radar_sweep (radar_params *radar, float *cw_sweep_start_offset, float *cw_sweep_end_offset, unsigned* completed_sweep)
{
	float
		sweep_min_limit,
		sweep_max_limit;

	*completed_sweep = FALSE;

	ASSERT (radar);

	ASSERT (cw_sweep_start_offset);

	ASSERT (cw_sweep_end_offset);

//	ASSERT (radar->sweep_mode != RADAR_SWEEP_MODE_SINGLE_INACTIVE);
	ASSERT (radar_active);

	if (radar->scan_arc_size == RADAR_SCAN_ARC_SIZE_360)
	{
		if (radar->sweep_direction == RADAR_SWEEP_CW)
		{
			*cw_sweep_start_offset = radar->sweep_offset;

			if (!mma_pinned)
				radar->sweep_offset += radar->sweep_rate * radar->sweep_direction * get_delta_time ();

			if (radar->sweep_offset > rad (180.0))
			{
				radar->sweep_offset -= rad (360.0);
			}

			*cw_sweep_end_offset = radar->sweep_offset;

			if ((*cw_sweep_start_offset < rad (0.0)) && (*cw_sweep_end_offset >= rad (0.0)))
			{
				*completed_sweep = TRUE;
				if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE)
				{
					radar_active = FALSE;
					radar->sweep_offset = rad (0.0);
					*cw_sweep_end_offset = rad (0.0);
				}
			}
		}
		else
		{
			*cw_sweep_end_offset = radar->sweep_offset;

			if (!mma_pinned)
				radar->sweep_offset += radar->sweep_rate * radar->sweep_direction * get_delta_time ();

			if (radar->sweep_offset < rad (-180.0))
			{
				radar->sweep_offset += rad (360.0);
			}

			*cw_sweep_start_offset = radar->sweep_offset;

			if ((*cw_sweep_start_offset <= rad (0.0)) && (*cw_sweep_end_offset > rad (0.0)))
			{
				*completed_sweep = TRUE;
				if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE)
				{
					radar_active = FALSE;
					radar->sweep_offset = rad (0.0);
					*cw_sweep_end_offset = rad (0.0);
//					update_radar_contacts_after_full_sweep();
				}
			}
		}
	}
	else
	{
		sweep_min_limit = radar->scan_arc_size * -0.5;

		sweep_max_limit = radar->scan_arc_size * 0.5;

		if (radar->sweep_direction == RADAR_SWEEP_CW)
		{
			*cw_sweep_start_offset = radar->sweep_offset;

			if (!mma_pinned)
				radar->sweep_offset += radar->sweep_rate * radar->sweep_direction * get_delta_time ();

			if (radar->sweep_offset > sweep_max_limit)
			{
				*cw_sweep_end_offset = sweep_max_limit;

				radar->bar++;
				if (radar->bar >= radar->bar_scan)
				{
					radar->bar = 0;
//					update_radar_contacts_after_full_sweep();
					*completed_sweep = TRUE;
				}

				if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE && *completed_sweep)
				{
					radar_active = FALSE;
					radar->sweep_offset = sweep_max_limit;
				}
				else
				{
					radar->sweep_offset = sweep_max_limit - (radar->sweep_offset - sweep_max_limit);
					radar->sweep_offset = max (radar->sweep_offset, sweep_min_limit);

					if (radar->sweep_offset < *cw_sweep_start_offset)
						*cw_sweep_start_offset = radar->sweep_offset;
				}

				radar->sweep_direction = RADAR_SWEEP_CCW;
			}
			else
			{
				*cw_sweep_end_offset = radar->sweep_offset;
			}
		}
		else
		{
			*cw_sweep_end_offset = radar->sweep_offset;

			if (!mma_pinned)
				radar->sweep_offset += radar->sweep_rate * radar->sweep_direction * get_delta_time ();

			if (radar->sweep_offset < sweep_min_limit)
			{
				*cw_sweep_start_offset = sweep_min_limit;

				radar->bar++;
				if (radar->bar >= radar->bar_scan)
				{
					radar->bar = 0;
					//update_radar_contacts_after_full_sweep();
					*completed_sweep = TRUE;
				}

				if (radar->sweep_mode == RADAR_SWEEP_MODE_SINGLE && radar->bar == 0)
				{
					radar_active = FALSE;
					radar->sweep_offset = sweep_min_limit;
				}
				else
				{
					radar->sweep_offset = sweep_min_limit + (sweep_min_limit - radar->sweep_offset);
					radar->sweep_offset = min (radar->sweep_offset, sweep_max_limit);

					if (radar->sweep_offset > *cw_sweep_end_offset)
						*cw_sweep_end_offset = radar->sweep_offset;
				}

				radar->sweep_direction = RADAR_SWEEP_CW;
			}
			else
			{
				*cw_sweep_start_offset = radar->sweep_offset;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_bearing_within_cw_sweep_segment (float bearing, float cw_sweep_start_direction, float cw_sweep_end_direction)
{
	int
		result;

	if (cw_sweep_start_direction <= cw_sweep_end_direction)
	{
		result = (bearing >= cw_sweep_start_direction) && (bearing <= cw_sweep_end_direction);
	}
	else
	{
		//
		// crossed over +/-180 degs
		//

		if (bearing > 0.0)
		{
			result = bearing >= cw_sweep_start_direction;
		}
		else
		{
			result = bearing <= cw_sweep_end_direction;
		}
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LARGE_STEP_SIZE			  	((float) 200.0)
#define ONE_OVER_LARGE_STEP_SIZE	((float) 1.0 / LARGE_STEP_SIZE)

#define NUM_SMALL_STEPS				(10)
#define ONE_OVER_NUM_SMALL_STEPS	((float) 1.0 / NUM_SMALL_STEPS)

#define SMALL_STEP_SIZE			 	((float) LARGE_STEP_SIZE / NUM_SMALL_STEPS)
#define ONE_OVER_SMALL_STEP_SIZE	((float) 1.0 / SMALL_STEP_SIZE)

static int get_terrain_los_clear (vec3d *source_position, vec3d *target_position)
{
	int
		count;

	float
		dx,
		dy,
		dz,
		ddx,
		ddy,
		ddz,
		flat_range,
		step_ratio;

	vec3d
		position;

	ASSERT (source_position);

	ASSERT (target_position);

	dx = target_position->x - source_position->x;
	dy = target_position->y - source_position->y;
	dz = target_position->z - source_position->z;

	flat_range = sqrt ((dx * dx) + (dz * dz));

	if (flat_range < (LARGE_STEP_SIZE * 2.0))
	{
		////////////////////////////////////////
		//
		// short range
		//
		////////////////////////////////////////

		//
		// small steps across the entire range
		//

		convert_float_to_int (flat_range * ONE_OVER_SMALL_STEP_SIZE, &count);

		if (count == 0)
		{
			count = 1;
		}

		step_ratio = 1.0 / (float) (count + 1);

		ddx = dx * step_ratio;
		ddy = dy * step_ratio;
		ddz = dz * step_ratio;

		position = *source_position;

		while (count--)
		{
			position.x += ddx;
			position.y += ddy;
			position.z += ddz;

			if (draw_radar_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
			{
				create_rotated_debug_3d_object
				(
					&position,
					0.0,
					0.0,
					0.0,
					TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT,
					TERRAIN_LOS_MARKER_LIFETIME,
					TERRAIN_LOS_MARKER_SCALE
				);
			}

			if (point_below_ground (&position))
			{
				return (FALSE);
			}
		}
	}
	else
	{
		////////////////////////////////////////
		//
		// long range
		//
		////////////////////////////////////////

		//
		// large steps across the entire range
		//

		convert_float_to_int (flat_range * ONE_OVER_LARGE_STEP_SIZE, &count);

		if (count == 0)
		{
			count = 1;
		}

		step_ratio = 1.0 / (float) (count + 1);

		ddx = dx * step_ratio;
		ddy = dy * step_ratio;
		ddz = dz * step_ratio;

		position = *source_position;

		while (count--)
		{
			position.x += ddx;
			position.y += ddy;
			position.z += ddz;

			if (draw_radar_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
			{
				create_rotated_debug_3d_object
				(
					&position,
					0.0,
					0.0,
					0.0,
					TERRAIN_LOS_MARKER_LARGE_STEP_3D_OBJECT,
					TERRAIN_LOS_MARKER_LIFETIME,
					TERRAIN_LOS_MARKER_SCALE
				);
			}

			if (point_below_ground (&position))
			{
				return (FALSE);
			}
		}

		//
		// small steps across first large step (near source)
		//

		ddx *= ONE_OVER_NUM_SMALL_STEPS;
		ddy *= ONE_OVER_NUM_SMALL_STEPS;
		ddz *= ONE_OVER_NUM_SMALL_STEPS;

		position = *source_position;

		count = NUM_SMALL_STEPS - 1;

		while (count--)
		{
			position.x += ddx;
			position.y += ddy;
			position.z += ddz;

			if (draw_radar_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
			{
				create_rotated_debug_3d_object
				(
					&position,
					0.0,
					0.0,
					0.0,
					TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT,
					TERRAIN_LOS_MARKER_LIFETIME,
					TERRAIN_LOS_MARKER_SCALE
				);
			}

			if (point_below_ground (&position))
			{
				return (FALSE);
			}
		}

		//
		// small steps across last large step (near target)
		//

		position = *target_position;

		count = NUM_SMALL_STEPS - 1;

		while (count--)
		{
			position.x -= ddx;
			position.y -= ddy;
			position.z -= ddz;

			if (draw_radar_terrain_los_markers && (get_view_mode () == VIEW_MODE_EXTERNAL))
			{
				create_rotated_debug_3d_object
				(
					&position,
					0.0,
					0.0,
					0.0,
					TERRAIN_LOS_MARKER_SMALL_STEP_3D_OBJECT,
					TERRAIN_LOS_MARKER_LIFETIME,
					TERRAIN_LOS_MARKER_SCALE
				);
			}

			if (point_below_ground (&position))
			{
				return (FALSE);
			}
		}
	}

	return (TRUE);
}

#undef LARGE_STEP_SIZE
#undef ONE_OVER_LARGE_STEP_SIZE

#undef NUM_SMALL_STEPS
#undef ONE_OVER_NUM_SMALL_STEPS

#undef SMALL_STEP_SIZE
#undef ONE_OVER_SMALL_STEP_SIZE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE_DISABLE_OBJECT_LOS

static int get_object_los_clear (entity *target, vec3d *source_position, vec3d *target_position)
{
	return (TRUE);
}

#else

#define OBJECT_LOS_RANGE	((float) 500.0)

static int get_object_los_clear (entity *target, vec3d *source_position, vec3d *target_position)
{
	float
		dx,
		dy,
		dz,
		ddx,
		ddy,
		ddz,
		flat_range,
		ratio;

	vec3d
		position,
		intercept_point,
		face_normal;

	ASSERT (target);

	ASSERT (source_position);

	ASSERT (target_position);

	dx = target_position->x - source_position->x;
	dy = target_position->y - source_position->y;
	dz = target_position->z - source_position->z;

	flat_range = sqrt ((dx * dx) + (dz * dz));

	if (flat_range <= (OBJECT_LOS_RANGE * 2.0))
	{
		if (get_line_of_sight_collision_entity (get_gunship_entity (), target, source_position, target_position, &intercept_point, &face_normal))
		{
			return (FALSE);
		}

		if (get_line_of_sight_collision_tree (source_position, target_position, &intercept_point, &face_normal, FALSE, TRUE))
		{
			return (FALSE);
		}
	}
	else
	{
		ratio = OBJECT_LOS_RANGE / flat_range;

		ddx = dx * ratio;
		ddy = dy * ratio;
		ddz = dz * ratio;

		position.x = source_position->x + ddx;
		position.y = source_position->y + ddy;
		position.z = source_position->z + ddz;

		if (get_line_of_sight_collision_entity (get_gunship_entity (), target, source_position, &position, &intercept_point, &face_normal))
		{
			return (FALSE);
		}

		if (get_line_of_sight_collision_tree (source_position, &position, &intercept_point, &face_normal, FALSE, TRUE))
		{
			return (FALSE);
		}

		////////////////////////////////////////
		//
		// speed up ground radar around large cities - reduce LOS range at target end
		//

		position.x = target_position->x - (ddx * 0.5);
		position.y = target_position->y - (ddy * 0.5);
		position.z = target_position->z - (ddz * 0.5);

		/*
		position.x = target_position->x - ddx;
		position.y = target_position->y - ddy;
		position.z = target_position->z - ddz;
		*/

		//
		////////////////////////////////////////

		if (get_line_of_sight_collision_entity (get_gunship_entity (), target, &position, target_position, &intercept_point, &face_normal))
		{
			return (FALSE);
		}

		if (get_line_of_sight_collision_tree (&position, target_position, &intercept_point, &face_normal, FALSE, TRUE))
		{
			return (FALSE);
		}
	}

	return (TRUE);
}

#undef OBJECT_LOS_RANGE

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_gunship_target_valid_for_ground_radar (entity *target)
{
	target_types
		target_type;

	ASSERT (target);

	target_type = (target_types) get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE);

	switch (target_type)
	{
		////////////////////////////////////////
		case TARGET_TYPE_INVALID:
		////////////////////////////////////////
		{
			//
			// this implicitly ignores radar clutter
			//

			return (FALSE);

			break;
		}
		////////////////////////////////////////
		case TARGET_TYPE_HAZZARD:
		////////////////////////////////////////
		{
			return TRUE;
		}
		////////////////////////////////////////
		case TARGET_TYPE_GROUND:
		////////////////////////////////////////
		{

			// loke 030322
			// infantry should never show up on ground radar


			if (session_ground_radar_ignores_infantry)
			{
				if (get_local_entity_int_value (target, INT_TYPE_VIEW_CATEGORY) == VIEW_CATEGORY_INFANTRY)
				{
					return (FALSE);
				}
			}

			return (TRUE);

			break;
		}
		////////////////////////////////////////
		case TARGET_TYPE_AIR:
		////////////////////////////////////////
		{
			if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
			{
				//
				// allow low and slow flying aircraft
				//

				if (get_local_entity_float_value (target, FLOAT_TYPE_VELOCITY) < knots_to_metres_per_second (50.0))
				{
					if (get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) < 10.0)
					{
						return (TRUE);
					}
				}
			}
			else
			{
				if (!get_local_entity_int_value (target, INT_TYPE_INSIDE_HANGAR))
				{
					if (!get_local_entity_int_value (target, INT_TYPE_LANDED_ON_CARRIER))
					{
						return (TRUE);
					}
				}
			}

			return (FALSE);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid target type = %d", target_type);

			return (FALSE);

			break;
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_ground_radar_los_clear (entity *target, vec3d *source_position, vec3d *target_position, float dx, float dz)
{
	ASSERT (target);

	ASSERT (source_position);

	ASSERT (target_position);

	if (get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
	{
		return (TRUE);
	}

	if (get_terrain_los_clear (source_position, target_position))
	{
		////////////////////////////////////////
		//
		// speed up ground radar around large cities - ignore bridge segments
		//

		if (get_local_entity_type (target) == ENTITY_TYPE_SEGMENT)
		{
			return (TRUE);
		}

		//
		////////////////////////////////////////

		if (get_object_los_clear (target, source_position, target_position))
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_best_ground_radar_target (void)
{
	float
		score,
		best_score,
		delta_score,
		one_over_scan_range,
		scan_arc_limit,
		weapon_min_range,
		weapon_max_range,
		target_range,
		source_heading,
		dx,
		dz,
		target_bearing,
		theta;

	entity
		*source,
		*target,
		*best_target;

	vec3d
		*source_position,
		*target_position;

	entity_sub_types
		weapon_sub_type;

	//
	// clear best score and target
	//

	best_score = 0.0;

	best_target = NULL;

	//
	// source
	//

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	//
	// scan limits
	//

	one_over_scan_range = 1.0 / ground_radar.scan_range;

	scan_arc_limit = ground_radar.scan_arc_size * 0.5;

	//
	// weapon min and max ranges
	//

	weapon_sub_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		weapon_min_range = weapon_database[weapon_sub_type].min_range;

		weapon_max_range = weapon_database[weapon_sub_type].max_range;
	}
	else
	{
		weapon_min_range = FLT_MAX;

		weapon_max_range = FLT_MIN;
	}

	//
	// evaluate each target
	//

	for (target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);
		 target;
		 target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET))
	{
		////////////////////////////////////////
		//
		// keep MANDATORY checks the same as get_selectable_ground_radar_target ()
		//
		////////////////////////////////////////

		//
		// MANDATORY: valid ground radar target
		//

		if (get_gunship_target_valid_for_ground_radar (target))
		{
			//
			// MANDATORY: target matches declutter criteria
			//

			if (get_target_matches_ground_radar_declutter_criteria (target))
			{
				//
				// MANDATORY: target within scan range
				//

				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

				// arneh, 20061106 - filter away targets outside pfz for apache
				if (get_global_gunship_type() == GUNSHIP_TYPE_APACHE)
					if (!is_valid_pfz_target(target_position))
						continue;

				target_range = get_3d_range (source_position, target_position);
				if (target_range <= ground_radar.scan_range)
				{
					//
					// MANDATORY: ahead of aircraft
					//

					dx = target_position->x - source_position->x;
					dz = target_position->z - source_position->z;

					target_bearing = atan2 (dx, dz);

					theta = target_bearing - source_heading;

					if (theta > rad (180.0))
					{
						theta -= rad (360.0);
					}
					else if (theta < rad (-180.0))
					{
						theta += rad (360.0);
					}

					if ((theta >= rad (-45.0)) && (theta <= rad (45.0)))
					{
						////////////////////////////////////////
						//
						// evaluate score for target
						//
						////////////////////////////////////////

						score = 0.0;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("GROUND RADAR: evaluating %s", get_local_entity_string (target, STRING_TYPE_FULL_NAME));

						#endif

						//
						// SCORE: within radar scan arc limit
						//

						theta = target_bearing - (source_heading + ground_radar.scan_datum);

						if (theta > rad (180.0))
						{
							theta -= rad (360.0);
						}
						else if (theta < rad (-180.0))
						{
							theta += rad (360.0);
						}

						theta = fabs (theta);

						if (theta <= scan_arc_limit)
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (within radar scan arc limit, theta = %.2f, limit = %.2f)", delta_score, score, deg (theta), deg (scan_arc_limit));

						#endif

						//
						// SCORE: deviation from radar scan datum
						//

						theta = min (theta, rad (45.0f));

						delta_score = 1.0 - (theta * (1.0 / rad (45.0)));

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (deviation from radar scan datum)", delta_score, score);

						#endif

						//
						// SCORE: line of sight clear
						//

						if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (line of sight clear)", delta_score, score);

						#endif

						//
						// SCORE: target priority
						//

						switch (get_local_entity_int_value (target, INT_TYPE_TARGET_PRIORITY_TYPE))
						{
							case TARGET_PRIORITY_UNKNOWN:
							{
								delta_score = 0.0;

								break;
							}
							case TARGET_PRIORITY_LOW:
							{
								delta_score = 0.5;

								break;
							}
							case TARGET_PRIORITY_MEDIUM:
							{
								delta_score = 1.0;

								break;
							}
							case TARGET_PRIORITY_HIGH:
							{
								delta_score = 2.0;

								break;
							}
							default:
							{
								debug_fatal ("Unknown target priority type");

								break;
							}
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (target priority)", delta_score, score);

						#endif

						//
						// SCORE: targetting player
						//

						if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
						{
							if (source == get_local_entity_parent (target, LIST_TYPE_TARGET))
							{
								delta_score = 1.0;
							}
							else
							{
								delta_score = 0.0;
							}
						}
						else
						{
							delta_score = 0.0;
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (targetting player)", delta_score, score);

						#endif

						//
						// SCORE: within selected weapon range
						//

						if ((target_range >= weapon_min_range) && (target_range <= weapon_max_range))
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (within selected weapon range, min = %.2f, max = %.2f)", delta_score, score, weapon_min_range, weapon_max_range);

						#endif

						//
						// SCORE: range
						//

						delta_score = 1.0 - (target_range * one_over_scan_range);

						score += delta_score;

						#if DEBUG_MODULE_BEST_TARGET_SCORING

						debug_log ("-->delta = %.2f, score = %.2f (range = %.2f, scan range = %.2f)", delta_score, score, target_range, ground_radar.scan_range);

						#endif

						////////////////////////////////////////
						//
						// compare score with best score
						//
						////////////////////////////////////////

						if (score > best_score)
						{
							best_score = score;

							best_target = target;
						}
					}
				}
			}
		}


	}

	return (best_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_selectable_ground_radar_target (entity *target)
{
	float
		target_range,
		source_heading,
		dx,
		dz,
		target_bearing,
		theta;

	entity
		*source;

	vec3d
		*source_position,
		*target_position;

	ASSERT (target);

	////////////////////////////////////////
	//
	// keep MANDATORY checks the same as get_best_ground_radar_target ()
	//
	////////////////////////////////////////

	//
	// MANDATORY: valid ground radar target
	//

	if (get_gunship_target_valid_for_ground_radar (target))
	{
		//
		// MANDATORY: target matches declutter criteria
		//

		if (get_target_matches_ground_radar_declutter_criteria (target))
		{
			source = get_gunship_entity ();

			//
			// MANDATORY: target within scan range
			//

			source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

			target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			// arneh, 20061106 - filter away targets outside pfz for apache
			if (get_global_gunship_type() == GUNSHIP_TYPE_APACHE)
				if (!is_valid_pfz_target(target_position))
					return FALSE;

			target_range = get_3d_range (source_position, target_position);
			if (target_range <= ground_radar.scan_range)
			{
				//
				// MANDATORY: ahead of aircraft
				//

				source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

				dx = target_position->x - source_position->x;
				dz = target_position->z - source_position->z;

				target_bearing = atan2 (dx, dz);

				theta = target_bearing - source_heading;

				if (theta > rad (180.0))
				{
					theta -= rad (360.0);
				}
				else if (theta < rad (-180.0))
				{
					theta += rad (360.0);
				}

				if ((theta >= rad (-45.0)) && (theta <= rad (45.0)))
				{
					return (TRUE);
				}
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_target_matches_ground_radar_declutter_criteria (entity *target)
{
	// TODO
	ASSERT (target);

	if (ground_radar.target_priority_type == TARGET_PRIORITY_UNKNOWN)
	{
		return (TRUE);
	}
// Jabberwock 031107 Designated targets

	if (ground_radar.target_priority_type == TARGET_PRIORITY_DESIGNATED)
	{
		if (get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
		{
			return (TRUE);
		}
	}
// Jabberwock 031107 ends

	if (ground_radar.target_priority_type == get_local_entity_int_value (target, INT_TYPE_TARGET_PRIORITY_TYPE))
	{
		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_next_ground_radar_target (void)
{
	// TODO

	entity
		*current_target,
		*new_target;

	ground_radar.auto_target = FALSE;

	ground_radar.target_locked = FALSE;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target && get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET))
	{
		new_target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

		while (new_target != current_target)
		{
			if (get_selectable_ground_radar_target (new_target))
			{
				break;
			}

			new_target = get_local_entity_child_succ_circular (new_target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
	else
	{
		new_target = get_best_ground_radar_target ();
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_previous_ground_radar_target (void)
{
	// TODO

	entity
		*current_target,
		*new_target;

	ground_radar.auto_target = FALSE;

	ground_radar.target_locked = FALSE;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target && get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET))
	{
		new_target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

		while (new_target != current_target)
		{
			if (get_selectable_ground_radar_target (new_target))
			{
				break;
			}

			new_target = get_local_entity_child_pred_circular (new_target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
	else
	{
		new_target = get_best_ground_radar_target ();
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void for_all_profile_lines(profile_line_iterator_handler handler)
{
	unsigned
		num_angle_sample_points = RADAR_RETURN_WIDTH_SAMPLE_POINTS,
		sample_x;

	float
		angle,
		angle_step;

	angle = rad(-180.0) * 0.5;
	angle_step = rad(180.0) / (RADAR_RETURN_WIDTH_SAMPLE_POINTS - 1);

	if (radar_mode != RADAR_MODE_TPM || tpm_profile_mode == RADAR_TPM_PROFILE_TEST)
		return;

	for (sample_x = 0; sample_x < num_angle_sample_points; sample_x++, angle += angle_step)
	{
		unsigned profile_line;
		vec2d prev_vector, vector;

		get_2d_unit_vector_from_heading(&prev_vector, angle - angle_step);
		get_2d_unit_vector_from_heading(&vector, angle);

		for (profile_line = 0; profile_line < NUM_TPM_PROFILE_LINES; profile_line++)
		{
			if (highest_elevation_in_range[sample_x][profile_line].elevation > 0 && highest_elevation_in_range[sample_x-1][profile_line].elevation > 0)
			{
				vec2d relative_point, prev_relative_point;

				float
					distance = highest_elevation_in_range[sample_x][profile_line].distance,
					prev_distance;

				relative_point.x = distance * vector.x;
				relative_point.y = distance * vector.y;

				if (sample_x > 0
					&& highest_elevation_in_range[sample_x-1][profile_line].elevation >= 0.0
					&& highest_elevation_in_range[sample_x][profile_line].bar == highest_elevation_in_range[sample_x-1][profile_line].bar
					&& highest_elevation_in_range[sample_x][profile_line].age == highest_elevation_in_range[sample_x-1][profile_line].age)
				{
					prev_distance = highest_elevation_in_range[sample_x-1][profile_line].distance;

					if (fabs(distance - prev_distance) > 100.0 || highest_elevation_in_range[sample_x-1][profile_line].distance < 0)
						continue;

					prev_relative_point.x = prev_distance * prev_vector.x;
					prev_relative_point.y = prev_distance * prev_vector.y;

					handler(&prev_relative_point, &relative_point, &highest_elevation_in_range[sample_x-1][profile_line].position, &highest_elevation_in_range[sample_x][profile_line].position, profile_line);
				}
				else
					handler(NULL, &relative_point, NULL, &highest_elevation_in_range[sample_x][profile_line].position, profile_line);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_zoomed_radar_limits(float* min_scan_angle, float* max_scan_angle, float* min_distance, float* max_distance)
{
	vec3d near_left, near_right, far_left, far_right;

	ASSERT(radar_zoomed);
	ASSERT(min_scan_angle && max_scan_angle && min_distance && max_distance);

	near_left.x = zoomed_radar_relative_pos.x - ZOOMED_RADAR_RADIUS;
	near_left.z = zoomed_radar_relative_pos.z - ZOOMED_RADAR_RADIUS;

	near_right.x = zoomed_radar_relative_pos.x + ZOOMED_RADAR_RADIUS;
	near_right.z = zoomed_radar_relative_pos.z - ZOOMED_RADAR_RADIUS;

	far_left.x = zoomed_radar_relative_pos.x - ZOOMED_RADAR_RADIUS;
	far_left.z = zoomed_radar_relative_pos.z + ZOOMED_RADAR_RADIUS;

	far_right.x = zoomed_radar_relative_pos.x + ZOOMED_RADAR_RADIUS;
	far_right.z = zoomed_radar_relative_pos.z + ZOOMED_RADAR_RADIUS;

	if (near_left.x < 0)
		*min_scan_angle = max(atan2(near_left.x, near_left.z), GROUND_RADAR_MIN_SCAN_ANGLE);
	else
		*min_scan_angle = max(atan2(far_left.x, far_left.z), GROUND_RADAR_MIN_SCAN_ANGLE);

	if (near_right.x > 0)
		*max_scan_angle = min(atan2(near_right.x, near_right.z), GROUND_RADAR_MAX_SCAN_ANGLE);
	else
		*max_scan_angle = min(atan2(far_right.x, far_right.z), GROUND_RADAR_MAX_SCAN_ANGLE);

	*min_distance = max(50.0, (get_3d_vector_magnitude(&zoomed_radar_relative_pos) - ZOOMED_RADAR_RADIUS - 150.0));

	if (fabs(far_left.x) > fabs(far_right.x))
		*max_distance = sqrt((far_left.x * far_left.x) + (far_left.z * far_left.z));
	else
		*max_distance = sqrt((far_right.x * far_right.x) + (far_right.z * far_right.z));
}

#define TPM_TERRAIN_ABOVE_OWNSHIP_COLOUR 15
#define TPM_IN_CLEARANCE_HEIGHT_COLOUR 0
#define TPM_RADAR_SHADOW_COLOUR 7
#define TPM_TERRAIN_CLEAR_COLOUR (-1)

#define RMAP_RADAR_SHADOW_COLOUR (-1)

static void update_terrain_radar_returns(vec3d* origin, radar_params* radar, float start_sweep_angle, float end_sweep_angle)
{
	unsigned x, y, num_angle_sample_points = RADAR_RETURN_WIDTH_SAMPLE_POINTS;
	float angle, angle_step, distance, distance_step, regular_distance_step;
	float radar_min_elevation, radar_max_elevation, radar_top_elevation;
	float min_distance = 0.075 * radar->scan_range;
	terrain_3d_point_data terrain_info;

	memset (&terrain_info, 0, sizeof (terrain_3d_point_data));

	regular_distance_step = (radar->scan_range - min_distance) / RADAR_RETURN_DISTANCE_SAMPLE_POINTS;

	// get x and y step
	if (radar_zoomed && radar_mode == RADAR_MODE_RMAP)  // have to figure out area to cover when radar is zoomed
	{
		ASSERT(radar == &zoomed_radar);

		num_angle_sample_points = ZOOMED_RADAR_RETURN_WIDTH_SAMPLE_POINTS;

		//if (radar->sweep_offset == 0.0)
		{
			entity* source = get_gunship_entity();
			entity* target = get_local_entity_parent(source, LIST_TYPE_TARGET);
			vec3d* source_position = get_local_entity_vec3d_ptr(source, VEC3D_TYPE_POSITION);
			float range, min_angle, max_angle;

			// find position we're zoomed in on
			if (target)
				get_local_entity_vec3d(target, VEC3D_TYPE_POSITION, &zoomed_radar_centre_pos);

			zoomed_radar_relative_pos.x = zoomed_radar_centre_pos.x - source_position->x;
			zoomed_radar_relative_pos.y = zoomed_radar_centre_pos.y - source_position->y;
			zoomed_radar_relative_pos.z = zoomed_radar_centre_pos.z - source_position->z;

			rotate_3d_vector(&zoomed_radar_relative_pos, -current_flight_dynamics->heading.value);

			// find limits of area surrounding zoomed point
			get_zoomed_radar_limits(&min_angle, &max_angle, &radar->scan_min_range, &radar->scan_range);

			radar->scan_arc_size = max_angle - min_angle;
			radar->scan_datum = bound((max_angle + min_angle) * 0.5, rad(-45.0), rad(45.0));

			range = sqrt((zoomed_radar_relative_pos.x * zoomed_radar_relative_pos.x) + (zoomed_radar_relative_pos.z * zoomed_radar_relative_pos.z));
			radar->elevation = bound(atan2(zoomed_radar_relative_pos.y, range), MIN_RADAR_ELEVATION_ANGLE, MAX_RADAR_ELEVATION_ANGLE);
		}

		min_distance = radar->scan_min_range;
		angle = radar->scan_datum - 0.5 * radar->scan_arc_size;
		angle_step = radar->scan_arc_size / (num_angle_sample_points - 1);
		distance_step = (radar->scan_range - min_distance) / RADAR_RETURN_DISTANCE_SAMPLE_POINTS;
	}
	else
	{
		angle = rad(-180.0) * 0.5;
		angle_step = rad(180.0) / (RADAR_RETURN_WIDTH_SAMPLE_POINTS - 1);

		distance_step = regular_distance_step;
	}

	if (radar->bar_scan == 1)  // second bar is lowest
	{
		radar_min_elevation = atan(radar->elevation - 0.5 * RADAR_BAR_COVERAGE_ANGLE);
		radar_max_elevation = radar_top_elevation = atan(radar->elevation + 0.5 * RADAR_BAR_COVERAGE_ANGLE);
	}
	else if (radar->bar == 0)  // first bar is highest
	{
		radar_min_elevation = atan(radar->elevation);
		radar_max_elevation = radar_top_elevation = atan(radar->elevation + RADAR_BAR_COVERAGE_ANGLE);
	}
	else  // use entire coverage area
	{
		radar_min_elevation = atan(radar->elevation - RADAR_BAR_COVERAGE_ANGLE);
		radar_max_elevation = atan(radar->elevation);
		radar_top_elevation = atan(radar->elevation + RADAR_BAR_COVERAGE_ANGLE);
	}

	// step through all through azimuth sample points
	for (x = 0; x < num_angle_sample_points; x++, angle += angle_step)
	{
		vec3d scan_vector;
		float radar_shadow_angle = radar_min_elevation, last_elevation = -1.0;
		unsigned profile_line;

		// ... but skip if it's not in the area being scanned this frame
		if (angle < (radar->scan_datum + start_sweep_angle) || angle > (radar->scan_datum + end_sweep_angle))
			continue;

		get_3d_unit_vector_from_heading_and_pitch(&scan_vector, angle + current_flight_dynamics->heading.value, 0.0);

		// reset profile line elevations for this azimuth (if old data was from same bar)
		for (profile_line = 0; profile_line < NUM_TPM_PROFILE_LINES; profile_line++)
			if (radar->bar == highest_elevation_in_range[x][profile_line].bar)  // always replace value if it's from the same bar in previous scan
				highest_elevation_in_range[x][profile_line].elevation = -1.0;

		profile_line = 0;

		distance = regular_distance_step;

		// we don't scan the area closest to helicopter (it's too close)
		// but still need to figure out if the area shadows what's further away
		for (; distance < min_distance; distance += regular_distance_step)
		{
			float elevation, elevation_angle;

			elevation = get_3d_terrain_elevation(origin->x + scan_vector.x * distance, origin->z + scan_vector.z * distance);
			elevation_angle = (elevation - origin->y + 1.0) / distance;

			if (elevation_angle > radar_shadow_angle)
				radar_shadow_angle = elevation_angle;
		}

		distance = min_distance;

		// now start scanning sample points at regular intervals out on this azimuth
		for (y = 0; y < RADAR_RETURN_DISTANCE_SAMPLE_POINTS; y++, distance = (y + 1) * distance_step + min_distance)
		{
			vec3d rel_position, world_position;
			float elevation, elevation_angle;

			if (radar_mode == RADAR_MODE_TPM && distance > profile_sample_ranges[profile_line])
			{
				// we're in the sample area for the next profile line now
				profile_line++;
				ASSERT(profile_line < NUM_TPM_PROFILE_LINES);
			}

			// get position of this sample point
			rel_position.x = scan_vector.x * distance;
			rel_position.y = 0.0;
			rel_position.z = scan_vector.z * distance;

			world_position.x = origin->x + rel_position.x;
			world_position.y = 0.0;
			world_position.z = origin->z + rel_position.z;

			if (!point_inside_map_area(&world_position))
			{
				if (radar_mode == RADAR_MODE_TPM)
					terrain_radar_return[x][y] = TPM_RADAR_SHADOW_COLOUR;
				else
					terrain_radar_return[x][y] = RMAP_RADAR_SHADOW_COLOUR;

				break;
			}

			get_3d_terrain_point_data (world_position.x, world_position.z, &terrain_info);
			world_position.y = elevation = get_3d_terrain_point_data_elevation (&terrain_info);

			elevation_angle = (elevation - origin->y + 1.0) / distance;

			if (elevation_angle > radar_shadow_angle && elevation_angle <= radar_max_elevation)
			{
				// this point is not in radar shadow

				if (radar_mode == RADAR_MODE_TPM)
				{
					if (elevation > highest_elevation_in_range[x][profile_line].elevation)
					{
						// this is highest point for this profile line, keep it
						highest_elevation_in_range[x][profile_line].elevation = elevation;
						highest_elevation_in_range[x][profile_line].distance = distance;
						highest_elevation_in_range[x][profile_line].bar = radar->bar;
						highest_elevation_in_range[x][profile_line].age = 0;
						highest_elevation_in_range[x][profile_line].position = world_position;
					}

					// compare to clearance etc.
					if (elevation >= origin->y)
						terrain_radar_return[x][y] = TPM_TERRAIN_ABOVE_OWNSHIP_COLOUR;
					else if (elevation >= origin->y - tpm_clearance_height)
						terrain_radar_return[x][y] = TPM_IN_CLEARANCE_HEIGHT_COLOUR;
					else
						terrain_radar_return[x][y] = TPM_TERRAIN_CLEAR_COLOUR;
				}
				else
				{
					// RMAP mode, colour according to terrain type
					int colour;

					switch (get_3d_terrain_point_data_type(&terrain_info))
					{
					case TERRAIN_TYPE_RIVER:
					case TERRAIN_TYPE_RESERVOIR:
					case TERRAIN_TYPE_TRENCH:
					case TERRAIN_TYPE_SEA:
						colour = 2;
						break;
					case TERRAIN_TYPE_RIVER_BANK:
					case TERRAIN_TYPE_TRENCH_SIDE_X:
					case TERRAIN_TYPE_TRENCH_SIDE_Z:
						colour = 5;
						break;
						// Sunken features banks

					case TERRAIN_TYPE_BEACH:
						colour = 6;
						break;

					case TERRAIN_TYPE_LAND:
						colour = 8;
						break;

					case TERRAIN_TYPE_FIELD1:
					case TERRAIN_TYPE_FIELD2:
					case TERRAIN_TYPE_FIELD3:
					case TERRAIN_TYPE_FIELD4:
					case TERRAIN_TYPE_FIELD5:
					case TERRAIN_TYPE_FIELD6:
					case TERRAIN_TYPE_FIELD7:
					case TERRAIN_TYPE_FIELD8:
					case TERRAIN_TYPE_FIELD9:
					case TERRAIN_TYPE_FIELD10:
					case TERRAIN_TYPE_FIELD11:
						colour = 6;
						break;

					case TERRAIN_TYPE_ALTERED_LAND1:
					case TERRAIN_TYPE_ALTERED_LAND2:
					case TERRAIN_TYPE_ALTERED_LAND3:
						colour = 10;
						break;

					case TERRAIN_TYPE_FOREST_FLOOR:
						colour = 3;
						break;

						// Raised features banks
					case TERRAIN_TYPE_ROAD_BANK:
					case TERRAIN_TYPE_RAIL_BANK:
						colour = 12;
						break;

						// Raised features sides
					case TERRAIN_TYPE_HEDGE_SIDE_X:
					case TERRAIN_TYPE_HEDGE_SIDE_Z:
					case TERRAIN_TYPE_WALL_SIDE_X:
					case TERRAIN_TYPE_WALL_SIDE_Z:
						colour = 5;
						break;

					case TERRAIN_TYPE_FOREST_SIDE_BOTTOM_X:
					case TERRAIN_TYPE_FOREST_SIDE_BOTTOM_Z:
					case TERRAIN_TYPE_FOREST_SIDE_MID_X:
					case TERRAIN_TYPE_FOREST_SIDE_MID_Z:
					case TERRAIN_TYPE_FOREST_SIDE_TOP_X:
					case TERRAIN_TYPE_FOREST_SIDE_TOP_Z:
						colour = 3;
						break;

						// Raised features tops
					case TERRAIN_TYPE_BUILT_UP_AREA1:
					case TERRAIN_TYPE_BUILT_UP_AREA2:
					case TERRAIN_TYPE_BUILT_UP_AREA3:
					case TERRAIN_TYPE_BUILT_UP_AREA4:
						colour = 9;
						break;

					case TERRAIN_TYPE_ROAD:
					case TERRAIN_TYPE_TRACK:
					case TERRAIN_TYPE_RAIL:
						colour = 13;
						break;
					case TERRAIN_TYPE_WALL_TOP:
					case TERRAIN_TYPE_HEDGE_TOP:
						colour = 10;
						break;

					case TERRAIN_TYPE_FOREST_TOP:
						colour = 3;
						break;
					}

					// shade according to incline
					if (y > 0)
					{
						if (elevation - last_elevation > distance_step * 0.10)
							colour += 4;
						else if (elevation - last_elevation > distance_step * 0.05)
							colour += 3;
						else if (elevation - last_elevation > distance_step * 0.02)
							colour += 1;
						else if (elevation - last_elevation > distance_step * 0.01)
							colour += 1;

						else if (last_elevation - elevation > distance_step * 0.10)
							colour -= 4;
						else if (last_elevation - elevation > distance_step * 0.05)
							colour -= 3;
						else if (last_elevation - elevation > distance_step * 0.02)
							colour -= 2;
						else if (last_elevation - elevation > distance_step * 0.01)
							colour -= 1;
					}

					if (colour < 0)
						colour = 0;
					else if (colour >= ARRAY_LENGTH(radar_return_palette))
						colour = ARRAY_LENGTH(radar_return_palette) - 1;

					terrain_radar_return[x][y] = colour;
				}
			}
			else if (radar->bar == 1)  // scan is complete
			{
				// ... and we got no returns
				if (elevation_angle < radar_shadow_angle
					|| elevation_angle > radar_top_elevation)
				{
					if (radar_mode == RADAR_MODE_TPM)
						terrain_radar_return[x][y] = TPM_RADAR_SHADOW_COLOUR;
					else
						terrain_radar_return[x][y] = RMAP_RADAR_SHADOW_COLOUR;
				}
			}

			if (elevation_angle > radar_shadow_angle)
				radar_shadow_angle = elevation_angle;
			last_elevation = elevation;
		}
	}
}

// ugly hack, but we need these values in the draw_radar_profile_lines function
float draw_scale, draw_centre_y;

static void draw_radar_profile_lines(vec2d* prev_vector, vec2d* vector, vec3d* prev_abs_pos, vec3d* abs_pos, unsigned profile_line)
{
	float
		x1,
		x2,
		y1,
		y2;

	if (!prev_vector)
		return;

	x1 = prev_vector->x * draw_scale;
	y1 = draw_centre_y + prev_vector->y * draw_scale;

	x2 = vector->x * draw_scale;
	y2 = draw_centre_y + vector->y * draw_scale;

	draw_2d_half_thick_line(x1, y1, x2, y2, radar_return_palette[7]);
}

void draw_terrain_radar_returns(vec3d* origin, float centre_y, float scale)
{
	radar_params* radar = get_current_radar_params();
	float min_distance = 0.075 * radar->scan_range;

	int sample_x;
	int low_y, hi_y;

	float angle, angle_step, distance, distance_step;
	float sweep_min_limit = radar->scan_arc_size * -0.5 + radar->scan_datum;
	float sweep_max_limit = radar->scan_arc_size * 0.5 + radar->scan_datum;

	unsigned num_angle_sample_points = RADAR_RETURN_WIDTH_SAMPLE_POINTS;

	if (radar_zoomed && radar_mode == RADAR_MODE_RMAP)
	{
		num_angle_sample_points = ZOOMED_RADAR_RETURN_WIDTH_SAMPLE_POINTS;
		angle = radar->scan_datum - 0.5 * radar->scan_arc_size;

		angle_step = radar->scan_arc_size / (num_angle_sample_points - 1);
		distance_step = (radar->scan_range - radar->scan_min_range) / RADAR_RETURN_DISTANCE_SAMPLE_POINTS;
		min_distance = radar->scan_min_range;
	}
	else
	{
		angle = rad(-180.0) * 0.5;
		angle_step = rad(180.0) / (RADAR_RETURN_WIDTH_SAMPLE_POINTS - 1);

		distance_step = (radar->scan_range - min_distance) / RADAR_RETURN_DISTANCE_SAMPLE_POINTS;;
	}

	// draw terrain returns in sector
	for (sample_x = 0; sample_x < num_angle_sample_points; sample_x++, angle += angle_step)
	{
		vec3d scan_vector_min, scan_vector_max;

		distance = min_distance;

		// vector for each side of this slice
		get_3d_unit_vector_from_heading_and_pitch(&scan_vector_min, max(angle - 0.5 * angle_step, sweep_min_limit), 0.0);
		get_3d_unit_vector_from_heading_and_pitch(&scan_vector_max, min(angle + 0.5 * angle_step, sweep_max_limit), 0.0);

		low_y = 0;
		hi_y = low_y + 1;
		while (hi_y <= RADAR_RETURN_DISTANCE_SAMPLE_POINTS)
		{
			float x1, x2, x3, x4, y1, y2, y3, y4;
			float start_distance, end_distance;
			int index = terrain_radar_return[sample_x][low_y];

			// find how far we have the same colour
			while (hi_y < RADAR_RETURN_DISTANCE_SAMPLE_POINTS && terrain_radar_return[sample_x][hi_y] == index)
				hi_y++;

			if (index >= 0)
			{
				// draw slice from low to hi
				start_distance = (low_y) * distance_step + min_distance;
				end_distance = (hi_y) * distance_step + min_distance;

				x1 = scan_vector_min.x * start_distance * scale;
				y1 = centre_y + scan_vector_min.z * start_distance * scale;

				x2 = scan_vector_max.x * start_distance * scale;
				y2 = centre_y + scan_vector_max.z * start_distance * scale;

				x3 = scan_vector_min.x * end_distance * scale;
				y3 = centre_y + scan_vector_min.z * end_distance * scale;

				x4 = scan_vector_max.x * end_distance * scale;
				y4 = centre_y + scan_vector_max.z * end_distance * scale;

				if (radar_zoomed && radar_mode == RADAR_MODE_RMAP)
				{
					x1 -= zoomed_radar_relative_pos.x * scale;
					y1 -= zoomed_radar_relative_pos.z * scale;
					x2 -= zoomed_radar_relative_pos.x * scale;
					y2 -= zoomed_radar_relative_pos.z * scale;
					x3 -= zoomed_radar_relative_pos.x * scale;
					y3 -= zoomed_radar_relative_pos.z * scale;
					x4 -= zoomed_radar_relative_pos.x * scale;
					y4 -= zoomed_radar_relative_pos.z * scale;
				}

				draw_2d_filled_triangle(x1, y1, x3, y3, x2, y2, radar_return_palette[index]);
				draw_2d_filled_triangle(x2, y2, x3, y3, x4, y4, radar_return_palette[index]);
			}

			low_y = hi_y;
			hi_y++;
		}

	}

	draw_scale = scale;
	draw_centre_y = centre_y;
	if (radar_mode == RADAR_MODE_TPM)
		for_all_profile_lines(draw_radar_profile_lines);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_radar_target(entity* target, vec3d* absolute_position, vec3d* relative_position)
{
	if (use_separate_radar_target_list() && debug_var_x <= 0)
	{
		int index = get_local_entity_int_value(target, INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX);

		ASSERT(index > 0 && index < ARRAY_LENGTH(radar_contacts));
		ASSERT(radar_contacts[index].en == target);

		radar_contacts[index].previous_position = radar_contacts[index].last_position;
		radar_contacts[index].last_position = *absolute_position;
		radar_contacts[index].display_position.x = relative_position->x;
		radar_contacts[index].display_position.y = relative_position->z;
		get_local_entity_vec3d(target, VEC3D_TYPE_MOTION_VECTOR, &radar_contacts[index].velocity);

		radar_contacts[index].age = 0;
		radar_contacts[index].last_contact = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
	}
	else
	{
		if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
		{
			set_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR, TRUE);
			set_local_entity_float_value (target, FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT, AIR_RADAR_CONTACT_TIMEOUT);
		}
		else
		{
			delete_local_entity_from_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
}

void add_new_radar_target(entity* target, vec3d* absolute_position, vec3d* relative_position)
{
	if (use_separate_radar_target_list())
	{
		ASSERT(!get_local_entity_int_value(target, INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX));
		if (nradar_contacts < ARRAY_LENGTH(radar_contacts) - 1)  // TODO: remove lowest pri or oldest target if not room
		{
			nradar_contacts++;

			radar_contacts[nradar_contacts].en = target;

			radar_contacts[nradar_contacts].last_position = radar_contacts[nradar_contacts].previous_position = *absolute_position;
			radar_contacts[nradar_contacts].display_position.x = relative_position->x;
			radar_contacts[nradar_contacts].display_position.y = relative_position->z;
			get_local_entity_vec3d(target, VEC3D_TYPE_MOTION_VECTOR, &radar_contacts[nradar_contacts].velocity);

			radar_contacts[nradar_contacts].priority = 0;  // TODO
			radar_contacts[nradar_contacts].age = 0;
			radar_contacts[nradar_contacts].last_contact = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

			set_local_entity_int_value(target, INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX, nradar_contacts);
		}
	}
	else
		insert_local_entity_into_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET, get_gunship_entity(), NULL);
}

void update_radar_contacts_after_full_sweep()
{
	unsigned
		nremoved = 0,
		i;

	float
		current_time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);


	radar_params* radar = get_current_radar_params();

	// clean up contact list, removing old targets etc.
	for (i = 1; i <= nradar_contacts; i++)
	{
		int
			remove_contact = FALSE,
			is_airborne_target = get_local_entity_int_value(radar_contacts[i].en, INT_TYPE_AIRBORNE_AIRCRAFT);

		float
			lifetime = is_airborne_target ? AIR_TARGET_LIFETIME : GROUND_TARGET_LIFETIME;

		if (current_time - radar_contacts[i].last_contact > lifetime)  // no contact for some time
			remove_contact = TRUE;
		else if (!valid_target_for_radar_mode(radar_contacts[i].en, TRUE))
			remove_contact = TRUE;
		else if (radar_contacts[i].age)  // no contact this sweep
		{
			vec3d
				*gunship_position = get_local_entity_vec3d_ptr(get_gunship_entity(), VEC3D_TYPE_POSITION);

			float
				dx, dy,
				bearing;

			dx = radar_contacts[i].last_position.x - gunship_position->x;
			dy = radar_contacts[i].last_position.z - gunship_position->z;

			bearing = atan2(dx, dy);

			// remove if outside of sweep sector
			if (!check_bearing_within_cw_sweep_segment(bearing, radar->scan_datum - radar->scan_arc_size * 0.5, radar->scan_datum + radar->scan_arc_size * 0.5))
				remove_contact = TRUE;
		}

		if (remove_contact)
		{
			set_local_entity_int_value(radar_contacts[i].en, INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX, 0);

			debug_log("remove: %s [%d]: lifetime: %.1f, age: %d", get_sub_type_name(radar_contacts[i].en), i, current_time - radar_contacts[i].last_contact, radar_contacts[i].age);

			nremoved++;
			continue;
		}

//		debug_log("after sweep: %s [%d]: bearing: %.1f, min sweep: %.1f max sweep: %.1f, age: %d", get_sub_type_name(radar_contacts[i].en), i, deg(bearing), deg(radar->scan_datum - radar->scan_arc_size * 0.5), deg(radar->scan_datum + radar->scan_arc_size * 0.5), radar_contacts[i].age);

		// increase age
		if (radar_contacts[i].age < 8)
			radar_contacts[i].age++;

		// move up contacts to fill space left by removed contacts
		if (nremoved)
		{
			int new_index = i - nremoved;
			radar_contacts[new_index] = radar_contacts[i];
			set_local_entity_int_value(radar_contacts[i].en, INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX, new_index);
		}
	}

	nradar_contacts -= nremoved;
}

radar_contact* get_radar_contacts(unsigned* ncontacts)
{
	*ncontacts = nradar_contacts;
	if (nradar_contacts > 0)
		return &radar_contacts[1];  // index 0 is empty
	else
		return NULL;
}

radar_contact* get_radar_contact_from_entity(entity* en)
{
	unsigned index = get_local_entity_int_value(en, INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX);

	if (index)
		return &radar_contacts[index];
	else
		return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int valid_target_for_radar_mode(entity* target, int strict)
{
	switch (radar_mode)
	{
	case RADAR_MODE_ATM:
		if (strict)
		{
			if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
				if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
					if (get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) > 5.0)
						return (TRUE);

			return FALSE;
		}
		else
			return get_local_entity_int_value(target, INT_TYPE_TARGET_TYPE) == TARGET_TYPE_AIR;
	default:
		if (strict)
		{
			if (get_local_entity_int_value (target, INT_TYPE_ALIVE))
			{
				target_types target_type = get_local_entity_int_value (target, INT_TYPE_TARGET_TYPE);

				switch (target_type)
				{
					case TARGET_TYPE_INVALID:
						return (get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER));

					case TARGET_TYPE_GROUND:
						if (radar_mode != RADAR_MODE_TPM)
							return TRUE;
						else
						{
							target_symbol_types symbol = get_local_entity_int_value(target, INT_TYPE_TARGET_SYMBOL_TYPE);

							return symbol == TARGET_SYMBOL_HAZZARD || symbol == TARGET_SYMBOL_STRUCTURE;
						}

					case TARGET_TYPE_HAZZARD:
						return TRUE;

					case TARGET_TYPE_AIR:
						if (!use_separate_radar_target_list() && get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
						{
							//
							// allow low and slow flying aircraft
							//

							if (get_local_entity_float_value (target, FLOAT_TYPE_VELOCITY) < knots_to_metres_per_second (50.0))
							{
								if (get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) < 10.0)
									return TRUE;
							}
						}
						else if (!get_local_entity_int_value (target, INT_TYPE_INSIDE_HANGAR))
							if (!get_local_entity_int_value (target, INT_TYPE_LANDED_ON_CARRIER))
								return (TRUE);

						return FALSE;

					default:
						debug_fatal ("Invalid target type = %d", target_type);
						return FALSE;
				}
			}
		}
		else  // not strict
			return (get_local_entity_int_value(target, INT_TYPE_TARGET_TYPE) != TARGET_TYPE_INVALID) || get_local_entity_int_value(target, INT_TYPE_GROUND_RADAR_CLUTTER);
	}

	return FALSE;
}

void update_common_radar (int inactive_check)
{
	int
		x_sec,
		z_sec,
		x_sec_min,
		z_sec_min,
		x_sec_max,
		z_sec_max;

	float
		cw_sweep_start_offset,
		cw_sweep_end_offset,
		cw_sweep_start_direction,
		cw_sweep_end_direction,
		heading,
		x_min,
		z_min,
		x_max,
		z_max,
		radar_stealth_factor,
		sqr_scan_range,
		sqr_target_range;

	entity
		*source,
		*target,
		*old_target,
		*new_target = NULL,
		*sector;

	vec3d
		*source_position,
		*target_position,
		cw_sweep_start_position,
		cw_sweep_end_position;

	radar_params* radar = get_current_radar_params();

	if (radar_mode == RADAR_MODE_TPM)
	{
		// TPM automaticly switches scan size depending on speed
		if (current_flight_dynamics->velocity_z.value > knots_to_metres_per_second(55.0))
			radar->scan_arc_size = rad(90.0);
		else if (current_flight_dynamics->velocity_z.value < knots_to_metres_per_second(45.0))
			radar->scan_arc_size = rad(180.0);
	}

	if (fcr_power_up_timer > 0.0)
	{
		fcr_power_up_timer -= get_delta_time();

		if (fcr_power_up_timer <= 0.0)
		{
			fcr_powered = TRUE;
			if (fcr_powered && get_global_gunship_type() == GUNSHIP_TYPE_APACHE)
				add_apache_advisory("FCR POWERED");
		}
	}

	////////////////////////////////////////
	//
	// get source data
	//
	////////////////////////////////////////

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	////////////////////////////////////////
	//
	// get radar sweep start and end
	//
	////////////////////////////////////////

	if ((radar_active && get_fcr_powered())
		|| inactive_check)
	{
		unsigned completed_sweep;

		update_radar_sweep (radar, &cw_sweep_start_offset, &cw_sweep_end_offset, &completed_sweep);

		update_terrain_radar_returns(source_position, radar, cw_sweep_start_offset, cw_sweep_end_offset);

		//
		// note: it is possible for sweep_mode to have switched to RADAR_SWEEP_MODE_SINGLE_INACTIVE after update_radar_sweep
		//

		heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

		cw_sweep_start_direction = heading + radar->scan_datum + cw_sweep_start_offset;
		if (cw_sweep_start_direction > rad (180.0))
			cw_sweep_start_direction -= rad (360.0);
		else if (cw_sweep_start_direction < rad (-180.0))
			cw_sweep_start_direction += rad (360.0);

		cw_sweep_end_direction = heading + radar->scan_datum + cw_sweep_end_offset;
		if (cw_sweep_end_direction > rad (180.0))
			cw_sweep_end_direction -= rad (360.0);
		else if (cw_sweep_end_direction < rad (-180.0))
			cw_sweep_end_direction += rad (360.0);

		////////////////////////////////////////
		//
		// get sector scan area
		//
		////////////////////////////////////////

		cw_sweep_start_position.x = source_position->x + (sin (cw_sweep_start_direction) * radar->scan_range);
		cw_sweep_start_position.y = source_position->y;
		cw_sweep_start_position.z = source_position->z + (cos (cw_sweep_start_direction) * radar->scan_range);

		cw_sweep_end_position.x = source_position->x + (sin (cw_sweep_end_direction) * radar->scan_range);
		cw_sweep_end_position.y = source_position->y;
		cw_sweep_end_position.z = source_position->z + (cos (cw_sweep_end_direction) * radar->scan_range);

		//
		// draw sweep
		//

		if (draw_radar_sweep && (get_view_mode () == VIEW_MODE_EXTERNAL))
		{
			create_debug_3d_line (source_position, &cw_sweep_start_position, sys_col_green, 0.0);
			create_debug_3d_line (source_position, &cw_sweep_end_position, sys_col_red, 0.0);
			create_debug_3d_line (&cw_sweep_start_position, &cw_sweep_end_position, sys_col_white, 0.0);
		}

		//
		// sector scan min
		//

		x_min = min (min (cw_sweep_start_position.x, cw_sweep_end_position.x), source_position->x);
		z_min = min (min (cw_sweep_start_position.z, cw_sweep_end_position.z), source_position->z);

		get_x_sector (x_sec_min, x_min);
		get_z_sector (z_sec_min, z_min);

		x_sec_min = max (x_sec_min, MIN_MAP_X_SECTOR);
		z_sec_min = max (z_sec_min, MIN_MAP_Z_SECTOR);

		//
		// sector scan max
		//

		x_max = max (max (cw_sweep_start_position.x, cw_sweep_end_position.x), source_position->x);
		z_max = max (max (cw_sweep_start_position.z, cw_sweep_end_position.z), source_position->z);

		get_x_sector (x_sec_max, x_max);
		get_z_sector (z_sec_max, z_max);

		x_sec_max = min (x_sec_max, MAX_MAP_X_SECTOR);
		z_sec_max = min (z_sec_max, MAX_MAP_Z_SECTOR);

		////////////////////////////////////////
		//
		// sector scan
		//
		////////////////////////////////////////

		sqr_scan_range = radar->scan_range * radar->scan_range;

		for (z_sec = z_sec_min; z_sec <= z_sec_max; z_sec++)
		{
			for (x_sec = x_sec_min; x_sec <= x_sec_max; x_sec++)
			{
				sector = get_local_raw_sector_entity (x_sec, z_sec);

				for (target = get_local_entity_first_child (sector, LIST_TYPE_SECTOR);
					 target;
					 target = get_local_entity_child_succ (target, LIST_TYPE_SECTOR))
				{
					if (valid_target_for_radar_mode(target, FALSE))
					{
						int
							known_target = FALSE,
							is_airborne_target = get_local_entity_int_value(target, INT_TYPE_TARGET_TYPE) == TARGET_TYPE_AIR;

						if (use_separate_radar_target_list())
							known_target = get_local_entity_int_value(target, INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX);
						else
							known_target = get_local_entity_parent(target, LIST_TYPE_GUNSHIP_TARGET) != NULL;

						if (known_target || ((target != source) && valid_target_for_radar_mode(target, TRUE)))
						{
// TODO: re-enable this code if needed.  possibly only for unrealistic mode, where scan heights are not as narrow?
#if 0
							//
							// reduce number of los checks by only considering 'even' entities on CW sweep and 'odd' entities on CCW sweep
							//

							if (radar->sweep_mode == RADAR_SWEEP_MODE_CONTINUOUS)
							{
								if (get_local_entity_index (target) & 1)
								{
									sweep_direction = RADAR_SWEEP_CCW;
								}
								else
								{
									sweep_direction = RADAR_SWEEP_CW;
								}
							}
							else
							{
								//
								// sweep all targets in single sweep mode
								//

								sweep_direction = radar->sweep_direction;
							}
							if (radar->sweep_direction == sweep_direction && !inactive_check)
#endif
							{
								// only update target info if the target is within range, sweep segment and los is clear
								target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
								sqr_target_range = get_sqr_3d_range (source_position, target_position);

								radar_stealth_factor = get_local_entity_float_value (target, FLOAT_TYPE_RADAR_STEALTH_FACTOR);
								if (radar_stealth_factor < NO_RADAR_STEALTH_FACTOR)
									sqr_target_range /= radar_stealth_factor * radar_stealth_factor;

								if (sqr_target_range <= sqr_scan_range)
								{
									vec3d relative_position, target_vector;
									float bearing, pitch;

									relative_position.x = target_position->x - source_position->x;
									relative_position.y = target_position->y - source_position->y;
									relative_position.z = target_position->z - source_position->z;

									target_vector = relative_position;
									normalise_any_3d_vector(&target_vector);

									//bearing = atan2(relative_position.x, relative_position.y);

									get_heading_and_pitch_from_3d_unit_vector(&target_vector, &bearing, &pitch);

									if (check_bearing_within_cw_sweep_segment (bearing, cw_sweep_start_direction, cw_sweep_end_direction) &&
										(!use_separate_radar_target_list() ||
										 (pitch >= radar->elevation - 0.5 * RADAR_BAR_COVERAGE_ANGLE &&
										  pitch <= radar->elevation + 0.5 * RADAR_BAR_COVERAGE_ANGLE)))
									{
										int los_clear = FALSE;

										if (is_airborne_target)
											los_clear = get_los_clear (target, source_position, target_position);
										else
											los_clear = get_ground_radar_los_clear (target, source_position, target_position, relative_position.x, relative_position.y);

										if (los_clear)
										{
											rotate_3d_vector(&relative_position, -current_flight_dynamics->heading.value);

											if (known_target)  // old target, update it
												update_radar_target(target, target_position, &relative_position);
											else // new target - add it
												add_new_radar_target(target, target_position, &relative_position);
										}
										else if (known_target)
											set_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR, FALSE);
									}
								}
							}
						}
					}
				}
			}
		}

		if (completed_sweep)
		{
			unsigned x;
			update_radar_contacts_after_full_sweep();

			for (x = 0; x < RADAR_RETURN_WIDTH_SAMPLE_POINTS; x++)
			{
				unsigned profile_line;
				for (profile_line = 0; profile_line < NUM_TPM_PROFILE_LINES; profile_line++)
					highest_elevation_in_range[x][profile_line].age = 1;
			}
		}
	}


// TODO: check if we should only do this for some acquisition systems
//	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
	{
		////////////////////////////////////////
		//
		// update target
		//
		////////////////////////////////////////

		int select_new_target = FALSE;

		old_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

		new_target = old_target;

		if (radar->auto_target && !radar->target_locked)
			select_new_target = TRUE;
		else
		{
			if (old_target)
			{
				if (get_local_entity_parent (old_target, LIST_TYPE_GUNSHIP_TARGET))
				{
					// check if target is no longer valid
					if (radar_mode == RADAR_MODE_ATM)
						select_new_target = !get_selectable_air_radar_target(old_target);
					else
						select_new_target = !get_selectable_ground_radar_target (old_target);
				}
				else // target is no longer on the radar
					select_new_target = TRUE;
			}
			else // no target
				select_new_target = TRUE;
		}

		if (select_new_target)
		{
			// TODO: new tgt selection algorithm for realistic radar - only select target after each full sweep
			if (radar_mode == RADAR_MODE_ATM)
				new_target = get_best_air_radar_target ();
			else
				new_target = get_best_ground_radar_target ();

			set_gunship_target (new_target);
		}

		if (radar->target_locked)
		{
			if ((new_target != old_target) || (new_target == NULL))
				radar->target_locked = FALSE;
		}
	}

	if (get_global_avionics_realism() == AVIONICS_DETAIL_REALISTIC)
	{
		if (radar_mode == RADAR_MODE_TPM)
			radar->elevation = (radar->elevation_mode == RADAR_ELEVATION_NEAR) ? atan(rad(-3.0)) : 0.0;
		else if (auto_pan_scan_datum)
		{
			unsigned do_pan = FALSE;
			float scan_to = 0.0, elevation_to = 0.0;

			switch (target_acquisition_system)
			{
			case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
			case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
				{
	//				entity* target = get_local_entity_parent(source, LIST_TYPE_TARGET);

					if (new_target)
					{
						vec3d* position = get_local_entity_vec3d_ptr(new_target, VEC3D_TYPE_POSITION);
						vec3d relative_position;

						relative_position.x = position->x - source_position->x;
						relative_position.y = position->y - source_position->y;
						relative_position.z = position->z - source_position->z;

						normalise_3d_vector(&relative_position);
	//					debug_log("target: %x, source: %.0f, %.0f;  target: %.0f, %.0f", target, source_position->x, source_position->z, position->x, position->z);
	//					debug_log("x: %.0f, y: %.0f, z: %.0f", relative_position.x, relative_position.y, relative_position.z);

						get_heading_and_pitch_from_3d_unit_vector(&relative_position, &scan_to, &elevation_to);
						scan_to -= current_flight_dynamics->heading.value;
						if (scan_to <= rad(-180.0))
							scan_to += rad(360.0);
						else if (scan_to > rad(180.0))
							scan_to -= rad(360.0);
	//					scan_to = atan2 (relative_position.x, relative_position.z) - current_flight_dynamics->heading.value;
	//					elevation_to = atan2(relative_position.y, relative_position.z);
						do_pan = TRUE;
					}

					break;
				}
			case TARGET_ACQUISITION_SYSTEM_FLIR:				// forward looking infra-red
			case TARGET_ACQUISITION_SYSTEM_DTV:				// daytime TV
			case TARGET_ACQUISITION_SYSTEM_DVO:				// direct view optics
			case TARGET_ACQUISITION_SYSTEM_LLLTV:				// low light level TV
			case TARGET_ACQUISITION_SYSTEM_PERISCOPE:		// periscope
				get_eo_azimuth_and_elevation(&scan_to, &elevation_to);
				do_pan = TRUE;
				break;
			case TARGET_ACQUISITION_SYSTEM_IHADSS:			// integrated helmet and display sighting system
			case TARGET_ACQUISITION_SYSTEM_HIDSS:				// helmet integrated display sight system
			case TARGET_ACQUISITION_SYSTEM_HMS:				// helmet mounted sight
				scan_to = -pilot_head_heading;
				elevation_to = pilot_head_pitch;
				do_pan = TRUE;
				break;
			}

			if (do_pan)
			{
				rotate_radar_scan_datum(scan_to - radar->scan_datum);
				pan_radar_elevation(elevation_to - radar->elevation);
			}
		}
		else
		{
			switch (radar->elevation_mode)
			{
			case RADAR_ELEVATION_AUTO:
				// TODO
			case RADAR_ELEVATION_MANUAL:
				// let pilot control elevation angle manually, don't override
				break;
			case RADAR_ELEVATION_BELOW:
				radar->elevation = atan(rad(-6.0));
				break;
			case RADAR_ELEVATION_NEAR:
				radar->elevation = atan(rad(-3.0));
				break;
			case RADAR_ELEVATION_FAR:
				radar->elevation = atan(rad(0.0));
				break;
			case RADAR_ELEVATION_ABOVE:
				radar->elevation = atan(rad(3.0));
				break;
			}
		}
	}

	if (!new_target)
		radar_zoomed = FALSE;

	target_locked = radar->target_locked;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_common_ground_radar (void)
{
	radar_active = TRUE;

/*
	if (ground_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
	{
		ground_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_ACTIVE;
	}
*/
	radar_mode = RADAR_MODE_GTM;

	ground_radar.target_locked = target_locked;
}

void toggle_ground_radar_active(void)
{
	if (radar_mode == RADAR_MODE_GTM && radar_active)
		deactivate_common_ground_radar();
	else
		activate_common_ground_radar();
}

unsigned ground_radar_is_active(void)
{
	return radar_mode == RADAR_MODE_GTM && radar_active;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_common_ground_radar (void)
{
	radar_active = FALSE;
//	radar_mode = RADAR_MODE_NONE;

	ground_radar.target_locked = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AIR RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_gunship_target_valid_for_air_radar (entity *target)
{
	ASSERT (target);

	if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
	{
		if (get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE) > 5.0)
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_los_clear (entity *target, vec3d *source_position, vec3d *target_position)
{
//	ASSERT (target);

	ASSERT (source_position);

	ASSERT (target_position);

	if (get_terrain_los_clear (source_position, target_position))
	{
		if (!target)
			return TRUE;

		if (get_object_los_clear (target, source_position, target_position))
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_best_air_radar_target (void)
{
	float
		score,
		best_score,
		delta_score,
		one_over_scan_range,
		scan_arc_limit,
		weapon_min_range,
		weapon_max_range,
		target_range,
		source_heading,
		target_heading,
		dx,
		dz,
		source_bearing,
		target_bearing,
		theta;

	entity
		*source,
		*target,
		*best_target;

	entity_sides
		source_side;

	vec3d
		*source_position,
		*target_position;

	entity_sub_types
		weapon_sub_type;

	//
	// clear best score and target
	//

	best_score = 0.0;

	best_target = NULL;

	//
	// source
	//

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	//
	// scan limits
	//

	one_over_scan_range = 1.0 / air_radar.scan_range;

	scan_arc_limit = air_radar.scan_arc_size * 0.5;

	//
	// weapon min and max ranges
	//

	weapon_sub_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		weapon_min_range = weapon_database[weapon_sub_type].min_range;

		weapon_max_range = weapon_database[weapon_sub_type].max_range;
	}
	else
	{
		weapon_min_range = FLT_MAX;

		weapon_max_range = FLT_MIN;
	}

	//
	// evaluate each target
	//

	target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

	while (target)
	{
		////////////////////////////////////////
		//
		// keep MANDATORY checks the same as get_selectable_air_radar_target ()
		//
		////////////////////////////////////////

		// TODO
		if (get_gunship_target_valid_for_air_radar (target))
		{
			//
			// MANDATORY: target matches declutter criteria
			//

			if (get_target_matches_air_radar_declutter_criteria (target, source_side))
			{
				//
				// MANDATORY: target within scan range
				//

				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

				target_range = get_3d_range (source_position, target_position);

				if (target_range <= air_radar.scan_range)
				{
					////////////////////////////////////////
					//
					// evaluate score for target
					//
					////////////////////////////////////////

					score = 0.0;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("AIR RADAR: evaluating %s", get_local_entity_string (target, STRING_TYPE_FULL_NAME));

					#endif

					//
					// SCORE: within radar scan arc limit
					//

					dx = target_position->x - source_position->x;
					dz = target_position->z - source_position->z;

					target_bearing = atan2 (dx, dz);

					if (air_radar.scan_arc_size == RADAR_SCAN_ARC_SIZE_360)
					{
						theta = target_bearing - source_heading;

						if (theta > rad (180.0))
						{
							theta -= rad (360.0);
						}
						else if (theta < rad (-180.0))
						{
							theta += rad (360.0);
						}

						theta = fabs (theta);

						delta_score = 1.0;
					}
					else
					{
						theta = target_bearing - (source_heading + air_radar.scan_datum);

						if (theta > rad (180.0))
						{
							theta -= rad (360.0);
						}
						else if (theta < rad (-180.0))
						{
							theta += rad (360.0);
						}

						theta = fabs (theta);

						if (theta <= scan_arc_limit)
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (within radar scan arc limit, theta = %.2f, limit = %.2f)", delta_score, score, deg (theta), deg (scan_arc_limit));

					#endif

					//
					// SCORE: deviation from radar scan datum
					//

					delta_score = 1.0 - (theta * (1.0 / rad (180.0)));

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (deviation from radar scan datum)", delta_score, score);

					#endif

					//
					// SCORE: aspect (target facing player)
					//

					source_bearing = target_bearing + rad (180.0);

					if (source_bearing > rad (180.0))
					{
						source_bearing -= rad (360.0);
					}
					else if (source_bearing < rad (-180.0))
					{
						source_bearing += rad (360.0);
					}

					target_heading = get_local_entity_float_value (target, FLOAT_TYPE_HEADING);

					theta = source_bearing - target_heading;

					if (theta > rad (180.0))
					{
						theta -= rad (360.0);
					}
					else if (theta < rad (-180.0))
					{
						theta += rad (360.0);
					}

					theta = fabs (theta);

					delta_score = 1.0 - (theta * (1.0 / rad (180.0)));

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (aspect, theta = %.2f, source bearing = %.2f, target heading = %.2f)", delta_score, score, deg (theta), deg (source_bearing), deg (target_heading));

					#endif

					//
					// SCORE: line of sight clear
					//

					if (get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
					{
						delta_score = 1.0;
					}
					else
					{
						delta_score = 0.0;
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (line of sight clear)", delta_score, score);

					#endif

					//
					// SCORE: targetting player
					//

					if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_AIRCRAFT))
					{
						if (source == get_local_entity_parent (target, LIST_TYPE_TARGET))
						{
							delta_score = 1.0;
						}
						else
						{
							delta_score = 0.0;
						}
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (targetting player)", delta_score, score);

					#endif

					//
					// SCORE: within selected weapon range
					//

					if ((target_range >= weapon_min_range) && (target_range <= weapon_max_range))
					{
						delta_score = 1.0;
					}
					else
					{
						delta_score = 0.0;
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (within selected weapon range, min = %.2f, max = %.2f)", delta_score, score, weapon_min_range, weapon_max_range);

					#endif

					//
					// SCORE: range
					//

					delta_score = 1.0 - (target_range * one_over_scan_range);

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (range = %.2f, scan range = %.2f)", delta_score, score, target_range, air_radar.scan_range);

					#endif

					//
					// SCORE: enemy
					//

					if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
					{
						delta_score = 1.0;
					}
					else
					{
						delta_score = 0.0;
					}

					score += delta_score;

					#if DEBUG_MODULE_BEST_TARGET_SCORING

					debug_log ("-->delta = %.2f, score = %.2f (enemy)", delta_score, score);

					#endif

					////////////////////////////////////////
					//
					// compare score with best score
					//
					////////////////////////////////////////

					if (score > best_score)
					{
						best_score = score;

						best_target = target;
					}
				}
			}
		}

		target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
	}

	return (best_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_selectable_air_radar_target (entity *target)
{
	float
		target_range;

	entity
		*source;

	entity_sides
		source_side;

	vec3d
		*source_position,
		*target_position;

	ASSERT (target);

	source = get_gunship_entity ();

	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);

	////////////////////////////////////////
	//
	// keep MANDATORY checks the same as get_best_air_radar_target ()
	//
	////////////////////////////////////////

	// TODO
	if (get_gunship_target_valid_for_air_radar (target))
	{
		//
		// MANDATORY: target matches declutter criteria
		//

		if (get_target_matches_air_radar_declutter_criteria (target, source_side))
		{
			//
			// MANDATORY: target within scan range
			//

			source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

			target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			target_range = get_3d_range (source_position, target_position);

			if (target_range <= air_radar.scan_range)
			{
				return (TRUE);
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_target_matches_air_radar_declutter_criteria (entity *target, entity_sides source_side)
{
	ASSERT (target);

	if (air_radar.show_allied_targets)
	{
		return (TRUE);
	}

	if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
	{
		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_next_air_radar_target (void)
{
	entity
		*current_target,
		*new_target;

	air_radar.auto_target = FALSE;

	air_radar.target_locked = FALSE;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target && get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET))
	{
		new_target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

		while (new_target != current_target)
		{
			if (get_selectable_air_radar_target (new_target))
			{
				break;
			}

			new_target = get_local_entity_child_succ_circular (new_target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
	else
	{
		new_target = get_best_air_radar_target ();
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_previous_air_radar_target (void)
{
	entity
		*current_target,
		*new_target;

	air_radar.auto_target = FALSE;

	air_radar.target_locked = FALSE;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (current_target && get_local_entity_parent (current_target, LIST_TYPE_GUNSHIP_TARGET))
	{
		new_target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_GUNSHIP_TARGET);

		while (new_target != current_target)
		{
			if (get_selectable_air_radar_target (new_target))
			{
				break;
			}

			new_target = get_local_entity_child_pred_circular (new_target, LIST_TYPE_GUNSHIP_TARGET);
		}
	}
	else
	{
		new_target = get_best_air_radar_target ();
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void activate_common_air_radar (void)
{
/*
	if (air_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
	{
		air_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_ACTIVE;
	}
*/
	radar_mode = RADAR_MODE_ATM;
	radar_active = TRUE;

	air_radar.target_locked = target_locked;
}

void toggle_air_radar_active(void)
{
	if (radar_mode == RADAR_MODE_ATM && radar_active)
		deactivate_common_air_radar();
	else
		activate_common_air_radar();
}

int air_radar_is_active(void)
{
	return radar_mode == RADAR_MODE_ATM && radar_active;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_common_air_radar (void)
{
//	radar_mode = RADAR_MODE_NONE;
	radar_active = FALSE;

	air_radar.target_locked = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031108 Designated targets

void select_next_designated_ground_radar_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
	{
		target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

		while (target)
		{
			if (get_selectable_ground_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	else
	{
		target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_DESIGNATED_TARGET);

		while (target != current_target)
		{
			if (get_selectable_ground_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ_circular (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_designated_ground_radar_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
	{
		target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

		while (target)
		{
			if (get_selectable_ground_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	else
	{
		target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_DESIGNATED_TARGET);

		while (target != current_target)
		{
			if (get_selectable_ground_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_pred_circular (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	set_gunship_target (new_target);
}

void select_next_designated_air_radar_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
	{
		target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

		while (target)
		{
			if (get_selectable_air_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	else
	{
		target = get_local_entity_child_succ_circular (current_target, LIST_TYPE_DESIGNATED_TARGET);

		while (target != current_target)
		{
			if (get_selectable_air_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ_circular (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}

	set_gunship_target (new_target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_designated_air_radar_target (void)
{
	entity
		*target,
		*new_target,
		*current_target;

	new_target = NULL;

	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if ((!current_target) || (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET) == NULL))
	{
		target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET);

		while (target)
		{
			if (get_selectable_air_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	else
	{
		target = get_local_entity_child_pred_circular (current_target, LIST_TYPE_DESIGNATED_TARGET);

		while (target != current_target)
		{
			if (get_selectable_air_radar_target (target))
			{
				new_target = target;

				break;
			}

			target = get_local_entity_child_pred_circular (target, LIST_TYPE_DESIGNATED_TARGET);
		}
	}
	set_gunship_target (new_target);
}
