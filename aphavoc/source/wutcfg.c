// 
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
// 
// 	 Please see the document LICENSE.TXT for the full licence agreement
// 
// 2. LICENCE
//  2.1 	
//  	Subject to the provisions of this Agreement we now grant to you the 
//  	following rights in respect of the Source Code:
//   2.1.1 
//   	the non-exclusive right to Exploit  the Source Code and Executable 
//   	Code on any medium; and 
//   2.1.2 
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2 	
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1 
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
// 
// 3. GENERAL OBLIGATIONS
//  3.1 
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1 
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2 
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3 
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4 
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5 
// 	not to place any restrictions on the operability of the Source 
// 	Code;
//   3.1.6 
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7 
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
// 

//
//   VJ WUT mod, date: 26-mar-03
//
//   Description: reads TEXT file from Destro's Weapons and Units Tweaker, 
//                changes version 1.4.7X to the version in the wut file
//   Details: http://home.planet.nl/~jette073
//

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char WUT_filename [128]	= "\0"; 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define WUT_DEBUG 0


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void get_values(char *q, float *v2, int *d2)
{
     float v1;
     int j, d1;
     
     for (j = 0; j < strlen(q); j++)
        if (q[j] == ',') q[j] = '.';
	     // get the values at the end of the string
	     // replace , with .
	 
     sscanf(q,"%f %f",&v1, v2);
     sscanf(q,"%d %d",&d1, d2);
     
     debug_log("try wut %f %d\n",v2, d2);                
}	


void parse_WUT_file(char *fname)
{
    FILE *f;
    int i;
    char *buf = (char *)malloc(255);
    char *buf1 = (char *)malloc(255);
    char *p;
    char ent[64];
    
   
    if (!file_exist(fname))   
    {
	   debug_fatal("WUT filename error",fname);   
       return;    
    }   
    
    f = fopen(fname, "r");
    if (!f)
    {
	   debug_fatal("Error opening WUT file: [ %s ]",fname);   
       return;    
    }   



    //########################################################################
    //#### AIRCRAFT ##########################################################
    //########################################################################


    fscanf(f,"%[^\n]\n",buf);

    // skip untill first group
    while (!strstr(buf,"Helicopters and Aircrafts"))
        fscanf(f,"%[^\n]\n",buf);
    fscanf(f,"%[^\n]\n",buf);
    strcpy(buf1, buf);
    

  
    // continue untill the next group
    while (buf1[0] != '\0' && buf1[0] != '\n' && !(strcmp(buf1,"Ground Vehicles, Ships, Infantry")==0))
    {
    	       
        fscanf(f,"%[^\n]\n",buf);
        // read a line
        strcpy(buf1, buf);
        // keep a copy
        
        p = strtok(buf," ");
        strcpy(ent,p);
        // get the first part of th entity name (e.g. AH64D) = unique !

        // search through all the aircraft list 
        for (i = 0; i < NUM_ENTITY_SUB_TYPE_AIRCRAFT; i++)
        {
            // if entity found, parse the variable
            if (strcmp(aircraft_database[i].short_display_name, ent) == 0)
            {
                float v2=0;
                int d2 = 0;
                char *vname, *q = buf1+83;

                get_values(q, &v2, &d2);

                // convert value string to float
                // all floats, last one is int
                if (strstr(buf1 , "Centre Of Gravity To Ground Distance {m}")) { aircraft_database[i].centre_of_gravity_to_ground_distance=v2;}  
                if (strstr(buf1 , "Centre Of Gravity To Ground Distance Destroyed {m}")) { aircraft_database[i].centre_of_gravity_to_ground_distance_destroyed=v2;}  
                if (strstr(buf1 , "Chase View Min Distance {m}")) { aircraft_database[i].chase_view_min_distance=v2;}  
                if (strstr(buf1 , "Chase View Max Distance {m}")) { aircraft_database[i].chase_view_max_distance=v2;}  
                if (strstr(buf1 , "Chase View Min Distance Test {m}")) { aircraft_database[i].chase_view_min_distance_test=v2;}  
                if (strstr(buf1 , "Chase View Max Distance Test {m}")) { aircraft_database[i].chase_view_max_distance_test=v2;}        
                if (strstr(buf1 , "Cruise Speed {m/s}")!=NULL) { aircraft_database[i].cruise_velocity=v2;}
                if (strstr(buf1 , "Cruise Altitude {m}")) { aircraft_database[i].cruise_altitude=v2;}  
                if (strstr(buf1 , "Atack Altitude {m}")) { aircraft_database[i].attack_altitude=v2;}                     
                if (strstr(buf1 , "Destroyed Bank Offset {rad}")) { aircraft_database[i].destroyed_bank_offset=v2;}               
                if (strstr(buf1 , "Destroyed Pitch offset {rad}")) { aircraft_database[i].destroyed_pitch_offset=v2;}  
                if (strstr(buf1 , "Fuselage Angle {rad}")) { aircraft_database[i].fuselage_angle=v2;}                      
                if (strstr(buf1 , "Liftoff Velocity {m/s}")) { aircraft_database[i].liftoff_velocity=v2;}                    
                if (strstr(buf1 , "Main Rotor Shaft Angle {rad}")) { aircraft_database[i].main_rotor_shaft_angle=v2;}  
                if (strstr(buf1 , "Main Rotor Direction {rad}")) { aircraft_database[i].main_rotor_direction=v2;}  
                if (strstr(buf1 , "Main Rotor Blade Drop Angle {rad}")) { aircraft_database[i].main_rotor_blade_droop_angle=v2;}        
                if (strstr(buf1 , "Propellor Direction {rad}")) { aircraft_database[i].propellor_direction=v2;}                 
                if (strstr(buf1 , "Max Turn Rate {rad/s}")) { aircraft_database[i].max_turn_rate=v2;}                       
                if (strstr(buf1 , "Max Roll {rad}")) { aircraft_database[i].max_roll=v2;}                            
                if (strstr(buf1 , "Max Vertical Turn Allowance")) { aircraft_database[i].max_vertical_turn_allowance=v2;}         
                if (strstr(buf1 , "Avoidance Radius")) { aircraft_database[i].avoidance_radius=v2;}  
                if (strstr(buf1 , "G Max {m/s/s}")) { aircraft_database[i].g_max=v2;}                               
                if (strstr(buf1 , "Power Output")) { aircraft_database[i].power_output=v2;}                        
                if (strstr(buf1 , "Tail Rotor Direction")) { aircraft_database[i].tail_rotor_direction=v2;}                
                if (strstr(buf1 , "Recon Radius {m}")) { aircraft_database[i].recon_radius=v2;}                        
                if (strstr(buf1 , "Scan Interval {s}")) { aircraft_database[i].target_scan_delay=v2;}  
                if (strstr(buf1 , "Air Scan Range {m}")) { aircraft_database[i].air_scan_range=v2;}  
                if (strstr(buf1 , "Ground Scan Range {m}")) { aircraft_database[i].surface_scan_range=v2;}  
                if (strstr(buf1 , "Air Threat")) { aircraft_database[i].potential_air_to_air_threat=v2;}  
                if (strstr(buf1 , "Ground Threat")) { aircraft_database[i].potential_air_to_surface_threat=v2;}  
                if (strstr(buf1 , "Ammo Economy")) { aircraft_database[i].ammo_economy=v2;}  
                if (strstr(buf1 , "Fuel Default Weight")) { aircraft_database[i].fuel_default_weight=v2;}  
                if (strstr(buf1 , "Fuel Economy")) { aircraft_database[i].fuel_economy=v2;}  
                if (strstr(buf1 , "Structure Points")) { aircraft_database[i].initial_damage_level=d2;}


  		        #ifdef WUT_DEBUG

                q = buf1+41;
                vname = strtok(q,"-");
                debug_log("WUT: AIRCRAFT: Entity - %s [%s]; VAR: %s - %f [%d]\n", aircraft_database[i].short_display_name, ent, vname,v2,d2);

				#endif
                
            }//variable names
      }//for AIRCRAFT entities
    }//while AIRCRAFT


    //########################################################################
    //#### VEHICLES ##########################################################
    //########################################################################

    fscanf(f,"%[^\n]\n",buf);
    strcpy(buf1, buf);

    // continue untill the next group
    while (buf1[0] != '\0' && buf1[0] != '\n' && !(strcmp(buf1,"Weapons, Decoys, Crate, Ejection Debris")==0))
    {
        int infnr = 0, done = 0;
        
        fscanf(f,"%[^\n]\n",buf);
        // read a line
        strcpy(buf1, buf);

        strncpy(ent,buf,63);
        ent[39] = '\0';        
        i = (int)strlen(ent) - 1;        
        while (ent[i] == '-') 
           i--;        
        ent[i+1] = '\0';        
             
        // replace some labels that are not correct
		if(strstr(ent," LCAC (air cushion)")) strcpy(ent,"Landing Craft Air Cushioned");
		if(strstr(ent," US I"              )) strcpy(ent,"Infantry");
		infnr = 0;
		if(strstr(ent," US I SAM Standing" )) strcpy(ent,"Infantry with SAM");
		infnr = 550;
		if(strstr(ent," US I Sam Kneeling" )) strcpy(ent,"Infantry with SAM");
		infnr = 551;
		if(strstr(ent," CIS I"             )) strcpy(ent,"Infantry");         
		infnr = 0;
		if(strstr(ent," CIS I SAM Standing")) strcpy(ent,"Infantry with SAM");
		infnr = 552;
		if(strstr(ent," CIS I Sam Kneeling")) strcpy(ent,"Infantry with SAM");       
		infnr = 553;
// 0 =		WEAPON_CONFIG_TYPE_UNARMED
//550 = "WEAPON_CONFIG_TYPE_US_INFANTRY_SAM_STANDING";
//551 = "WEAPON_CONFIG_TYPE_US_INFANTRY_SAM_KNEELING";
//552 = "WEAPON_CONFIG_TYPE_CIS_INFANTRY_SAM_STANDING";
//553 = "WEAPON_CONFIG_TYPE_CIS_INFANTRY_SAM_KNEELING";


        // search through all the vehicle list
        for (i = 0; i < NUM_ENTITY_SUB_TYPE_VEHICLES; i++)
        {
            // if found
            if (strcmp(vehicle_database[i].full_name, ent) == 0)
            {
                float v2=0;
                int d2 = 0;
                char *vname, *q = buf1+83;

                if (strstr(ent,"Infantry") &&  vehicle_database[i].default_weapon_config_type != infnr)
                   break;
                // if the entity if an infantry, check if this infantry has the right
                // weapons config type else skip, standing,kneeling,sam,cis,us is recognized by it

                if (infnr == 0 && done == 1)
                   break;
                if (infnr == 0 && done == 0)
                   done = 1;
                
                
                get_values(q, &v2, &d2);

                if (strstr(buf1 , "Chase View Min Distance {m}")) {  vehicle_database[i].chase_view_min_distance=v2;}  
                if (strstr(buf1 , "Chase View Max Distance {m}")) {  vehicle_database[i].chase_view_max_distance=v2;}  
                if (strstr(buf1 , "Chase View Min Distance Test {m}")) {  vehicle_database[i].chase_view_min_distance_test=v2;}  
                if (strstr(buf1 , "Chase View Max Distance Test {m}")) {  vehicle_database[i].chase_view_max_distance_test=v2;}  
                if (strstr(buf1 , "Cruise Velocity {m/s}")) {  vehicle_database[i].cruise_velocity=v2;}  
                if (strstr(buf1 , "Axle Length {m}")) {  vehicle_database[i].axle_length=v2;}  
                if (strstr(buf1 , "Max Acceleration")) {  vehicle_database[i].max_acceleration=v2;}  
                if (strstr(buf1 , "Max Turn Rate {rad/s}")) {  vehicle_database[i].max_turn_rate=v2;}  
                if (strstr(buf1 , "G Max {m/s/s}")) {  vehicle_database[i].g_max=v2;}  
                if (strstr(buf1 , "Speed {m/s}")) {  vehicle_database[i].power_output=v2;}  
                if (strstr(buf1 , "Recon Range {m}")) {  vehicle_database[i].recon_radius=v2;}  
                if (strstr(buf1 , "Scan Interval {s}")) {  vehicle_database[i].target_scan_delay=v2;}  
                if (strstr(buf1 , "Air Search Min {m}")) {  vehicle_database[i].air_scan_floor=v2;}  
                if (strstr(buf1 , "Air Search Max {m}")) {  vehicle_database[i].air_scan_ceiling=v2;}  
                if (strstr(buf1 , "Air Scan Range {m}")) {  vehicle_database[i].air_scan_range=v2;}  
                if (strstr(buf1 , "Ground Scan Range {m}")) {  vehicle_database[i].surface_scan_range=v2;}  
                if (strstr(buf1 , "Air Threat")) {  vehicle_database[i].potential_surface_to_air_threat=v2;}  
                if (strstr(buf1 , "Ground Threat")) {  vehicle_database[i].potential_surface_to_surface_threat=v2;}  
                if (strstr(buf1 , "Ammo Economy")) {  vehicle_database[i].ammo_economy=v2;}  
                if (strstr(buf1 , "Fuel Economy")) {  vehicle_database[i].fuel_economy=v2;}  
                if (strstr(buf1 , "Front Damage Modifier")) {  vehicle_database[i].armour_front=v2;}  
                if (strstr(buf1 , "Flank Damage Modifier")) {  vehicle_database[i].armour_side=v2;}  
                if (strstr(buf1 , "Rear Damage Modifier")) {  vehicle_database[i].armour_rear=v2;}  
                if (strstr(buf1 , "Structure Points")) {  vehicle_database[i].initial_damage_level=d2;}


    			#ifdef WUT_DEBUG
                q = buf1+41;
                vname = strtok(q,"-");
	    		debug_log("WUT: VEHICLE: Entity - %s [%s]; VAR %s - %f [%d]\n", vehicle_database[i].full_name, ent, vname,v2,d2);
				
		    	#endif
                
            }//variable names
      }//for VEHICLES entities
    }//while VEHICLES


    //#######################################################################
    //#### WEAPONS ##########################################################
    //#######################################################################

    fscanf(f,"%[^\n]\n",buf);
    strcpy(buf1, buf);

    while (buf1[0] != '\0' && buf1[0] != '\n' && !(strcmp(buf1,"Keysites")==0))
    {
        fscanf(f,"%[^\n]\n",buf);
        // read a line
        strcpy(buf1, buf);

        strncpy(ent,buf,63);
        ent[39] = '\0';        
        i = (int)strlen(ent) - 1;        
        while (ent[i] == '-') 
           i--;        
        ent[i+1] = '\0';        
        

        // search through all the vehicle list
        for (i = 0; i < NUM_ENTITY_SUB_TYPE_WEAPONS; i++)
        {
	        if (strcmp(weapon_database[i].full_name, ent) == 0)
	        {
	            float v2 = 0;
	            int d2 = 0;
	            char *vname, *q = buf1+83;

               get_values(q, &v2, &d2);
    			//VJ 030603 changed "Guidance Type" to "Guidance" for WUT 3.5
            if ( strstr(buf1, "Guidance"                            )) { weapon_database[i].guidance_type = d2; }                         
				if ( strstr(buf1, "Aiming Type"                         )) { weapon_database[i].aiming_type = d2; }                           
				if ( strstr(buf1, "Decoy Type"                          )) { weapon_database[i].decoy_type = d2; }                            
				if ( strstr(buf1, "Warhead Type"                        )) { weapon_database[i].warhead_type = d2; }                          
				if ( strstr(buf1, "Threat Type"                         )) { weapon_database[i].threat_type = d2; }                           
				if ( strstr(buf1, "Launch Sound Effect Sub Type"        )) { weapon_database[i].launch_sound_effect_sub_type = d2; }          
				if ( strstr(buf1, "Interior Launch Sound Effect"        )) { weapon_database[i].interior_launch_sound_effect = d2; }          
				if ( strstr(buf1, "Exterior Launch Sound Effect"        )) { weapon_database[i].exterior_launch_sound_effect = d2; }          
				if ( strstr(buf1, "Continuous Sound Effect"             )) { weapon_database[i].continuous_sound_effect = d2; }               
				if ( strstr(buf1, "Weapon Selected CPG Speech"          )) { weapon_database[i].weapon_selected_cpg_speech = d2; }            
				if ( strstr(buf1, "Weapon Low CPG Speech"               )) { weapon_database[i].weapon_low_cpg_speech = d2; }                 
				if ( strstr(buf1, "Weapon Out CPG Speech"               )) { weapon_database[i].weapon_out_cpg_speech = d2; }                 
				if ( strstr(buf1, "Weapon Launched CPG Speech"          )) { weapon_database[i].weapon_launched_cpg_speech = d2; }            
				if ( strstr(buf1, "Weapon Launched Wingman Speech"      )) { weapon_database[i].weapon_launched_wingman_speech = d2; }        
				if ( strstr(buf1, "Report Ammo Low Count"               )) { weapon_database[i].report_ammo_low_count = d2; }                 
				if ( strstr(buf1, "Gun Shake"                           )) { weapon_database[i].gun_shake = d2; }                             
				if ( strstr(buf1, "Damage Soft"                         )) { weapon_database[i].soft_damage_capability = d2; }                
				if ( strstr(buf1, "Damage Hard"                         )) { weapon_database[i].hard_damage_capability = d2; }                
				if ( strstr(buf1, "Smoke Trail Type"                    )) { weapon_database[i].smoke_trail_type = d2; }                      
				if ( strstr(buf1, "Acquires Launchers Forward Velocity" )) { weapon_database[i].acquire_parent_forward_velocity = d2; }       
				if ( strstr(buf1, "Ignore Gravity"                      )) { weapon_database[i].ignore_gravity = d2; }                        
				if ( strstr(buf1, "Survive Ground Impact"               )) { weapon_database[i].survive_ground_impact = d2; }                 
				if ( strstr(buf1, "In Flight Collision Check"           )) { weapon_database[i].in_flight_collision_check = d2; }             
				if ( strstr(buf1, "Viewable Weapon"                     )) { weapon_database[i].viewable_weapon = d2; }                       
				if ( strstr(buf1, "Boresight Weapon"                    )) { weapon_database[i].boresight_weapon = d2; }                      
				if ( strstr(buf1, "Hellfire Flight Profile"             )) { weapon_database[i].hellfire_flight_profile = d2; }               
				if ( strstr(buf1, "Weapon Class"                        )) { weapon_database[i].weapon_class = d2; }                          
				if ( strstr(buf1, "Weight {kg}"                         )) { weapon_database[i].weight = v2; }                                     
				if ( strstr(buf1, "Min Range {m}"                       )) { weapon_database[i].min_range = v2; }                                  
				if ( strstr(buf1, "Max Range {m}"                       )) { weapon_database[i].max_range = v2; }                                  
				if ( strstr(buf1, "Effective Range used by AI {m}"      )) { weapon_database[i].effective_range = v2; }                            
				if ( strstr(buf1, "Min Range LOAL {m}"                  )) { weapon_database[i].min_range_loal = v2; }                             
				if ( strstr(buf1, "Max Range LOAL {m}"                  )) { weapon_database[i].max_range_loal = v2; }                             
				if ( strstr(buf1, "Max Range Error Ratio"               )) { weapon_database[i].max_range_error_ratio = v2; }                      
				if ( strstr(buf1, "Muzzle Velocity {m/s}"               )) { weapon_database[i].muzzle_velocity = v2; }                            
				if ( strstr(buf1, "Muzzle Velocity Max Error"           )) { weapon_database[i].muzzle_velocity_max_error = v2; }                  
				if ( strstr(buf1, "Cruise Velocity {m/s}"               )) { weapon_database[i].cruise_velocity = v2; }                            
				if ( strstr(buf1, "G Max {m/s/s}"                       )) { weapon_database[i].g_max = v2; }                                      
				if ( strstr(buf1, "Burn Time {s}"                       )) { weapon_database[i].burn_time = v2; }                                  
				if ( strstr(buf1, "Cruise Time {s}"                     )) { weapon_database[i].cruise_time = v2; }                                
				if ( strstr(buf1, "Cruise Time Max Error {s}"           )) { weapon_database[i].cruise_time_max_error = v2; }                      
				if ( strstr(buf1, "Inhibit Time {s}"                    )) { weapon_database[i].inhibit_time = v2; }                               
				if ( strstr(buf1, "Burst Duration"                      )) { weapon_database[i].burst_duration = v2; }                             
				if ( strstr(buf1, "Rate Of Fire"                        )) { weapon_database[i].rate_of_fire = v2; }                               
				if ( strstr(buf1, "Reload Time {s}"                     )) { weapon_database[i].reload_time = v2; }                                
				if ( strstr(buf1, "Seeker Field Of View {rad}"          )) { weapon_database[i].max_launch_angle_error = v2; }                     

				#ifdef WUT_DEBUG
            		q = buf1+41;
            		vname = strtok(q,"-");
					debug_log("WUT: WEAPON: Entity - %s [%s]; VAR %s - %f [%d]\n", weapon_database[i].full_name, ent, vname,v2,d2);
				#endif
            }   //variable names
        }//for WEAPONS entities
    }//while WEAPONS


    //########################################################################
    //#### KEYSITES ##########################################################
    //########################################################################

    fscanf(f,"%[^\n]\n",buf);
    strcpy(buf1, buf);

    while (buf1[0] != '\0' && buf1[0] != '\n' && !(strcmp(buf1,"Groups")==0))
    {
    	
        fscanf(f,"%[^\n]\n",buf);
        // read a line
        strcpy(buf1, buf);
        
        strncpy(ent,buf,63);
        ent[39] = '\0';        
        i = (int)strlen(ent) - 1;        
        while (ent[i] == '-') 
           i--;        
        ent[i+1] = '\0';        


        // search through all the vehicle list
        for (i = 0; i < NUM_ENTITY_SUB_TYPE_KEYSITES; i++)
        {        	
            // if entity found
            if (strcmp(keysite_database[i].full_name, ent) == 0)
            {
	            float v2 = 0;
	            int d2 = 0;
	            char *vname, *q = buf1+83;

                get_values(q, &v2, &d2);
         
                if (strstr(buf1 ,"Air Ground Supply")) { keysite_database[i].default_supply_usage.air_to_ground_ammo_supply_level = v2; }  
                if (strstr(buf1 ,"Air Air Supply")) { keysite_database[i].default_supply_usage.air_to_air_ammo_supply_level = v2; }     
                if (strstr(buf1 ,"Ammo Usage")) { keysite_database[i].default_supply_usage.ammo_supply_level = v2; }                  
                if (strstr(buf1 ,"Fuel Usage")) { keysite_database[i].default_supply_usage.fuel_supply_level = v2; }                                 
                if (strstr(buf1 ,"Importance")) { keysite_database[i].importance = v2; }                   
                if (strstr(buf1 ,"Minimum Efficiency")) { keysite_database[i].minimum_efficiency = v2; }   
                if (strstr(buf1 ,"Importance Radius {m}")) { keysite_database[i].importance_radius = v2; }    
                if (strstr(buf1 ,"Air Coverage Radius {m}")) { keysite_database[i].air_coverage_radius = v2; }  
                if (strstr(buf1 ,"Recon Distance {m}")) { keysite_database[i].recon_distance = v2; }       
                if (strstr(buf1 ,"Sector Side Max Value")) { keysite_database[i].sector_side_max_value = v2; }  
                if (strstr(buf1 ,"Binary (col.13)")) { ;
                	// bitwise stuff controls map display, do not touch!               	
                }  	
                if (strstr(buf1 ,"Report Ammo Level")) { keysite_database[i].report_ammo_level = v2; }           
                //  UNDEFINED if (strcmp(keysite_varname[j].name,"15")) { dummy = v2; }  
                if (strstr(buf1 ,"Report Fuel Level")) { keysite_database[i].report_fuel_level = v2; }   
                if (strstr(buf1,"Binary (col.17)")) 
                { 
                   keysite_database[i].assign_task_count = (0 | (d2 & 3));
                   keysite_database[i].reserve_task_count = (0 | (d2 & 12));
                   keysite_database[i].requires_cap			= ((d2 >> 4) & 0x01);
                   keysite_database[i].requires_barcap		= ((d2 >> 5) & 0x01);
                   keysite_database[i].repairable			= ((d2 >> 6) & 0x01);
                   keysite_database[i].oca_target			= ((d2 >> 7) & 0x01);
                   keysite_database[i].recon_target			= ((d2 >> 8) & 0x01);
                   keysite_database[i].ground_strike_target	= ((d2 >> 9) & 0x01);
                   keysite_database[i].ship_strike_target	= ((d2 >> 10) & 0x01);
                   keysite_database[i].troop_insertion_target = ((d2 >> 11) & 0x01);
                   keysite_database[i].campaign_objective	= ((d2 >> 12) & 0x01);                              	                	
                       
				#ifdef WUT_DEBUG
                   debug_log("1 [%s]: %d","requires_cap\n",keysite_database[i].requires_cap			);    
                   debug_log("2 [%s]: %d","requires_barcap\n",keysite_database[i].requires_barcap		);    
                   debug_log("3 [%s]: %d","repairable\n",keysite_database[i].repairable			);    
                   debug_log("4 [%s]: %d","oca_target\n",keysite_database[i].oca_target			);    
                   debug_log("5 [%s]: %d","recon_target\n",keysite_database[i].recon_target			);    
                   debug_log("6 [%s]: %d","ground_strike_target\n",keysite_database[i].ground_strike_target	);    
                   debug_log("7 [%s]: %d","ship_strike_target\n",keysite_database[i].ship_strike_target	);    
                   debug_log("8 [%s]: %d","troop_insertion_target\n",keysite_database[i].troop_insertion_target);   
                   debug_log("9 [%s]: %d","campaign_objective\n",keysite_database[i].campaign_objective	);    
                #endif   
                }
                
				#ifdef WUT_DEBUG
                
                q = buf1+41;
                vname = strtok(q,"-");
                debug_log("WUT: KEYSITE: Entity - %s [%s]; VAR [%s] - %f [%d]\n", keysite_database[i].full_name, ent, vname,v2,d2);
				
				#endif
            }//variable names
      }//for KEYSITES entities
    }//while KEYSITES


    //########################################################################
    //#### GROUPS ############################################################
    //########################################################################

    fscanf(f,"%[^\n]\n",buf);
    strcpy(buf1, buf);
    
    while (buf1[0] != '\0' && buf1[0] != '\n' && !(strcmp(buf1,"Tasks")==0))
    {
        fscanf(f,"%[^\n]\n",buf);
        strcpy(buf1, buf);
               
        strncpy(ent,buf,63);
        ent[39] = '\0';        
        i = (int)strlen(ent) - 1;        
        while (ent[i] == '-') 
           i--;        
        ent[i+1] = '\0';        

//NOTE: infantry 3 groups not distinguished, but these are static entities anyway...

        // search through all the vehicle list
        for (i = 0; i < NUM_ENTITY_SUB_TYPE_GROUPS; i++)
        {        	
            if (strcmp(group_database[i].full_name, ent) == 0)
            {
                float v2=0;
                int d2 = 0;
                char *vname, *q = buf1+83;
                
                get_values(q, &v2, &d2);
           
                //if (strstr(buf1,"Full Name {text}"           )) { group_database[i].full_name                       = v2; }                          
                //if (strstr(buf1,"Group Short Name {text}"    )) { group_database[i].group_short_name                = v2; }                          
                if (strstr(buf1,"Group Category"             )) { group_database[i].group_category                  = d2; }                           
                if (strstr(buf1,"Registery List"             )) { group_database[i].registry_list_type              = d2; }                           
                if (strstr(buf1,"Group List"                 )) { group_database[i].group_list_type                 = d2; }                           
                if (strstr(buf1,"Movement Type"              )) { group_database[i].movement_type                   = d2; }                           
                if (strstr(buf1,"Landing Type"               )) { group_database[i].default_landing_type            = d2; }                           
                if (strstr(buf1,"Default Entity Type"        )) { group_database[i].default_entity_type             = d2; }                           
                if (strstr(buf1,"Default Blue Force Sub Type")) { group_database[i].default_blue_force_sub_type     = d2; }                           
                if (strstr(buf1,"Default Red Force Sub Type" )) { group_database[i].default_red_force_sub_type      = d2; }                           
                if (strstr(buf1,"Default Group Formation"    )) { group_database[i].default_group_formation         = d2; }                           
                if (strstr(buf1,"Default Group Division"     )) { group_database[i].default_group_division          = d2; }                           
                if (strstr(buf1,"Maximum Groups Per Division")) { group_database[i].maximum_groups_per_division     = d2; }                           
                if (strstr(buf1,"Platoon Name {text}"        )) 
                {
                	if (d2 == 6708896) group_database[i].platoon_name = strdup("N/A");
                	if (d2 == 6709584) group_database[i].platoon_name = strdup("Landing Craft (%s)");
                	if (d2 == 6709548) group_database[i].platoon_name = strdup("Frigates (%s)");
                	if (d2 == 6709524) group_database[i].platoon_name = strdup("%s");
                	if (d2 == 6709496) group_database[i].platoon_name = strdup("%c Company");
                	if (d2 == 6709428) group_database[i].platoon_name = strdup("%s Battalion");
                	
					#ifdef WUT_DEBUG
                    	debug_log("WUT: platoon: %s",group_database[i].platoon_name);
                	#endif    
                }
                if (strstr(buf1,"Platoon Short Name Type"    )) { group_database[i].platoon_short_name_type         = v2; }                           
                if (strstr(buf1,"Map Layer Type"             )) { group_database[i].map_layer_type                  = d2; }                           
                if (strstr(buf1,"Map Icon Type"              )) { group_database[i].map_icon                        = d2; }                           
                if (strstr(buf1,"Rearming Time (s)"          )) { group_database[i].rearming_time                   = v2; }             
                if (strstr(buf1,"Binary (col.19)"            )) 
                {
                	long value = (long) v2;
                	group_database[i].frontline_flag		= (0 | (value & 3));     //2
                	group_database[i].local_only_group	    = ((value >> 2) & 0x01); //1
                	group_database[i].default_engage_enemy  = ((value >> 3) & 0x01); //1
                	group_database[i].amalgamate			= ((value >> 4) & 0x01); //1
                	group_database[i].platoon_id_type		= ((0 | (value & 224)) >> 5);//3
                	group_database[i].maximum_member_count  = ((0 | (value & 7936)) >> 8); //5
                	group_database[i].minimum_idle_count	= ((0 | (value & 122880)) >> 13); //4
                	group_database[i].resupply_source		= ((0 | (value & 917504)) >> 17); //3                	
                }
                if (strstr(buf1,"Air Attack Strength"        )) { group_database[i].ai_stats.air_attack_strength    = d2; } 
                if (strstr(buf1,"Ground Attack Strength"     )) { group_database[i].ai_stats.ground_attack_strength = d2; }
                if (strstr(buf1,"Movement Speed"             )) { group_database[i].ai_stats.movement_speed         = d2; }  
                if (strstr(buf1,"Movement Stealth"           )) { group_database[i].ai_stats.movement_stealth       = d2; }
                if (strstr(buf1,"Cargo Space"                )) { group_database[i].ai_stats.cargo_space            = d2; }
                if (strstr(buf1,"Troop Space"                )) { group_database[i].ai_stats.troop_space            = d2; }
                
			    #ifdef WUT_DEBUG
                  
                q = buf1+41;
                vname = strtok(q,"-");
                debug_log("WUT: GROUPS: Entity - %s [%s]; VAR [%s] - %f [%d]\n", group_database[i].full_name, ent,vname,v2,d2);

			    #endif
            }//variable names
        }//for GROUP entities
    }//while GROUP

    //########################################################################
    //#### TASKS #############################################################
    //########################################################################

    fscanf(f,"%[^\n]\n",buf);
    strcpy(buf1, buf);

    while (buf1[0] != '\0' && buf1[0] != '\n' && !(strcmp(buf1,"Waypoints")==0))
    {
        int done = 0;    	
        
        fscanf(f,"%[^\n]\n",buf);
        // read a line
        strcpy(buf1, buf);
        
        strncpy(ent,buf,63);
        ent[39] = '\0';        
        i = (int)strlen(ent) - 1;        
        while (ent[i] == '-') 
           i--;        
        ent[i+1] = '\0';        


        // search through all the vehicle list
        for (i = 0; i < NUM_ENTITY_SUB_TYPE_TASKS; i++)
        {        	
            if (strcmp(task_database[i].full_name, ent) == 0)
            {
                float v2=0;
                int d2 = 0;
                char *vname, *q = buf1+83;
    
                if (strcmp(ent,"Transfer"))
                { 
                   if (done) break;
                   done = 1;
                }
                   
                get_values(q, &v2, &d2);                

                //if (strstr(buf1,"Name {text}"            )) { task_database[i].*full_name = v2; }                          
                //if (strstr(buf1,"Short Name {text}"      )) { task_database[i].*short_name = v2; }                         
                //if (strstr(buf1,"Key {text}"             )) { task_database[i].*key = v2; }                                
                if (strstr(buf1,"Task Category"          )) { task_database[i].task_category = d2; }                    
                if (strstr(buf1,"Task Priority"          )) { task_database[i].task_priority = v2; }  //the only float                
                if (strstr(buf1,"Difficulty Rating"      )) { task_database[i].difficulty_rating = d2; }                     
                if (strstr(buf1,"7"                      )) 
                { 
   					task_database[i].task_default_target_class = (0 | (d2 & 3));
   					task_database[i].task_default_target_source = (d2 >> 2);

/*                	
                	//task_default_target_class en task_default_target_source
                	1e 2 bits zijn getallen 0,1of 2
                	bits 3-6 zijn getallen 0,1,2,3,4,5,6
                	bijv 22 = 10110 = 101:10 = 5 en 2 = SOURCE_TASK_OBJECTIVE, en _CLASS_ground,
                	bijv 20 = 10100 = 101:00 = 5 en 0     source none            class all
                	
                	4 = 100 = 001:00 = 1 en 0 scan air en class all
                	
                	16 = 10000 = 100:00 = 4 en 0 = source objective en class all 
                	            class ground source none 6 en 2
					00 0    TASK_TARGET_CLASS_ALL,                    
					01 1	TASK_TARGET_CLASS_AIR,                    
					10 2	TASK_TARGET_CLASS_GROUND,                 
						
					001 1	TASK_TARGET_SOURCE_SCAN_AIR,              
					010 2	TASK_TARGET_SOURCE_SCAN_ALL,              
					011 3	TASK_TARGET_SOURCE_SCAN_GROUND,             
					100 4	TASK_TARGET_SOURCE_OBJECTIVE_NOMINATED,   
					101 5	TASK_TARGET_SOURCE_TASK_OBJECTIVE,        
					110 6	TASK_TARGET_SOURCE_NONE,                  					
					111	7   NUM_TASK_TASK_TARGET_SOURCE_TYPES
*/	 
                }
                if (strstr(buf1,"Binary (col.8)"         )) 
                {
					if ((d2 == 0) & 0x01) task_database[i].task_default_target_type = 0;   
					if ((d2 >> 0) & 0x01) task_database[i].task_default_target_type = 1;   
					if ((d2 >> 1) & 0x01) task_database[i].task_default_target_type = 2;   
					if ((d2 >> 2) & 0x01) task_database[i].task_default_target_type = 3;   
					if ((d2 >> 3) & 0x01) task_database[i].task_default_target_type = 4;   
					if ((d2 >> 4) & 0x01) task_database[i].task_default_target_type = 5;   
					if ((d2 >> 5) & 0x01) task_database[i].task_default_target_type = 6;   
					if ((d2 >> 6) & 0x01) task_database[i].task_default_target_type = 7;   
					if ((d2 >> 7) & 0x01) task_database[i].task_default_target_type = 8;   
					if ((d2 >> 8) & 0x01) task_database[i].task_default_target_type = 9;   
					if ((d2 >> 9) & 0x01) task_database[i].task_default_target_type = 10;  
					if ((d2 >> 10)& 0x01) task_database[i].task_default_target_type = 11;  
					if ((d2 >> 11)& 0x01) task_database[i].task_default_target_type = 12;  
					if ((d2 >> 12)& 0x01) task_database[i].task_default_target_type = 13;  
					if ((d2 >> 13)& 0x01) task_database[i].task_default_target_type = 14;  
					if ((d2 >> 14)& 0x01) task_database[i].task_default_target_type = 15;  
					if ((d2 >> 15)& 0x01) task_database[i].task_default_target_type = 16;  
					if ((d2 >> 16)& 0x01) task_database[i].task_default_target_type = 17;                 
                }
                if (strstr(buf1,"Binary (col.9)"         )) 
                {  
   					int value = 0;
   					value = value | (d2 & 3); //0000000000000011
   					task_database[i].task_objective_info = value;
			   	    
                    value = 0;
   					value = value | (d2 & 60); //0000000000111100
                    task_database[i].minimum_member_count = value >> 2;
                    	    
                    value = 0;
   					value = value | (d2 & 384); //0000 0000 1100 0000
                    task_database[i].rules_of_engagement = value >> 6;

                    value = 0;
   					value = value | (d2 & 512); //0000 0001 0000 0000
                    task_database[i].engage_enemy = value >> 8;

                    value = 0;
   					value = value | (d2 & 7680); //0001 1110 0000 0000
                    task_database[i].escort_required_threshold = value >> 9;
                }                                                            
                if (strstr(buf1,"10"                     )) { ; } //waypoint_route_colour
                if (strstr(buf1,"Binary 11"              )) 
                { 
                	task_database[i].add_start_waypoint				= ((d2 >> 0) & 0x01); 
                	task_database[i].primary_task					= ((d2 >> 1) & 0x01); 
                	task_database[i].solo_task						= ((d2 >> 2) & 0x01); 
                	task_database[i].persistent_task				= ((d2 >> 3) & 0x01); 
                	task_database[i].visible_task					= ((d2 >> 4) & 0x01); 
                	task_database[i].keysite_air_force_capacity		= (0 | (d2 & 96)); // 2 bit value
                   	task_database[i].assess_landing					= ((d2 >> 7) & 0x01); 
                	task_database[i].task_route_search				= ((d2 >> 8) & 0x01); 
                	task_database[i].perform_debrief				= ((d2 >> 9) & 0x01); 
                	task_database[i].delay_task_assignment			= ((d2 >> 10) & 0x01); 
                	task_database[i].task_objective_preview			= ((d2 >> 11) & 0x01); 
                	task_database[i].counts_towards_player_log		= ((d2 >> 12) & 0x01); 
                	task_database[i].wait_for_end_task				= ((d2 >> 13) & 0x01); 
                	task_database[i].player_reserve_factor			= (d2 >> 14); // 3 bit value
                }                    
                if (strstr(buf1,"TaskCompleted Score"   )) { task_database[i].task_completed_score = d2; }             
                if (strstr(buf1,"Moveent Type"          )) { task_database[i].movement_type = d2; }                    
                if (strstr(buf1,"Landing Types"         )) { task_database[i].landing_types = d2; }             
                if (strstr(buf1,"Air Attack strength"   )) { task_database[i].ai_stats.air_attack_strength = d2; }     
                if (strstr(buf1,"Ground Attack strength")) { task_database[i].ai_stats.ground_attack_strength = d2; }  
                if (strstr(buf1,"Movement Speed"        )) { task_database[i].ai_stats.movement_speed = d2; }          
                if (strstr(buf1,"Movement"              )) { task_database[i].ai_stats.movement_stealth = d2; }        
                if (strstr(buf1,"Cargo Space"           )) { task_database[i].ai_stats.cargo_space = d2; }             
                if (strstr(buf1,"Troop Space"           )) { task_database[i].ai_stats.troop_space = d2; }             

				#ifdef WUT_DEBUG
                
                q = buf1+41;
                vname = strtok(q,"-");
                debug_log("WUT: TASK: Entity - %s [%s]; VAR [%s] - %f [%d]\n", task_database[i].full_name, ent, vname,v2,d2);
				
				#endif
            }//variable names
      }//for TASK entities
    }//while TASK


    //########################################################################
    //#### WAYPOINTS #########################################################
    //########################################################################

    fscanf(f,"%[^\n]\n",buf);
    strcpy(buf1, buf);

    while (buf1[0] != '\0' && buf1[0] != '\n' && !(strcmp(buf1,"Weapon Config Types")==0))
    {
    	
        fscanf(f,"%[^\n]\n",buf);
        // read a line
        strcpy(buf1, buf);
        
        
        strncpy(ent,buf,63);
        ent[39] = '\0';        
        i = (int)strlen(ent) - 1;        
        while (ent[i] == '-') 
           i--;        
        ent[i+1] = '\0';        


        // search through all the vehicle list
        for (i = 0; i < NUM_ENTITY_SUB_TYPE_WAYPOINTS; i++)
        {        	
            // if entity found, but not Landed, that is taken care of in the new code
            if (strcmp(waypoint_database[i].full_name, ent) == 0 && !strcmp(ent,"Landed"))
            {
                float v1=0, v2=0;
                int j;
                char *vname, *q = buf1+83;

                for (j = 0; j < strlen(q); j++)
                   if (q[j] == ',') q[j] = '.';
                // get the values at the end of the string                
                // replace , with .
                sscanf(q,"%f %f",&v1, &v2);       	    

                if (strstr(buf1,"Fixed Wing Minimum Previous Waypoint Distance {m}" )) {waypoint_database[i].fw_minimum_previous_waypoint_distance = v2; }    
                if (strstr(buf1,"Fixed Wing Action Radius {m}"                      )) {waypoint_database[i].fw_action_radius                      = v2; }    
                if (strstr(buf1,"Fixed Wing Reached Radius {m}"                     )) {waypoint_database[i].fw_reached_radius                     = v2; }    
                if (strstr(buf1,"Fixed Wing Velocity {m}"                           )) {waypoint_database[i].fw_velocity                           = v2; }    
                if (strstr(buf1,"Helicopter Minimum Previous Waypoint Distance {m}" )) {waypoint_database[i].hc_minimum_previous_waypoint_distance = v2; }
                if (strstr(buf1,"Helicopter Action Radius {m}"                      )) {waypoint_database[i].hc_action_radius                      = v2; }
                if (strstr(buf1,"Helicopter Reached Radius {m}"                     )) {waypoint_database[i].hc_reached_radius                     = v2; }
                if (strstr(buf1,"Helicopter Velocity {m}"                           )) {waypoint_database[i].hc_velocity                           = v2; }
                if (strstr(buf1,"Ground Minimum Previous Waypoint Distance {m}"     )) {waypoint_database[i].rv_minimum_previous_waypoint_distance = v2; }
                if (strstr(buf1,"Ground Action Radius {m}"                          )) {waypoint_database[i].rv_action_radius                      = v2; }
                if (strstr(buf1,"Ground Reached Radius {m}"                         )) {waypoint_database[i].rv_reached_radius                     = v2; }
                if (strstr(buf1,"Ground Velocity {m}"                               )) {waypoint_database[i].rv_velocity                           = v2; }
                if (strstr(buf1,"Sea Minimum Previous Waypoint Distance {m}"        )) {waypoint_database[i].sh_minimum_previous_waypoint_distance = v2; }   
                if (strstr(buf1,"Sea Action Radius {m}"                             )) {waypoint_database[i].sh_action_radius                      = v2; }   
                if (strstr(buf1,"Sea Reached Radius {m}"                            )) {waypoint_database[i].sh_reached_radius                     = v2; }   
                if (strstr(buf1,"Sea Velocity {m}"                                  )) {waypoint_database[i].sh_velocity                           = v2; }   

				#ifdef WUT_DEBUG
                
                q = buf1+41;
                vname = strtok(q,"-");
                debug_log("WUT: WAYPOINT: Entity - %s [%s]; VAR [%s] - %f [%f]\n", waypoint_database[i].full_name, ent, vname,v2,v1);
				
				#endif
               
            }//variable names
      }//for WAYPOINT entities
    }//while WAYPOINT


    //######################################################################
    //#### WEAPON CONFIG TYPES #############################################
    //######################################################################
    // struct WEAPON_PACKAGE in weapon.h line 1418                 
    // enum WEAPON_CONFIG_TYPES in weapon.h line 291               
    //weapon_package weapon_config_database in wp_dbase.c line 5010

    fscanf(f,"%[^\n]\n",buf);
    strcpy(buf1, buf);
/*
    while (buf1[0] != '\0' && buf1[0] != '\n' &&!(strcmp(buf1,"End - List Of Changes")==0))
    {
    	//
    	int entnr = 0;
        float v1=0, v2=0;
        int d1 = 0, d2 = 0;
        int j;
        char *vname, *q = buf1+83;

        fscanf(f,"%[^\n]\n",buf);
        // read a line

        
        if (buf1[0] == '\0' || buf1[0] == '\n')
           break;       
        
        strcpy(buf1, buf);
        
        p = strtok(buf,"-");
        entnr = atoi(p);
        // entities are numbers 495-553 see below
        
        if (entnr == 0)
          break;
        
        if (entnr != oldentnr)
           wcp = 0;        


        get_values(q, &v2, &d2);
        debug_log("try wut %f %d\n",v2, d2);
           
       	if (strchr(q,',')|| strchr(q,'.'))
       	{
       	    for (j = 0; j < strlen(q); j++)
       	       if (q[j] == ',') q[j] = '.';
       	    // get the values at the end of the string
       	    // replace , with .
       	
       	    sscanf(q,"%f %f",&v1, &v2);
       	}
       	else
       	{
       	    sscanf(q,"%d %d",&d1, &d2);
       	}              
        
        
        
        if (strstr(buf1, "Weapon Type"                        )) {weapon_config_database[entnr][wcp].sub_type = (int)d2;}
        if (strstr(buf1, "Number Of Weapons"                  )) {weapon_config_database[entnr][wcp].number = (int)d2;}
        if (strstr(buf1, "Hard Point"                         )) {weapon_config_database[entnr][wcp].heading_depth = (int)d2;}
        if (strstr(buf1, "Salvo"                              )) {weapon_config_database[entnr][wcp].salvo_size = (int)d2;}

        if (strstr(buf1, "Horizontal Turn Speed {rad/s}"      )) {weapon_config_database[entnr][wcp].heading_rate = v2;}
        if (strstr(buf1, "Min Horizontal Tracking Angle {rad}")) {weapon_config_database[entnr][wcp].min_heading_limit = v2;}
        if (strstr(buf1, "Max Horizontal Tracking Angle {rad}")) {weapon_config_database[entnr][wcp].max_heading_limit = v2;}
        if (strstr(buf1, "Vertical Turn Speed {rad/s}"        )) {weapon_config_database[entnr][wcp].pitch_rate = v2;}
        if (strstr(buf1, "Min Vertical Tracking Angle {rad}"  )) {weapon_config_database[entnr][wcp].min_pitch_limit = v2;}
        if (strstr(buf1, "Max Vertical Tracking Angle {rad}"  )) {weapon_config_database[entnr][wcp].max_pitch_limit = v2;}
        if (strstr(buf1, "15 {rad}"                           )) {weapon_config_database[entnr][wcp].muzzle_rotate_rate = v2;}
       // if (strstr(buf1, "16"                                 )) {weapon_config_database[entnr][wcp].rotate_inhibit_velocity = v2;}
              
        #ifdef WUT_DEBUG
              
            if(entnr == 495) strcpy(vname,"UH60_BLACK_HAWK          ");                
            if(entnr == 496) strcpy(vname,"MI24D_HIND               ");                
            if(entnr == 497) strcpy(vname,"CH46E_SEA_KNIGHT         ");                
            if(entnr == 498) strcpy(vname,"KA29_HELIX_B             ");                
            if(entnr == 499) strcpy(vname,"CH3_JOLLY_GREEN_GIANT    ");                
            if(entnr == 500) strcpy(vname,"MI17_HIP                 ");                
            if(entnr == 501) strcpy(vname,"CH47D_CHINOOK            ");                
            if(entnr == 502) strcpy(vname,"MI6_HOOK                 ");
            if(entnr == 503) strcpy(vname,"A10A_THUNDERBOLT         ");
            if(entnr == 504) strcpy(vname,"SU25_FROGFOOT            ");
            if(entnr == 505) strcpy(vname,"F16_FIGHTING_FALCON      ");
            if(entnr == 506) strcpy(vname,"F16_FIGHTING_FALCON      ");
            if(entnr == 507) strcpy(vname,"MIG29_FULCRUM            ");
            if(entnr == 508) strcpy(vname,"MIG29_FULCRUM            ");
            if(entnr == 509) strcpy(vname,"AV8B_HARRIER             ");
            if(entnr == 510) strcpy(vname,"YAK141_FREESTYLE         ");
            if(entnr == 511) strcpy(vname,"FA18_HORNET              ");
            if(entnr == 512) strcpy(vname,"FA18_HORNET              ");
            if(entnr == 513) strcpy(vname,"SU33_FLANKER             ");
            if(entnr == 514) strcpy(vname,"SU33_FLANKER             ");
            if(entnr == 515) strcpy(vname,"AH64A_APACHE             ");
            if(entnr == 516) strcpy(vname,"AH64A_APACHE             ");
            if(entnr == 517) strcpy(vname,"KA50_HOKUM               ");
            if(entnr == 518) strcpy(vname,"KA50_HOKUM               ");
            if(entnr == 519) strcpy(vname,"OH58D_KIOWA_WARRIOR      ");
            if(entnr == 520) strcpy(vname,"MV22_OSPREY              ");
            if(entnr == 521) strcpy(vname,"AH1T_SEACOBRA            ");
            if(entnr == 522) strcpy(vname,"AH1W_SUPERCOBRA          ");
            if(entnr == 523) strcpy(vname,"CH53E_SUPER_STALLION     ");
            if(entnr == 524) strcpy(vname,"C17_GLOBEMASTER_III      ");
            if(entnr == 525) strcpy(vname,"IL76MD_CANDID_B          ");
            if(entnr == 526) strcpy(vname,"C130J_HERCULES_II        ");
            if(entnr == 527) strcpy(vname,"AN12B_CUB                ");
            if(entnr == 528) strcpy(vname,"M1A2_ABRAMS              ");
            if(entnr == 529) strcpy(vname,"T80U                     ");
            if(entnr == 530) strcpy(vname,"M2A2_BRADLEY             ");
            if(entnr == 531) strcpy(vname,"BMP2                     ");
            if(entnr == 532) strcpy(vname,"BMP3                     ");
            if(entnr == 533) strcpy(vname,"M113A2                   ");
            if(entnr == 534) strcpy(vname,"BTR80                    ");
            if(entnr == 535) strcpy(vname,"BRDM2                    ");
            if(entnr == 536) strcpy(vname,"M109A2                   ");
            if(entnr == 537) strcpy(vname,"2S19                     ");
            if(entnr == 538) strcpy(vname,"M270_MLRS                ");
            if(entnr == 539) strcpy(vname,"BM21_GRAD                ");
            if(entnr == 540) strcpy(vname,"M163_VULCAN              ");
            if(entnr == 541) strcpy(vname,"SA19_GRISON              ");
            if(entnr == 542) strcpy(vname,"M1037_AVENGER            ");
            if(entnr == 543) strcpy(vname,"M48A1_CHAPARRAL          ");
            if(entnr == 544) strcpy(vname,"SA13_GOPHER              ");
            if(entnr == 545) strcpy(vname,"TARAWA_CLASS             ");
            if(entnr == 546) strcpy(vname,"KIEV_CLASS               ");
            if(entnr == 547) strcpy(vname,"OLIVER_HAZARD_PERRY_CLASS");
            if(entnr == 548) strcpy(vname,"KRIVAK_II_CLASS          ");
            if(entnr == 549) strcpy(vname,"AIST_CLASS               ");
            if(entnr == 550) strcpy(vname,"US_INFANTRY_SAM_STANDING ");
            if(entnr == 551) strcpy(vname,"US_INFANTRY_SAM_KNEELING ");
            if(entnr == 552) strcpy(vname,"CIS_INFANTRY_SAM_STANDING");
            if(entnr == 553) strcpy(vname,"CIS_INFANTRY_SAM_KNEELING");
            q = buf1+41;
            vname = strtok(q,"-");
            debug_log("WUT: WEAPON CONFIG: Entity - %d %s VAR [%d] - %f [%f] %d [%d]\n", entnr, vname, wcp,v2,v1,d2,d1);
		
		#endif

        wcp++;           
        oldentnr = entnr;		

        
    }//while WEAPON CONFIG  
*/

  		#ifdef WUT_DEBUG
  
              debug_log("WUT: DONE!!!\n");
		
		#endif
    
    
    // close wut cfg file            
    fclose(f);  
    
    // free text buffers
    free(buf);  
    free(buf1); 
}               
                
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                
/* transation in weapons type config  
struct WEAPON_PACKAGE
{
	int
		sub_type,
		number,
		heading_depth,
		pitch_depth,
		muzzle_depth,
		make_weapon_system_ready,
		rotate,
		salvo_size;

	float
		heading_rate,
		min_heading_limit,
		max_heading_limit,
		pitch_rate,
		min_pitch_limit,
		max_pitch_limit,
		muzzle_rotate_rate,
		rotate_inhibit_velocity;

	unsigned int
		heading_share_mask,
		pitch_share_mask;

	muzzle_flash_types
		muzzle_flash_type;

              
if(entnr == 495) vname = "UH60_BLACK_HAWK          ";                
if(entnr == 496) vname = "MI24D_HIND               ";                
if(entnr == 497) vname = "CH46E_SEA_KNIGHT         ";                
if(entnr == 498) vname = "KA29_HELIX_B             ";                
if(entnr == 499) vname = "CH3_JOLLY_GREEN_GIANT    ";                
if(entnr == 500) vname = "MI17_HIP                 ";                
if(entnr == 501) vname = "CH47D_CHINOOK            ";                
if(entnr == 502) vname = "MI6_HOOK                 ";
if(entnr == 503) vname = "A10A_THUNDERBOLT         ";
if(entnr == 504) vname = "SU25_FROGFOOT            ";
if(entnr == 505) vname = "F16_FIGHTING_FALCON      ";
if(entnr == 506) vname = "F16_FIGHTING_FALCON      ";
if(entnr == 507) vname = "MIG29_FULCRUM            ";
if(entnr == 508) vname = "MIG29_FULCRUM            ";
if(entnr == 509) vname = "AV8B_HARRIER             ";
if(entnr == 510) vname = "YAK141_FREESTYLE         ";
if(entnr == 511) vname = "FA18_HORNET              ";
if(entnr == 512) vname = "FA18_HORNET              ";
if(entnr == 513) vname = "SU33_FLANKER             ";
if(entnr == 514) vname = "SU33_FLANKER             ";
if(entnr == 515) vname = "AH64A_APACHE             ";
if(entnr == 516) vname = "AH64A_APACHE             ";
if(entnr == 517) vname = "KA50_HOKUM               ";
if(entnr == 518) vname = "KA50_HOKUM               ";
if(entnr == 519) vname = "OH58D_KIOWA_WARRIOR      ";
if(entnr == 520) vname = "MV22_OSPREY              ";
if(entnr == 521) vname = "AH1T_SEACOBRA            ";
if(entnr == 522) vname = "AH1W_SUPERCOBRA          ";
if(entnr == 523) vname = "CH53E_SUPER_STALLION     ";
if(entnr == 524) vname = "C17_GLOBEMASTER_III      ";
if(entnr == 525) vname = "IL76MD_CANDID_B          ";
if(entnr == 526) vname = "C130J_HERCULES_II        ";
if(entnr == 527) vname = "AN12B_CUB                ";
if(entnr == 528) vname = "M1A2_ABRAMS              ";
if(entnr == 529) vname = "T80U                     ";
if(entnr == 530) vname = "M2A2_BRADLEY             ";
if(entnr == 531) vname = "BMP2                     ";
if(entnr == 532) vname = "BMP3                     ";
if(entnr == 533) vname = "M113A2                   ";
if(entnr == 534) vname = "BTR80                    ";
if(entnr == 535) vname = "BRDM2                    ";
if(entnr == 536) vname = "M109A2                   ";
if(entnr == 537) vname = "2S19                     ";
if(entnr == 538) vname = "M270_MLRS                ";
if(entnr == 539) vname = "BM21_GRAD                ";
if(entnr == 540) vname = "M163_VULCAN              ";
if(entnr == 541) vname = "SA19_GRISON              ";
if(entnr == 542) vname = "M1037_AVENGER            ";
if(entnr == 543) vname = "M48A1_CHAPARRAL          ";
if(entnr == 544) vname = "SA13_GOPHER              ";
if(entnr == 545) vname = "TARAWA_CLASS             ";
if(entnr == 546) vname = "KIEV_CLASS               ";
if(entnr == 547) vname = "OLIVER_HAZARD_PERRY_CLASS";
if(entnr == 548) vname = "KRIVAK_II_CLASS          ";
if(entnr == 549) vname = "AIST_CLASS               ";
if(entnr == 550) vname = "US_INFANTRY_SAM_STANDING ";
if(entnr == 551) vname = "US_INFANTRY_SAM_KNEELING ";
if(entnr == 552) vname = "CIS_INFANTRY_SAM_STANDING";
if(entnr == 553) vname = "CIS_INFANTRY_SAM_KNEELING";
*/
