//
//   Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
//   Copyright (C) 2000 Empire Interactive (Europe) Ltd,
//   677 High Road, North Finchley, London N12 0DA
//
//   Please see the document LICENSE.TXT for the full licence agreement
//
// 2. LICENCE
//  2.1
//      Subject to the provisions of this Agreement we now grant to you the
//      following rights in respect of the Source Code:
//   2.1.1
//      the non-exclusive right to Exploit  the Source Code and Executable
//      Code on any medium; and
//   2.1.2
//      the non-exclusive right to create and distribute Derivative Works.
//  2.2
//      Subject to the provisions of this Agreement we now grant you the
//  following rights in respect of the Object Code:
//   2.2.1
//  the non-exclusive right to Exploit the Object Code on the same
//  terms and conditions set out in clause 3, provided that any
//  distribution is done so on the terms of this Agreement and is
//  accompanied by the Source Code and Executable Code (as
//  applicable).
//
// 3. GENERAL OBLIGATIONS
//  3.1
//      In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1
//  that when you distribute the Source Code or Executable Code or
//  any Derivative Works to Recipients you will also include the
//  terms of this Agreement;
//   3.1.2
//  that when you make the Source Code, Executable Code or any
//  Derivative Works ("Materials") available to download, you will
//  ensure that Recipients must accept the terms of this Agreement
//  before being allowed to download such Materials;
//   3.1.3
//  that by Exploiting the Source Code or Executable Code you may
//  not impose any further restrictions on a Recipient's subsequent
//  Exploitation of the Source Code or Executable Code other than
//  those contained in the terms and conditions of this Agreement;
//   3.1.4
//  not (and not to allow any third party) to profit or make any
//  charge for the Source Code, or Executable Code, any
//  Exploitation of the Source Code or Executable Code, or for any
//  Derivative Works;
//   3.1.5
//  not to place any restrictions on the operability of the Source
//  Code;
//   3.1.6
//  to attach prominent notices to any Derivative Works stating
//  that you have changed the Source Code or Executable Code and to
//  include the details anddate of such change; and
//   3.1.7
//      not to Exploit the Source Code or Executable Code otherwise than
//  as expressly permitted by  this Agreement.
//

//
//   VJ eech.ini mod, date: 030403
//
//   Description: reads TEXT file "eech.ini" with commandline options
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#define EECH_INI "EECH.INI"

#define DEFAULT_GWUT_FILE "GWUT1140.CSV"

// Casm 09JUN09 Advanced options processing BEGIN

struct config_option
{
	const char* short_name;
	const char* long_name;
	const char* description;
	int* int_value;
	float* float_value;
	char* str_value;
	unsigned flag_length;
	void ( *parse_function )( const struct config_option *, const char * );
	void ( *print_function )( const struct config_option *, char * );
};

static void set_int ( const struct config_option *option, const char *value )
{
	*option->int_value = value && *value ? atoi ( value ) : 1;
}

static void get_int ( const struct config_option *option, char *value )
{
	sprintf ( value, "%i", *option->int_value );
}

static void set_float ( const struct config_option *option, const char *value )
{
	*option->float_value = value ? atof ( value ) : 0.0;
}

static void get_float ( const struct config_option *option, char *value )
{
	sprintf ( value, "%3.1f", *option->float_value );
}

static void set_string ( const struct config_option *option, const char *value )
{
	if ( value && *value && strlen ( value ) < option->flag_length )
	{
		strcpy ( option->str_value, value );
	}
}

static void get_string ( const struct config_option *option, char *value )
{
	strcpy ( value, option->str_value );
}

static void set_32bit ( const struct config_option *option, const char *value )
{
	command_line_display_bpp = value && atoi ( value ) ? 32 : 16;
}

static void get_32bit ( const struct config_option *option, char *value )
{
	sprintf ( value, "%i", command_line_display_bpp == 32 );
}

static void set_3dreset ( const struct config_option *option, const char *value )
{
	if ( atoi ( value ) )
	{
		set_global_3d_visual_screen_width ( 640.0 );
		set_global_3d_visual_screen_height ( 480.0 );
	}
}

static void get_zero ( const struct config_option *option, char *value )
{
	value[0] = '0';
	value[1] = '\0';
}

static void set_position ( const struct config_option *option, const char *value )
{
	unsigned who = option->flag_length;
	sscanf ( value, "%f,%f,%f,%f", &wide_cockpit_position[who].c.x, &wide_cockpit_position[who].c.y, &wide_cockpit_position[who].c.z, &wide_cockpit_position[who].c.p );
}

static void get_position ( const struct config_option *option, char *value )
{
	unsigned who = option->flag_length;
	sprintf ( value, "%.3f,%.3f,%.3f,%.3f", wide_cockpit_position[who].c.x, wide_cockpit_position[who].c.y, wide_cockpit_position[who].c.z, wide_cockpit_position[who].c.p );
}

static void set_hud_code ( const struct config_option *option, const char *value )
{
	int
		i, j;
	const char
		*cur;

	if ( *value != 'A' )
	{
	 	sscanf ( value, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &hud_code[0][0],&hud_code[0][1],&hud_code[0][2], &hud_code[1][0],&hud_code[1][1],&hud_code[1][2], &hud_code[2][0],&hud_code[2][1],&hud_code[2][2], &hud_code[3][0],&hud_code[3][1],&hud_code[3][2]);
		return;
	}

	cur = value + 1;
	for ( i = 0; i < sizeof ( hud_code ) / sizeof ( *hud_code ) ; i++ )
	{
		for ( j = 0; j < sizeof ( *hud_code ) / sizeof ( **hud_code ) ; j++ )
		{
			const char
				*next;
			for ( next = cur + 1; isdigit ( *next ); next++ );
			if ( *next == ';' )
			{
				cur = next + 1;
				break;
			}
			if ( !sscanf ( cur, "%d", &hud_code[i][j] ) || !*next )
			{
				return;
			}
			cur = next + 1;
		}
	}
}

static void get_hud_code ( const struct config_option *option, char *value )
{
	int
		i, j;

	strcpy ( value, "A" );
	for ( i = 0; i < sizeof ( hud_code ) / sizeof ( *hud_code ) ; i++ )
	{
		for ( j = 0; j < sizeof ( *hud_code ) / sizeof ( **hud_code ) ; j++ )
		{
			char buf[128];
			sprintf ( buf, "%s%d", j ? "," : "", hud_code[i][j] );
			strcat ( value, buf );
		}
		strcat ( value, ";" );
	}
}

static void set_canopy_amp ( const struct config_option *option, const char *value )
{
	int
		i, j;
	const char
		*cur;

	cur = value;
	for ( i = 0; i < ARRAY_LENGTH ( canopy_sound_amp ); i++ )
	{
		for ( j = 0; j < ARRAY_LENGTH ( *canopy_sound_amp ); j++ )
		{
			const char
				*next;
			for ( next = cur + 1; isdigit ( *next ); next++ );
			if ( !sscanf ( cur, "%d", &canopy_sound_amp[i][j] ) || !*next )
			{
				return;
			}
			cur = next + 1;
			if ( *next == ';' )
			{
				break;
			}
		}
		for (cur--; *cur != ';'; cur++)
		{
			if (!*cur)
			{
				return;
			}
		}
		cur++;
	}
}

static void get_canopy_amp ( const struct config_option *option, char *value )
{
	int
		i, j;

	*value = '\0';
	for ( i = 0; i < sizeof ( canopy_sound_amp ) / sizeof ( *canopy_sound_amp ) ; i++ )
	{
		for ( j = 0; j < sizeof ( *canopy_sound_amp ) / sizeof ( **canopy_sound_amp ) ; j++ )
		{
			char buf[128];
			sprintf ( buf, "%s%d", j ? "," : "", canopy_sound_amp[i][j] );
			strcat ( value, buf );
		}
		strcat ( value, ";" );
	}
}

static void set_axis ( const struct config_option *option, const char *value )
{
	*option->int_value = value ? atoi(value) - 1 : 0;
}

static void get_axis ( const struct config_option *option, char *value )
{
	sprintf ( value, "%d", *option->int_value + 1 );
}

static void set_mfd_pos ( const struct config_option *option, const char *value )
{
	sscanf ( value, "%d,%d,%d,%d", &option->int_value[0], &option->int_value[1], &option->int_value[2], &option->int_value[3]);
}

static void get_mfd_pos ( const struct config_option *option, char *value )
{
	sprintf ( value, "%d,%d,%d,%d", option->int_value[0], option->int_value[1], option->int_value[2], option->int_value[3]);
}

static void set_sound_device ( const struct config_option *option, const char *value )
{
	if ( value && *value && strlen ( value ) < option->flag_length )
	{
		int
			i;
		const char
			*devices,
			*default_device;

		for ( i = 0; ; i++ )
		{
			switch ( value[i] )
			{
			case '\0':
				option->str_value[i] = '\0';
				break;;
			case '_':
				option->str_value[i] = ' ';
				continue;
			case '%':
				option->str_value[i] = '#';
				continue;
			default:
				option->str_value[i] = value[i];
				continue;
			}
			break;
		}

		if ( get_sound_system_devices ( &devices, &default_device ) )
		{
			const char*
				device;

			ASSERT ( devices );
			ASSERT ( default_device );

			for ( device = devices; *device; device += strlen ( device ) + 1 )
			{
				if ( !strcmp ( device, option->str_value ) )
				{
					return;
				}
			}
		}

		option->str_value[0] = '\0';
	}
}

static void get_sound_device ( const struct config_option *option, char *value )
{
	int
		i;
	for ( i = 0; ; i++ )
	{
		switch ( option->str_value[i] )
		{
		case '\0':
			value[i] = '\0';
			break;;
		case ' ':
			value[i] = '_';
			continue;
		case '#':
			value[i] = '%';
			continue;
		default:
			value[i] = option->str_value[i];
			continue;
		}
		break;
	}
}

static void set_force_vectors ( const struct config_option *option, const char *value )
{
	set_global_dynamics_options_draw_flight_path ( value && atoi ( value ) );
}

static void get_force_vectors ( const struct config_option *option, char *value )
{
	sprintf ( value, "%d", get_global_dynamics_options_draw_flight_path() );
}

static void set_autosave ( const struct config_option *option, const char *value )
{
	command_line_autosave = atoi ( value ) * 60;
}

static void get_autosave ( const struct config_option *option, char *value )
{
	sprintf ( value, "%d", command_line_autosave / 60 );
}

static void set_wut ( const struct config_option *option, const char *value )
{
	if ( value && *value && strlen ( value ) < option->flag_length )
	{
		strcpy ( option->str_value, value );

		debug_log ( "wutfile ini [%s]", WUT_filename );

		command_line_wut = file_exist ( WUT_filename );

		if ( *WUT_filename && !command_line_wut )
		{
			strcpy ( WUT_filename, DEFAULT_GWUT_FILE );

			debug_log ( "default wutfile ini [%s]", WUT_filename );

			command_line_wut = file_exist ( WUT_filename );
		}
	}
}

static void set_ip_address ( const struct config_option *option, const char *value )
{
	if ( value && *value && strlen ( value ) < option->flag_length )
	{
		strcpy ( option->str_value, value );

		strcpy ( global_options.ip_address, command_line_ip_address );
	}
}

static void set_faa ( const struct config_option *option, const char *value )
{
	int craft;

	set_int ( option, value );

	if ( !value )
	{
		for ( craft = 0; craft < NUM_ENTITY_SUB_TYPE_AIRCRAFT; craft++ )
		{
			if ( aircraft_database[craft].gunship_type == NUM_GUNSHIP_TYPES )
			{
				aircraft_database[craft].player_controllable = FALSE;
			}
		}
	}
}

// Casm 20MAY12 Cloud puffs BEGIN
static void set_cloud_puffs_colours ( const struct config_option *option, const char *value )
{
	int
		new_number_of_cloud_puffs_colours;
	real_colour
		*new_cloud_puffs_colours;
	int
		count,
		cloud_puff_colour;
	unsigned
		red,
		green,
		blue;

	if ( !value || !*value )
	{
		return;
	}

	new_number_of_cloud_puffs_colours = 1;
	for ( count = 0; value[count]; count++ )
	{
		if ( value[count] == ';' )
		{
			new_number_of_cloud_puffs_colours++;
		}
	}

	new_cloud_puffs_colours = ( real_colour* ) safe_malloc ( new_number_of_cloud_puffs_colours * sizeof ( *new_cloud_puffs_colours ) );
	count = 0;
	cloud_puff_colour = 0;
	for ( ; ; )
	{
		if ( value[count] == ';' || value[count] == '\0' )
		{
			if ( sscanf ( value, "%u,%u,%u", &red, &green, &blue ) != 3 || red > 255 || green > 255 || blue > 255 )
			{
				safe_free ( new_cloud_puffs_colours );
				return;
			}
			new_cloud_puffs_colours[cloud_puff_colour].red = red;
			new_cloud_puffs_colours[cloud_puff_colour].green = green;
			new_cloud_puffs_colours[cloud_puff_colour].blue = blue;
			cloud_puff_colour++;
			if ( value[count] == '\0' )
			{
				break;
			}
			value += count + 1;
			count = 0;
		}
		else
		{
			count++;
		}
	}

	if ( cloud_puffs_colours )
	{
		safe_free ( cloud_puffs_colours );
	}
	number_of_cloud_puffs_colours = new_number_of_cloud_puffs_colours;
	cloud_puffs_colours = new_cloud_puffs_colours;
}

static void get_cloud_puffs_colours ( const struct config_option *option, char *value )
{
	int
		count;

	*value = '\0';
	for ( count = 0; count < number_of_cloud_puffs_colours; count++ ) 
	{
		sprintf ( value, "%i,%i,%i;", cloud_puffs_colours[count].red, cloud_puffs_colours[count].green, cloud_puffs_colours[count].blue );
		value += strlen ( value );
	}
	if ( number_of_cloud_puffs_colours )
	{
		value[-1] = '\0';
	}
}
// Casm 20MAY12 Cloud puffs END

// Casm 21DEC07
static void set_themes ( const struct config_option *option, const char *themes )
{
	int
		nthemes;
	char
		allthemes[1024],
		*ptr,
		*ptrs[64];

	if (themes[0] == '\0' || strlen(themes) >= sizeof(command_line_themes))
		return;

	strcpy(command_line_themes, themes);

	if (themes[1] == '\0' && isdigit(themes[0]))
	{
		int
			rc;
		long
			handle;
		struct _finddata_t
			fi;

		if (themes[0] == '0')
			return;

		allthemes[0] = '\0';
		handle = _findfirst("GRAPHICS\\UI\\COHOKUM\\*.*", &fi);
		for (rc = handle; rc != -1; rc = _findnext(handle, &fi))
		{
			if (!(fi.attrib & _A_SUBDIR))
				continue;
			if (!strcmp(fi.name, ".") || !strcmp(fi.name, ".."))
				continue;
			if (!stricmp(fi.name, "ICONS") || !stricmp(fi.name, "KEY") || !stricmp(fi.name, "MAP"))
				continue;
			strcat(allthemes, fi.name);
			strcat(allthemes, ",");
		}
		_findclose(handle);

		if (themes[0] == '1' && allthemes[0])
			allthemes[strlen(allthemes) - 1] = '\0';
	}
	else
		strcpy(allthemes, themes);

	nthemes = 1;
	ptr = allthemes;
	for (ptrs[0] = ptr; *ptr; ptr++)
	{
		if (*ptr != ',')
			continue;
		ptrs[nthemes++] = ptr + 1;
		*ptr = '\0';
	}

	strcpy(psd_theme, ptrs[time(NULL) % nthemes]);
}

static void set_cint ( const struct config_option *option, const char *value )
{
	*option->int_value = value && *value ? atoi ( value ) : atoi ( option->description );

	debug_log ( "ARG=%s RESPONSE=%d", option->short_name, *option->int_value );
}

static void set_cfloat ( const struct config_option *option, const char *value )
{
	*option->float_value = value && *value ? atof ( value ) : atof ( option->description );

	debug_log ( "ARG=%s RESPONSE=%3.1f", option->short_name, *option->float_value );
}

static void set_cstring ( const struct config_option *option, const char *value )
{
	if ( value && *value && strlen ( value ) < option->flag_length )
	{
		strcpy ( option->str_value, value );
	}
	else
	{
		strcpy ( option->str_value, option->description );
	}

	debug_log ( "ARG=%s RESPONSE=%s", option->short_name, *option->str_value );
}

static void set_3dw ( const struct config_option *option, const char *value )
{
	set_cint ( option, value );
	set_global_3d_visual_screen_width ( command_line_3d_visual_screen_width );
}

static void set_3dh ( const struct config_option *option, const char *value )
{
	set_cint ( option, value );
	set_global_3d_visual_screen_height ( command_line_3d_visual_screen_height );
}

static void set_version_number ( const struct config_option *option, const char *value )
{
	set_cint ( option, value );
	if ( command_line_version_number != IGNORE_COMMAND_LINE_VERSION_NUMBER )
	{
		set_global_version_number ( command_line_version_number );
	}
}

static void set_guarsend ( const struct config_option *option, const char *value )
{
	set_cint ( option, value );
	direct_play_use_guaranteed_packets = *option->int_value;
}

static void set_cdrom ( const struct config_option *option, const char *value )
{
	*option->int_value = value && *value ? *value : 'Z';
}

#define NONE NULL, NULL, NULL, 0, NULL, NULL
#define INT(x) &x, NULL, NULL, 0, set_int, get_int
#define FLOAT(x) NULL, &x, NULL, 0, set_float, get_float
#define STR(x) NULL, NULL, x, sizeof(x), set_string, get_string
#define SPEC(x, y) NULL, NULL, NULL, 0, x, y
#define SPECINT(x, y, z) &x, NULL, NULL, 0, y, z
#define SPECSTR(x, y, z) NULL, NULL, x, sizeof(x), y, z
#define SPEC2(x, y, z) NULL, NULL, NULL, x, y, z
#define CINT(x) &x, NULL, NULL, 0, set_cint, NULL
#define CFLOAT(x) NULL, &x, NULL, 0, set_cfloat, NULL
#define CSTR(x) NULL, NULL, x, sizeof(x), set_cstring, NULL

static const struct config_option options[] =
{
	{ NULL, NULL, "[Commandline options]",
		NONE },
	{ NULL, NULL, "for more information see readme file in game directory",
		NONE },
	{ NULL, NULL, "for more information see http://www.eechcentral.com/wiki/index.php?title=Eech.ini",
		NONE },
	{ NULL, NULL, "",
		NONE },

	{ NULL, "25", "[Communications]",
		NONE },
	{ "maxplayers", "", "maximum number of players in a multiplayer game (def = 4)",
		INT(command_line_maxplayers) },
	{ "ipa", "ip_address", "IP address (TCP/IP address) to connect to. A host can leave out the value.",
		SPECSTR(command_line_ip_address, set_ip_address, get_string) },
	{ "usemaster", "", "Report game to internet masterserver (0 = off/private game, 1 = on) (def = 0) (recommended = 1)",
		INT(command_line_report_to_masterserver) },
	{ "pss", "primary_server_setting", "primary masterserver internet address (def = hoxdna.org)",
		STR(command_line_primary_server_setting) },
	{ "sss", "secondary_server_setting", "secondary masterserver internet address (def = eech.dhs.org)",
		STR(command_line_secondary_server_setting) },
	{ "ccrs", "comms_connection_receive_size", "connection receive size, initial guess of campaign data size (def = 215040)",
		INT(command_line_comms_connection_receive_size) },
	{ "cdrs", "comms_data_record_size", "data record size, similar to above (def = 215040)",
		INT(command_line_comms_data_record_size) },
	{ "cpbs", "comms_pack_buffer_size", "pack buffer size, similar to above (def = 215040)",
		INT(command_line_comms_pack_buffer_size) },
	{ "cpds", "comms_packet_data_size", "packet data size (def = 512)",
		INT(command_line_comms_packet_data_size) },
	{ "cgs", "command_line_comms_guaranteed_send", "force the comms to use DirectPlay guaranteed send instead of its own (0 = off, 1 = on) (def = 1)",
		SPECINT(command_line_comms_guaranteed_send, set_guarsend, get_int) },
	{ "crls", "comms_resend_list_size", "packet history list size, increase if client keeps getting kicked out by server (default = 1000)",
		INT(command_line_comms_resend_list_size) },
	{ "crl", "comms_rerequest_limit", "number of times a client can re-request the same packet, increase for poor connections (def = 10)",
		INT(command_line_comms_packet_rerequest_limit) },
	{ "cpt", "comms_packet_timer", "time delay for comms to wait for a packet before re-requesting it (n = seconds) (def = 5)",
		FLOAT(command_line_comms_packet_resend_timer) },
	{ "crto", "comms_resend_timeout", "time delay for comms to wait before assuming re-requested packets was lost (n = seconds) (def = 2)",
		FLOAT(command_line_comms_resend_timeout) },
	{ "mur", "max_update_rate", "max update framerate for a server (not available for client) (n = frames/second) (TCP/IP = 5, IPX = 15) (def = 5)",
		INT(command_line_max_game_update_rate) },
	{ "cig", "command_line_comms_interpolate_gunships", "interpolate helicopter position for smoother visuals (0 = off, 1 = on) (def = 1)",
		INT(command_line_comms_interpolate_gunships) },
	{ "cvc", "command_line_comms_validate_connections", "removes dead player husks when client crashes to validate connection (0 = off, 1 = on) (def = 1)",
		INT(command_line_comms_validate_connections) },
	{ "cptl", "comms_packet_throttle_limit", "packet throttle limit, governs the flow rate of packets (mainly for modems) (def = 10)",
		INT(command_line_comms_packet_throttle_limit) },
	{ "cto", "comms_timeout", "timeout time before removing dead player husks (def = 15)",
		INT(command_line_comms_timeout) },
	{ "eufr", "entity_update_frame_rate", "client server entity update framerate, number of iterations (def = 2)",
		INT(command_line_entity_update_frame_rate) },
	{ "css", "comms_show_stats", "show comms stats (0 = off, 1 = on) (def = 0)",
		INT(command_line_comms_show_stats) },
	{ "cist", "command_line_comms_initial_sleep_time", "comms initial sleep time (def = 500)",
		INT(command_line_comms_initial_sleep_time) },
	{ "servlog", "server_log_filename", "filename for server log",
		STR(command_line_server_log_filename) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, NULL, "[Dedicated server]",
		NONE },
	{ NULL, NULL, "for more information see http://www.eechcentral.com/wiki/index.php?title=Dedicated_server",
		NONE },
	{ "dedicated", "command_line_comms_dedicated_server", "dedicated server mode (0 = off, 1 = on) (def = 0)",
		INT(command_line_comms_dedicated_server) },
	{ "pauseserv", "pause_server", "pause server if no clients connected (0 = off, 1 = on) (def = 0)",
		INT(command_line_pause_server) },
	{ "game_type", "command_line_game_initialisation_phase_game_type", "available game types (1 = Freeflight, 2 = Campaign, 3 = Skirmish) (def = 0)",
		INT(command_line_game_initialisation_phase_game_type) },
	{ "gunship_type", "command_line_game_initialisation_phase_gunship_type", "available gunship types (0 = Apache, 1 = Havoc, 2 = Comanche, 3 = Hokum, ...)",
		INT(command_line_game_initialisation_phase_gunship_type) },
	{ "path", "command_line_game_initialisation_phase_path", "path to map/campaign/skirmish folder",
		STR(command_line_game_initialisation_phase_path) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, NULL, "[Graphics and Textures]",
		NONE },
	{ "cbar", "city_block_approximation_range", "distance that city blocks resolve (n = meters) (def = 500)",
		FLOAT(command_line_city_block_approximation_range) },
	{ "fs", "full_screen", "full screen mode (0 = window mode, 1 = full screen mode) (def = 1)",
		INT(command_line_full_screen) },
	{ "mfr", "max_frame_rate", "maximum visual frame rate (n = frame rate) (def = 30)",
		INT(command_line_max_frame_rate) },
	{ "32bit", "", "32-bit rendering (0 = off, 1 = on) (def = 1)",
		SPEC(set_32bit, get_32bit) },
	{ "nrt", "", "rendering to texture (0 = enabled, 1 = disabled) (def = 0) (disable in case of visual problems with MFDs or TADS)",
		INT(command_line_no_render_to_texture) },
	{ "notnl", "", "GeForce \"TnL\" support (0 = enabled, 1 = disabled) (def = 0)",
		INT(command_line_no_hardware_tnl) },
	{ "nodx9zbufferfix", "", "Disable the dx9 zbuffer fix introduced in 1.11.1.  In case it causes graphical problems",
		INT(command_line_no_dx9zbuffer_fix) },
	{ "3dreset", "", "reset screen resolution to 640x480 (0 = off, 1 = on) (def = 0)",
		SPEC(set_3dreset, get_zero) },
	{ "dxtm", "directx_texture_management", "DirectX texture management (should fix \"unable to allocate hardware slot\" error) (0 = off, 1 = on) (def = 0)",
		INT(command_line_d3d_use_texture_management) },
	{ "cg", "clean_graphics", "(clean graphics) re-installs graphics files (0 = off, 1 = on) (def = 0)",
		SPECINT(command_line_clean_graphics, set_int, get_zero) },
	{ "palette", "", "use textures.pal (if videocard supports it) (0 = off, 1 = on) (def = 0)",
		INT(d3d_allow_paletted_textures) },
	{ "eofullrange", "", "eo ranges near to max fog distance (and objects are drawn up to it) 1=yes 0=no",
		INT(command_line_eo_full_range) },
	{ "render-tree-shadows", "", "1=yes 0=no",
		INT(command_line_render_tree_shadows) },
	{ "trees-fog", "", "fog affects groups of trees (0 = off, 1 = on, 2 = auto off when fps less than 20, auto on when fps more than 30 ) (def = 2)",
		INT(command_line_trees_fog) },
	{ NULL, NULL, "",
		NONE },
	{ "high_lod_hack", "", "[EXPERIMENTAL!] Enables highest level-of-detail models at far distances. Nice for higher FOVs, bad for FPS (esp. near cities)",
		INT(command_line_high_lod_hack) },
	{ "dwash", "downwash", "rotor downwash (dust) (0 = off, 1 = on) (def = 1)",
		INT(command_line_downwash) },
	{ "restricted_nvg_fov", "", "night vision restriction (0 = off, 1 = on) (def = 1)",
		INT(command_line_restricted_nvg_fov) },
	{ "russian_nvg_no_ir", "", "russian night vision has no FLIR (0 = off, 1 = on) (def = 0)",
		INT(command_line_russian_nvg_no_ir) },
	{ "colourmfd", "", "MFDs will use colour when available (0 = off, 1 = on) (def = 1)",
		INT(command_line_colour_mfd) },
	{ "highreshud", "", "high resolution HUD (0 = off, 1 = on) (def = 1)",
		INT(command_line_high_res_hud) },
	{ "tsdrender", "", "TSD render options (0 - 4) (def = 0 (contours only))",
		INT(command_line_tsd_render_mode) },
	{ "tsdpalette", "", "TSD palette options (0 - 2) (def = 0)",
		INT(command_line_tsd_palette) },
	{ "tsdenemy", "", "TSD showing red force blue force colours (0 = off, 1 = on) (def = 1)",
		INT(command_line_tsd_enemy_colours) },
	{ "tsddetail", "",
		"TSD in high detail (0 = off, 1 = on) (def = 0)", INT(global_tsd_detail) },
	{ "texture_colour", "", "Use texture colours and noisemaps directly. [WARNING!] Use only with correct texture packs. (0 = off, 1 = on, 2 = also use noisemap for higher resolution) (def = 0)",
		INT(command_line_texture_colour) },
	{ "texture_filtering", "", "[EXPERIMENTAL!] texture blending (reacts to anisotropic filter setting) (0 = off, 1 = on) (def = 0)",
		INT(global_anisotropic) },
	{ "mipmapping", "", "mipmapped textures (dds files). [WARNING!] Use only with correct texture packs. (0 = off, 1 = on) (def = 0)",
		INT(global_mipmapping) },
	{ "dynamic_water", "", "dynamic water textures (0 = off, 1 = on) (def = 0)",
		INT(global_dynamic_water) },
	{ "night_light", "", "night light darkness level (0.0 - 1.0) (0.0 = fully dark, 1.0 = less dark) (def = 1.0)",
		FLOAT(global_night_light_level) },
	{ "persistent_smoke", "", "Burning targets emitting smoke for a long time. [Warning!] CPU intensive. (0 = off, 1 = on) (def = 1)",
		INT(command_line_persistent_smoke) },
	{ "cloud_puffs", "", "Cloud puffs. (0 = off, 1 = all maps except desert, 2 = all maps) (def = 1)",
		INT(command_line_cloud_puffs) },
	{ "cloud_puffs_colours", "", "colours for cloud puffs",
		SPEC(set_cloud_puffs_colours, get_cloud_puffs_colours) },
	{ "themes", "", "comma-separated list of directories for alternate psd files",
		SPECSTR(command_line_themes, set_themes, get_string) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, NULL, "[Views and Cameras]",
		NONE },
	{ NULL, NULL, "minfov is linked to key 7, maxfov is linked to key 9, normal fov is linked to key 8, normal fov = 60",
		NONE },
	{ "minfov", "", "general field of view minimum",
		INT(command_line_min_fov) },
	{ "maxfov0", "", "general field of view maximum for Apache pits",
		INT(command_line_max_fov0) },
	{ "maxfov1", "", "general field of view maximum for Havoc pit",
		INT(command_line_max_fov1) },
	{ "maxfov2", "", "general field of view maximum for Comanche pit",
		INT(command_line_max_fov2) },
	{ "maxfov3", "", "general field of view maximum for Hokum-B pit",
		INT(command_line_max_fov3) },
	{ "maxfov4", "", "general field of view maximum for Hind pit",
		INT(command_line_max_fov4) },
	{ "maxfov5", "", "general field of view maximum for Kiowa pit",
		INT(command_line_max_fov5) },
	{ "maxfov6", "", "general field of view maximum for Viper pit",
		INT(command_line_max_fov6) },
	{ "maxfov7", "", "general field of view maximum for Ka-50 pit",
		INT(command_line_max_fov7) },
	{ NULL, "49", "",
		NONE },
	{ "g-force_head_movement", "", "amount of head movement caused by gravitational force (wideview only) (n = Gs, 1.0 = normal, 0.0 = off) (default = 0.0)",
		FLOAT(command_line_g_force_head_movment_modifier) },
	{ "comanche_pilot", "", "wideview pilot position",
		SPEC2(WIDEVIEW_COMANCHE_PILOT, set_position, get_position) },
	{ "comanche_co-pilot", "", "wideview co-pilot position",
		SPEC2(WIDEVIEW_COMANCHE_COPILOT, set_position, get_position) },
	{ "hokum_pilot", "", "wideview pilot position",
		SPEC2(WIDEVIEW_HOKUM_PILOT, set_position, get_position) },
	{ "hokum_co-pilot", "", "wideview co-pilot position",
		SPEC2(WIDEVIEW_HOKUM_COPILOT, set_position, get_position) },
	{ "apache_pilot", "", "wideview pilot position",
		SPEC2(WIDEVIEW_APACHE_PILOT, set_position, get_position) },
	{ "apache_copilot", "", "wideview co-pilot position",
		SPEC2(WIDEVIEW_APACHE_COPILOT, set_position, get_position) },
	{ "havoc_pilot", "", "wideview pilot position",
		SPEC2(WIDEVIEW_HAVOC_PILOT, set_position, get_position) },
	{ "hind_pilot", "", "wideview pilot position",
		SPEC2(WIDEVIEW_HIND_PILOT, set_position, get_position) },
	{ "hind_copilot", "", "wideview co-pilot position",
		SPEC2(WIDEVIEW_HIND_COPILOT, set_position, get_position) },
	{ "viper_pilot", "", "wideview pilot position",
		SPEC2(WIDEVIEW_VIPER_PILOT, set_position, get_position) },
	{ "viper_copilot", "", "wideview co-pilot position",
		SPEC2(WIDEVIEW_VIPER_COPILOT, set_position, get_position) },
	{ "kiowa_pilot", "", "wideview pilot position",
		SPEC2(WIDEVIEW_KIOWA_PILOT, set_position, get_position) },
	{ "kiowa_copilot", "", "wideview co-pilot position",
		SPEC2(WIDEVIEW_KIOWA_COPILOT, set_position, get_position) },
	{ "ka50_pilot", "", "wideview pilot position",
		SPEC2(WIDEVIEW_KA50_PILOT, set_position, get_position) },
	{ "hud_code", "", "hud code for 4 gunships",
		SPEC(set_hud_code, get_hud_code) },
	{ "wobbly-camera", "", "Make external cameras move wobbly and smoother (0 = off, 1 = on) (def = 1)",
		INT(command_line_wobbly_camera) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, "33", "[Dynamics]",
		NONE },
	{ "flight_model", "", "0 is default flight model, 1 is werewolf's flight model, 2 is arneh's model with suspension (def = 2)",
		INT(command_line_dynamics_flight_model) },
	{ "enginerealism", "", "realistic engine workload simulation model (0 = off, 1 = on) (def = 1)",
		INT(command_line_dynamics_advanced_engine_model) },
	{ "enginestartup", "", "manual engine start up, off by default (0 = off, 1 = on) (def = 0)",
		INT(command_line_dynamics_engine_startup) },
	{ "drbs", "command_line_dynamics_retreating_blade_stall_effect", "retreating blade stall, floating point scaling factor for RBS effect (default = 1.0)",
		FLOAT(command_line_dynamics_retreating_blade_stall_effect) },
	{ "drv", "dynamics_rudder_value", "rudder value, scaling factor for drag on tail rotation (default = 1.0)",
		FLOAT(command_line_dynamics_rudder_value) },
	{ "dra", "dynamics_rudder_acceleration", "rudder acceleration, scaling factor for tail rotation acceleration (default = 0.8)",
		FLOAT(command_line_dynamics_rudder_acceleration) },
	{ "drd", "dynamics_rotor_drag", "main rotor drag, scaling factor for drag caused by main rotor (default = 1.0)",
		FLOAT(command_line_dynamics_main_rotor_drag) },
	{ "dmrl", "dynamics_main_rotor_lift", "main rotor lift, scaling factor for lift of main rotor (default = 1.0)",
		FLOAT(command_line_dynamics_main_rotor_lift) },
	{ "dtrd", "dynamics_tail_rotor_drag", "tail rotor drag, scaling factor for drag caused by tail in forward flight (default = 1.0)",
		FLOAT(command_line_dynamics_tail_rotor_drag) },
	{ "dzd", "dynamics_cyclic_dead_zone", "cyclic deadzone (n = %deadzone, 0.0 = no deadzone) (default = 0.0)",
		FLOAT(command_line_dynamics_cyclic_dead_zone) },
	{ "dyal", "dynamics_yaw_altitude_loss", "yaw altitude loss (default = 5.0)",
		FLOAT(command_line_dynamics_yaw_altitude_loss) },
	{ "debug_show_force_vectors", "", "show force vectors on own helicopter for debuging purposes",
		SPEC(set_force_vectors, get_force_vectors) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, "28", "[WUT]",
		NONE },
	{ NULL, NULL, "for more information see http://www.eechcentral.com/wiki/index.php?title=WUT",
		NONE },
	{ "wut", "", "Weapons and Unit Tweaking file (n = filename)",
		SPECSTR(WUT_filename, set_wut, get_string) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, "25", "[Gameplay]",
		NONE },
	{ "chaff", "", "effectiveness of chaff  (0.0 - 1.0) (0.0 = ineffective, 1.0 = fully effective) (def = 1.0)",
		FLOAT(command_line_chaff_effectiveness) },
	{ "flare", "", "effectiveness of flares (0.0 - 1.0) (0.0 = ineffective, 1.0 = fully effective) (def = 1.0)",
		FLOAT(command_line_flare_effectiveness) },
	{ "smoke", "", "effectiveness of smoke  (0.0 - 1.0) (0.0 = ineffective, 1.0 = fully effective) (def = 1.0)",
		FLOAT(command_line_smoke_effectiveness) },
	{ "fog", "", "sets reshroud time for \"fog of war\" (n = seconds) (def = 14400 (4 hours))",
		FLOAT(command_line_fog_of_war_maximum_value) },
	{ "cpac", "capture_aircraft", "Capture and utilize aircraft landed at captured bases (0 = off, 1 = on) (def = 1)",
		INT(command_line_capture_aircraft) },
	{ "uit", "user_invulnerable_time", "User invulnerable time at mission start (n = seconds) (def = 5.0)",
		FLOAT(command_line_user_invulnerable_time) },
	{ NULL, "33", "",
		NONE },
	{ "faa", "", "fly any aircraft (0 = off, 1 = on) (def = 1)",
		SPECINT(command_line_fly_any_airplane, set_faa, get_int) },
	{ "radarinf", "invisible_infantry", "infantry invisible and undetectable by radar (0 = off, 1 = on) (def = 1)",
		INT(command_line_ground_radar_ignores_infantry) },
	{ "grstab", "enable_ground_stabilisation", "ground stabilisation of FLIR (0 = off, 1 = on) (def = 1)",
		INT(command_line_ground_stabilisation_available) },
	{ "manual_laser/radar", "manual_laser_radar", "operate radar and laser manually (0 = off, 1 = on) (def = 0)",
		INT(command_line_manual_laser_radar) },
	{ "targeting_system_auto_page", "", "autoswitch MFD to according targeting system (0 = off, 1 = on) (def = 1)",
		INT(command_line_targeting_system_auto_page) },
	{ "camcom", "", "Campaign Commander (0 = off, 1 = on) (def = 0)",
		INT(command_line_camcom) },
	{ "campaign_map_mode", "", "campaign map resolution (1 = default resolution, 2 = high resolution) (def = 1)",
		INT(command_line_campaign_map) },
	{ "campaign_map_palette", "", "campaign map palette    (1 = default shades, 2 = like paper map",
		INT(command_line_campaign_map_palette) },
	{ "map_update_interval", "", "enemy units update rate (n = seconds) (def = 120)",
		INT(command_line_campaign_map_update_interval) },
	{ "tacview_logging", "", "generate log for tacview (0 = off, 1 = generate log for mission with fog of war, 2 = generate log for mission, all units visible, 3 = generate log for entire campaing",
		INT(command_line_tacview_logging) },
	{ "destgt", "designated_targets", "designated target list (0 = off, 1 = on) (def = 0)",
		INT(command_line_designated_targets) },
	{ "cannontrack", "", "cannon tracking boresight (0 = no tracking, 1 = track if no acquire, 2 = always track IHADSS/HIDSS/HMS) (def = 1) ",
		INT(command_line_cannontrack) },
	{ "unpadlock_on_handover", "", "unpadlock on handover from HMS to TADS = 0 (off)",
		INT(command_line_unpadlock_on_handover) },
	{ "pilot_as_periscope_default", "", "stay in pilot seat when switching to periscope = 0 (off)",
		INT(command_line_pilot_as_periscope_default) },
	{ "autoreturn_to_pilot_after_periscope", "", "switch to pilot seat when deactivating periscope = 0 (off)",
		INT(command_line_autoreturn_to_pilot_after_periscope) },
	{ "TSD_mouse_control", "", "allows mouse control of TSD (Apache only) for selecting targets and creating PFZs",
		INT(command_line_mouse_tsd_target_select) },
	{ "co_pilot_reports_targets", "", "Co-pilot will report targets he finds, and add them to TSD",
		INT(global_co_pilot_scans_for_targets) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, "25", "[Joysticks and TrackIR]",
		NONE },
	{ "eopann", "pan_joystick_index", "joystick number for EO-camera panning",
		INT(command_line_eo_pan_joystick_index) },
	{ "eopanv", "pan_joystick_vertical_axis", "joystick DirectX axis for vertical EO-camera panning",
		SPECINT(command_line_eo_pan_vertical_joystick_axis, set_axis, get_axis) },
	{ "eopanh", "pan_joystick_horizontal_axis", "joystick DirectX axis for horizontal EO-camera panning",
		SPECINT(command_line_eo_pan_horizontal_joystick_axis, set_axis, get_axis) },
	{ "eozoomn", "zoom_joystick_index", "joystick number for EO-camera zooming",
		INT(command_line_eo_zoom_joystick_index) },
	{ "eozoomax", "zoom_joystick_axis", "joystick DirectX axis for EO-camera zooming",
		SPECINT(command_line_eo_zoom_joystick_axis, set_axis, get_axis) },
	{ "field_of_viewn", "", "joystick number for field of view (zoom) of main view",
		INT(command_line_field_of_view_joystick_index) },
	{ "field_of_viewax", "", "joystick DirectX axis for field of view (zoom) of main view",
		SPECINT(command_line_field_of_view_joystick_axis, set_axis, get_axis) },
	{ "cyclicn", "cyclic_joystick_index", "Joystick number for cyclic",
		INT(command_line_cyclic_joystick_index) },
	{ "cyclich", "cyclic_joystick_x_axis", "Joystick DirectX axis for cyclic horizontal",
		SPECINT(command_line_cyclic_joystick_x_axis, set_axis, get_axis) },
	{ "cyclicv", "cyclic_joystick_y_axis", "Joystick DirectX axis for cyclic vertical",
		SPECINT(command_line_cyclic_joystick_y_axis, set_axis, get_axis) },
	{ "collectiven", "collective_joystick_index", "Joystick no. for the collective",
		INT(command_line_collective_joystick_index) },
	{ "collectiveax", "collective_joystick_axis", "Joystick DirectX acis for the collective",
		SPECINT(command_line_collective_joystick_axis, set_axis, get_axis) },
	{ "ruddern", "rudder_joystick_index", "Joystick no. for the rudder",
		INT(command_line_rudder_joystick_index) },
	{ "rudderax", "rudder_joystick_axis", "Joystick DirectX axis for the rudder",
		SPECINT(command_line_rudder_joystick_axis, set_axis, get_axis) },
	{ "joylookn", "joylookn_joystick_axis", "joystick no. used for joystick look",
		INT(command_line_joylook_joystick_index) },
	{ "joylookh", "joylookh_joystick_axis", "joystick DirectX axis used for horizontal joystick look",
		SPECINT(command_line_joylookh_joystick_axis, set_axis, get_axis) },
	{ "joylookv", "joylookv_joystick_axis", "joystick DirectX axis used for vertical joystick look",
		SPECINT(command_line_joylookv_joystick_axis, set_axis, get_axis) },
	{ "joylookst", "joylook_step", "joystick look step (1 = min, 100 = max) (def = 30)",
		INT(command_line_joylook_step) },
	{ "nonlinear-cyclic", "", "use non-linear control for cyclic (less sensitive around center) (0 = off, 1 = on) (def = 1)",
		INT(command_line_nonlinear_pedals) },
	{ "nonlinear-pedals", "", "use non-linear control for pedals (less sensitive around center) (0 = off, 1 = on) (def = 1)",
		INT(command_line_nonlinear_cyclic) },
	{ "nonlinear-collective-zone1", "", "non-linear control value for throttle (n = % throttle position joystick to represents  60% collective) (10% = 0.1) (0.0 = off (linear control), 1.0 = max) (def = 0.3)",
		FLOAT(command_line_collective_zone_1_limit) },
	{ "nonlinear-collective-zone2", "", "non-linear control value for throttle (n = % throttle position joystick to represents 100% collective) (10% = 0.1) (0.0 = off (linear control), 1.2 = max) (def = 0.7)",
		FLOAT(command_line_collective_zone_2_limit) },
	{ "nonlinear-collective-percentage-at-zone1", "", "collective percentage at zone1. Valid values are in range from 1.0 to 99.0, default is 60.0.",
		FLOAT(command_line_collective_percentage_at_zone1) },
	{ "reverse_pedal", "", "reversed pedal input (0 = off/blue force/USA, 1 = on/red force/Russia) (def = 0)",
		INT(command_line_reverse_pedal) },
	{ "reverse_cyclic_x", "", "reverse cyclic x axis (0 = off, 1 = on) (def = 0)",
		INT(command_line_reverse_cyclic_x) },
	{ "reverse_cyclic_y", "", "reverse cyclic y axis (0 = off, 1 = on) (def = 0)",
		INT(command_line_reverse_cyclic_y) },
	{ "msl", "mouselook", "activates mouselook (and TrackIR when present) (0 = off, 1 = internal, 2 = external, 3 = both) (def = 0)",
		INT(command_line_mouse_look) },
	{ "msls", "mousespeed", "mouselook speed (when msl=1) (n > 0) (def = 15), POV speed (when msl=0) (n > 0, max = 20) (def = 13)",
		INT(command_line_mouse_look_speed) },
	{ "TIR_6DOF", "", "6 DoF support for TrackIR (0 = off, 1 = on) (def = 0)",
		INT(command_line_TIR_6DOF) },
	{ "external_trackir", "", "(only when msl=1) external cameras controlled by TrackIR (0 = off, 1 = on) (def = 0)",
		INT(command_line_external_trackir) },
	{ "external_trackir_dir", "external_trackir_direction", "(only when external_trackir=1) invert external cameras view direction (0 = off, 1 = on) (def = 0)",
		INT(command_line_external_trackir_direction) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, NULL, "[Miscellaneous]",
		NONE },
	{ "filter", "session_filter", "session filtering (0 = off, 1 = on) (def = 1)",
		INT(command_line_session_filter) },
	{ "autosave", "", "autosave (n = minutes, 0 = off) (def = 0)",
		SPEC(set_autosave, get_autosave) },
	{ "dfr", "framerate", "display framerate (0 = off, 1 = on, 2 = log to file \"framerate.txt\") (def = 0)",
		INT(command_line_framerate) },
	{ "goto", "planner_goto_button", "\"GOTO\" (teleport) functionality on campaign map (0 = off, 1 = on) (def = 0)",
		INT(command_line_planner_goto_button) },
	{ "vfm", "vector_flight_model", "vector flight model (activates viewer or \"UFO\" flight mode) (0 = off, 1 = on) (def = 0)",
		INT(command_line_vector_flight_model) },
	{ "psr", "player_start_rank", "player start rank for new pilots (1 - 5) (def = 1)",
		INT(command_line_player_start_rank) },
	{ "mta", "max_time_acceleration", "maximum time acceleration (n = time multiplier) (default = 4)",
		INT(command_line_max_time_acceleration) },
	{ "nomcm", "", "no mission complete music (0 = off, 1 = on) (def = 0)",
		INT(command_line_no_mission_complete_music) },
	{ "disable_text_messages", "", "Disables the text messages displayed at top of screen (messages can still be heard) (def = 0)",
		INT(command_line_disable_message_text) },
	{ NULL, "41", "",
		NONE },

	{ "MEMEXPORT", "", "export cockpit information to a shared memory area (0 = off, 1 = on) (def = 0)",
		INT(command_line_shared_mem_export) },
	{ "export_mfd", "", "enables MFD export on multimon systems (0 = off, 1 = on) (def = 0)",
		INT(command_line_export_mfd) },
	{ "export_mfd_adapter", "", "graphic adapter for MFD export screen (0 = first, 1 = second, ...) (def = 0)",
		INT(command_line_export_mfd_adapter) },
	{ "export_mfd_screen_width", "", "resolution of export screen (n = pixels horizontally) (def = 640)",
		INT(command_line_export_mfd_screen_width) },
	{ "export_mfd_screen_height", "", "resolution of export screen (n = pixels vertically) (def = 400)",
		INT(command_line_export_mfd_screen_height) },
	{ "export_mfd_left_pos", "", "left MFD position   (def = 0,0,256,256)",
		SPECINT(command_line_export_mfd_left_pos[0], set_mfd_pos, get_mfd_pos) },
	{ "export_mfd_right_pos", "", "right MFD position (def = 384,0,640,256)",
		SPECINT(command_line_export_mfd_right_pos[0], set_mfd_pos, get_mfd_pos) },
	{ "export_mfd_single_pos", "", "single MFD position (Havoc, Hind and Black Shark only) (def = 0,0,256,256)",
		SPECINT(command_line_export_mfd_single_pos[0], set_mfd_pos, get_mfd_pos) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, "33", "[Sounds]",
		NONE },
	{ "ns", "no_sound", "bypass soundcard (useful for tracking hardware conflicts) (0 = off, 1 = on) (def = 0)",
		INT(command_line_no_sound) },
	{ "sound_device", "", "sound device name",
		SPECSTR(command_line_sound_device, set_sound_device, get_sound_device) },
	{ "sound_device_speech", "", "sound device name for speech",
		SPECSTR(command_line_sound_device_speech, set_sound_device, get_sound_device) },
	{ "hdwrbuf", "", "hardware buffers to use for sound (0 = software only, n = number of hard buffers) (def = 0)",
		INT(command_line_sound_hdwrbuf) },
	{ "canopy_sounds_amp", "", "canopy sounds amplifier controller",
		SPEC(set_canopy_amp, get_canopy_amp) },
	{ "ui_sounds_muted", "", "campaign UI mute (0 = normal UI sounds, 1 = UI sounds muted) (default = 0)",
		INT(command_line_ui_sounds_muted) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, "25", "[Random weather]",
		NONE },
	{ "rw_rrmin", "", "Rain effect minimum radius (meters)",
		FLOAT(weather_rain_radius_min) },
	{ "rw_rrmax", "", "Rain effect maximum radius (meters)",
		FLOAT(weather_rain_radius_max) },
	{ "rw_rsp", "", "Rain effect speed (meters per second)",
		FLOAT(weather_rain_speed) },
	{ "rw_wrmin", "", "Wind effect minimum radius (meters)",
		FLOAT(weather_wind_radius_min) },
	{ "rw_wrmax", "", "Wind effect maximum radius (meters)",
		FLOAT(weather_wind_radius_max) },
	{ "rw_wsp", "", "Wind effect speed (meters per second)",
		FLOAT(weather_wind_speed) },
	{ NULL, NULL, "",
		NONE },

	{ NULL, NULL, "[end of file]",
		NONE },

	{ "directory", "command_line_game_initialisation_phase_directory", "/0",
		CSTR(command_line_game_initialisation_phase_directory) },
	{ "filename", "command_line_game_initialisation_phase_filename", "/0",
		CSTR(command_line_game_initialisation_phase_filename) },
	{ "3dw", NULL, "640",
		SPECINT(command_line_3d_visual_screen_width, set_3dw, NULL) },
	{ "3dh", NULL, "480",
		SPECINT(command_line_3d_visual_screen_height, set_3dh, NULL) },
	{ "3dce", NULL, "1",
		CINT(command_line_3d_visual_clear_edges) },
	{ "cbt", NULL, "1",
		CINT(command_line_cpu_blit_textures) },
	{ "force_resolution", NULL, "1",
		CINT(command_line_force_resolution) },
	{ "vn", "version_number", "",
		SPECINT(command_line_version_number, set_version_number, NULL) },
	{ "aitool_grid_pitch", NULL, "0.0",
		CFLOAT(command_line_aitool_grid_pitch) },
	{ "run_mode", NULL, "0",
		CINT(command_line_run_mode) },
	{ "cdrom", NULL, "Z",
		SPECINT(command_line_cdrom_drive_letter, set_cdrom, NULL) },
	{ "new_graphics", NULL, "1",
		CINT(command_line_new_graphics) },
	{ "ai_use_route_generator", NULL, "1",
		CINT(command_line_ai_use_route_generator) },
	{ "no_convert_graphics", NULL, "1",
		CINT(command_line_no_graphics_conversion) },
	{ "target_point", NULL, "1",
		CINT(command_line_target_point_check) },
	{ "no_pilot_rejection", NULL, "0",
		CINT(command_line_no_pilot_rejection) },
	{ "cheats_on", NULL, "0",
		CINT(command_line_cheats_on) },
	{ "dynamics_sonic_buildup", NULL, "1",
		CINT(command_line_dynamics_sonic_buildup) },
	{ "object_level_of_detail", NULL, "1.0",
		CFLOAT(command_line_object_lod_factor) },
	{ "debug_input", NULL, "1",
		CINT(command_line_debug_input) },
	{ "dump_session", NULL, "1",
		CINT(command_line_dump_session) },
	{ "hardware_render", NULL, "1",
		CINT(command_line_hardware_render) },
	{ "high_res_mfd", NULL, "1",
		CINT(command_line_high_res_mfd) },
	{ "generate_srtm_data", NULL, "0",
		CINT(command_line_tacview_generate_srtm_height_data) },
	{ "3d_cockpit", NULL, "0",
		CINT(command_line_3d_cockpit) },
	{ "ini", NULL, "1",
		CINT(command_line_dump_ini) }
};

#undef NONE
#undef INT
#undef FLOAT
#undef STR
#undef SPEC
#undef SPECINT
#undef SPECSTR
#undef SPEC2
#undef CINT
#undef CFLOAT
#undef CSTR

int parse_option ( const char *name, const char *value )
{
	int i;

	for ( i = 0; i < sizeof ( options ) / sizeof ( *options ); i++ )
	{
		const struct config_option* option = &options[i];
		if ( !option->short_name )
		{
			continue;
		}

		if ( strcmp ( name, option->short_name ) && ( !option->long_name || stricmp ( name, option->long_name ) ) )
		{
			continue;
		}

		option->parse_function ( option, value );

		return TRUE;
	}

	return FALSE;
}

// Casm 09JUN09 Advanced options processing END
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050207 use enum definitions from wm_data.h
static void wide_cockpit_initialize(void)
{
	int
		count;

	//VJ 050205 new wideview init settings
		wide_cockpit_position[WIDEVIEW_COMANCHE_PILOT].cockpit = "Comanche";
		wide_cockpit_position[WIDEVIEW_COMANCHE_PILOT].d.x = 0;
		wide_cockpit_position[WIDEVIEW_COMANCHE_PILOT].d.y = 0.105;
		wide_cockpit_position[WIDEVIEW_COMANCHE_PILOT].d.z = 0.180;
		wide_cockpit_position[WIDEVIEW_COMANCHE_PILOT].d.p = 0;

		wide_cockpit_position[WIDEVIEW_COMANCHE_COPILOT].cockpit = "Comanche";
		wide_cockpit_position[WIDEVIEW_COMANCHE_COPILOT].d.x = 0;
		wide_cockpit_position[WIDEVIEW_COMANCHE_COPILOT].d.y = 0.105;
		wide_cockpit_position[WIDEVIEW_COMANCHE_COPILOT].d.z = 0.180;
		wide_cockpit_position[WIDEVIEW_COMANCHE_COPILOT].d.p = 0;

		wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].cockpit = "Hokum";
		wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].d.z = 0.200;
		wide_cockpit_position[WIDEVIEW_HOKUM_PILOT].d.p = 0.0;

		wide_cockpit_position[WIDEVIEW_HOKUM_COPILOT].cockpit = "Hokum";
		wide_cockpit_position[WIDEVIEW_HOKUM_COPILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_HOKUM_COPILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_HOKUM_COPILOT].d.z = 0.200;
		wide_cockpit_position[WIDEVIEW_HOKUM_COPILOT].d.p = 0.0;
//VJ 050210 defined in vm_data.h
		wide_cockpit_position[WIDEVIEW_APACHE_PILOT].cockpit = "Apache";
		wide_cockpit_position[WIDEVIEW_APACHE_PILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_APACHE_PILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_APACHE_PILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_APACHE_PILOT].d.p = -7.0;

		wide_cockpit_position[WIDEVIEW_APACHE_COPILOT].cockpit = "Apache";
		wide_cockpit_position[WIDEVIEW_APACHE_COPILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_APACHE_COPILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_APACHE_COPILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_APACHE_COPILOT].d.p = -10.0;

		wide_cockpit_position[WIDEVIEW_HAVOC_PILOT].cockpit = "Havoc";
		wide_cockpit_position[WIDEVIEW_HAVOC_PILOT].d.x = BASE_X_HAVOC;
		wide_cockpit_position[WIDEVIEW_HAVOC_PILOT].d.y = BASE_Y_HAVOC;
		wide_cockpit_position[WIDEVIEW_HAVOC_PILOT].d.z = BASE_Z_HAVOC;
		wide_cockpit_position[WIDEVIEW_HAVOC_PILOT].d.p = BASE_P_HAVOC;

		wide_cockpit_position[WIDEVIEW_HIND_PILOT].cockpit = "Hind";
		wide_cockpit_position[WIDEVIEW_HIND_PILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_HIND_PILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_HIND_PILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_HIND_PILOT].d.p = -5.0;

		wide_cockpit_position[WIDEVIEW_HIND_COPILOT].cockpit = "Hind";
		wide_cockpit_position[WIDEVIEW_HIND_COPILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_HIND_COPILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_HIND_COPILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_HIND_COPILOT].d.p = -5.0;

		wide_cockpit_position[WIDEVIEW_VIPER_PILOT].cockpit = "Viper";
		wide_cockpit_position[WIDEVIEW_VIPER_PILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_VIPER_PILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_VIPER_PILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_VIPER_PILOT].d.p = -5.0;

		wide_cockpit_position[WIDEVIEW_VIPER_COPILOT].cockpit = "Viper";
		wide_cockpit_position[WIDEVIEW_VIPER_COPILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_VIPER_COPILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_VIPER_COPILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_VIPER_COPILOT].d.p = -5.0;

		wide_cockpit_position[WIDEVIEW_KIOWA_PILOT].cockpit = "Kiowa";
		wide_cockpit_position[WIDEVIEW_KIOWA_PILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_KIOWA_PILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_KIOWA_PILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_KIOWA_PILOT].d.p = -5.0;

		wide_cockpit_position[WIDEVIEW_KIOWA_COPILOT].cockpit = "Kiowa";
		wide_cockpit_position[WIDEVIEW_KIOWA_COPILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_KIOWA_COPILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_KIOWA_COPILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_KIOWA_COPILOT].d.p = -5.0;

		wide_cockpit_position[WIDEVIEW_KA50_PILOT].cockpit = "Ka-50";
		wide_cockpit_position[WIDEVIEW_KA50_PILOT].d.x = 0.0;
		wide_cockpit_position[WIDEVIEW_KA50_PILOT].d.y = 0.0;
		wide_cockpit_position[WIDEVIEW_KA50_PILOT].d.z = 0.0;
		wide_cockpit_position[WIDEVIEW_KA50_PILOT].d.p = -5.0;

	for (count = 0; count < NUM_WIDEVIEW_NRS; count++)
	{
		wide_cockpit_position[count].c = wide_cockpit_position[count].d;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 030807 adjustable radar ranges
//LEAVE THESE:  even if they are not in eech.ini they need to be initialized before a wut file is read
static void initialize_radar_ranges(void)
{
	radar_range_apache[0] = 500;
	radar_range_apache[1] = 1000;
	radar_range_apache[2] = 2000;
	radar_range_apache[3] = 4000;
	radar_range_apache[4] = 8000;

	radar_range_comanche[0] = 500;
	radar_range_comanche[1] = 1000;
	radar_range_comanche[2] = 2000;
	radar_range_comanche[3] = 4000;
	radar_range_comanche[4] = 8000;

	radar_range_blackhawk[0] = 500;
	radar_range_blackhawk[1] = 1000;
	radar_range_blackhawk[2] = 2000;
	radar_range_blackhawk[3] = 4000;
	radar_range_blackhawk[4] = 8000;

	radar_range_havoc[0] = 1000;
	radar_range_havoc[1] = 2000;
	radar_range_havoc[2] = 4000;
	radar_range_havoc[3] = 6000;

	radar_range_hokum[0] = 1000;
	radar_range_hokum[1] = 2000;
	radar_range_hokum[2] = 4000;
	radar_range_hokum[3] = 6000;
	radar_range_hokum[4] = 10000;

	radar_range_hind[0] = 1000;
	radar_range_hind[1] = 2000;
	radar_range_hind[2] = 4000;
	radar_range_hind[3] = 6000;

	// GCsDriver  08-12-2007
	radar_range_default[0] = 500;
	radar_range_default[1] = 1000;
	radar_range_default[2] = 2000;
	radar_range_default[3] = 4000;
	radar_range_default[4] = 8000;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialize_options ( void )
{
	int
		i;

//VJ 030511, get wideview cockpit mod defaults in aphavoc\source\gunships\views\vm_event.c
	wide_cockpit_initialize();

//VJ 030807 initialize radar ranges, do it here because they need initializing even if eech.ini doesn't work
//VJ 050125 changed back: this should always be done
	initialize_radar_ranges();

	//VJ 060212 hud info mod
	memset ( hud_code, 0, sizeof ( hud_code ) );
	for ( i = 0; i < sizeof ( hud_code ) / sizeof ( *hud_code ) ; i++ )
	{
		hud_code[i][HUD_CODES_SIZE] = 10;
		hud_code[i][HUD_CODES_MFD] = 20;
	}

// Casm 03MAR10 Canopy sound amplification control
	memset ( canopy_sound_amp, 0, sizeof ( canopy_sound_amp ) );
	set_canopy_amp ( NULL, "450,90,375;15,15,100;120,80,100;10,10,100;240,10,100;20,20,100;180,20,100;180,10,100;" );

	strcpy(WUT_filename, DEFAULT_GWUT_FILE);
	command_line_wut = file_exist ( WUT_filename );

	strcpy ( command_line_themes, "2" );

	set_cloud_puffs_colours ( NULL, "220,230,255;230,230,255;235,235,255;245,245,255;250,250,255;255,255,255" );
}

void process_ini_file (void)
{
	FILE *file;

	char buf[1024];

	if ( !command_line_dump_ini )
	{
		return;
	}

//VJ 030409, changed to generate eech.ini when it doesn't exist
	if ( !file_exist ( EECH_INI ) )
	{
		dump_ini_file();
	}

	file = safe_fopen ( EECH_INI, "r" );

	while ( fgets ( buf, sizeof ( buf ), file ) )
	{
		char *ptr = strchr ( buf, '#' );
		if ( ptr )
		{
			*ptr = '\0';
		}
		else
		{
			ptr = buf + strlen ( buf );
		}

		if ( ptr == buf )
		{
			continue;
		}

		while ( --ptr != buf && isspace ( *ptr ) );

		*++ptr = '\0';

		ptr = strchr ( buf, '=' );

		if ( ptr )
		{
			*ptr = 0;
			parse_option ( buf, ptr + 1 );
		}
	}

	fclose ( file );

//VJ 050818 water doesn't work without the colour texture mod
	if ( command_line_texture_colour == 0 )
		global_dynamic_water = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 030511 rewrote dump_ini_file
//Kassie 071101 eech.ini makeover
// parameter=n (information about n) (def = n)
void dump_ini_file ( void )
{
	size_t column = 40;
	FILE *file = safe_fopen ( EECH_INI, "w" );
	unsigned i;

	for ( i = 0; i < sizeof ( options ) / sizeof ( *options ); i++ )
	{
		const struct config_option* option = &options[i];
		if ( option->short_name )
		{
			char value[256];

			if ( !option->print_function )
			{
				continue;
			}

			{
				char print_value[256];
				option->print_function ( option, print_value );
				snprintf ( value, sizeof ( value ), "%s=%s", option->short_name, print_value );
			}

			{
				size_t length = strlen ( value ) - 1;
				length = length < column ? column - length : 1;
				fprintf ( file, "%s% *c# %s\n", value, length, ' ', option->description );
			}
		}
		else
		{
			if ( option->description[0] == '[' || option->description[0] == '\0' )
			{
				fprintf ( file, "%s\n", option->description );
			}
			else
			{
				fprintf ( file, "# %s\n", option->description );
			}

			if ( option->long_name )
			{
				column = atoi ( option->long_name );
			}
		}
	}

	fclose ( file );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
