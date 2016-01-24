// Retro 8Mar2005

#include "project.h"

#ifndef OGRE_EE
// fixing watcom 1.7 critical error

#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#ifndef _MSC_VER
/*
 * Copy src to string dst of size siz.  At most siz-1 characters
 * will be copied.  Always NUL terminates (unless siz == 0).
 * Returns strlen(src); if retval >= siz, truncation occurred.
 */
size_t strlcpy(char *dst, const char *src, size_t size)
{
   char *d = dst;
   const char *s = src;
   size_t n = size;

   /* Copy as many bytes as will fit */
   if (n != 0 && --n != 0) {
      do {
         if ((*d++ = *s++) == 0)
            break;
      } while (--n != 0);
   }

   /* Not enough room in dst, add NUL and traverse rest of src */
   if (n == 0) {
      if (size != 0)
         *d = '\0';             /* NUL-terminate dst */
      while (*s++);
   }

   return (s - src - 1);        /* count does not include NUL */
}
#endif

static HANDLE gHandleSharedMemory;

shared_memory_t* gPtrSharedMemory = NULL;

int Initialise_Shared_Memory(void)
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
		gPtrSharedMemory = (shared_memory_t*) MapViewOfFile(gHandleSharedMemory, FILE_MAP_WRITE, 0, 0, 0);

		gPtrSharedMemory->version = SHARED_MEM_DATA_VERSION;

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
		gPtrSharedMemory->version = - SHARED_MEM_DATA_VERSION;
		UnmapViewOfFile(gPtrSharedMemory);
		gPtrSharedMemory = NULL;
	}
	CloseHandle(gHandleSharedMemory);
}

extern ah64a_lamp_flags ah64a_lamps;
extern apache_lamp_flags apache_lamps;
extern blackhawk_lamp_flags blackhawk_lamps;
extern comanche_lamp_flags comanche_lamps;

extern havoc_lamp_flags havoc_lamps;
extern hind_lamp_flags hind_lamps;
extern hokum_lamp_flags hokum_lamps;
extern ka50_lamp_flags ka50_lamps;
extern viper_lamp_flags viper_lamps;
extern kiowa_lamp_flags kiowa_lamps;

// GCsDriver  08-12-2007
extern default_lamp_flags default_lamps;

void update_ah64a_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_AH64A;
	gPtrSharedMemory->cockpit_lamps.ah64a_lamps = ah64a_lamps;
}

void update_apache_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_APACHE;
	gPtrSharedMemory->cockpit_lamps.apache_lamps = apache_lamps;
}

void update_blackhawk_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_BLACKHAWK;
	gPtrSharedMemory->cockpit_lamps.blackhawk_lamps = blackhawk_lamps;
}

void update_comanche_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_COMANCHE;
	gPtrSharedMemory->cockpit_lamps.comanche_lamps = comanche_lamps;
}

void update_havoc_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_HAVOC;
	gPtrSharedMemory->cockpit_lamps.havoc_lamps = havoc_lamps;
}

void update_hind_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_HIND;
	gPtrSharedMemory->cockpit_lamps.hind_lamps = hind_lamps;
}

void update_hokum_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_HOKUM;
	gPtrSharedMemory->cockpit_lamps.hokum_lamps = hokum_lamps;
}

void update_ka50_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_KA50;
	gPtrSharedMemory->cockpit_lamps.ka50_lamps = ka50_lamps;
}

void update_viper_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_VIPER;
	gPtrSharedMemory->cockpit_lamps.viper_lamps = viper_lamps;
}

void update_kiowa_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_KIOWA;
	gPtrSharedMemory->cockpit_lamps.kiowa_lamps = kiowa_lamps;
}

// GCsDriver  08-12-2007
void update_default_avionics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->current_gunship = GUNSHIP_TYPE_APACHE;
	gPtrSharedMemory->cockpit_lamps.default_lamps = default_lamps;
}

void update_upfront_display_shared_mem(char *l1, char *l2, char *l3, char *l4)
{
	if (gPtrSharedMemory == 0)
		return;

	if (l1)
	{
		strlcpy(gPtrSharedMemory->cockpit_strings.upfront_display[0], l1, MAX_UFD_STRINGLEN);
	}

	if (l2)
	{
		strlcpy(gPtrSharedMemory->cockpit_strings.upfront_display[1], l2, MAX_UFD_STRINGLEN);
	}

	if (l3)
	{
		strlcpy(gPtrSharedMemory->cockpit_strings.upfront_display[2], l3, MAX_UFD_STRINGLEN);
	}

	if (l4)
	{
		strlcpy(gPtrSharedMemory->cockpit_strings.upfront_display[3], l4, MAX_UFD_STRINGLEN);
	}
}

void update_ekran_shared_mem(char *l1, char *l2, char *l3, char *l4)
{
	if (gPtrSharedMemory == 0)
		return;

	if (l1)
	{
		strlcpy(gPtrSharedMemory->cockpit_strings.ekran_display[0], l1, MAX_EKRAN_STRINGLEN);
	}

	if (l2)
	{
		strlcpy(gPtrSharedMemory->cockpit_strings.ekran_display[1], l2, MAX_EKRAN_STRINGLEN);
	}

	if (l3)
	{
		strlcpy(gPtrSharedMemory->cockpit_strings.ekran_display[2], l3, MAX_EKRAN_STRINGLEN);
	}

	if (l4)
	{
		strlcpy(gPtrSharedMemory->cockpit_strings.ekran_display[3], l4, MAX_EKRAN_STRINGLEN);
	}
}

void update_dynamics_shared_mem (void)
{
	if (gPtrSharedMemory == 0)
		return;

	gPtrSharedMemory->time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	gPtrSharedMemory->pitch = current_flight_dynamics->pitch.value;
	gPtrSharedMemory->roll = current_flight_dynamics->roll.value;
	gPtrSharedMemory->heading = current_flight_dynamics->heading.value;

	gPtrSharedMemory->indicated_airspeed = current_flight_dynamics->indicated_airspeed.value;
	gPtrSharedMemory->indicated_slip = current_flight_dynamics->indicated_slip.value;
	gPtrSharedMemory->vertical_speed = current_flight_dynamics->world_velocity_y.value;

	gPtrSharedMemory->barometric_altitude = current_flight_dynamics->barometric_altitude.value;
	gPtrSharedMemory->radar_altitude = current_flight_dynamics->radar_altitude.value;

	gPtrSharedMemory->g_force = current_flight_dynamics->g_force.value;

	gPtrSharedMemory->left_engine_rpm = current_flight_dynamics->left_engine_rpm.value;
	gPtrSharedMemory->left_engine_n1_rpm = current_flight_dynamics->left_engine_n1_rpm.value;
	gPtrSharedMemory->left_engine_torque = current_flight_dynamics->left_engine_torque.value;
	gPtrSharedMemory->left_engine_temp = current_flight_dynamics->left_engine_temp.value;

	gPtrSharedMemory->right_engine_rpm = current_flight_dynamics->right_engine_rpm.value;
	gPtrSharedMemory->right_engine_n1_rpm = current_flight_dynamics->right_engine_n1_rpm.value;
	gPtrSharedMemory->right_engine_torque = current_flight_dynamics->right_engine_torque.value;
	gPtrSharedMemory->right_engine_temp = current_flight_dynamics->right_engine_temp.value;

	gPtrSharedMemory->combined_engine_rpm = current_flight_dynamics->combined_engine_rpm.value;
	gPtrSharedMemory->combined_engine_torque = current_flight_dynamics->combined_engine_torque.value;

	gPtrSharedMemory->fuel_weight = current_flight_dynamics->fuel_weight.value;
}

void update_waypoint_shared_mem(void)
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

		gPtrSharedMemory->waypoint_data.waypoint = get_local_entity_char_value(wp, CHAR_TYPE_TAG);
		gPtrSharedMemory->waypoint_data.waypoint_range = get_2d_range (gunship_position, &waypoint_position);

		dx = waypoint_position.x - gunship_position->x;
		dz = waypoint_position.z - gunship_position->z;

		bearing = deg(atan2(dx, dz));
		if (bearing < 0.0)
			bearing += 360.0;

		gPtrSharedMemory->waypoint_data.waypoint_bearing = bearing;
	}
	else
		memset(&gPtrSharedMemory->waypoint_data, 0, sizeof(waypoint_data_t));
}

void update_weapon_load_shared_mem (void)
{
	weapon_package_status
		*package_status;

	unsigned next_free = 0;

	if (!gPtrSharedMemory || !get_gunship_entity())
		return;

	package_status = (weapon_package_status *) get_local_entity_ptr_value(get_gunship_entity(), PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		int package;
		weapon_config_types config_type = (weapon_config_types) get_local_entity_int_value (get_gunship_entity(), INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < MAX_WEAPON_LOAD_DATA; package++)
		{
			entity_sub_types weapon_type;
			int number;

			weapon_type = weapon_config_database[config_type][package].sub_type;
			number = package_status[package].number;

			gPtrSharedMemory->weapon_load[next_free].weapon_type = weapon_type;
			gPtrSharedMemory->weapon_load[next_free].weapon_count = number;
			next_free++;
		}
	}
	else
		memset(gPtrSharedMemory->weapon_load, 0, sizeof(gPtrSharedMemory->weapon_load));
}
#endif
