// Retro 8Mar2005

#define INTERNAL_MODULES 1

#include "project.h"

/********* IMPORTANT ************************************************
 * please increase this number when changing the layout of the data, 
 * it makes life so much easier for those using the data
 *******************************************************************/
#define SHARED_MEM_DATA_VERSION 2

static HANDLE gHandleSharedMemory;

void* gPtrSharedMemory = (void*)0;

int Initialise_Shared_Memory()
{
	gPtrSharedMemory = 0;

	gHandleSharedMemory = CreateFileMapping(INVALID_HANDLE_VALUE,			// current file handle 
											NULL,                           // default security 
											PAGE_READWRITE,                 // read/write permission 
											0,								// max. object size 
											sizeof(shared_memory_t),        // size of hFile 
											"EECHSharedMemory");            // name of mapping object 
		
	if (gHandleSharedMemory != NULL) 
	{ 
		gPtrSharedMemory = MapViewOfFile(gHandleSharedMemory, FILE_MAP_WRITE, 0, 0, 0);

		((shared_memory_t*)gPtrSharedMemory)->version = SHARED_MEM_DATA_VERSION;

		return 1;
	}
	else
	{
		CloseHandle(gHandleSharedMemory);
		return 0;
	}
}

void DeInitialise_Shared_Memory(void)
{
	if (gPtrSharedMemory)
	{
		UnmapViewOfFile(gPtrSharedMemory);
		gPtrSharedMemory = (void*)0;
	}
	CloseHandle (gHandleSharedMemory);
}

extern ah64a_lamp_flags ah64a_lamps;
extern apache_lamp_flags apache_lamps;
extern blackhawk_lamp_flags blackhawk_lamps;
extern comanche_lamp_flags comanche_lamps;

extern havoc_lamp_flags havoc_lamps;
extern hind_lamp_flags hind_lamps;
extern hokum_lamp_flags hokum_lamps;
extern ka50_lamp_flags ka50_lamps;

// GCsDriver  08-12-2007
extern default_lamp_flags default_lamps;

void update_ah64a_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_AH64A;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.ah64a_lamps, &ah64a_lamps, sizeof(ah64a_lamp_flags));
}

void update_apache_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_APACHE;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.apache_lamps, &apache_lamps, sizeof(apache_lamp_flags));
}

void update_blackhawk_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_BLACKHAWK;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.blackhawk_lamps, &blackhawk_lamps, sizeof(blackhawk_lamp_flags));
}

void update_comanche_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_COMANCHE;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.comanche_lamps, &comanche_lamps, sizeof(comanche_lamp_flags));
}

void update_havoc_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_HAVOC;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.havoc_lamps, &havoc_lamps, sizeof(havoc_lamp_flags));
}

void update_hind_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_HIND;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.hind_lamps, &hind_lamps, sizeof(hind_lamp_flags));
}

void update_hokum_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_HOKUM;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.hokum_lamps, &hokum_lamps, sizeof(hokum_lamp_flags));
}

void update_ka50_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_KA50;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.ka50_lamps, &ka50_lamps, sizeof(ka50_lamp_flags));
}

// GCsDriver  08-12-2007
void update_default_avionics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

    ((shared_memory_t*)gPtrSharedMemory)->current_gunship = GUNSHIP_TYPE_APACHE;
	memcpy(&((shared_memory_t*)gPtrSharedMemory)->cockpit_lamps.default_lamps, &default_lamps, sizeof(default_lamp_flags));
}

void update_upfront_display_shared_mem(char *l1, char *l2, char *l3, char *l4)
{
	if (gPtrSharedMemory == 0)
		return;

	if (l1)
	{
		strncpy (&((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.upfront_display[0][0], l1, MAX_UFD_STRINGLEN);
		((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.upfront_display[0][MAX_UFD_STRINGLEN] = '\0';
	}

	if (l2)
	{
		strncpy (&((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.upfront_display[1][0], l2, MAX_UFD_STRINGLEN);
		((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.upfront_display[1][MAX_UFD_STRINGLEN] = '\0';
	}

	if (l3)
	{
		strncpy (&((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.upfront_display[2][0], l3, MAX_UFD_STRINGLEN);
		((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.upfront_display[2][MAX_UFD_STRINGLEN] = '\0';
	}

	if (l4)
	{
		strncpy (&((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.upfront_display[3][0], l4, MAX_UFD_STRINGLEN);
		((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.upfront_display[3][MAX_UFD_STRINGLEN] = '\0';
	}
}

void update_ekran_shared_mem(char *l1, char *l2, char *l3, char *l4)
{
	if (gPtrSharedMemory == 0)
		return;

	if (l1)
	{
		strncpy (&((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.ekran_display[0][0], l1, MAX_EKRAN_STRINGLEN);
		((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.ekran_display[0][MAX_EKRAN_STRINGLEN] = '\0';
	}

	if (l2)
	{
		strncpy (&((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.ekran_display[1][0], l2, MAX_EKRAN_STRINGLEN);
		((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.ekran_display[1][MAX_EKRAN_STRINGLEN] = '\0';
	}

	if (l3)
	{
		strncpy (&((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.ekran_display[2][0], l3, MAX_EKRAN_STRINGLEN);
		((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.ekran_display[2][MAX_EKRAN_STRINGLEN] = '\0';
	}

	if (l4)
	{
		strncpy (&((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.ekran_display[3][0], l4, MAX_EKRAN_STRINGLEN);
		((shared_memory_t*)gPtrSharedMemory)->cockpit_strings.ekran_display[3][MAX_EKRAN_STRINGLEN] = '\0';
	}
}

void update_dynamics_shared_mem ()
{
	if (gPtrSharedMemory == 0)
		return;

	((shared_memory_t*)gPtrSharedMemory)->time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	((shared_memory_t*)gPtrSharedMemory)->pitch					= current_flight_dynamics->pitch.value;
	((shared_memory_t*)gPtrSharedMemory)->roll					= current_flight_dynamics->roll.value;
	((shared_memory_t*)gPtrSharedMemory)->heading				= current_flight_dynamics->heading.value;

	((shared_memory_t*)gPtrSharedMemory)->indicated_airspeed	= current_flight_dynamics->indicated_airspeed.value;
	((shared_memory_t*)gPtrSharedMemory)->indicated_slip		= current_flight_dynamics->indicated_slip.value;
	((shared_memory_t*)gPtrSharedMemory)->vertical_speed		= current_flight_dynamics->world_velocity_y.value;

	((shared_memory_t*)gPtrSharedMemory)->barometric_altitude	= current_flight_dynamics->barometric_altitude.value;
	((shared_memory_t*)gPtrSharedMemory)->radar_altitude		= current_flight_dynamics->radar_altitude.value;

	((shared_memory_t*)gPtrSharedMemory)->g_force				= current_flight_dynamics->g_force.value;

	((shared_memory_t*)gPtrSharedMemory)->left_engine_rpm		= current_flight_dynamics->left_engine_rpm.value;
	((shared_memory_t*)gPtrSharedMemory)->left_engine_n1_rpm	= current_flight_dynamics->left_engine_n1_rpm.value;
	((shared_memory_t*)gPtrSharedMemory)->left_engine_torque	= current_flight_dynamics->left_engine_torque.value;
	((shared_memory_t*)gPtrSharedMemory)->left_engine_temp		= current_flight_dynamics->left_engine_temp.value;

	((shared_memory_t*)gPtrSharedMemory)->right_engine_rpm		= current_flight_dynamics->right_engine_rpm.value;
	((shared_memory_t*)gPtrSharedMemory)->right_engine_n1_rpm	= current_flight_dynamics->right_engine_n1_rpm.value;
	((shared_memory_t*)gPtrSharedMemory)->right_engine_torque	= current_flight_dynamics->right_engine_torque.value;
	((shared_memory_t*)gPtrSharedMemory)->right_engine_temp		= current_flight_dynamics->right_engine_temp.value;

	((shared_memory_t*)gPtrSharedMemory)->combined_engine_rpm	= current_flight_dynamics->combined_engine_rpm.value;
	((shared_memory_t*)gPtrSharedMemory)->combined_engine_torque= current_flight_dynamics->combined_engine_torque.value;

	((shared_memory_t*)gPtrSharedMemory)->fuel_weight			= current_flight_dynamics->fuel_weight.value;
}

void update_waypoint_shared_mem()
{
	entity* wp;

	if (!gPtrSharedMemory || !get_gunship_entity())
		return;

	wp = get_local_entity_current_waypoint(get_gunship_entity());

	if (wp)
	{
		vec3d
			*gunship_position,
			waypoint_position;

		float
			dx,
			dz,
			bearing;

		gunship_position = get_local_entity_vec3d_ptr(get_gunship_entity(), VEC3D_TYPE_POSITION);
		get_waypoint_display_position (get_gunship_entity(), wp, &waypoint_position);

		((shared_memory_t*)gPtrSharedMemory)->waypoint_data.waypoint = get_local_entity_char_value(wp, CHAR_TYPE_TAG);
		((shared_memory_t*)gPtrSharedMemory)->waypoint_data.waypoint_range = get_2d_range (gunship_position, &waypoint_position);

		dx = waypoint_position.x - gunship_position->x;
		dz = waypoint_position.z - gunship_position->z;

		bearing = deg(atan2(dx, dz));
		if (bearing < 0.0)
			bearing += 360.0;

		((shared_memory_t*)gPtrSharedMemory)->waypoint_data.waypoint_bearing = bearing;
	}
	else
		memset(&((shared_memory_t*)gPtrSharedMemory)->waypoint_data, 0, sizeof(waypoint_data_t));
}

void update_weapon_load_shared_mem()
{
	weapon_package_status
		*package_status;

	unsigned next_free = 0;

	if (!gPtrSharedMemory || !get_gunship_entity())
		return;

	package_status = get_local_entity_ptr_value(get_gunship_entity(), PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		int package;
		weapon_config_types config_type = get_local_entity_int_value (get_gunship_entity(), INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < MAX_WEAPON_LOAD_DATA; package++)
		{
			entity_sub_types weapon_type;
			int number;

			weapon_type = weapon_config_database[config_type][package].sub_type;
			number = package_status[package].number;

			((shared_memory_t*)gPtrSharedMemory)->weapon_load[next_free].weapon_type = weapon_type;
			((shared_memory_t*)gPtrSharedMemory)->weapon_load[next_free].weapon_count = number;
			next_free++;
		}
	}
	else
		memset(((shared_memory_t*)gPtrSharedMemory)->weapon_load, 0, sizeof(((shared_memory_t*)gPtrSharedMemory)->weapon_load));
}
