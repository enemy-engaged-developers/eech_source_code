/*
 * ap_hud_mfd_common.h
 *
 *  Created on: 20. apr. 2010
 *      Author: arneh
 */

#ifndef AP_HUD_MFD_COMMON_H_
#define AP_HUD_MFD_COMMON_H_

typedef enum {
	RENDER_TARGET_HUD,
	RENDER_TARGET_TADS,
	RENDER_TARGET_FCR
} avionics_render_target;

// radar altitude in 1 foot increments below 50 feet, 10 feet increments above
int get_apache_display_radar_altitude(void);

int get_apache_c_scope_enabled();
void toggle_apache_c_scope();

void draw_c_scope_symbology(int is_hud, rgb_colour colour, rgb_colour bg_colour);
void draw_apache_acquisition_source_symbology(viewpoint* vp, rgb_colour colour, float position, float cue_dot_limit);

// returns TRUE if position is visible on texture
int get_apache_texture_coordinate_for_position(vec3d* absolute_position, float* i, float* j, int is_hud);

void initialise_apache_hud_mfd_common(void);
void deinitialise_apache_hud_mfd_common(void);

void draw_apache_high_action_display(avionics_render_target, rgb_colour colour);

void draw_hellfire_loal_solid_target_marker(float x, float y, rgb_colour colour);
void draw_hellfire_loal_dashed_target_marker(float x, float y, rgb_colour colour, rgb_colour* bg_colour);
void draw_hellfire_lobl_solid_target_marker(float x, float y, rgb_colour colour);
void draw_hellfire_lobl_dashed_target_marker(float x, float y, rgb_colour colour, rgb_colour* bg_colour);

void draw_dashed_i_beam(float x, float y, rgb_colour colour);
void draw_solid_i_beam(float x, float y, rgb_colour colour);

#endif /* AP_HUD_MFD_COMMON_H_ */
