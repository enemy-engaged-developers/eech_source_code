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


void process_ini_file(void)
{
    FILE *f;//, *fo = fopen("try.txt","w");

    char *buf = (char *)malloc(255);
    char *p, *q;
    char fname[12] = "eech.ini";
    float v1;
    int d1;
   
    if (!file_exist(fname))   
    {
//       dump_ini_file();
       //debug_fatal("file \"eech.ini\" created for future use");   
       return;    
    }   
   
    f = fopen(fname, "r");
    if (!f)
    {
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

        if (strcmp(p, "chaff")==0)  command_line_chaff_effectiveness = v1;
        if (strcmp(p, "flare")==0)  command_line_flare_effectiveness = v1;
        if (strcmp(p, "smoke")==0)  command_line_smoke_effectiveness = v1;
        if (strcmp(p, "fog"  )==0)  command_line_fog_of_war_maximum_value = v1;
        if (strcmp(p, "cpac")==0) command_line_capture_aircraft = d1;
        if (strcmp(p, "uit")==0) command_line_user_invulnerable_time = v1;                       
        if (strcmp(p, "cbar")==0)  command_line_city_block_approximation_range = v1;
        if (strcmp(p, "mfr")==0)  command_line_max_frame_rate = d1;
        if (strcmp(p, "fs")==0) command_line_full_screen = d1;
        if (strcmp(p, "32bit")==0)
        {
            if (d1 == 1)
				 command_line_display_bpp=32;
            else 
       			 command_line_display_bpp=16;
        }

        if (strcmp(p, "nrt")==0)  command_line_no_render_to_texture = d1;
        if (strcmp(p, "notnl")==0) command_line_no_hardware_tnl = d1;                
        if (strcmp(p, "3dreset")==0)
        {
            if (d1 == 1)
            {
                set_global_3d_visual_screen_width(640.0);
                set_global_3d_visual_screen_height(480.0);
            }
        }   
        if (strcmp(p, "dxtm")==0) command_line_d3d_use_texture_management = d1;
        if (strcmp(p, "cg")==0) command_line_clean_graphics = d1;
        if (strcmp(p, "ipa")==0) 
           if(strlen(q)!=0) 
               strcpy(command_line_ip_address, q);
        if (strcmp(p, "pss")==0) 
           if(strlen(q)!=0) 
               strcpy(command_line_primary_server_setting, q);
        if (strcmp(p, "sss")==0) 
           if(strlen(q)!=0) 
               strcpy(command_line_secondary_server_setting, q);
        if (strcmp(p, "ccrs")==0) command_line_comms_connection_receive_size = d1;
        if (strcmp(p, "cdrs")==0) command_line_comms_data_record_size = d1;
        if (strcmp(p, "cpbs")==0) command_line_comms_pack_buffer_size = d1;
        if (strcmp(p, "cpds")==0) command_line_comms_packet_data_size = d1;
        if (strcmp(p, "cgs")==0) command_line_comms_guaranteed_send = d1;
        if (strcmp(p, "crls")==0) command_line_comms_resend_list_size = d1;
        if (strcmp(p, "crl")==0) command_line_comms_packet_rerequest_limit = d1;
        if (strcmp(p, "cpt")==0) command_line_comms_packet_resend_timer = v1;
        if (strcmp(p, "crto")==0) command_line_comms_resend_timeout = v1;
        if (strcmp(p, "mur")==0) command_line_max_game_update_rate = d1;
        if (strcmp(p, "cig")==0) command_line_comms_interpolate_gunships = d1;
        if (strcmp(p, "cvc")==0) command_line_comms_validate_connections = d1;
        if (strcmp(p, "cptl")==0) command_line_comms_packet_throttle_limit = d1;
        if (strcmp(p, "cto")==0) command_line_comms_timeout = d1;
        if (strcmp(p, "eufr")==0) command_line_entity_update_frame_rate = d1;
        if (strcmp(p, "css")==0) command_line_comms_show_stats = d1;
        if (strcmp(p, "cist")==0) command_line_comms_initial_sleep_time = d1;
        if (strcmp(p, "dedicated")==0) command_line_comms_dedicated_server = d1;
        if (strcmp(p, "game_type")==0) command_line_game_initialisation_phase_game_type = d1;
        if (strcmp(p, "gunship_type")==0) command_line_game_initialisation_phase_gunship_type = d1;
        if (strcmp(p, "path")==0)   
           if (strlen(q)!=0) 
              strcpy(command_line_game_initialisation_phase_path, q);        
        if (strcmp(p, "drbs")==0) command_line_dynamics_retreating_blade_stall_effect = v1;
        if (strcmp(p, "drv")==0) command_line_dynamics_rudder_value = v1;
        if (strcmp(p, "dra")==0) command_line_dynamics_rudder_acceleration = v1;
        if (strcmp(p, "drd")==0) command_line_dynamics_main_rotor_drag = v1;
        if (strcmp(p, "dmrl")==0) command_line_dynamics_main_rotor_lift = v1;
        if (strcmp(p, "dtrd")==0) command_line_dynamics_tail_rotor_drag = v1;
        if (strcmp(p, "dcdz")==0) command_line_dynamics_cyclic_dead_zone = v1;
        if (strcmp(p, "dyal")==0) command_line_dynamics_yaw_altitude_loss = v1;
        if (strcmp(p, "goto")==0) command_line_planner_goto_button = d1;
        if (strcmp(p, "vfm")==0) command_line_vector_flight_model = d1;
        if (strcmp(p, "psr")==0) command_line_player_start_rank = d1;
        if (strcmp(p, "ns")==0) command_line_no_sound=d1;            
        if (strcmp(p, "mta")==0) command_line_max_time_acceleration = d1;
        if (strcmp(p, "nomcm")==0) command_line_no_mission_complete_music = d1;
        if (strcmp(p, "msl") == 0) command_line_mouse_look = d1;
        if (strcmp(p, "msls") == 0) command_line_mouse_look_speed = d1;
        if (strcmp(p, "minfov") == 0) command_line_min_fov = d1;
        if (strcmp(p, "maxfov") == 0) command_line_max_fov = d1;
        if (strcmp(p, "eopann") == 0) command_line_eo_pan_joystick_index = d1;
        if (strcmp(p, "eopanv") == 0) command_line_eo_pan_vertical_joystick_axis = d1;
        if (strcmp(p, "eopanh") == 0) command_line_eo_pan_horizontal_joystick_axis = d1;
        if (strcmp(p, "eozoomn") == 0) command_line_eo_zoom_joystick_index = d1;
        if (strcmp(p, "eozoomax") == 0) command_line_eo_zoom_joystick_axis = d1;
        if (strcmp(p, "radarinf") == 0) command_line_ground_radar_ignores_infantry = d1;
        if (strcmp(p, "grstab") == 0) command_line_ground_stabilisation_available = d1;
        if (strcmp(p, "dfr") == 0) command_line_framerate = d1;
        if (strcmp(p, "keymap") == 0) command_line_key_mapping = d1;
        if (strcmp(p, "dwash") == 0) command_line_no_downwash = d1;
        if (strcmp(p, "wut") == 0) 
        {
            if (strlen(q)!=0) 
               strcpy(WUT_filename, q);
            if (strlen(WUT_filename) != 0) 
               command_line_wut = TRUE; 
            // wut filename checking is done elsewhere
        }    
    }

  fclose(f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void dump_ini_file(void)
{
    FILE *f = fopen("eech.ini","w");

	fprintf(f,"[Enemy Engaged - Comanche Hokum commandline options]\n"); 
	fprintf(f,"[Game]\n");
	fprintf(f,"chaff=1.0           # Effectivness of chaff where n = 0.0 (ineffective) to 1.0 (fully effective - default)\n");
	fprintf(f,"flare=1.0           # Effectivness of flares where n = 0.0 (ineffective) to 1.0 (fully effective - default)\n");
	fprintf(f,"smoke=1.0           # Effectivness of smoke where n = 0.0 (ineffective) to 1.0 (fully effective - default)\n");
	fprintf(f,"fog=14400           # Sets the time (sec) taken for the \"fog of war\" to reshroud enemy sector info (def 4 hours).\n");
	fprintf(f,"cpac=0              # capture aircraft: aircraft landed at captured bases or FARPS become usable by your side.\n");
	fprintf(f,"uit=5.0             # user invulnerable time (default 5 sec), when starting mission (?)\n");
	fprintf(f,"[Graphics]\n");
	fprintf(f,"cbar=500            # city_block_approximation_range            n = distance in meters that city blocks resolve\n");
	fprintf(f,"fs=1                # Switch for turning off the default FULL SCREEN video mode, (def = 1, full screen)\n");
	fprintf(f,"mfr=30              # Max visual frame rate, (defaults = 30)\n");
	fprintf(f,"32bit=0             # Activates 32bit rendering if your video card supports it\n");
	fprintf(f,"nrt=0               # Turns off rendering to texture in case of visual problems with MFDs or TADS\n");
	fprintf(f,"notnl=0             # Turns off GeForce \"TnL\" support for troubleshooting\n");
	fprintf(f,"3dreset=0           # Reset screen resolution to 640x480\n");
	fprintf(f,"dxtm=0              # directx texture management, should fix \"unable to allocate hardware slot\" error\n");
	fprintf(f,"cg=0                # clean graphics, re-installs graphics files\n");
	fprintf(f,"[Communications]\n");
	fprintf(f,"ipa=                # ip address = TCPIP address to connect to. A HOST can leave out the value.\n");
	fprintf(f,"pss=                # primary server setting (server internet address)\n");
	fprintf(f,"sss=                # secondary server setting (server internet address)\n");
	fprintf(f,"ccrs=204800         # connection receive size, initial guess of campaign data size (default = 200k)\n");
	fprintf(f,"cdrs=204800         # data record size, similar to above…\n");
	fprintf(f,"cpbs=204800         # pack buffer size, similar to above…\n");
	fprintf(f,"cpds=512            # packet data size (edf = 512)\n");
	fprintf(f,"cgs=0               # guaranteed send, force the comms to use DirectPlay guaranteed send instead of its own (def=0).\n");
	fprintf(f,"crls=1000           # packet history list size, increase if client keeps getting kicked out by server (default = 1000)\n");        
	fprintf(f,"crl=10              # number of times a client can re-request the same packet. Increase for poor connections (def=10)\n");      
	fprintf(f,"cpt=5               # time delay in seconds the comms will wait for a packet before re-requesting it. (default = 5s)\n");     
	fprintf(f,"crto=2              # resend timeout n=time comms will wait before assuming re-requested packets was lost (default = 2s)\n");            
	fprintf(f,"mur=15              # max update framerate for a server, na for a client (default = 5fps for TCPIP, 15fps for IPX)\n");    
	fprintf(f,"cig=1               # interpolate helicopter position for smoother visuals\n");
	fprintf(f,"cvc=1               # validate connection, removes dead player husks when client crashes\n");
	fprintf(f,"cptl=10             # packet throttle limit, mainly for modems, governs the flow rate of packets\n");
	fprintf(f,"cto=5               # timeout, the amount of time to wait before removing dead player husks\n");
	fprintf(f,"eufr=2              # client server entity update framerate, no. of iterations\n");
	fprintf(f,"css=0               # show communication stats (def = 0)\n");
	fprintf(f,"cist=500            # comms initial sleep time\n");
	fprintf(f,"dedicated=0         # active server mode, off by default.\n");                                 
	fprintf(f,"game_type=2         # Valid game_types are: 1 = Freeflight, 2 = Campaign, 3 = Skirmish\n");
	fprintf(f,"gunship_type=0      # Gunship_types are, 0 = Apache, 1 = Havoc, 2 = Comanche, 3 = Havoc\n");
	fprintf(f,"path=               # Path to map, campaign, skirmish\n");                                                               
	fprintf(f,"[Dynamics]\n");
	fprintf(f,"drbs=1.0            # retreating blade stall, floating point scaling factor for RBS effect (default = 1.0)\n");
	fprintf(f,"drv=1.0             # rudder value, scaling factor for drag on tail rotation (default = 1.0)\n");                                 
	fprintf(f,"dra=0.8             # rudder acceleration, scaling factor for tail rotation acceleration (default = 0.8)\n");         
	fprintf(f,"drd=1.0             # main rotor drag, scaling factor for drag caused by main rotor (default = 1.0)\n");             
	fprintf(f,"dmrl=1.0            # main rotor lift, scaling factor for lift of main rotor (default = 1.0)\n");         
	fprintf(f,"dtrd=1.0            # tail rotor drag, scaling factor for drag caused by tail in forward flight (default = 1.0)\n");
	fprintf(f,"dzd=0.0             # cyclic dead zone, percentage deadzone for the cyclic (default = 0.0)\n");                             
	fprintf(f,"dyal=5.0            # yaw altitude loss (default = 5.0)\n");
	fprintf(f,"[Miscellaneous]\n");
	fprintf(f,"goto=0              # Activates \"GOTO\" teleport button on the campaign map.\n");
	fprintf(f,"vfm=0               # vector flight model, activates viewer or \"UFO\" flight mode.\n");
	fprintf(f,"psr=1               # player start rank for new pilots\n");
	fprintf(f,"ns=0                # Bypass soundcard, useful for tracking hardware conflicts\n");
	fprintf(f,"mta=4               # The maximum multiplier allowed for time acceleration (default - 4)\n");
	fprintf(f,"nomcm=1             # no mission complete music\n");
	fprintf(f,"[Mods]\n");
	fprintf(f,"msl=0               # activates mouselook\n");
	fprintf(f,"msls=15             # mouselook speed when activated\n");
	fprintf(f,"minfov=20           # general field of view minimum, linked to key '7', normal fov = key '8'\n");
	fprintf(f,"maxfov=80           # general field of view maximum, linked to key '9'\n");
	fprintf(f,"eopann=-1           # joystick no. used for FLIR panning\n");
	fprintf(f,"eopanv=6            # joystick DirectX axis used for vertical FLIR panning\n");
	fprintf(f,"eopanh=8            # joystick DirectX axis used for horizontal FLIR panning\n");
	fprintf(f,"eozoomn=-1          # joystick no. used for FLIR zoom\n");
	fprintf(f,"eozoomax=7          # joystick DirextX axis used for FLIR zoom\n");
	fprintf(f,"radarinf=1          # infantry no longer visible on radar (def = 1)\n");
	fprintf(f,"grstab=1            # ground stabilisation of FLIR (def = 1)\n");
	fprintf(f,"dfr=0               # display framerate, 0 = off, 1 = on, 2 = log to file \"framerate.txt\"\n");
	fprintf(f,"keymap=0            # key mapping (def = 0)\n");
	fprintf(f,"dwash=0             # rotor downwash (dust), def = 0 (downwash visible)\n");
	fprintf(f,"wut=                # supply a filename of a wut text file here\n");
	fprintf(f,"[end of file]\n");    

	fclose(f);
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
