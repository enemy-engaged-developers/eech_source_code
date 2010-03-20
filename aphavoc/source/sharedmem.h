// Retro 8Mar2005

#define MAX_UFD_STRINGLEN 14
#define MAX_EKRAN_STRINGLEN 9
#define MAX_WEAPON_LOAD_DATA 14

typedef struct
{
	entity_sub_types   weapon_type;
	int                weapon_count;
} weapon_load_data_t;

typedef struct
{
	char waypoint;            // capital letter of selected waypoint
	float waypoint_range;     // in meters
	float waypoint_bearing;	  // absolute bearing to waypoint in degrees
} waypoint_data_t;

/********* IMPORTANT ************************************************
 * please increase this number when changing the layout of the data,
 * it makes life so much easier for those using the data
 *******************************************************************/
#define SHARED_MEM_DATA_VERSION 2

typedef struct	// all values are metric ! Distances in meters, speeds in m/s
{
//	gunship_types
	int
		version,
		current_gunship;		// this determines which lamp flags are valid in here..

	float
		time_of_day,
		pitch,
		roll,
		heading,

		indicated_airspeed,
		indicated_slip,
		vertical_speed,

		barometric_altitude,
		radar_altitude,

		g_force,

		left_engine_rpm,
		left_engine_n1_rpm,
		left_engine_torque,
		left_engine_temp,

		right_engine_rpm,
		right_engine_n1_rpm,
		right_engine_torque,
		right_engine_temp,

		combined_engine_rpm,
		combined_engine_torque,

		fuel_weight;

	union helo_specific_strings	// ufd for blue ac (not comanche), rest for red (not for hokum)
	{
		char upfront_display[4][MAX_UFD_STRINGLEN + 1];
		char ekran_display[4][MAX_EKRAN_STRINGLEN + 1];
	} cockpit_strings;

	union helo_specific	// current_gunship tells which it is..
	{
	havoc_lamp_flags
		havoc_lamps;

	hokum_lamp_flags
		hokum_lamps;

	hind_lamp_flags
		hind_lamps;

	ka50_lamp_flags
		ka50_lamps;

	apache_lamp_flags
		apache_lamps;

	ah64a_lamp_flags
		ah64a_lamps;

	blackhawk_lamp_flags
		blackhawk_lamps;

	comanche_lamp_flags
		comanche_lamps;

// GCsDriver  08-12-2007
	default_lamp_flags
		default_lamps;

	} cockpit_lamps;

	waypoint_data_t waypoint_data;
	weapon_load_data_t weapon_load[MAX_WEAPON_LOAD_DATA];
} shared_memory_t;

extern shared_memory_t* gPtrSharedMemory;

int Initialise_Shared_Memory(void);
void DeInitialise_Shared_Memory(void);

void update_apache_avionics_shared_mem ();
void update_ah64a_avionics_shared_mem ();
void update_blackhawk_avionics_shared_mem ();
void update_comanche_avionics_shared_mem ();

void update_upfront_display_shared_mem(char *l1, char *l2, char *l3, char *l4);
void update_ekran_shared_mem(char *l1, char *l2, char *l3, char *l4);

void update_havoc_avionics_shared_mem ();
void update_hind_avionics_shared_mem ();
void update_hokum_avionics_shared_mem ();
void update_ka50_avionics_shared_mem ();

// GCsDriver  08-12-2007
void update_default_avionics_shared_mem ();

void update_dynamics_shared_mem ();
void update_texture_shared_mem (void* target);
void update_waypoint_shared_mem();
void update_weapon_load_shared_mem();
