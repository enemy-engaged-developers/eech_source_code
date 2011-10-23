#include "project.h"
#include "co_undercarriage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_GEAR_POINTS 8
#define SUSPENSION_NAME_MAX_LENGTH 32

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	int
		damaged,
		retractable,
		can_turn,
		has_brakes;

	double_vec3d
		world_position;

	vec3d
		velocity,
		position;   // relative to CoG with suspension fully extended

	float
		turn_angle,
		rotation_speed,
		rotation_angle,
		suspension_compression,  // how much the suspension is compressed, meters
		resistance_force,
		brake_force,
		max_suspension_compression,
		suspension_stiffness,    // kN per meter of suspension movement
		damper_stiffness,
		damping,        // resistance to change in compression
		bump_stiffness,
		radius;

	char
		name[SUSPENSION_NAME_MAX_LENGTH];

	object_3d_sub_object_index_numbers
		sub_index;
} landing_gear_point;

typedef enum
{
	LGPT_RIGHT_MAIN_WHEEL,
	LGPT_LEFT_MAIN_WHEEL,
	LGPT_NOSE_WHEEL,
	LGPT_TAIL_WHEEL,
	LGPT_LAST,
} landing_gear_point_type;

typedef struct {
	unsigned
		num_gear_points;

	landing_gear_point
		*gear_points;
	landing_gear_point
		*gear_points_types[LGPT_LAST];
} landing_gear_system;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static landing_gear_system
	landing_gears[NUM_GUNSHIP_TYPES + 1];

static landing_gear_system
	*current_landing_gear;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const struct LANDING_GEAR_INFO
{
	const char
		*name;
	landing_gear_point_type
		type;
	object_3d_sub_object_index_numbers
		sub_index;
} landing_gear_info[] =
{
	{
		"name = left main wheel",
		LGPT_LEFT_MAIN_WHEEL,
		OBJECT_3D_SUB_OBJECT_ROTATING_WHEEL_LEFT
	},
	{
		"name = right main wheel",
		LGPT_RIGHT_MAIN_WHEEL,
		OBJECT_3D_SUB_OBJECT_ROTATING_WHEEL_RIGHT
	},
	{
		"name = nose wheel",
		LGPT_NOSE_WHEEL,
		OBJECT_3D_SUB_OBJECT_ROTATING_WHEEL_NOSE
	},
	{
		"name = tail wheel",
		LGPT_TAIL_WHEEL,
		OBJECT_3D_SUB_OBJECT_ROTATING_WHEEL_TAIL
	},
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct
{
	float
		ta,
		ct,
		tb,
		stfb,
		sbtf,
		ttfb,
		de,
		ep;
} apache_landing_gear;

static apache_landing_gear
	apache_main_gear, apache_tail_gear;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// returns a value between 1.0 (fully extended) and 0.0 (fully retracted)
static float get_undercarriage_state(void)
{
	float uc_state = get_local_entity_float_value (get_gunship_entity(), FLOAT_TYPE_UNDERCARRIAGE_STATE);
	if (uc_state >= 3.0)  // 3.0 -> 4.0 = retracting
		uc_state = 4.0 - uc_state;
	else if (uc_state > 1.0)  // extending
		uc_state -= 1.0;

	return uc_state;
}

static void initialise_landing_gear(landing_gear_system* gear, const char* filename)
{
	gear->num_gear_points = 0;
	gear->gear_points = NULL;
	memset(gear->gear_points_types, 0, sizeof(gear->gear_points_types));

	if (filename)
	{
		char filepath[256];
		FILE* file;

		snprintf(filepath, ARRAY_LENGTH(filepath), "..\\common\\data\\dyn\\%s", filename);

		file = safe_fopen(filepath, "r");
		if (file)
		{
			fscanf(file, "suspension_points = %d\n", &gear->num_gear_points);

			if (gear->num_gear_points > 0 && gear->num_gear_points <= 16)
			{
				unsigned i;

				gear->gear_points = (landing_gear_point *) safe_malloc(sizeof(landing_gear_point) * gear->num_gear_points);
				memset(gear->gear_points, 0, gear->num_gear_points * sizeof(landing_gear_point));

				for (i = 0; i < gear->num_gear_points; i++)
				{
					landing_gear_point* point = &gear->gear_points[i];
					unsigned len;
					unsigned nread = 0;

					if (!fgets(point->name, SUSPENSION_NAME_MAX_LENGTH, file))
						break;

					len = strlen(point->name);
					ASSERT(len < SUSPENSION_NAME_MAX_LENGTH - 1);
					if (point->name[len-1] == '\n')
						point->name[len-1] = '\0';

					nread += fscanf(file, "retractable = %d\n", &point->retractable);
					nread += fscanf(file, "has_brakes = %d\n", &point->has_brakes);
					nread += fscanf(file, "can_turn = %d\n", &point->can_turn);

					nread += fscanf(file, "position = %f, %f, %f\n", &point->position.x, &point->position.y, &point->position.z);

					nread += fscanf(file, "max_spring_compression = %f\n", &point->max_suspension_compression);
					nread += fscanf(file, "spring_stiffness = %f\n", &point->suspension_stiffness);
					nread += fscanf(file, "damper_stiffness = %f\n", &point->damper_stiffness);
					nread += fscanf(file, "bump_stiffness = %f\n", &point->bump_stiffness);
					nread += fscanf(file, "radius = %f\n", &point->radius);

					if (nread != 11)
						debug_fatal("error in file %s suspension point %d, values read only %d", filepath, i, nread);

					{
						unsigned
							i;

						point->sub_index = OBJECT_3D_INVALID_SUB_OBJECT_INDEX;
						for ( i = 0; i < ARRAY_LENGTH ( landing_gear_info ); i++ )
						{
							if ( !strcmp ( point->name, landing_gear_info[i].name ) )
							{
								point->sub_index = landing_gear_info[i].sub_index;
								gear->gear_points_types[landing_gear_info[i].type] = point;
								break;
							}
						}
					}
				}

				if (i != gear->num_gear_points)
					debug_fatal("suspension file %s claims there should be %d points, but only %d found", filepath, gear->num_gear_points, i - 1);
			}

			safe_fclose(file);
		}
	}
}

static void update_gear_world_position(landing_gear_point* point, matrix3x3 attitude)
{
	vec3d
		gear_position;

	point->world_position.x = current_flight_dynamics->position.x;
	point->world_position.y = current_flight_dynamics->position.y;
	point->world_position.z = current_flight_dynamics->position.z;

	gear_position = point->position;

	multiply_transpose_matrix3x3_vec3d(&gear_position, attitude, &gear_position);

	point->world_position.x += gear_position.x;
	point->world_position.y += gear_position.y;
	point->world_position.z += gear_position.z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_suspension(void)
{
	matrix3x3
		attitude,
		inv_attitude;

	unsigned
		i;

	float
		inv_delta_time = 1.0 / get_model_delta_time();

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	get_inverse_matrix(inv_attitude, attitude);

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
	{
		landing_gear_point* point = &current_landing_gear->gear_points[i];

		if (!point->damaged
			&& (!point->retractable || current_flight_dynamics->undercarriage_state.value == 1.0))
		{
			double_vec3d
				old_world_position;

			float
				spring_compression,
				terrain_elevation,
				compression_change;

			old_world_position = point->world_position;

			if (!fixed_collision_count && !moving_collision_count)
				update_gear_world_position(point, inv_attitude);

			point->velocity.x = (point->world_position.x - old_world_position.x) * inv_delta_time;
			point->velocity.y = (point->world_position.y - old_world_position.y) * inv_delta_time;
			point->velocity.z = (point->world_position.z - old_world_position.z) * inv_delta_time;

			multiply_transpose_matrix3x3_vec3d(&point->velocity, attitude, &point->velocity);

			terrain_elevation = get_3d_terrain_elevation(point->world_position.x, point->world_position.z);
			spring_compression = (terrain_elevation - point->world_position.y);

			if (spring_compression > 0.55)
			{
				int
					collisions;

				collisions = FALSE;
				switch ( get_game_type () )
				{
					case GAME_TYPE_FREE_FLIGHT:
					{
						collisions = get_global_session_free_flight_realism_invulnerable_from_collisions ();
						break;
					}
					case GAME_TYPE_CAMPAIGN:
					case GAME_TYPE_SKIRMISH:
					{
						collisions = get_global_session_campaign_realism_invulnerable_from_collisions ();
						break;
					}
				}

				if (!collisions)
				{
					point->damaged = TRUE;
					//point->suspension_compression = 0.0;
					continue;
				}

				spring_compression = 0.55;
			}

			if (spring_compression > 0.0)
			{
				compression_change = spring_compression - point->suspension_compression;

#if 0
				if ((fixed_collision_count || moving_collision_count) && compression_change > 0.0)
				{
					point->damping = 0.0;
				}
				else
#endif
				{
					point->damping = bound(compression_change * inv_delta_time * point->damper_stiffness, -25.0f, 25.0f);

					if (compression_change < 0.0)
					{
						// rebound produces more damping than bump
						point->damping *= 2.0;
					}

					if (spring_compression >= point->max_suspension_compression)
					{
						// increase damper stiffness on the bump to get this descent stopped quickly
						if (compression_change > 0.0)  // bump
							point->damping *= 2.0;
					}
				}

				point->suspension_compression = spring_compression;

				if (point->can_turn && (fabs(point->velocity.x) > 0.1 || fabs(point->velocity.z) > 0.1))
				{
					float
						max_turn_rate = rad(180) * get_model_delta_time() * (min(fabs(point->velocity.z) + fabs(point->velocity.x), 2.0f)) * 0.5,
						angle_diff,
						new_angle;


					if (fabs(point->velocity.z) > 0.05)
					{
						new_angle = atan(point->velocity.x / fabs(point->velocity.z));
						if (point->velocity.z < 0.0)
							if (new_angle > 0.0)
								new_angle = rad(180.0) - new_angle;
							else
								new_angle = rad(-180.0) - new_angle;
					}
					else if (point->velocity.x > 0.0)
						new_angle = 90.0;
					else
						new_angle = -90.0;

					angle_diff = new_angle - point->turn_angle;
					if (angle_diff > rad(180.0))
						angle_diff -= rad(360.0);
					else if (angle_diff < rad(-180.0))
						angle_diff += rad(360);

					point->turn_angle += bound(angle_diff, -max_turn_rate, max_turn_rate);
					if (point->turn_angle > rad(180.0))
						point->turn_angle -= rad(360.0);
					else if (point->turn_angle < rad(-180.0))
						point->turn_angle += rad(360);
 				}
			}
			else
			{
				point->suspension_compression = 0.0;

				if (point->can_turn)
				{
					float
						turn_rate = get_model_delta_time() * rad(180.0),
						angle_diff = 0.0 - point->turn_angle;

					// straighten wheel
					point->turn_angle += bound(angle_diff, -turn_rate, turn_rate);
				}
			}
		}
	}
}

static void apply_suspension_forces(void)
{
	matrix3x3
		attitude;
	vec3d
		up_direction,
		direction;
	unsigned
		i;

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	up_direction.x = 0.0;
	up_direction.y = 1.0;
	up_direction.z = 0.0;

	multiply_transpose_matrix3x3_vec3d (&up_direction, attitude, &up_direction);

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
	{
		landing_gear_point* point = &current_landing_gear->gear_points[i];
		vec3d position;
		float wheel_load;

		if (!point->retractable || current_flight_dynamics->undercarriage_state.value == 1.0)
			if (!point->damaged && point->suspension_compression > 0.0)
			{
				position.x = point->position.x;
				position.y = point->position.y - point->suspension_compression + 3.0;
				position.z = point->position.z;

				if (point->suspension_compression >= point->max_suspension_compression)
					wheel_load = G * (point->max_suspension_compression * point->suspension_stiffness + (point->suspension_compression - point->max_suspension_compression) * point->bump_stiffness);
				else
					wheel_load = G * point->suspension_compression * point->suspension_stiffness;

				wheel_load += point->damping;

				add_dynamic_force (point->name, wheel_load, 0.0, &position, &up_direction, TRUE);

				// wheel sideways resistance
				if (!point->can_turn)
				{
					float
						max_force,
						force,
						force_diff,
						max_force_change = get_model_delta_time() * 10.0;

					max_force = min(wheel_load * 2.5f, 0.5f * G);  // depends on load on wheel

					force = bound(point->velocity.x * 1.0, -1.0, 1.0);
					force_diff = (max_force * force) - point->resistance_force;

					point->resistance_force += bound(force_diff, -max_force_change, max_force_change);

					direction.x = (point->resistance_force > 0.0) ? -1.0 : 1.0;
					direction.y = 0.0;
					direction.z = 0.0;

					add_dynamic_force ("sideways wheel resistance", fabs(point->resistance_force), 0.0, &position, &direction, TRUE);
				}

				// wheel longitudinal resistance/brakes
				{
					float
						max_force,
						force,
						force_diff,
						max_force_change = get_model_delta_time() * 20.0;

					if (point->has_brakes && current_flight_dynamics->wheel_brake)
						max_force = min(wheel_load * 1.0, 1.0 * G);  // depends on load on wheel
					else
						max_force = min(wheel_load * 0.025f, G);  // general rolling resistance

					force = bound(point->velocity.z * 2.0, -1.0, 1.0);
					force_diff = (max_force * force) - point->brake_force;

					point->brake_force += bound(force_diff, -max_force_change, max_force_change);

					direction.x = 0.0;
					direction.y = 0.0;
					direction.z = (point->brake_force > 0.0) ? -1.0 : 1.0;

					add_dynamic_force ("brakes", fabs(point->brake_force), 0.0, &position, &direction, TRUE);
				}
			}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void apache_initialise_landing_gear(apache_landing_gear* gear, float b, float c, float t, float a, float u, float f)
{
	float
		sb,
		stf;

	sb = b * b;
	stf = t * t + f * f;

	gear->ta = t + a;
	gear->ct = c / t;
	gear->tb = 2 * b;
  gear->stfb = sb + stf;
  gear->sbtf = sb - stf;
  gear->ttfb = sqrt(stf) * gear->tb;
  gear->de = atan2(f, t);
  gear->ep = acos(gear->ct) + gear->de + acos((gear->stfb - u * u) / gear->ttfb);
}

void initialise_undercarriage_database(void)
{
	const char
		*filenames[NUM_GUNSHIP_TYPES + 1];
	unsigned
		gunship;

	memset(filenames, 0, sizeof(filenames));

	filenames[GUNSHIP_TYPE_APACHE] = "ah-64-suspension.txt";
	filenames[GUNSHIP_TYPE_AH64A] = "ah-64-suspension.txt";
	filenames[GUNSHIP_TYPE_COMANCHE] = "rah-66-suspension.txt";
	filenames[GUNSHIP_TYPE_BLACKHAWK] = "uh-60-suspension.txt";
	filenames[GUNSHIP_TYPE_HAVOC] = "mi-28-suspension.txt";
	filenames[GUNSHIP_TYPE_HOKUM] = "ka-52-suspension.txt";
	filenames[GUNSHIP_TYPE_KA50] = "ka-52-suspension.txt";
	filenames[GUNSHIP_TYPE_HIND] = "mi-24-suspension.txt";
	filenames[GUNSHIP_TYPE_VIPER] = "ah-1-suspension.txt";

	for (gunship = 0; gunship < ARRAY_LENGTH(filenames); gunship++)
		initialise_landing_gear(&landing_gears[gunship], filenames[gunship]);

	apache_initialise_landing_gear(&apache_main_gear, 0.58, 0.46, 0.79, 0.62, 1.13, 0.09);
	apache_initialise_landing_gear(&apache_tail_gear, 0.40, 0.27, 0.62, 0.39, 0.79, 0.31);
}

void deinitialise_undercarriage_database(void)
{
	unsigned
		i;

	for (i = 0; i < ARRAY_LENGTH(landing_gears); i++)
	{
		if (landing_gears[i].gear_points)
			safe_free(landing_gears[i].gear_points);

		landing_gears[i].num_gear_points = 0;
		landing_gears[i].gear_points = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_undercarriage_dynamics(void)
{
	matrix3x3
		attitude;
	unsigned
		i;

	current_landing_gear = &landing_gears[get_global_gunship_type()];

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	get_inverse_matrix(attitude, attitude);

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
	{
		current_landing_gear->gear_points[i].damaged = FALSE;
		current_landing_gear->gear_points[i].resistance_force = 0.0;
		current_landing_gear->gear_points[i].brake_force = 0.0;
		current_landing_gear->gear_points[i].damping = 0.0;
		current_landing_gear->gear_points[i].suspension_compression = 0.0;
		current_landing_gear->gear_points[i].turn_angle = 0.0;
		current_landing_gear->gear_points[i].rotation_speed = 0.0;
		current_landing_gear->gear_points[i].rotation_angle = rand() * PI / RAND_MAX;

		current_landing_gear->gear_points[i].velocity.x = 0.0;
		current_landing_gear->gear_points[i].velocity.y = 0.0;
		current_landing_gear->gear_points[i].velocity.z = 0.0;

		update_gear_world_position(&current_landing_gear->gear_points[i], attitude);
	}
}

void deinitialise_undercarriage_dynamics(void)
{

}

void reset_undercarriage_world_position(void)
{
	matrix3x3
		attitude;
	unsigned
		i;

//	debug_log("resetting gear position");

	current_landing_gear = &landing_gears[get_global_gunship_type()];

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	get_inverse_matrix(attitude, attitude);

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
		update_gear_world_position(&current_landing_gear->gear_points[i], attitude);
}

void repair_wheels(void)
{
	unsigned
		i;

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
	{
		current_landing_gear->gear_points[i].damaged = FALSE;
	}
}

int helicopter_has_undercarriage_modelling(void)
{
	return command_line_dynamics_flight_model >= 2 && current_landing_gear->num_gear_points > 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int weight_on_wheels(void)
{
	unsigned int i;

	if (command_line_dynamics_flight_model < 2)
		return FALSE;

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
	{
		if (!current_landing_gear->gear_points[i].damaged && current_landing_gear->gear_points[i].suspension_compression > 0.0)
		{
			return TRUE;
			break;
		}
	}

	return FALSE;
}

void update_undercarriage_dynamics(void)
{
	ASSERT(get_gunship_entity());

	current_flight_dynamics->undercarriage_state.value = get_undercarriage_state();

	update_suspension();
	apply_suspension_forces();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_hind_suspension(object_3d_instance* inst3d)
{
	landing_gear_point
		*nose,
		*left,
		*right;

	static object_3d_sub_instance
		*left_wheel,
		*right_wheel,
		*nose_wheel,
		*nose_strut;

	static const object_3d_sub_object_search_batch
		search[] =
			{
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_LEFT_WHEEL, &left_wheel },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_RIGHT_WHEEL, &right_wheel },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_NOSE_WHEEL, &nose_wheel },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_NOSE_STRUT, &nose_strut },
			};

	nose = landing_gears[GUNSHIP_TYPE_HIND].gear_points_types[LGPT_NOSE_WHEEL];
	left = landing_gears[GUNSHIP_TYPE_HIND].gear_points_types[LGPT_LEFT_MAIN_WHEEL];
	right = landing_gears[GUNSHIP_TYPE_HIND].gear_points_types[LGPT_RIGHT_MAIN_WHEEL];

	if (!nose || !left || !right)
	{
		return;
	}

	if (!find_object_3d_sub_objects(inst3d, search, ARRAY_LENGTH(search)))
		return;

	{
		float
			uc_state = get_undercarriage_state(),
			turn_angle = nose->turn_angle,
			front_compression = min(nose->suspension_compression, nose->max_suspension_compression);

		left_wheel->relative_pitch = (rad(-13.0) + min(left->suspension_compression, left->max_suspension_compression) * rad(70)) * uc_state;
		right_wheel->relative_pitch = (rad(-13.0) + min(right->suspension_compression, right->max_suspension_compression) * rad(70)) * uc_state;

		nose_strut->relative_position.z = (-0.15 + front_compression * 0.85) * uc_state;

		nose_wheel->relative_position.y = sin(rad(60)) * (-0.15 + front_compression * 0.8) * uc_state;
		nose_wheel->relative_position.z = cos(rad(60)) * (-0.15 + front_compression * 0.8) * uc_state;

		nose_wheel->relative_pitch = (rad(-15) + front_compression * rad(70)) * uc_state;

		nose_wheel->relative_heading = turn_angle;
		nose_wheel->relative_roll = sin(nose_wheel->relative_heading) * rad(40);
		nose_wheel->relative_pitch += rad(-30) + cos(nose_wheel->relative_heading) * rad(30);

		nose_wheel->relative_position.z += cos(nose_wheel->relative_heading) * 0.05 - 0.05;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void apache_set(const apache_landing_gear* gear, float h, object_3d_sub_instance* arm, object_3d_sub_instance* cylinder, object_3d_sub_instance* piston)
{
	float
		l,
		l2,
		al,
		be;

  be = gear->ep - acos(gear->ct - h / gear->ta);
  l2 = gear->stfb - gear->ttfb * cos(be - gear->de);
  l = sqrt(l2);
  al = acos((l2 + gear->sbtf) / (l * gear->tb));

	arm->relative_pitch = - be;
	cylinder->relative_pitch = al;
	piston->relative_pitch = al + be;
}

void animate_apache_suspension(object_3d_instance* inst3d)
{
	landing_gear_point
		*tail,
		*left,
		*right;

	static object_3d_sub_instance
		*right_cylinder,
		*right_arm,
		*right_piston,
		*left_cylinder,
		*left_arm,
		*left_piston,
		*tail_cylinder,
		*tail_arm,
		*tail_piston,
		*tail_fork;

	static const object_3d_sub_object_search_batch
		search[] =
			{
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_RIGHT_WHEEL, &right_arm },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_RIGHT_PISTON, &right_piston },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_RIGHT_CYLINDER, &right_cylinder },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_LEFT_WHEEL, &left_arm },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_LEFT_PISTON, &left_piston },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_LEFT_CYLINDER, &left_cylinder },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_TAIL_WHEEL, &tail_arm },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_TAIL_PISTON, &tail_piston },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_TAIL_CYLINDER, &tail_cylinder },
				{ OBJECT_3D_SUB_OBJECT_SUSPENSION_TAIL_STRUT, &tail_fork },
			};

	left = landing_gears[GUNSHIP_TYPE_APACHE].gear_points_types[LGPT_LEFT_MAIN_WHEEL];
	right = landing_gears[GUNSHIP_TYPE_APACHE].gear_points_types[LGPT_RIGHT_MAIN_WHEEL];
	tail = landing_gears[GUNSHIP_TYPE_APACHE].gear_points_types[LGPT_TAIL_WHEEL];

	if (!tail || !left || !right)
		return;

	if (!find_object_3d_sub_objects(inst3d, search, ARRAY_LENGTH(search)))
		return;

	apache_set(&apache_main_gear, min(right->suspension_compression - 0.25f, right->max_suspension_compression), right_arm, right_cylinder, right_piston);
	apache_set(&apache_main_gear, min(left->suspension_compression - 0.25f, left->max_suspension_compression), left_arm, left_cylinder, left_piston);
	apache_set(&apache_tail_gear, min(tail->suspension_compression - 0.3f, tail->max_suspension_compression), tail_arm, tail_cylinder, tail_piston);
	tail_fork->relative_heading = tail->turn_angle;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int wheel_locked_down(const landing_gear_point* point)
{
	if (command_line_dynamics_flight_model < 2)
		return get_local_entity_undercarriage_state(get_gunship_entity()) == AIRCRAFT_UNDERCARRIAGE_DOWN;

	return !point || (!point->damaged && (!point->retractable || current_flight_dynamics->undercarriage_state.value == 1.0));
}

int nose_wheel_locked_down(void)
{
	return wheel_locked_down(current_landing_gear->gear_points_types[LGPT_NOSE_WHEEL]);
}

int left_main_wheel_locked_down(void)
{
	return wheel_locked_down(current_landing_gear->gear_points_types[LGPT_LEFT_MAIN_WHEEL]);
}

int right_main_wheel_locked_down(void)
{
	return wheel_locked_down(current_landing_gear->gear_points_types[LGPT_RIGHT_MAIN_WHEEL]);
}

void rotate_helicopter_wheels(object_3d_instance* inst3d)
{
	unsigned
		i,
		j;
	object_3d_sub_object_search_data
		search;

	ASSERT ( current_landing_gear );

	for ( i = 0; i < current_landing_gear->num_gear_points; i++ )
	{
		landing_gear_point
			*gear_point = current_landing_gear->gear_points + i;

		if ( gear_point->damaged || gear_point->sub_index == OBJECT_3D_INVALID_SUB_OBJECT_INDEX )
		{
			continue;
		}

		if ( gear_point->suspension_compression == 0.0 )
		{
			if ( gear_point->rotation_speed == 0.0 )
			{
				continue;
			}
			gear_point->rotation_speed = gear_point->rotation_speed < 0.0 ? min(gear_point->rotation_speed + 0.1, 0.0) : max(gear_point->rotation_speed - 0.1, 0.0);
		}
		else
		{
			gear_point->rotation_speed = (gear_point->can_turn ? sqrt(gear_point->velocity.x * gear_point->velocity.x + gear_point->velocity.z * gear_point->velocity.z) : gear_point->velocity.z) / gear_point->radius;
		}

		gear_point->rotation_angle += gear_point->rotation_speed * get_model_delta_time();
		if ( gear_point->rotation_angle < 0.0 )
		{
			do
			{
				gear_point->rotation_angle += PI2;
			}
			while ( gear_point->rotation_angle < 0.0 );
		}
		else
		{
			while ( gear_point->rotation_angle >= PI2 )
			{
				gear_point->rotation_angle -= PI2;
			}
		}

		search.search_object = inst3d;
		search.sub_object_index = gear_point->sub_index;
		for ( j = 0; ; j++ )
		{
			search.search_depth = j;
			if ( find_object_3d_sub_object ( &search ) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
			{
				break;
			}

			search.result_sub_object->relative_pitch = gear_point->rotation_angle;
		}
	}
}
