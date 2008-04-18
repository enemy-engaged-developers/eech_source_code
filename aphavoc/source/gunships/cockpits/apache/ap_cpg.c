/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#define DEBUG_MODULE 0

#define MAX_TURN_ANGLE rad(70.0)
#define MIN_PITCH rad(-45.0)  // 45 degrees up
#define MAX_PITCH rad(20.0)   // 20 degrees down
#define MIN_BEND  rad(-5.0)
#define MAX_BEND  rad(30.0)

#define MIN_MOVEMENT_RATE rad(45.0)
#define MAX_MOVEMENT_RATE rad(180.0)
#define MAX_BENDING_RATE  (1.5 * MAX_BEND - MIN_BEND)

typedef enum {
	CPG_ANIM_STATE_REST,
	CPG_ANIM_STATE_EO,
	CPG_ANIM_STATE_ORT,
	CPG_ANIM_STATE_MFD_LEFT,
	CPG_ANIM_STATE_MFD_RIGHT,
	CPG_ANIM_STATE_LOOK_LEFT,
	CPG_ANIM_STATE_LOOK_RIGHT,
	CPG_ANIM_STATE_LOOK_UP,
	NUM_CPG_ANIM_STATES
} head_looking_states;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	time_until_state_change,
	current_movement_rate_heading,
	current_movement_rate_pitch,
	requested_bend,
	requested_heading,
	requested_pitch;

static head_looking_states
	looking_state;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_reset_co_pilot_anim_delay (void)
{
	if (frand1 () < 0.2)
		return 0.0;

	return (frand1 () * 3.0) + 2.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int set_new_static_direction(float cur_heading, float cur_pitch)
{
	float movement_time = 0.25 + frand1() * 0.5;
	float multiplier = 1.0;

	// don't use the fixed headings as often when we have a target
	if (target_acquisition_system != TARGET_ACQUISITION_SYSTEM_OFF && (rand() % 3 != 0))
		return FALSE;

	switch (looking_state)
	{
	default:
	case CPG_ANIM_STATE_REST:
		requested_heading = 0.0;
		requested_pitch = 5.0;
		break;
	case CPG_ANIM_STATE_MFD_RIGHT:
		multiplier = -1.0;
		// fall through
	case CPG_ANIM_STATE_MFD_LEFT:
		requested_heading = -rad(5.0) * multiplier;
		requested_pitch = rad(10.0);
		break;
	case CPG_ANIM_STATE_LOOK_RIGHT:
		multiplier = -1.0;
		// fall through
	case CPG_ANIM_STATE_LOOK_LEFT:
		requested_heading = (-rad(20.0) - (rad(60.0)) * frand1()) * multiplier;
		requested_pitch = -rad(30.0) + (rad(50.0)) * frand1();
		break;
	case CPG_ANIM_STATE_LOOK_UP:
		requested_heading = (-rad(20.0) + (rad(40.0)) * frand1());
		requested_pitch = -rad(40.0) + (rad(50.0)) * frand1();
		break;
	}

	requested_bend = MIN_BEND;

	#if DEBUG_MODULE
	debug_log("new heading: %.0f %.0f, move for %.1f seconds", deg(requested_heading), deg(requested_pitch), movement_time);
	#endif

	current_movement_rate_heading = bound(fabs(requested_heading - cur_heading) / movement_time, 0.0, MAX_TURN_ANGLE);
	current_movement_rate_pitch = bound(fabs(requested_pitch - cur_pitch) / movement_time, 0.0, MAX_PITCH);

	#if DEBUG_MODULE
	debug_log("movement rate: %.0f %.0f", deg(current_movement_rate_heading), deg(current_movement_rate_pitch));
	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int set_new_follow_eo_state(float cur_heading, float cur_pitch)
{
	// don't follow EO if it's not active
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_OFF)
		return FALSE;

	current_movement_rate_heading = rad(60.0) + frand1() * rad(60.0);
	current_movement_rate_pitch = current_movement_rate_pitch;

	requested_bend = MIN_BEND;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_follow_eo(void)
{
	// update heading and pitch to where EO is pointing now
	requested_heading = eo_azimuth;
	requested_pitch = -eo_elevation;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int set_new_ort_position(void)
{
	// don't look through ORT if EO is not active
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_OFF)
		return FALSE;

	// bend forward and keep head pointing ahead
	requested_heading = 0.0;
	requested_pitch = 0.0;
	requested_bend = MAX_BEND;

	current_movement_rate_heading = MAX_MOVEMENT_RATE;
	current_movement_rate_pitch = MAX_MOVEMENT_RATE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void switch_head_aiming_state(object_3d_sub_instance* helmet_inst)
{
	int
		valid_state = FALSE;

	float
		cur_heading = helmet_inst->relative_heading,
		cur_pitch = helmet_inst->relative_pitch,
		state_multiplier = 1.0;

	while (!valid_state)  // until we have a valid new state
	{
		looking_state = rand() % NUM_CPG_ANIM_STATES;

		#if DEBUG_MODULE
		debug_log("try state: %d", looking_state);
		#endif

		switch (looking_state)
		{
		default:
			break;
		case CPG_ANIM_STATE_REST:
		case CPG_ANIM_STATE_MFD_LEFT:
		case CPG_ANIM_STATE_MFD_RIGHT:
		case CPG_ANIM_STATE_LOOK_LEFT:
		case CPG_ANIM_STATE_LOOK_RIGHT:
		case CPG_ANIM_STATE_LOOK_UP:
			valid_state = set_new_static_direction(cur_heading, cur_pitch);
			break;
		case CPG_ANIM_STATE_EO:
			valid_state = set_new_follow_eo_state(cur_heading, cur_pitch);
			break;
		case CPG_ANIM_STATE_ORT:
			valid_state = set_new_ort_position();
			// look through ORT longer than other states
			state_multiplier = 3.0;
			break;
		}
	};

	time_until_state_change = get_reset_co_pilot_anim_delay() * state_multiplier;

	#if DEBUG_MODULE
	debug_log("next state change in %.1f seconds", time_until_state_change);
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_co_pilot_head(object_3d_instance* cockpit_inst3d)
{
	float
		diff = 0.0,
		dt = get_delta_time(),
		delta;
	object_3d_sub_instance
		*torso_inst,
		*helmet_inst;
	object_3d_sub_object_search_data
		search;

	search.search_depth = 0;
	search.search_object = cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WSO_CHEST;
	if ( find_object_3d_sub_object ( &search ) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		return;
	torso_inst = search.result_sub_object;

	search.search_depth = 0;
	search.search_object = cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WSO_HEAD;
	if ( find_object_3d_sub_object ( &search ) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		return;
	helmet_inst = search.result_sub_object;

	// don't display co-pilot's helmet when you are co-pilot. it's just in the way
	torso_inst->visible_object = helmet_inst->visible_object = get_crew_role() == CREW_ROLE_PILOT;

	if (get_time_acceleration() == 0)
		return;

	// switch to different state when time runs out
	if (time_until_state_change <= 0.0)
		switch_head_aiming_state(helmet_inst);

	switch (looking_state)
	{
	case CPG_ANIM_STATE_EO:
		update_follow_eo();
		break;
	default:
		// most states don't need update between state changes
		break;
	}

	// update head rotation
	delta = bound(requested_heading - helmet_inst->relative_heading, -current_movement_rate_heading, current_movement_rate_heading) * get_delta_time();
	helmet_inst->relative_heading = bound(helmet_inst->relative_heading + delta, -MAX_TURN_ANGLE, MAX_TURN_ANGLE);

	delta = bound(requested_pitch - helmet_inst->relative_pitch, -current_movement_rate_pitch, current_movement_rate_pitch) * get_delta_time();
	helmet_inst->relative_pitch = bound(helmet_inst->relative_pitch + delta, MIN_PITCH, MAX_PITCH);

	// update torso bending
	diff = requested_bend - torso_inst->relative_pitch;
	if (diff < 0.0)
		delta = -MAX_BENDING_RATE * dt;
	else if (diff > 0.0)
		delta = MAX_BENDING_RATE * dt;
	else
		delta = 0.0;
	torso_inst->relative_pitch = bound(torso_inst->relative_pitch + delta, 0.0, MAX_BEND);

	time_until_state_change -= get_delta_time();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_co_pilot_head_animations(void)
{
	looking_state = CPG_ANIM_STATE_REST;

	time_until_state_change = 0.0;

	current_movement_rate_heading = 0.0;
	current_movement_rate_pitch = 0.0;

	requested_heading = 0.0;
	requested_pitch = 5.0;
	requested_bend = 0.0;
}
