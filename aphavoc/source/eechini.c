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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ 030807 adjustable cannon rounds
//VJ 040229 also needed in new GWUT structure, if new aircraft flyable add here
int 	rounds_comanche, 
		rounds_apache, 
		rounds_hokum_HE, 
		rounds_hokum_AP, 
		rounds_havoc_HE, 
		rounds_havoc_AP, 
		rounds_blackhawk, 
		rounds_hind_HE,
		rounds_hind_AP;


static void initialize_rounds(void)
{
	//VJ 040229 default values
	rounds_comanche = 500;	// wp 5
	rounds_apache = 1200;	//wp 3
	rounds_hokum_HE = 230;	//wp 5
	rounds_hokum_AP = 240;	// wp 6
	rounds_havoc_HE = 130;   // wp 3
	rounds_havoc_AP = 130;   // wp 4
	rounds_blackhawk = 1200; //wp 3
	rounds_hind_HE = 130;   // wp 3
	rounds_hind_AP = 130;   // wp 4
}	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 030511 moved to eechini from vm_event.c, needed for intialisation of wide view cockpit
static void wide_cockpit_initialize(void)
{
		wide_cockpit_position[0].x = 0;
		wide_cockpit_position[0].y = 1.1;
		wide_cockpit_position[0].z = -2.43;
		//comanche
		wide_cockpit_position[1].x = 0;
		wide_cockpit_position[1].y = 0.8;
		wide_cockpit_position[1].z = -1.03;
		//comanche co-pilot
		
		wide_cockpit_position[2].x = 0.375;
		wide_cockpit_position[2].y = 2.075;
		wide_cockpit_position[2].z = -1.810;
		//hokum
		
		wide_cockpit_position[3].x = -0.375;
		wide_cockpit_position[3].y = 2.075;
		wide_cockpit_position[3].z = -1.810;
		//hokum co-pilot
		
		wide_cockpit_position[4].x = 0;
		wide_cockpit_position[4].y = 0.07;
		wide_cockpit_position[4].z = 0.55;
		//apache
		
		wide_cockpit_position[5].x = 0;
		wide_cockpit_position[5].y = 0.095;
		wide_cockpit_position[5].z = 0.335;			
		//havoc
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 030807 adjustable radar ranges
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
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 030807 adjustable cannon rounds
//VJ 040229 This becomes obsolete with new type GWUT
void adjust_rounds(int start, int stop, int type, int value, int *rounds)
{
	int config_type, package;
	for(config_type = start; config_type <= stop; config_type++)
		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == type)
			{
				weapon_config_database[config_type][package].number = value;
			}
		}	   
	*rounds = value;	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_ini_file(int argc, char *argv[])
{
	 FILE *f;

	 char *buf;
	 char *p, *q;
	 char fname[12] = "eech.ini";
	 float v1;
	 int d1, k;

//VJ 030511, get wideview cockpit mod defaults in aphavoc\source\gunships\views\vm_event.c
	 wide_cockpit_initialize();

//VJ 030807 initialize radar ranges, do it here because they need initializing even if eech.ini doesn't work 
	 initialize_radar_ranges();	

//VJ 030807 initialize nr rounds cannons
	 initialize_rounds();

		
	 buf = malloc (255);
	 if (buf == NULL)
	 {
		  debug_fatal ("Could not allocate buffer");
		  return;
	 }

//VJ 030414, commandline /ini:0 starts up without ini file
	 while(argc--)
	 {
		 p = *argv++;
		 debug_log("eech.ini %s",p);
		 if( strstr(p, "ini:0"))
		 {
			free(buf);
			return;
		 }
	 }
	 
//VJ 030409, changed to generate eech.ini when it doesn't exist
	 if (command_line_dump_ini && !file_exist(fname))
	 {
		 dump_ini_file();
	 }

	 f = fopen(fname, "r");
	 if (!f)
	 {
		 free(buf);
		 debug_fatal("Error opening eech.ini");
		 return;
	 }
	 while (!strstr(buf,"end of file"))
	 {
		int i = 0;
		fscanf(f,"%[^\n]\n",buf);
      
		if (!strchr(buf,'='))
		  continue;
      
		p = strtok(buf,"=");
		q = strtok(NULL,"#");
		while(q[i]!=' ')
		 i++;
		q[i] = '\0';

		sscanf(q,"%f",&v1);
		sscanf(q,"%d",&d1);
//GAME
		if (strcmp(p, "chaff")==0)  command_line_chaff_effectiveness = v1;
		if (strcmp(p, "flare")==0)  command_line_flare_effectiveness = v1;
		if (strcmp(p, "smoke")==0)  command_line_smoke_effectiveness = v1;
		if (strcmp(p, "fog"  )==0)  command_line_fog_of_war_maximum_value = v1;
		if (strcmp(p, "cpac")==0) 	command_line_capture_aircraft = d1;
		if (strcmp(p, "uit")==0) 	command_line_user_invulnerable_time = v1;
//GRAPH
		if (strcmp(p, "cbar")==0)  	command_line_city_block_approximation_range = v1;
		if (strcmp(p, "mfr")==0)  	command_line_max_frame_rate = d1;
		if (strcmp(p, "fs")==0) 		command_line_full_screen = d1;
		if (strcmp(p, "32bit")==0)
		{
			command_line_display_bpp=16;
		 if (d1 == 1)
			command_line_display_bpp=32;
		}

		if (strcmp(p, "nrt")==0)  	command_line_no_render_to_texture = d1;
		if (strcmp(p, "notnl")==0) 	command_line_no_hardware_tnl = d1;
		if (strcmp(p, "3dreset")==0)
		{
			if (d1 == 1)
			{
				 set_global_3d_visual_screen_width(640.0);
				 set_global_3d_visual_screen_height(480.0);
			}
		}
		if (strcmp(p, "dxtm")==0) 	command_line_d3d_use_texture_management = d1;
		if (strcmp(p, "cg")==0) 		command_line_clean_graphics = d1;
//COMMS
		if (strcmp(p, "ipa")==0)
		  if(strlen(q)!=0)
				strcpy(command_line_ip_address, q);
		if (strcmp(p, "pss")==0)
		  if(strlen(q)!=0)
				strcpy(command_line_primary_server_setting, q);
		if (strcmp(p, "sss")==0)
		  if(strlen(q)!=0)
				strcpy(command_line_secondary_server_setting, q);

		if (strcmp(p, "usemaster")==0) 	command_line_report_to_masterserver = d1; //Werewolf 2 Jan 04
				
		if (strcmp(p, "ccrs")==0) 	command_line_comms_connection_receive_size = d1;
		if (strcmp(p, "cdrs")==0) 	command_line_comms_data_record_size = d1;
		if (strcmp(p, "cpbs")==0) 	command_line_comms_pack_buffer_size = d1;
		if (strcmp(p, "cpds")==0) 	command_line_comms_packet_data_size = d1;
		if (strcmp(p, "cgs")==0) 	command_line_comms_guaranteed_send = d1;
		if (strcmp(p, "crls")==0) 	command_line_comms_resend_list_size = d1;
		if (strcmp(p, "crl")==0) 	command_line_comms_packet_rerequest_limit = d1;
		if (strcmp(p, "cpt")==0) 	command_line_comms_packet_resend_timer = v1;
		if (strcmp(p, "crto")==0) 	command_line_comms_resend_timeout = v1;
		if (strcmp(p, "mur")==0) 	command_line_max_game_update_rate = d1;
		if (strcmp(p, "cig")==0) 	command_line_comms_interpolate_gunships = d1;
		if (strcmp(p, "cvc")==0) 	command_line_comms_validate_connections = d1;
		if (strcmp(p, "cptl")==0) 	command_line_comms_packet_throttle_limit = d1;
		if (strcmp(p, "cto")==0) 	command_line_comms_timeout = d1;
		if (strcmp(p, "eufr")==0) 	command_line_entity_update_frame_rate = d1;
		if (strcmp(p, "css")==0) 	command_line_comms_show_stats = d1;
		if (strcmp(p, "cist")==0) 	command_line_comms_initial_sleep_time = d1;
		if (strcmp(p, "servlog")==0) // Jabberwock 031119 Server log
		  if (strlen(q)!=0)
			  strcpy(command_line_server_log_filename, q); 
		if (strcmp(p, "pauseserv")==0) 	command_line_pause_server = d1; // Jabberwock 040220 Pause server
		if (strcmp(p, "dedicated")==0) 	command_line_comms_dedicated_server = d1;
		if (strcmp(p, "game_type")==0) 	command_line_game_initialisation_phase_game_type = d1;
		if (strcmp(p, "gunship_type")==0) command_line_game_initialisation_phase_gunship_type = d1;
		if (strcmp(p, "path")==0)
		  if (strlen(q)!=0)
			  strcpy(command_line_game_initialisation_phase_path, q);
//DYN
		if (strcmp(p, "advancedfm")==0) command_line_dynamics_advanced_flight_model = d1; //Werewolf 3 Jan 04
		if (strcmp(p, "drbs")==0) 	command_line_dynamics_retreating_blade_stall_effect = v1;
		if (strcmp(p, "drv")==0) 	command_line_dynamics_rudder_value = v1;
		if (strcmp(p, "dra")==0) 	command_line_dynamics_rudder_acceleration = v1;
		if (strcmp(p, "drd")==0) 	command_line_dynamics_main_rotor_drag = v1;
		if (strcmp(p, "dmrl")==0) 	command_line_dynamics_main_rotor_lift = v1;
		if (strcmp(p, "dtrd")==0) 	command_line_dynamics_tail_rotor_drag = v1;
		if (strcmp(p, "dcdz")==0) 	command_line_dynamics_cyclic_dead_zone = v1;
		if (strcmp(p, "dyal")==0) 	command_line_dynamics_yaw_altitude_loss = v1;
//MISC
		if (strcmp(p, "goto")==0) 	command_line_planner_goto_button = d1;
		if (strcmp(p, "vfm")==0) 	command_line_vector_flight_model = d1;
		if (strcmp(p, "psr")==0) 	command_line_player_start_rank = d1;
		if (strcmp(p, "ns")==0) 		command_line_no_sound=d1;
		if (strcmp(p, "mta")==0) 	command_line_max_time_acceleration = d1;
		if (strcmp(p, "nomcm")==0) 	command_line_no_mission_complete_music = d1;
//WUT
//VJ 030511 WUT is a separate part of the eech.ini
		if (strcmp(p, "wut") == 0)
		{
			if (strlen(q)!=0)
				strcpy(WUT_filename, q);

			debug_log("wutfile ini [%s]",WUT_filename);

			if (WUT_filename[0] != 0 && file_exist(WUT_filename))
				command_line_wut = TRUE;
			// wut filename checking is done elsewhere	
		}
//WIDEVIEW
//VJ 030511 added the wideview params to eech.ini
 	if (strcmp(p, "commanche pilot")==0)
 	{
    	     
 	     p = strtok(q,",");
        wide_cockpit_position[0].x = atof(p);
 	     p = strtok(NULL,",");
	     wide_cockpit_position[0].y = atof(p);
	     p = strtok(NULL,",");
	     wide_cockpit_position[0].z = atof(p);
	}
 	if (strcmp(p, "commanche co-pilot")==0)
 	{
    	     
 	     p = strtok(q,",");
        wide_cockpit_position[1].x = atof(p);
 	     p = strtok(NULL,",");
	     wide_cockpit_position[1].y = atof(p);
	     p = strtok(NULL,",");
	     wide_cockpit_position[1].z = atof(p);
	}
 	if (strcmp(p, "hokum pilot")==0)
 	{
    	     
 	     p = strtok(q,",");
        wide_cockpit_position[2].x = atof(p);
 	     p = strtok(NULL,",");
	     wide_cockpit_position[2].y = atof(p);
	     p = strtok(NULL,",");
	     wide_cockpit_position[2].z = atof(p);
	}
 	if (strcmp(p, "holum co-pilot")==0)
 	{
    	     
 	     p = strtok(q,",");
        wide_cockpit_position[3].x = atof(p);
 	     p = strtok(NULL,",");
	     wide_cockpit_position[3].y = atof(p);
	     p = strtok(NULL,",");
	     wide_cockpit_position[3].z = atof(p);
	}
 	if (strcmp(p, "apache pilot")==0)
 	{
    	     
 	     p = strtok(q,",");
        wide_cockpit_position[4].x = atof(p);
 	     p = strtok(NULL,",");
	     wide_cockpit_position[4].y = atof(p);
	     p = strtok(NULL,",");
	     wide_cockpit_position[4].z = atof(p);
	}
 	if (strcmp(p, "havoc pilot")==0)
 	{
    	     
 	     p = strtok(q,",");
        wide_cockpit_position[5].x = atof(p);
 	     p = strtok(NULL,",");
	     wide_cockpit_position[5].y = atof(p);
	     p = strtok(NULL,",");
	     wide_cockpit_position[5].z = atof(p);
	}
		
//MODS
		if (strcmp(p, "msl") == 0) 			command_line_mouse_look = d1;
		if (strcmp(p, "msls") == 0)			command_line_mouse_look_speed = d1;
		if (strcmp(p, "minfov") == 0) 		command_line_min_fov = d1;
		if (strcmp(p, "maxfov") == 0) 		command_line_max_fov = d1;
		if (strcmp(p, "eopann") == 0) 		command_line_eo_pan_joystick_index = d1;
		if (strcmp(p, "eopanv") == 0) 		command_line_eo_pan_vertical_joystick_axis = d1 - 1;
		if (strcmp(p, "eopanh") == 0) 		command_line_eo_pan_horizontal_joystick_axis = d1 - 1;
		if (strcmp(p, "eozoomn") == 0)		command_line_eo_zoom_joystick_index = d1;
		if (strcmp(p, "eozoomax") == 0)		command_line_eo_zoom_joystick_axis = d1 - 1;
		if (strcmp(p, "joylookn") == 0)		command_line_joylook_joystick_index = d1; // Jabberwock 031104
		if (strcmp(p, "joylookh") == 0)		command_line_joylookh_joystick_axis = d1 - 1; // Jabberwock 031104
		if (strcmp(p, "joylookv") == 0)		command_line_joylookv_joystick_axis = d1 - 1; // Jabberwock 031104
		if (strcmp(p, "joylookst") == 0)	command_line_joylook_step = d1; // Jabberwock 031104
		if (strcmp(p, "radarinf") == 0)		command_line_ground_radar_ignores_infantry = d1;
		if (strcmp(p, "grstab") == 0) 		command_line_ground_stabilisation_available = d1;

		if (strcmp(p, "dfr") == 0) 			command_line_framerate = d1;
		if (strcmp(p, "keymap") == 0) 		command_line_key_mapping = d1;		
		if (strcmp(p, "dwash") == 0)			command_line_downwash = d1; 
		if (strcmp(p, "cyclicn") == 0)		command_line_cyclic_joystick_index = d1;
		if (strcmp(p, "cyclich") == 0)		command_line_cyclic_joystick_x_axis = d1 - 1;
		if (strcmp(p, "cyclicv") == 0)		command_line_cyclic_joystick_y_axis = d1 - 1;
		if (strcmp(p, "collectiven") == 0)	command_line_collective_joystick_index = d1;
		if (strcmp(p, "collectiveax") == 0) command_line_collective_joystick_axis = d1 - 1;
		if (strcmp(p, "ruddern") == 0)		command_line_rudder_joystick_index = d1;
		if (strcmp(p, "rudderax") == 0)		command_line_rudder_joystick_axis = d1 - 1;
		if (strcmp(p, "highresmfd") == 0)	command_line_high_res_mfd = d1; // loke 030420
		if (strcmp(p, "maxplayers") == 0)	command_line_maxplayers = d1; // Werewolf 030518
		if (strcmp(p, "camcom") == 0)		command_line_camcom = d1; // Jabberwock 031007 Campaign Commander
		if (strcmp(p, "destgt") == 0)		command_line_designated_targets = d1; // Jabberwock 031107 Designated targets
		if (strcmp(p, "filter") == 0)		command_line_session_filter = d1; // Jabberwock 031210 Session filter
		if (strcmp(p, "greenmfd") == 0)		command_line_green_mfd = d1; // loke 030518
		if (strcmp(p, "tsdrender") == 0)		command_line_tsd_render_mode = d1; // VJ 030511
		if (strcmp(p, "tsdpalette") == 0)	command_line_tsd_palette = d1; // VJ 030511
		if (strcmp(p, "tsdenemy") == 0)		command_line_tsd_enemy_colours = d1; // VJ 030511
		if (strcmp(p, "reverse_pedal") == 0)command_line_reverse_pedal = d1;	// Retro 17Jul2004
		if (strcmp(p, "faa") == 0)
		{
			// VJ 030424 fly any aircraft optional, default on
			////Moje 030609 Changed k-value from 4 to 6 Blackhawk and Hind is always flyable now
			////Moje 030816 Changed the next expression to get the AH64A and KA50 always flyable
			////            number 21 and 22 in ac_dbase.c
			//// 030820 On a 2nd thought, I put back the orginal. Not everyone want's the new choppers

			command_line_fly_any_airplane = d1;
			if (command_line_fly_any_airplane == 0)
			{
				for (k=4; k < NUM_ENTITY_SUB_TYPE_AIRCRAFT; k++)
					aircraft_database[k].player_controllable = FALSE;
			}
		}
//VJ 030807 adjustable radar ranges		
//VJ 040229 radar ranges OBSOLETE when using new GWUT files, moved to GWUT file where they belong!
		if (strcmp(p, "radar_comanche") == 0)
		{
 	     p = strtok(q,",");
        radar_range_comanche[0] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_comanche[1] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_comanche[2] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_comanche[3] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_comanche[4] = atof(p);
		}
		if (strcmp(p, "radar_apache") == 0)
		{
 	     p = strtok(q,",");
        radar_range_apache[0] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_apache[1] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_apache[2] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_apache[3] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_apache[4] = atof(p);
		}
		if (strcmp(p, "radar_hokum") == 0)
		{
 	     p = strtok(q,",");
        radar_range_hokum[0] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_hokum[1] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_hokum[2] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_hokum[3] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_hokum[4] = atof(p);
		}
		if (strcmp(p, "radar_havoc") == 0)
		{
 	     p = strtok(q,",");
        radar_range_havoc[0] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_havoc[1] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_havoc[2] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_havoc[3] = atof(p);
		}
		if (strcmp(p, "radar_blackhawk") == 0)
		{
 	     p = strtok(q,",");
        radar_range_blackhawk[0] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_blackhawk[1] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_blackhawk[2] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_blackhawk[3] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_blackhawk[4] = atof(p);
		}
		if (strcmp(p, "radar_hind") == 0)
		{
 	     p = strtok(q,",");
        radar_range_hind[0] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_hind[1] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_hind[2] = atof(p);
 	     p = strtok(NULL,",");
        radar_range_hind[3] = atof(p);
		}
		
//VJ 030807 adjustable cannon rounds	
//VJ 040229 ammo OBSOLETE when using new GWUT files, moved to GWUT file where they belong!
		if (strcmp(p, "rounds_comanche") == 0)   
		  adjust_rounds(WEAPON_CONFIG_TYPE_RAH66_COMANCHE_1, WEAPON_CONFIG_TYPE_RAH66_COMANCHE_384, ENTITY_SUB_TYPE_WEAPON_M197_20MM_ROUND, d1, &rounds_comanche);
		if (strcmp(p, "rounds_apache") == 0)
		  adjust_rounds(WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_1, WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_50, ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND, d1, &rounds_apache);
		if (strcmp(p, "rounds_blackhawk") == 0)
		  adjust_rounds(WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_1, WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_9, ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND, d1, &rounds_blackhawk);
		if (strcmp(p, "rounds_hokum_HE") == 0)
		  adjust_rounds(WEAPON_CONFIG_TYPE_KA52_HOKUM_B_1, WEAPON_CONFIG_TYPE_KA52_HOKUM_B_30, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND, d1, &rounds_hokum_HE);
		if (strcmp(p, "rounds_hokum_AP") == 0)
		  adjust_rounds(WEAPON_CONFIG_TYPE_KA52_HOKUM_B_1,WEAPON_CONFIG_TYPE_KA52_HOKUM_B_30,ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,d1, &rounds_hokum_AP);
		if (strcmp(p, "rounds_havoc_HE") == 0)
		  adjust_rounds(WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_1,WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_30,ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,d1, &rounds_havoc_HE);
		if (strcmp(p, "rounds_havoc_AP") == 0)
		  adjust_rounds(WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_1,WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_30,ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,d1, &rounds_havoc_AP);
		if (strcmp(p, "rounds_hind_HE") == 0)
		  adjust_rounds(WEAPON_CONFIG_TYPE_MI24D_HIND_1,WEAPON_CONFIG_TYPE_MI24D_HIND_18,ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,d1, &rounds_hind_HE);
		if (strcmp(p, "rounds_hind_AP") == 0)
		  adjust_rounds(WEAPON_CONFIG_TYPE_MI24D_HIND_1,WEAPON_CONFIG_TYPE_MI24D_HIND_18,ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,d1, &rounds_hind_AP);
	}

	fclose(f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 030511 rewrote dump_ini_file
void dump_ini_file(void)
{
	FILE *f = fopen("eech.ini","w");
	
		
	fprintf(f,"[Enemy Engaged - Comanche Hokum commandline options]\n");
	fprintf(f,"[Game]\n");
	fprintf(f,"chaff=%3.1f        # Effectivness of chaff where n = 0.0 (ineffective) to 1.0 (fully effective - default)\n",command_line_chaff_effectiveness);
	fprintf(f,"flare=%3.1f        # Effectivness of flares where n = 0.0 (ineffective) to 1.0 (fully effective - default)\n",command_line_flare_effectiveness);
	fprintf(f,"smoke=%3.1f        # Effectivness of smoke where n = 0.0 (ineffective) to 1.0 (fully effective - default)\n",command_line_smoke_effectiveness);
	fprintf(f,"fog=%.0f            # Sets the time (sec) taken for the \"fog of war\" to reshroud enemy sector info (def 4 hours).\n",command_line_fog_of_war_maximum_value);
	fprintf(f,"cpac=%d              # capture aircraft: aircraft landed at captured bases or FARPS become usable by your side.\n",command_line_capture_aircraft);
	fprintf(f,"uit=%3.1f            # user invulnerable time (default 5 sec), when starting mission\n",command_line_user_invulnerable_time);
	fprintf(f,"[Graphics]\n");
	fprintf(f,"cbar=%.0f            # distance in meters that city blocks resolve\n",command_line_city_block_approximation_range);
	fprintf(f,"fs=%d                # Switch for turning off the default FULL SCREEN video mode, (def = 1, full screen)\n",command_line_full_screen);
	fprintf(f,"mfr=%d               # Max visual frame rate, (defaults = 30)\n",command_line_max_frame_rate);
	if (command_line_display_bpp == 16)
		fprintf(f,"32bit=0             # Activates 32bit rendering if your video card supports it\n");
	else
		fprintf(f,"32bit=1             # Activates 32bit rendering if your video card supports it\n");
	fprintf(f,"nrt=%d               # Turns off rendering to texture in case of visual problems with MFDs or TADS\n",command_line_no_render_to_texture);
	fprintf(f,"notnl=%d             # Turns off GeForce \"TnL\" support for troubleshooting\n",command_line_no_hardware_tnl);
	fprintf(f,"3dreset=0            # Reset screen resolution to 640x480 (def = 0)\n");
	fprintf(f,"dxtm=%d              # directx texture management, should fix \"unable to allocate hardware slot\" error (def = 0)\n",command_line_d3d_use_texture_management);
	fprintf(f,"cg=0                # clean graphics, re-installs graphics files (def = 0)\n");
	fprintf(f,"[Communications]\n");
	fprintf(f,"maxplayers=%d        # maximum number of players in a multiplayer game, def = 4\n",command_line_maxplayers);
	fprintf(f,"ipa=%s               # ip address = TCPIP address to connect to. A HOST can leave out the value.\n",command_line_ip_address);
	fprintf(f,"usemaster=%d         # Report game to internet masterserver (0 for private games)\n",command_line_report_to_masterserver);  //Werewolf 2 Jan 04
	fprintf(f,"pss=%s               # primary masterserver setting (server internet address)\n",command_line_primary_server_setting);  //Werewolf: Defaults changed 080403
	fprintf(f,"sss=%s               # secondary masterserver setting (server internet address)\n",command_line_secondary_server_setting);
	fprintf(f,"ccrs=%d              # connection receive size, initial guess of campaign data size (default = 200k)\n",command_line_comms_connection_receive_size);
	fprintf(f,"cdrs=%d              # data record size, similar to above…\n",command_line_comms_data_record_size);
	fprintf(f,"cpbs=%d              # pack buffer size, similar to above…\n",command_line_comms_pack_buffer_size);
	fprintf(f,"cpds=%d              # packet data size (def = 512)\n",command_line_comms_packet_data_size);
	fprintf(f,"cgs=%d               # force the comms to use DirectPlay guaranteed send instead of its own (def=0).\n",command_line_comms_guaranteed_send);
	fprintf(f,"crls=%d              # packet history list size, increase if client keeps getting kicked out by server (default = 1000)\n",command_line_comms_resend_list_size);
	fprintf(f,"crl=%d               # number of times a client can re-request the same packet, increase for poor connections (def=10)\n",command_line_comms_packet_rerequest_limit);
	fprintf(f,"cpt=%.0f             # time delay in seconds the comms will wait for a packet before re-requesting it. (default = 5s)\n",command_line_comms_packet_resend_timer);
	fprintf(f,"crto=%.0f            # time comms will wait before assuming re-requested packets was lost (default = 2s)\n",command_line_comms_resend_timeout);
	fprintf(f,"mur=%d               # max update framerate for a server, na for a client (default = 5fps for TCPIP, 15fps for IPX)\n",command_line_max_game_update_rate);
	fprintf(f,"cig=%d               # interpolate helicopter position for smoother visuals\n",command_line_comms_interpolate_gunships);
	fprintf(f,"cvc=%d               # validate connection, removes dead player husks when client crashes\n",command_line_comms_validate_connections);
	fprintf(f,"cptl=%d              # packet throttle limit, mainly for modems, governs the flow rate of packets\n",command_line_comms_packet_throttle_limit);
	fprintf(f,"cto=%d               # timeout, the amount of time to wait before removing dead player husks\n",command_line_comms_timeout);
	fprintf(f,"eufr=%d              # client server entity update framerate, no. of iterations\n",command_line_entity_update_frame_rate);
	fprintf(f,"css=%d               # show communication stats (def = 0)\n",command_line_comms_show_stats);
	fprintf(f,"cist=%d              # comms initial sleep time\n",command_line_comms_initial_sleep_time);
	fprintf(f,"servlog=%s           # filename for server log\n",command_line_server_log_filename);
	fprintf(f,"pauseserv=%d         # pause server if no clients connected\n",command_line_pause_server); // 040320 Jabberwock - Pause server
	fprintf(f,"dedicated=%d         # active server mode, off by default.\n",command_line_comms_dedicated_server);
	fprintf(f,"game_type=%d         # Valid game_types are: 1 = Freeflight, 2 = Campaign, 3 = Skirmish (def = 0)\n",command_line_game_initialisation_phase_game_type);
	fprintf(f,"gunship_type=%d      # Gunship_types are, 0 = Apache, 1 = Havoc, 2 = Comanche, 3 = Hokum\n",command_line_game_initialisation_phase_gunship_type);
	fprintf(f,"path=%s              # Path to map, campaign, skirmish\n",command_line_game_initialisation_phase_path);
	fprintf(f,"[Dynamics]\n");
	fprintf(f,"advancedfm=%d      # advanced (more complex) flight model, off by default.\n",command_line_dynamics_advanced_flight_model);
	fprintf(f,"drbs=%3.1f         # retreating blade stall, floating point scaling factor for RBS effect (default = 1.0)\n",command_line_dynamics_retreating_blade_stall_effect);
	fprintf(f,"drv=%3.1f          # rudder value, scaling factor for drag on tail rotation (default = 1.0)\n",command_line_dynamics_rudder_value);
	fprintf(f,"dra=%3.1f          # rudder acceleration, scaling factor for tail rotation acceleration (default = 0.8)\n",command_line_dynamics_rudder_acceleration);
	fprintf(f,"drd=%3.1f          # main rotor drag, scaling factor for drag caused by main rotor (default = 1.0)\n",command_line_dynamics_main_rotor_drag);
	fprintf(f,"dmrl=%3.1f         # main rotor lift, scaling factor for lift of main rotor (default = 1.0)\n",command_line_dynamics_main_rotor_lift);
	fprintf(f,"dtrd=%3.1f         # tail rotor drag, scaling factor for drag caused by tail in forward flight (default = 1.0)\n",command_line_dynamics_tail_rotor_drag);
	fprintf(f,"dzd=%3.1f          # cyclic dead zone, percentage deadzone for the cyclic (default = 0.0)\n",command_line_dynamics_cyclic_dead_zone);
	fprintf(f,"dyal=%3.1f         # yaw altitude loss (default = 5.0)\n",command_line_dynamics_yaw_altitude_loss);
	fprintf(f,"[Miscellaneous]\n");
	fprintf(f,"goto=%d              # Activates \"GOTO\" teleport button on the campaign map.\n",command_line_planner_goto_button);
	fprintf(f,"vfm=%d               # vector flight model, activates viewer or \"UFO\" flight mode.\n",command_line_vector_flight_model);
	fprintf(f,"psr=%d               # player start rank for new pilots\n",command_line_player_start_rank);
	fprintf(f,"ns=%d                # Bypass soundcard, useful for tracking hardware conflicts\n",command_line_no_sound);
	fprintf(f,"mta=%d               # The maximum multiplier allowed for time acceleration (default - 4)\n",command_line_max_time_acceleration);
	fprintf(f,"nomcm=%d             # no mission complete music\n",command_line_no_mission_complete_music);
	fprintf(f,"[WUT]\n");
	fprintf(f,"wut=%s               # supply a filename of a wut text file here\n",WUT_filename);
	fprintf(f,"[wideview]\n");
	fprintf(f, "commanche pilot=%.3f,%.3f,%.3f        #wideview pilot position\n",wide_cockpit_position[0].x,wide_cockpit_position[0].y,wide_cockpit_position[0].z);
	fprintf(f, "commanche co-pilot=%.3f,%.3f,%.3f     #wideview co-pilot position\n",wide_cockpit_position[1].x,wide_cockpit_position[1].y,wide_cockpit_position[1].z);
	fprintf(f, "hokum pilot=%.3f,%.3f,%.3f            #wideview pilot position\n",wide_cockpit_position[2].x,wide_cockpit_position[2].y,wide_cockpit_position[2].z);
	fprintf(f, "hokum co-pilot=%.3f,%.3f,%.3f        #wideview co-pilot position\n",wide_cockpit_position[3].x,wide_cockpit_position[3].y,wide_cockpit_position[3].z);
	fprintf(f, "apache pilot=%.3f,%.3f,%.3f            #wideview pilot position\n",wide_cockpit_position[4].x,wide_cockpit_position[4].y,wide_cockpit_position[4].z);
	fprintf(f, "havoc pilot=%.3f,%.3f,%.3f             #wideview pilot position\n",wide_cockpit_position[5].x,wide_cockpit_position[5].y,wide_cockpit_position[5].z);
	fprintf(f, "[Radar]\n");  //VJ 030807 adjustable radar ranges
   fprintf(f, "radar_comanche=%.0f,%.0f,%.0f,%.0f,%.0f   #radar ranges comanche (5 ranges in m, ordered small to large)\n",radar_range_comanche[0],radar_range_comanche[1],radar_range_comanche[2],radar_range_comanche[3],radar_range_comanche[4]);
   fprintf(f, "radar_apache=%.0f,%.0f,%.0f,%.0f,%.0f   #radar ranges apache (5 ranges in m, ordered small to large)\n",radar_range_apache[0],radar_range_apache[1],radar_range_apache[2],radar_range_apache[3],radar_range_apache[4]);
   fprintf(f, "radar_hokum=%.0f,%.0f,%.0f,%.0f,%.0f   #radar ranges hokum (5 ranges in m, ordered small to large)\n",radar_range_hokum[0],radar_range_hokum[1],radar_range_hokum[2],radar_range_hokum[3],radar_range_hokum[4]);
   fprintf(f, "radar_havoc=%.0f,%.0f,%.0f,%.0f   #radar ranges havoc (4 ranges in m, ordered small to large)\n",radar_range_havoc[0],radar_range_havoc[1],radar_range_havoc[2],radar_range_havoc[3]);
   fprintf(f, "radar_blackhawk=%.0f,%.0f,%.0f,%.0f,%.0f   #radar ranges blackhawk (5 ranges in m, ordered small to large)\n",radar_range_blackhawk[0],radar_range_blackhawk[1],radar_range_blackhawk[2],radar_range_blackhawk[3],radar_range_blackhawk[4]);
   fprintf(f, "radar_hind=%.0f,%.0f,%.0f,%.0f   #radar ranges hind (4 ranges in m, ordered small to large)\n",radar_range_hind[0],radar_range_hind[1],radar_range_hind[2],radar_range_hind[3]);
	fprintf(f, "[Cannon]\n");  //VJ 030807 adjustable cannon rounds 
	fprintf(f, "rounds_comanche=%d   #rounds cannon COMANCHE M197_20MM rounds (0 - 65000)\n",rounds_comanche);
	fprintf(f, "rounds_apache=%d     #rounds cannon APACHE M230_30MM rounds (0 - 65000)\n",rounds_apache);
	fprintf(f, "rounds_hokum_AP=%d   #rounds cannon HOKUM 2A42_30MM_AP rounds (0 - 65000)\n",rounds_hokum_AP);
	fprintf(f, "rounds_hokum_HE=%d   #rounds cannon HOKUM 2A42_30MM_HE rounds (0 - 65000)\n",rounds_hokum_HE);
	fprintf(f, "rounds_havoc_AP=%d   #rounds cannon HAVOC 2A42_30MM_AP rounds (0 - 65000)\n",rounds_havoc_AP);
	fprintf(f, "rounds_havoc_HE=%d   #rounds cannon HAVOC 2A42_30MM_HE rounds (0 - 65000)\n",rounds_havoc_HE);
	fprintf(f, "rounds_blackhawk=%d  #rounds cannon BLACKHAWK M230_30MM rounds (0 - 65000)\n",rounds_blackhawk);
	fprintf(f, "rounds_hind_AP=%d    #rounds cannon HIND 2A42_30MM_AP rounds (0 - 65000)\n",rounds_hind_AP);
	fprintf(f, "rounds_hind_HE=%d    #rounds cannon HIND 2A42_30MM_HE rounds (0 - 65000)\n",rounds_hind_HE);
	fprintf(f,"[Mods]\n");
	fprintf(f,"msl=%d               # activates mouselook, and TrackIR when present\n",command_line_mouse_look);
	fprintf(f,"msls=%d              # mouselook speed when activated (def=15, must be > 0) otherwise POV speed (min=1,def=13,max=20)\n",command_line_mouse_look_speed);
	fprintf(f,"minfov=%d            # general field of view minimum, linked to key '7', normal fov (60) = key '8'\n",command_line_min_fov);
	fprintf(f,"maxfov=%d            # general field of view maximum, linked to key '9'\n",command_line_max_fov);
	fprintf(f,"eopann=%d            # joystick no. used for FLIR panning\n",command_line_eo_pan_joystick_index);
	fprintf(f,"eopanv=%d            # joystick DirectX axis used for vertical FLIR panning\n",command_line_eo_pan_vertical_joystick_axis+1);   //VJ 030531 added +1
	fprintf(f,"eopanh=%d            # joystick DirectX axis used for horizontal FLIR panning\n",command_line_eo_pan_horizontal_joystick_axis+1); //VJ 030531 added +1
	fprintf(f,"eozoomn=%d           # joystick no. used for FLIR zoom\n",command_line_eo_zoom_joystick_index);
	fprintf(f,"eozoomax=%d          # joystick DirextX axis used for FLIR zoom\n",command_line_eo_zoom_joystick_axis+1);  //VJ 030531 added +1
	fprintf(f,"cyclicn=%d           # Joystick no. for the cyclic\n",command_line_cyclic_joystick_index);
	fprintf(f,"cyclich=%d           # Joystick DirectX axis for cyclic horizontal\n",command_line_cyclic_joystick_x_axis+1);  //VJ 030531 added +1
	fprintf(f,"cyclicv=%d           # Joystick DirectX axis for cyclic vertical\n",command_line_cyclic_joystick_y_axis+1);   //VJ 030531 added +1
	fprintf(f,"collectiven=%d       # Joystick no. for the collective\n",command_line_collective_joystick_index);
	fprintf(f,"collectiveax=%d      # Joystick DirectX acis for the collective\n",command_line_collective_joystick_axis+1);  //VJ 030531 added +1
	fprintf(f,"ruddern=%d           # Joystick no. for the rudder\n",command_line_rudder_joystick_index);
	fprintf(f,"rudderax=%d          # Joystick DirectX axis for the rudder\n",command_line_rudder_joystick_axis+1);   //VJ 030531 added +1
	fprintf(f,"joylookn=%d          # joystick no. used for joystick look\n",command_line_joylook_joystick_index); //Jabberwock 031104
	fprintf(f,"joylookh=%d          # joystick DirectX axis used for horizontal joystick look\n",command_line_joylookh_joystick_axis+1);   //Jabberwock 031104
	fprintf(f,"joylookv=%d          # joystick DirectX axis used for vertical joystick look\n",command_line_joylookv_joystick_axis+1); //Jabberwock 031104
	fprintf(f,"joylookst=%d         # joystick look step (min=1,def=30,max=100)\n",command_line_joylook_step); //Jabberwock 031104
	fprintf(f,"radarinf=%d          # infantry no longer visible on radar, def = 1 (on)\n",command_line_ground_radar_ignores_infantry);
	fprintf(f,"grstab=%d            # ground stabilisation of FLIR, def = 1 (on)\n",command_line_ground_stabilisation_available);
	fprintf(f,"dfr=%d               # display framerate, 0 = off, 1 = on, 2 = log to file \"framerate.txt\"\n",command_line_framerate);
	fprintf(f,"keymap=%d            # key mapping, def = 0 (off)\n",command_line_key_mapping);
	fprintf(f,"dwash=%d             # visible rotor downwash (dust), def = 1 (on)\n",command_line_downwash);
	fprintf(f,"highresmfd=%d        # high resolution mfd's, def = 0 (off)\n",command_line_high_res_mfd);
	fprintf(f,"greenmfd=%d          # mfd's are green (def = 0 (off), 1 = on)\n",command_line_green_mfd);
	fprintf(f,"faa=%d               # fligh any aircraft, def = 1 (on)\n",command_line_fly_any_airplane);
	fprintf(f,"tsdrender=%d         # TSD render options (0-4) def = 0 (contours only)\n",command_line_tsd_render_mode);
	fprintf(f,"tsdpalette=%d        # TSD palette options (0-2) def = 0 \n",command_line_tsd_palette);
	fprintf(f,"tsdenemy=%d          # TSD showing enemy colours (red, blue) def = 0 (off)\n",command_line_tsd_enemy_colours);
	fprintf(f,"camcom=%d            # Activates the Campaign Commander\n",command_line_camcom); // Jabberwock 031007
	fprintf(f,"destgt=%d            # Activates designated target list\n",command_line_designated_targets); // Jabberwock 031107
	fprintf(f,"filter=%d            # Turns on session filtering\n",command_line_session_filter); // Jabberwock 031210
	fprintf(f,"reverse_pedal=%d		# reversed pedal input\n",command_line_reverse_pedal);	// Retro 17Jul2004
	fprintf(f,"[end of file]\n");
	
	fclose(f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
