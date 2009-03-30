/*
 * tacview.c
 *
 *  Created on: 25.mar.2009
 *      Author: arneh
 */

#include "project.h"

#include "version.h"
#include "tacview.h"

#define M1 111132.92
#define M2 -559.82
#define M3 1.175
#define M4 -0.0023
#define P1 111412.84
#define P2 -93.5

#define tacview_id(obj)  (get_local_entity_safe_index(obj) + 2)

static FILE* log_file = NULL;

static float
	latitude_offset = rad(20.7 - 1.153),
	longitude_offset = rad(-76.7 - 2.308),
	latitude_scale = 0.0,
	tacview_starttime = 0.0;

static void write_coordinates(entity* en);

void open_tacview_log(void)
{
	char
		log_filename[256];

	int
		tod = get_system_time_of_day(),
		hour = tod / 3600,
		minute = (tod % 3600) / 60,
		day,
		month,
		year;

	get_system_date(&day, &month, &year);
	year += 2000;
	snprintf(log_filename, ARRAY_LENGTH(log_filename), "tacview-logs\\eech-%4d-%02d-%02dT%02d%02d.txt.acmi", year, month, day, hour, minute);

	if (log_file)
	{
		ASSERT(FALSE);
		close_tacview_log();
	}

	log_file = safe_fopen(log_filename, "wb");
}

void close_tacview_log(void)
{
	if (log_file)
	{
		safe_fclose(log_file);
		log_file = NULL;
	}
}

void write_tacview_header(entity* pilot, entity* player_gunship)
{
	char
		byte_order_mark[] = {0xEF, 0xBB, 0xBF, 0};

	int
		tod = get_system_time_of_day(),
		hour = tod / 3600,
		minute = (tod % 3600) / 60,
		second = tod % 60,
		day,
		month,
		year,
		game_day = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY),
		game_hour,
		game_minute,
		game_second;

	session_list_data_type
		*session = NULL;

	entity
		*player_task = get_player_task(NULL);

	tacview_starttime = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	// TODO: initialise latitude and longitude offset
	latitude_scale = 1.0 / (M1 + (M2 * cos(2 * rad(latitude_offset)) + (M3 * cos(4 * rad(latitude_offset)))));

	get_system_date(&day, &month, &year);
	year += 2000;
	get_digital_clock_int_values (tacview_starttime, &game_hour, &game_minute, &game_second);

	fputs(byte_order_mark, log_file);

	// CORE HEADER

	fputs("FileType=text/acmi/tacview\n", log_file);
	fputs("FileVersion=1.2\n", log_file);
	fprintf(log_file, "Source=EECH %d.%d.%d\n", MAJOR_VERSION, DATA_VERSION, MINOR_VERSION);
	fputs("Recorder=EECH\n", log_file);
	fprintf(log_file, "RecordingTime=%04d-%02d-%02dT%02d:%02d:%02dZ\n", year, month, day, hour, minute, second);
	if (pilot)
	{
		// TODO UTF-8 version of name if non-ascii chars supported
		const char* pilot_name = get_local_entity_string(pilot, STRING_TYPE_PILOTS_NAME);
		if (pilot_name)
			fprintf(log_file, "Author=%s\n", pilot_name);
	}

	session = get_current_game_session();

	// DECLARATIONS

	fprintf(log_file, "Title=%s\n", session->displayed_title);
	if (player_task)
		fprintf(log_file, "Category=%s\n", get_local_entity_string(player_task, STRING_TYPE_SHORT_DISPLAY_NAME));
	fprintf(log_file, "MissionTime=%04d-%02d-%02dT%02d:%02d:%02dZ\n", year, month, day + game_day - 1, game_hour, game_minute, game_second);

	fprintf(log_file, "LatitudeOffset=%f\n", deg(latitude_offset));
	fprintf(log_file, "LongitudeOffset=%f\n", deg(longitude_offset));

	fputs("Coalition=Neutral,Green\n", log_file);
	fputs("Coalition=Blue,Blue\n", log_file);
	fputs("Coalition=Red,Red\n", log_file);
	// TODO: provided events

	// ADDITIONAL INFO

	fprintf(log_file, "MainAircraftID=%x\n", tacview_id(player_gunship));

}

void write_tacview_frame_header(void)
{
	float time = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
	fprintf(log_file, "#%.2f\n", time - tacview_starttime);
}

void write_tacview_new_unit(entity* en)
{
	entity_sub_types sub_type;

	if (!en)
		return;

	sub_type = get_local_entity_int_value(en, INT_TYPE_ENTITY_SUB_TYPE);

	fprintf(log_file, "+%x,", tacview_id(en));

	switch (en->type)
	{
	case ENTITY_TYPE_HELICOPTER:
	case ENTITY_TYPE_FIXED_WING:
		{
			int
				type = (en->type == ENTITY_TYPE_HELICOPTER) ? 0x18 : 0x10;
			entity
				*group = NULL;
			const char
				*callsign = NULL,
				*pilot = NULL;

			if (get_local_entity_int_value(en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				entity* aircrew = get_local_entity_first_child(en, LIST_TYPE_AIRCREW);
				for (; aircrew; aircrew = get_local_entity_child_succ(aircrew, LIST_TYPE_AIRCREW))
				{
					if (get_local_entity_int_value(aircrew, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_PILOT_PILOT)
					{
						// TODO: UTF-8 string
						pilot = get_local_entity_string(aircrew, STRING_TYPE_PILOTS_NAME);
						break;
					}
				}
			}

			group = get_local_entity_parent (en, LIST_TYPE_MEMBER);
			if (group)
				callsign = get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN);

			// parent (empty), object type, coalition, country(empty), name, pilot, group, rank
			fprintf(log_file, ",%x,%x,,%s,%s,%s,%d\n",
					type,
					get_local_entity_int_value(en, INT_TYPE_SIDE),
					aircraft_database[sub_type].full_name,
					pilot ? pilot : "",
					callsign ? callsign : "",
					get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_ID));

			break;
		}
	case ENTITY_TYPE_UNKNOWN:
	case ENTITY_TYPE_ANTI_AIRCRAFT:
	case ENTITY_TYPE_BRIDGE:
	case ENTITY_TYPE_CAMERA:
	case ENTITY_TYPE_CARGO:
	case ENTITY_TYPE_CITY:
	case ENTITY_TYPE_CITY_BUILDING:
	case ENTITY_TYPE_CRATER:
	case ENTITY_TYPE_DIVISION:
	case ENTITY_TYPE_EXPLOSION:
	case ENTITY_TYPE_FORCE:
	case ENTITY_TYPE_GROUP:
	case ENTITY_TYPE_GUIDE:
	case ENTITY_TYPE_KEYSITE:
	case ENTITY_TYPE_LANDING:
	case ENTITY_TYPE_OBJECT:
	case ENTITY_TYPE_PARTICLE:
	case ENTITY_TYPE_PERSON:
	case ENTITY_TYPE_PILOT:
	case ENTITY_TYPE_PYLON:
	case ENTITY_TYPE_REGEN:
	case ENTITY_TYPE_ROUTED_VEHICLE:
	case ENTITY_TYPE_SCENIC:
	case ENTITY_TYPE_SECTOR:
	case ENTITY_TYPE_SEGMENT:
	case ENTITY_TYPE_SESSION:
	case ENTITY_TYPE_SHIP_VEHICLE:
	case ENTITY_TYPE_SITE:
	case ENTITY_TYPE_SITE_UPDATABLE:
	case ENTITY_TYPE_SMOKE_LIST:
	case ENTITY_TYPE_SOUND_EFFECT:
	case ENTITY_TYPE_SPRITE:
	case ENTITY_TYPE_TASK:
	case ENTITY_TYPE_UPDATE:
	case ENTITY_TYPE_WAYPOINT:
	case ENTITY_TYPE_WEAPON:
	default:
		ASSERT(FALSE);
		break;
	}

	write_tacview_unit_update(en);
}

void write_tacview_unit_removed(entity* en, tacview_event_type type)
{

}

void write_tacview_unit_update(entity* en)
{
	fprintf(log_file, "%x,", tacview_id(en));

	write_coordinates(en);

	// TODO: roll, pitch, yaw
	fprintf(log_file, ",0,0,0\n");
}

void write_coordinates(entity* en)
{
	vec3d
		*pos = get_local_entity_vec3d_ptr(en, VEC3D_TYPE_POSITION);
	float
		latitude = (pos->z * latitude_scale),
		abs_lat = fabs(latitude_offset + rad(latitude)),
		longitude_length = (P1 * cos(abs_lat)) + (P2 * cos(3 * abs_lat)),
		longitude = (pos->x / longitude_length);

	fprintf(log_file, "%.6f,%.6f,%.2f", latitude, longitude, pos->y);
}
