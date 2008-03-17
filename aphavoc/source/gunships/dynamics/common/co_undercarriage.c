#include "project.h"
#include "co_undercarriage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_GEAR_POINTS 8

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	int
		retracted,
		can_turn,
		has_brakes;
	
	vec3d
		position;   // relative to CoG with suspension fully extended

	float
		suspension_compression,  // how much the suspension is compressed, meters
		max_suspension_compression,
		suspension_stiffness,    // kN per meter of suspension movement
		damper_stiffness,
		damping,        // resistance to change in compression
		bump_stiffness;

	const char* name;
} landing_gear_point;

typedef struct {
	unsigned
		num_gear_points;

	landing_gear_point
		gear_points[MAX_GEAR_POINTS];
} landing_gear_system;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//static landing_gear_system
//	landing_gear[NUM_GUNSHIP_TYPES];

static landing_gear_system
	landing_gear;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_landing_gear(landing_gear_system* gear)
{
	unsigned i;

	gear->num_gear_points = 0;
	
	for (i=0; i < MAX_GEAR_POINTS; i++)
	{
		memset(&gear->gear_points[i], 0, sizeof(landing_gear_point));
		gear->gear_points[i].suspension_stiffness = 2.0;
		gear->gear_points[i].damper_stiffness = 5.0;
		gear->gear_points[i].max_suspension_compression = 0.3;
		gear->gear_points[i].bump_stiffness = 6.0;
	}

	gear->num_gear_points = 4;
	gear->gear_points[0].position.x = 1.65;
	gear->gear_points[0].position.y = -4.1;
	gear->gear_points[0].position.z = -1.35;
	gear->gear_points[0].name = "right main wheel";

	gear->gear_points[1].position.x = -1.65;
	gear->gear_points[1].position.y = -4.1;
	gear->gear_points[1].position.z = -1.35;
	gear->gear_points[1].name = "left main wheel";

	gear->gear_points[2].position.x = 0.0;
	gear->gear_points[2].position.y = -4.4;
	gear->gear_points[2].position.z = 3.0;
	gear->gear_points[2].suspension_stiffness = 1.5;
	gear->gear_points[2].damper_stiffness = 4.0;
	gear->gear_points[2].bump_stiffness = 4.0;
	gear->gear_points[2].name = "nose wheel";

	gear->gear_points[3].position.x = 0.0;
	gear->gear_points[3].position.y = -2.5;
	gear->gear_points[3].position.z = -10.0;
	gear->gear_points[3].suspension_stiffness = 4.0;
	gear->gear_points[3].max_suspension_compression = 0.3;
	gear->gear_points[3].name = "tail bumper";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_suspension(void)
{
	matrix3x3 attitude;
	unsigned i;

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	get_inverse_matrix(&attitude, &attitude);
	
	landing_gear.gear_points[2].bump_stiffness = 1.5 + debug_var_z;
	
	for (i = 0; i < landing_gear.num_gear_points; i++)
	{
		landing_gear_point* point = &landing_gear.gear_points[i];
		vec3d world_position, gear_position;
		float
			spring_compression,
			terrain_elevation,
			compression_change;

		world_position.x = current_flight_dynamics->position.x;
		world_position.y = current_flight_dynamics->position.y;
		world_position.z = current_flight_dynamics->position.z;
		
		gear_position = point->position;		
		
		multiply_transpose_matrix3x3_vec3d(&gear_position, attitude, &gear_position);
		
		world_position.x += gear_position.x;
		world_position.y += gear_position.y;
		world_position.z += gear_position.z;
		
		terrain_elevation = get_3d_terrain_elevation(world_position.x, world_position.z);
		
		spring_compression = (terrain_elevation - world_position.y);
		
		if (spring_compression > 0.0)
		{
			compression_change = spring_compression - point->suspension_compression;
			point->damping = compression_change * MODEL_FRAME_RATE * point->damper_stiffness;

			if (spring_compression >= point->max_suspension_compression)
			{
				// increase damper stiffness on the bump to get this descent stopped quickly
				if (compression_change > 0.0)  // bump
					point->damping *= 2.0;
			}
			
			point->suspension_compression = spring_compression;

			// TODO: hack, make proper brakes
			current_flight_dynamics->world_motion_vector.x = 0.0;
			if (i < 2)
				current_flight_dynamics->world_motion_vector.z = 0.0;
		}
		else
		{
			point->suspension_compression = 0.0;
		}
	}
}

static void apply_suspension_forces(void)
{
	matrix3x3 attitude;
	vec3d direction;
	unsigned i;
	
	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	direction.x = 0.0;
	direction.y = 1.0;
	direction.z = 0.0;

	multiply_transpose_matrix3x3_vec3d (&direction, attitude, &direction);
	
	for (i = 0; i < landing_gear.num_gear_points; i++)
	{
		landing_gear_point* point = &landing_gear.gear_points[i];
		vec3d position;
		float force;
		
		if (point->suspension_compression > 0.0)
		{
			position.x = point->position.x;
			position.y = point->position.y - point->suspension_compression;
			position.z = point->position.z;

			if (point->suspension_compression >= point->max_suspension_compression)
				force = G * point->suspension_compression * point->bump_stiffness;
			else
				force = G * point->suspension_compression * point->suspension_stiffness;

			force += point->damping;

			add_dynamic_force (point->name, force, 0.0, &position, &direction, FALSE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_undercarriage_dynamics(void)
{
	initialise_landing_gear(&landing_gear);
}

void deinitialise_undercarriage_dynamics(void)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_undercarriage_dynamics(void)
{
	ASSERT(get_gunship_entity());
	
	update_suspension();
	apply_suspension_forces();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_hind_suspension(object_3d_instance* inst3d)
{
	float front_compression = min(landing_gear.gear_points[2].suspension_compression, landing_gear.gear_points[2].max_suspension_compression);
	
	object_3d_sub_instance
		*left_wheel = &inst3d->sub_objects[2].sub_objects[0].sub_objects[0],
		*right_wheel = &inst3d->sub_objects[3].sub_objects[0].sub_objects[0],
		*nose_wheel = &inst3d->sub_objects[15].sub_objects[1].sub_objects[0],
		*nose_strut = &inst3d->sub_objects[15].sub_objects[0];

	left_wheel->relative_pitch = rad(-15) + min(landing_gear.gear_points[1].suspension_compression, landing_gear.gear_points[1].max_suspension_compression) * rad(70);
	right_wheel->relative_pitch = rad(-15) + min(landing_gear.gear_points[0].suspension_compression, landing_gear.gear_points[0].max_suspension_compression) * rad(70);

	nose_strut->relative_position.z = -0.20 + front_compression * 0.85;

	nose_wheel->relative_position.y = sin(rad(60)) * (-0.20 + front_compression * 0.8);
	nose_wheel->relative_position.z = cos(rad(60)) * (-0.20 + front_compression * 0.8);

	nose_wheel->relative_pitch = rad(-15) + front_compression * rad(70);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
