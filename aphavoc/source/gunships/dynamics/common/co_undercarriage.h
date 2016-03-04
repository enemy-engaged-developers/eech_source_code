#ifndef CO_UNDERCARRIAGE_H_
#define CO_UNDERCARRIAGE_H_

void initialise_undercarriage_database(void);
void deinitialise_undercarriage_database(void);

void initialise_undercarriage_dynamics(entity* en);
void deinitialise_undercarriage_dynamics(void);

void update_undercarriage_dynamics(void);

void reset_undercarriage_world_position(entity* en);

void repair_wheels(void);

int nose_wheel_locked_down(void);
int left_main_wheel_locked_down(void);
int right_main_wheel_locked_down(void);

int weight_on_wheels(void);
void animate_aircraft_suspension(entity* en);
void rotate_helicopter_wheels(object_3d_instance* inst3d);

void debug_adjust_damper_stiffness (event *ev);
#endif
