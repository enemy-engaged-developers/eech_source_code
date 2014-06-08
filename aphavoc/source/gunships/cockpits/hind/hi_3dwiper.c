#include "project.h"

#include "3d/3dsubobj.h"

static object_3d_instance
	*wiper_inst3d;

static object_3d_sub_instance
	*wiper_arm_object,
	*wiper_rod_object,
	*wiper_blade_object;

void initialise_hind_3d_cockpit_wiper(void)
{
	wiper_inst3d = construct_3d_object (OBJECT_3D_MI24V_WIPER);

	pilot_wiper = TRUE;
	pilot_wiped_rain_texture_screen = get_screen_of_system_texture (TEXTURE_INDEX_HAVOC_PILOT_RAIN_WIPE);
	pilot_wipe_type = WIPE_TYPE_LEFT_THEN_RIGHT;

	co_pilot_wiper = FALSE;
	co_pilot_wiped_rain_texture_screen = NULL;
	co_pilot_wipe_type = WIPE_TYPE_INVALID;

	wiper_arm_object = find_sub_object(wiper_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_WIPER_ARM);
	wiper_rod_object = find_sub_object(wiper_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_WIPER_ROD);
	wiper_blade_object = find_sub_object(wiper_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_WIPER_BLADE);
}

void deinitialise_hind_3d_cockpit_wiper (void)
{
	destruct_3d_object (wiper_inst3d);
}

void draw_hind_3d_cockpit_wiper (viewpoint *vp)
{
	//
	// rotate wiper arms
	//

	wiper_arm_object->relative_roll = rad(-44.0) + wiper_position * (rad (88.0) / MAX_WIPER_POSITION);
	wiper_rod_object->relative_roll = rad(-43.5) + wiper_position * (rad (87.0) / MAX_WIPER_POSITION);

	//
	// rotate wiper blade
	//

	wiper_blade_object->relative_roll = -wiper_arm_object->relative_roll;

	//
	// draw wiper arm and blade
	//

	memcpy (&wiper_inst3d->vp, vp, sizeof (viewpoint));
	insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &wiper_inst3d->vp.position, wiper_inst3d);
}
