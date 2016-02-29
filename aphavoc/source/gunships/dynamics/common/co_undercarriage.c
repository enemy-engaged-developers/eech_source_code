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
		velocity,
		world_position;

	vec3d
		position;   // relative to CoG with suspension fully extended

	float
		turn_angle,
		rotation_speed,
		rotation_angle,
		resistance_force,
		brake_force,
		max_suspension_compression,
		suspension_stiffness,    // kN per meter of suspension movement
		damper_stiffness,
		bump_stiffness,
		radius;
	double
		suspension_compression,  // how much the suspension is compressed, meters
		water_immersion, // how deep suspension points under water
		damping;        // resistance to change in compression
	char
		name[SUSPENSION_NAME_MAX_LENGTH];

	object_3d_sub_object_index_numbers
		sub_index;

} landing_gear_point;

typedef enum
{
	LGPT_RIGHT_MAIN_WHEEL,
	LGPT_LEFT_MAIN_WHEEL,
	LGPT_RIGHT_SECONDARY_WHEEL,
	LGPT_LEFT_SECONDARY_WHEEL,
	LGPT_NOSE_WHEEL,
	LGPT_TAIL_WHEEL,
	LGPT_RIGHT_SKI_BACK,
	LGPT_RIGHT_SKI_FRONT,
	LGPT_LEFT_SKI_BACK,
	LGPT_LEFT_SKI_FRONT,
	LGPT_TAIL_BUMPER,
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
	landing_gears[NUM_ENTITY_SUB_TYPE_AIRCRAFT + 1];

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
		"name = left secondary wheel",
		LGPT_LEFT_SECONDARY_WHEEL,
		OBJECT_3D_SUB_OBJECT_ROTATING_SECONDARY_WHEEL_LEFT
	},
	{
		"name = right secondary wheel",
		LGPT_RIGHT_SECONDARY_WHEEL,
		OBJECT_3D_SUB_OBJECT_ROTATING_SECONDARY_WHEEL_RIGHT
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
	{
		"name = left ski back end",
		LGPT_LEFT_SKI_BACK,
		OBJECT_3D_INVALID_SUB_OBJECT_INDEX
	},
	{
		"name = right ski back end",
		LGPT_RIGHT_SKI_BACK,
		OBJECT_3D_INVALID_SUB_OBJECT_INDEX
	},
	{
		"name = left ski front end",
		LGPT_LEFT_SKI_FRONT,
		OBJECT_3D_INVALID_SUB_OBJECT_INDEX
	},
	{
		"name = right ski front end",
		LGPT_RIGHT_SKI_FRONT,
		OBJECT_3D_INVALID_SUB_OBJECT_INDEX
	},
	{
		"name = tail bumper",
		LGPT_TAIL_BUMPER,
		OBJECT_3D_INVALID_SUB_OBJECT_INDEX
	},
	
};

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

		snprintf(filepath, ARRAY_LENGTH(filepath), "..\\common\\data\\suspension\\%s", filename);

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

static void update_ai_gear_world_position(landing_gear_point* point, vec3d* position, matrix3x3 attitude, entity* en)
{
	vec3d
		*ac_position,	
		gear_position;

	ASSERT (en);

	ac_position = get_local_entity_vec3d_ptr(en, VEC3D_TYPE_POSITION);
	gear_position = point->position;
	multiply_transpose_matrix3x3_vec3d(&gear_position, attitude, &gear_position);

	position->x = ac_position->x + gear_position.x;
	position->y = ac_position->y + gear_position.y;
	position->z = ac_position->z + gear_position.z;
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
	double
		inv_delta_time = 1.0 / get_model_delta_time();
	helicopter
		*raw;
	entity
		*keysite;
	terrain_classes
		terrain_class;

	ASSERT (get_gunship_entity());

	raw = (helicopter *) get_local_entity_data (get_gunship_entity ());
	terrain_class = get_terrain_type_class (get_3d_terrain_point_data_type (&raw->ac.terrain_info));
	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	get_inverse_matrix(inv_attitude, attitude);

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
	{
		landing_gear_point* point = &current_landing_gear->gear_points[i];
		
		point->damaged = current_flight_dynamics->undercarriage_state.damaged && point->damaged;

		if ((!point->retractable || current_flight_dynamics->undercarriage_state.value == 1.0) || 
				(terrain_class != TERRAIN_CLASS_LAND && get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT)))
		{
			double_vec3d
				old_world_position;
			
			double
				spring_compression,
				terrain_elevation,
				compression_change,
				water_immersion = 0;
			unsigned
				keysite_area = 0;

			old_world_position = point->world_position;

			update_gear_world_position(point, inv_attitude);

			point->velocity.x = (point->world_position.x - old_world_position.x) * inv_delta_time;
			point->velocity.y = (point->world_position.y - old_world_position.y) * inv_delta_time;
			point->velocity.z = (point->world_position.z - old_world_position.z) * inv_delta_time;

			multiply_transpose_matrix3x3_double_vec3d(&point->velocity, attitude, &point->velocity);

			ASSERT(point_inside_map_area(&point->world_position));
	
//			if (!bound_double_position_to_map_volume(&point->world_position))

			terrain_elevation = get_3d_terrain_elevation(point->world_position.x, point->world_position.z);
			
			spring_compression = (terrain_elevation - point->world_position.y);

			if (terrain_class != TERRAIN_CLASS_LAND)
			{
				keysite = get_closest_keysite (ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE, get_global_gunship_side (), &raw->ac.mob.position, 0.2 * KILOMETRE, NULL, FALSE, NULL);

				if (keysite)
					keysite_area = helicopter_within_keysite_area(get_gunship_entity());

				if (keysite_area && (!point->retractable || current_flight_dynamics->undercarriage_state.value == 1.0))
					spring_compression += (get_local_entity_int_value (keysite, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE) ? 19.95 : 16.65;	// update it of you will change carrier model! TODO: eliminate gunship side divide /thealx/
				else
				{
					water_immersion = min (2.0, spring_compression + point->position.y / 3);
					spring_compression = 0;
				}
//					debug_log("spring %f, immersion %f, airborn %i", spring_compression, water_immersion, get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIRBORNE_AIRCRAFT));			
			}
			
			if (spring_compression > 0.0) // solid
			{
				if (spring_compression > point->max_suspension_compression)
				{
					int
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

					if (!collisions && spring_compression > (1.5 + frand1()) * point->max_suspension_compression)
					{
						point->damaged = TRUE;
						dynamics_damage_model(DYNAMICS_DAMAGE_UNDERCARRIAGE, FALSE);
					}
				}

				compression_change = spring_compression - point->suspension_compression;

				point->damping = bound(compression_change * inv_delta_time * point->damper_stiffness, -25.0f, 25.0f);

				point->suspension_compression = spring_compression;
				point->water_immersion = 0;

					// let's add some roughness of terrain /thealx/
				if (fabs(point->velocity.z) > 1 && raw->ac.mob.velocity > 1)
					point->suspension_compression *= 1 + bound(point->velocity.z * sfrand1() / 200, 0, point->max_suspension_compression / 3);
				
				if (point->can_turn && (fabs(point->velocity.x) > 0.1 || fabs(point->velocity.z) > 0.1))
				{
					float
						max_turn_rate = rad(180) * get_model_delta_time() * (min(fabs(point->velocity.z) + fabs(point->velocity.x), 2.0)) * 0.5,
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

					modify_angle(&point->turn_angle, new_angle, max_turn_rate);
 				}
			}
			else if (water_immersion > 0.0) // liquid
			{
				compression_change = water_immersion - point->water_immersion;

				point->damping = - compression_change * inv_delta_time / 10;

				point->water_immersion = water_immersion;
				point->suspension_compression = 0;
			}
			else
			{
				point->water_immersion = point->suspension_compression = 0.0;

				if (point->can_turn)
				{
					float
						turn_rate = get_model_delta_time() * rad(180.0);

					// straighten wheel
					modify_angle(&point->turn_angle, 0.0f, turn_rate);
				}
			}
		}
		else
			point->water_immersion = point->suspension_compression = 0.0;

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

	ASSERT (get_gunship_entity());

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);

	up_direction.x = 0.0;
	up_direction.y = 1.0;
	up_direction.z = 0.0;

	multiply_transpose_matrix3x3_vec3d (&up_direction, attitude, &up_direction);

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
	{
		landing_gear_point* point = &current_landing_gear->gear_points[i];
		vec3d position;
		double wheel_load;
		char buffer[SUSPENSION_NAME_MAX_LENGTH + 16];

		if (point->suspension_compression > 0 || point->water_immersion > 0)
		{
			float suspension_stiffness;
			
			if (!point->damaged || point->suspension_compression >= point->max_suspension_compression)
				suspension_stiffness = point->suspension_stiffness;
			else if (point->suspension_compression / point->max_suspension_compression >= 0.5) // damaged wheel works only when it close to edge
				suspension_stiffness = point->suspension_stiffness * (point->suspension_compression / point->max_suspension_compression - 0.5) * 2;
			else
				suspension_stiffness = 0;
			
			position.x = point->position.x;
			position.y = -1.0;
			position.z = point->position.z;

//			if (point->suspension_compression >= point->max_suspension_compression)
//				wheel_load = G * (point->max_suspension_compression * suspension_stiffness + (point->suspension_compression - point->max_suspension_compression) * point->bump_stiffness);
//			else
			wheel_load = G * (point->suspension_compression ? min(point->suspension_compression, (double)point->max_suspension_compression) * suspension_stiffness : point->water_immersion);

			wheel_load = wheel_load + point->damping;

			sprintf(buffer, "%s load", point->name);
			if (!(point->water_immersion > 0 && !strcmp(point->name, "name = tail bumper")))
				add_dynamic_force (buffer, wheel_load, 0.0, &position, &up_direction, TRUE);

			point->suspension_compression = bound(point->suspension_compression, 0, point->max_suspension_compression);

			// wheel sideways resistance
			{
				float
					wheight_on_wheel = G * max(0.0, 1 - (point->max_suspension_compression - point->suspension_compression) / point->max_suspension_compression),  // depends on load on wheel
					force_diff = (wheight_on_wheel * point->velocity.x + point->resistance_force) / 2,
					max_force_change = get_model_delta_time() * 1000.0;

				if (!point->can_turn || point->water_immersion > 0 )
				{
					point->resistance_force = bound(force_diff, -max_force_change, max_force_change);

					direction.x = (point->resistance_force > 0.0) ? -1.0 : 1.0;
					direction.y = 0.0;
					direction.z = 0.0;

					sprintf(buffer, "%s sideway", point->name);
					add_dynamic_force (buffer, fabs(point->resistance_force), 0.0, &position, &direction, TRUE);
				}

			// wheel longitudinal resistance/brakes

				if ((!point->has_brakes || !current_flight_dynamics->wheel_brake) && point->suspension_compression > 0)
					wheight_on_wheel *= 0.005;  // general rolling resistance

				force_diff = (wheight_on_wheel * point->velocity.z + point->brake_force) / 2;
				point->brake_force = bound(force_diff, - max_force_change * 0.1, max_force_change * 0.1);

				direction.x = 0.0;
				direction.y = 0.0;
				direction.z = (point->brake_force > 0.0) ? -1.0 : 1.0;

				sprintf(buffer, "%s brakes", point->name);
				add_dynamic_force (buffer, fabs(point->brake_force), 0.0, &position, &direction, TRUE);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_undercarriage_database(void)
{
	const char
		*filenames[NUM_ENTITY_SUB_TYPE_AIRCRAFT];
	unsigned
		gunship;

	memset(filenames, 0, sizeof(filenames));

	filenames[ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW] = "ah-64-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE] = "ah-64-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE] = "rah-66-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK] = "uh-60-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER] = "ah-1-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA] = "ah-1-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA] = "ah-1-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR] = "oh-58-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY] = "mv-22-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION] = "ch-53-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT] = "ch-3-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT] = "ch-46-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK] = "ch-47-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B] = "mi-28-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B] = "ka-52-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM] = "ka-52-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND] = "mi-24-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP] = "mi-17-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK] = "mi-6-suspension.txt";
	filenames[ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B] = "ka-29-suspension.txt";

	for (gunship = 0; gunship < ARRAY_LENGTH(filenames); gunship++)
		if (filenames[gunship])
			initialise_landing_gear(&landing_gears[gunship], filenames[gunship]);

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

void initialise_undercarriage_dynamics(entity* en)
{
	matrix3x3
		attitude;
	unsigned
		i;

	ASSERT (en);

	current_landing_gear = &landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)];

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	get_inverse_matrix(attitude, attitude);

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
	{
		current_landing_gear->gear_points[i].damaged = FALSE;
		current_landing_gear->gear_points[i].resistance_force = 0.0;
		current_landing_gear->gear_points[i].brake_force = 0.0;
		current_landing_gear->gear_points[i].damping = 0.0;
		current_landing_gear->gear_points[i].suspension_compression = 0.0;
		current_landing_gear->gear_points[i].water_immersion = 0.0;
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

void reset_undercarriage_world_position(entity* en)
{
	matrix3x3
		attitude;
	unsigned
		i;

	ASSERT (en);
	ASSERT (get_gunship_entity());

//	debug_log("resetting gear position");

	current_landing_gear = &landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)];

	get_local_entity_attitude_matrix (get_gunship_entity (), attitude);
	get_inverse_matrix(attitude, attitude);

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
		update_gear_world_position(&current_landing_gear->gear_points[i], attitude);
}

void repair_wheels(void)
{
	unsigned i;

	ASSERT (get_gunship_entity());

	for (i = 0; i < current_landing_gear->num_gear_points; i++)
		current_landing_gear->gear_points[i].damaged = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int weight_on_wheels(void)
{
	unsigned int i;

	ASSERT (get_gunship_entity());
	
	for (i = 0; i < current_landing_gear->num_gear_points; i++)
		if (current_landing_gear->gear_points[i].suspension_compression > 0 || current_landing_gear->gear_points[i].water_immersion > 0.0)
			return TRUE;

	return FALSE;
}

void update_undercarriage_dynamics(void)
{
	if(get_gunship_entity())
	{
		current_flight_dynamics->undercarriage_state.value = get_undercarriage_state();

		update_suspension();
		apply_suspension_forces();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_aircraft_suspension(entity* en)
{
	object_3d_instance
		*inst3d;
	matrix3x3
		attitude,
		inv_attitude;
	float
		ter_elevation[5],
		left_compression = 0,
		right_compression = 0,
		left_secondary_compression = 0,
		right_secondary_compression = 0,
		third_compression = 0,
		nose_turn_angle = 0,
		tail_turn_angle = 0,
		left_secondary_turn_angle = 0,
		right_secondary_turn_angle = 0;
	unsigned int
		i;
	landing_gear_point
		*third,
		*left,
		*left_secondary,
		*right,
		*right_secondary;
	vec3d
		point_world_position[5];
	
	helicopter
		*raw;

	ASSERT (en);
	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
		return;
	if (get_local_entity_int_value (en, INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME))
		return;

	raw = (helicopter *) get_local_entity_data (en);
	inst3d = raw->ac.inst3d;
			
	switch (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
	{
		case ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION:
		{
			left = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_LEFT_MAIN_WHEEL];
			right = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_RIGHT_MAIN_WHEEL];
			third = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_NOSE_WHEEL];
			if (!right || !left || !third)
			{
				debug_log("Can't find suspension, aircraft sub type %i", get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
				return;
			}
			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE:
		case ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK:
		{
			left = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_LEFT_MAIN_WHEEL];
			right = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_RIGHT_MAIN_WHEEL];
			third = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_TAIL_WHEEL];
			if (!right || !left || !third)
			{
				debug_log("Can't find suspension, aircraft sub type %i", get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
				return;
			}
			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
		{
			left = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_LEFT_MAIN_WHEEL];
			left_secondary = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_LEFT_SECONDARY_WHEEL];
			right = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_RIGHT_MAIN_WHEEL];
			right_secondary = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_RIGHT_SECONDARY_WHEEL];
			if (!right || !right_secondary || !left || !left_secondary)
			{
				debug_log("Can't find suspension, aircraft sub type %i", get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
				return;
			}
			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA:
		case ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA:
		case ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR:
		{
			right = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_RIGHT_SKI_FRONT];
			right_secondary = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_RIGHT_SKI_BACK];
			left = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_LEFT_SKI_FRONT];
			left_secondary = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_LEFT_SKI_BACK];
			third = landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points_types[LGPT_TAIL_BUMPER];
			if (!right || !right_secondary || !left || !left_secondary || !third)
			{
				debug_log("Can't find suspension, aircraft sub type %i", get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE));
				return;
			}
			break;
		}
		default:
			return;
	}

	if (en != get_gunship_entity ())
	{
		get_local_entity_attitude_matrix (en, attitude);
		get_inverse_matrix(inv_attitude, attitude);
		for (i = 0; i < landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].num_gear_points; i++)
		{
			update_ai_gear_world_position(&landing_gears[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].gear_points[i], &point_world_position[i], inv_attitude, en);

			ASSERT(point_inside_map_area(&point_world_position[i]));
			
//			if(!bound_position_to_map_volume(&point_world_position[i]))

			ter_elevation[i] = get_3d_terrain_elevation(point_world_position[i].x, point_world_position[i].z);
		}

		switch (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
			{
				case ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER:
				case ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA:
				case ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA:
				case ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR:
				{
					right_compression = bound(max(ter_elevation[0] - point_world_position[0].y, ter_elevation[2] - point_world_position[2].y), 0, (left->max_suspension_compression + left_secondary->max_suspension_compression) / 2);
					left_compression = bound(max(ter_elevation[1] - point_world_position[1].y, ter_elevation[3] - point_world_position[3].y), 0, (right->max_suspension_compression + right_secondary->max_suspension_compression) / 2);
					break;
				}
				case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
				case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
				{
					right_compression = bound(ter_elevation[0] - point_world_position[0].y, 0, right->max_suspension_compression);
					left_compression = bound(ter_elevation[1] - point_world_position[1].y, 0, left->max_suspension_compression);
					right_secondary_compression = bound(ter_elevation[2] - point_world_position[2].y, 0, right_secondary->max_suspension_compression);
					left_secondary_compression = bound(ter_elevation[3] - point_world_position[3].y, 0, left_secondary->max_suspension_compression);
					break;
				}
				default:
				{
					right_compression = bound(ter_elevation[0] - point_world_position[0].y, 0, right->max_suspension_compression);
					left_compression = bound(ter_elevation[1] - point_world_position[1].y, 0, left->max_suspension_compression);
					third_compression = bound(ter_elevation[2] - point_world_position[2].y, 0, third->max_suspension_compression);
					break;
				}
			}

		nose_turn_angle = tail_turn_angle = left_secondary_turn_angle = right_secondary_turn_angle = 0;
	}
	else
	{
		switch (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
			{
				case ENTITY_SUB_TYPE_AIRCRAFT_AH1Z_VIPER:
				case ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA:
				case ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA:
				case ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR:
				{
					left_compression = max(left->suspension_compression, left_secondary->suspension_compression);
					right_compression = max(right->suspension_compression, right_secondary->suspension_compression);
					break;
				}
				case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
				case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
				{
					left_compression = left->suspension_compression;
					left_secondary_compression = left_secondary->suspension_compression;
					tail_turn_angle = left_secondary->turn_angle;
					right_compression = right->suspension_compression;
					right_secondary_compression = right_secondary->suspension_compression;
					nose_turn_angle = right_secondary->turn_angle;
					break;
				}
				default:
				{
					left_compression = left->suspension_compression;
					right_compression = right->suspension_compression;
					third_compression = third->suspension_compression;
					nose_turn_angle = tail_turn_angle = third->turn_angle;	
					break;
				}
			}
	}

	if (left_compression || right_compression || left_secondary_compression || right_secondary_compression || third_compression || nose_turn_angle || tail_turn_angle)
	{
		object_3d_sub_object_search_data
			result_sub_obj;

		result_sub_obj.search_object = inst3d;

		if (count_sub_object_type_depth(inst3d, OBJECT_3D_SUB_OBJECT_SUSPENSION_NOSE_STRUT))
		{
			result_sub_obj.search_depth = 0;
			result_sub_obj.sub_object_index = OBJECT_3D_SUB_OBJECT_SUSPENSION_NOSE_STRUT;
			while (find_object_3d_sub_object (&result_sub_obj) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				result_sub_obj.result_sub_object->relative_heading = nose_turn_angle;
				result_sub_obj.search_depth++;
			}
		}
		if (count_sub_object_type_depth(inst3d, OBJECT_3D_SUB_OBJECT_SUSPENSION_TAIL_STRUT)) // not "else if"! ch-47 and ka-29 use both
		{
			result_sub_obj.search_depth = 0;
			result_sub_obj.sub_object_index = OBJECT_3D_SUB_OBJECT_SUSPENSION_TAIL_STRUT;
			while (find_object_3d_sub_object (&result_sub_obj) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				result_sub_obj.result_sub_object->relative_heading = tail_turn_angle;
				result_sub_obj.search_depth++;
			}
		}

		animate_entity_simple_keyframed_sub_objects( inst3d, OBJECT_3D_SUB_OBJECT_SUSPENSION_RIGHT_WHEEL, bound(min(right_compression, right->max_suspension_compression) / left->max_suspension_compression, 0, 1));
		animate_entity_simple_keyframed_sub_objects( inst3d, OBJECT_3D_SUB_OBJECT_SUSPENSION_LEFT_WHEEL, bound(min(left_compression, left->max_suspension_compression) / left->max_suspension_compression, 0, 1));

		if (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK || get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B)
		{
			animate_entity_simple_keyframed_sub_objects( inst3d, OBJECT_3D_SUB_OBJECT_SUSPENSION_NOSE_WHEEL, bound(min(right_secondary_compression, right_secondary->max_suspension_compression) / right_secondary->max_suspension_compression, 0, 1));
			animate_entity_simple_keyframed_sub_objects( inst3d, OBJECT_3D_SUB_OBJECT_SUSPENSION_TAIL_WHEEL, bound(min(left_secondary_compression, left_secondary->max_suspension_compression) / left_secondary->max_suspension_compression, 0, 1));
		}
		else
		{
			animate_entity_simple_keyframed_sub_objects( inst3d, OBJECT_3D_SUB_OBJECT_SUSPENSION_NOSE_WHEEL, bound( min(third_compression, third->max_suspension_compression) / third->max_suspension_compression, 0, 1));
			animate_entity_simple_keyframed_sub_objects( inst3d, OBJECT_3D_SUB_OBJECT_SUSPENSION_TAIL_WHEEL, bound( min(third_compression, third->max_suspension_compression) / third->max_suspension_compression, 0, 1));
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int wheel_locked_down(const landing_gear_point* point)
{
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
	ASSERT (get_gunship_entity());

	if (get_time_acceleration () != TIME_ACCELERATION_PAUSE)
		for ( i = 0; i < current_landing_gear->num_gear_points; i++ )
		{
			if ( current_landing_gear->gear_points[i].sub_index == OBJECT_3D_INVALID_SUB_OBJECT_INDEX )
				return;

			if ( current_landing_gear->gear_points[i].suspension_compression == 0.0 )
			{
				if ( current_landing_gear->gear_points[i].rotation_speed == 0.0 )
					continue;

				current_landing_gear->gear_points[i].rotation_speed = (current_landing_gear->gear_points[i].rotation_speed < 0.0) ?
					min(current_landing_gear->gear_points[i].rotation_speed + 0.1 + (current_landing_gear->gear_points[i].has_brakes && current_flight_dynamics->wheel_brake), 0.0) : 
						max(current_landing_gear->gear_points[i].rotation_speed - 0.1 - (current_landing_gear->gear_points[i].has_brakes && current_flight_dynamics->wheel_brake), 0.0);
			}
			else
				current_landing_gear->gear_points[i].rotation_speed = (current_landing_gear->gear_points[i].can_turn ? sqrt(current_landing_gear->gear_points[i].velocity.x * current_landing_gear->gear_points[i].velocity.x + current_landing_gear->gear_points[i].velocity.z * current_landing_gear->gear_points[i].velocity.z) : current_landing_gear->gear_points[i].velocity.z) / current_landing_gear->gear_points[i].radius;

			current_landing_gear->gear_points[i].rotation_angle += current_landing_gear->gear_points[i].rotation_speed * get_model_delta_time();

			if ( current_landing_gear->gear_points[i].rotation_angle < 0.0 )
				do
					current_landing_gear->gear_points[i].rotation_angle += PI2;
				while ( current_landing_gear->gear_points[i].rotation_angle < 0.0 );
			else
				while ( current_landing_gear->gear_points[i].rotation_angle >= PI2 )
					current_landing_gear->gear_points[i].rotation_angle -= PI2;

			search.search_object = inst3d;
			search.sub_object_index = current_landing_gear->gear_points[i].sub_index;
			for ( j = 0; ; j++ )
			{
				search.search_depth = j;
				if ( find_object_3d_sub_object ( &search ) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
					break;

				search.result_sub_object->relative_pitch = current_landing_gear->gear_points[i].rotation_angle;
			}
		}
}
