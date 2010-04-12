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
////Moje 030818 This should be "shalsh"+"star" for VJ 030807 radar range adjustable
#define KA50_RADAR_SCAN_RANGE_1000						((float) 1000.0)
#define KA50_RADAR_SCAN_RANGE_2000		  				((float) 2000.0)
#define KA50_RADAR_SCAN_RANGE_4000	  					((float) 4000.0)
#define KA50_RADAR_SCAN_RANGE_6000		  				((float) 6000.0)
////Moje 030818 This should be "star"+"shlash"
//VJ 030807 radar range adjustable
/* ////Moje 030818 Added "Shlash"+"star" until VJ looks into this                 
extern float radar_range_ka50[4];                

extern float  	KA50_RADAR_SCAN_RANGE_1000,
					KA50_RADAR_SCAN_RANGE_2000,
					KA50_RADAR_SCAN_RANGE_4000,
					KA50_RADAR_SCAN_RANGE_6000;
////Moje 030818 added "star"+"shlash" next line until VJ looks into this
*/
#define KA50_RADAR_SCAN_ARC_SIZE_360			  		(RADAR_SCAN_ARC_SIZE_360)
#define KA50_RADAR_SCAN_ARC_SIZE_180	  		  		((float) rad (180.0f))
#define KA50_RADAR_SCAN_ARC_SIZE_90	  		  		((float) rad (90.0f))
#define KA50_RADAR_SCAN_ARC_SIZE_60	  		  		((float) rad (60.0f))
#define KA50_RADAR_SCAN_ARC_SIZE_45	  		  		((float) rad (45.0f))
#define KA50_RADAR_SCAN_ARC_SIZE_30	  		  		((float) rad (30.0f))
#define KA50_RADAR_SCAN_ARC_SIZE_15	  		  		((float) rad (15.0f))
#define KA50_RADAR_SCAN_ARC_SEGMENT_SIZE  	 		((float) rad (5.0f))

#define KA50_GROUND_RADAR_SCAN_DATUM_ROTATE_STEP	((float) KA50_RADAR_SCAN_ARC_SIZE_15 * 0.5)

#define KA50_AIR_RADAR_SCAN_DATUM_ROTATE_STEP 		((float) KA50_RADAR_SCAN_ARC_SIZE_30 * 0.5)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_ka50_radar (void);

extern void deinitialise_ka50_radar (void);

extern void update_ka50_ground_radar (void);

extern void centre_ka50_ground_radar (void);

extern void update_ka50_air_radar (void);

extern void centre_ka50_air_radar (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
