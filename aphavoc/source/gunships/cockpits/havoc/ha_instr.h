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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_havoc_instrument_colours (void);

extern void set_havoc_instrument_colours (void);

extern void draw_havoc_barometric_altimeter (cockpit_panels panel);

extern void draw_havoc_airspeed_indicator (cockpit_panels panel);

extern void draw_havoc_main_rotor_rpm_indicator (cockpit_panels panel);

extern void draw_havoc_g_meter (cockpit_panels panel);

extern void draw_havoc_engine_torque_indicator (cockpit_panels panel);

extern void draw_havoc_engine_temperature_indicator (cockpit_panels panel);

extern void draw_havoc_engine_rpm_indicator (cockpit_panels panel);

extern void draw_havoc_engine_temperature_and_rpm_indicator_ticks (cockpit_panels panel);

extern void draw_havoc_vertical_speed_indicator (cockpit_panels panel);

extern void draw_havoc_clock (cockpit_panels panel);

extern void draw_havoc_radar_altimeter (cockpit_panels panel);

extern void draw_havoc_fuel_gauge (cockpit_panels panel);

extern void draw_havoc_fixed_cockpit_hsi_waypoint_distance_digits (cockpit_panels panel);

extern void draw_havoc_fixed_cockpit_hsi_waypoint_identifier (cockpit_panels panel);

extern void get_havoc_virtual_cockpit_adi_angles (matrix3x3 attitude, float *heading, float *pitch, float *roll);

extern void get_havoc_virtual_cockpit_hsi_needle_values (float *direction_finder, float *flight_path, float *drift);

extern float get_airspeed_indicator_needle_value (void);

extern float get_havoc_virtual_cockpit_gmeter_needle_value (void);

extern float get_havoc_virtual_cockpit_vsi_needle_value (void);

extern float get_havoc_virtual_cockpit_rad_alt_needle_value (void);

extern void get_havoc_virtual_cockpit_clock_hand_values (float *hours, float *minutes, float *seconds);

extern float get_havoc_virtual_cockpit_rotor_rpm_needle_value(float rpm);

extern float get_havoc_barometric_alt_long_needle_value(void);

extern float get_havoc_barometric_alt_shrt_needle_value(void);

extern float get_havoc_fuel_quantity_needle_value(void);

extern float get_havoc_slip_needle_value(void);

// Casm 10SEP05 Havoc Instruments
extern void initialise_havoc_instruments (void);

extern void deinitialise_havoc_instruments (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
