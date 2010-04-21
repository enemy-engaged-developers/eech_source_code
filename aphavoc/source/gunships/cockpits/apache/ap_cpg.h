#ifndef AP_CPG_H_
#define AP_CPG_H_

void initialise_co_pilot_head_animations(void);

void animate_co_pilot_head(object_3d_instance* cockpit_inst3d);

void get_opposite_crew_head_vector(float* heading, float* pitch);

#endif /*AP_CPG_H_*/
