/*
 * ap_hud_mfd_common.h
 *
 *  Created on: 20. apr. 2010
 *      Author: arneh
 */

#ifndef AP_HUD_MFD_COMMON_H_
#define AP_HUD_MFD_COMMON_H_

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

#endif /* AP_HUD_MFD_COMMON_H_ */
