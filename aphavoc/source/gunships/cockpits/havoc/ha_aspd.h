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

static scale_data
	airspeed_indicator_airspeed_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 150, y = 329

		#define TICK_VALUE		(-50.0)
		#define TICK_INCREMENT	(50.0)
		{129, 338, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0))},
		{129, 337, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0))},
		{129, 336, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0))},
		{128, 335, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0))},
		{128, 334, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0))},
		{128, 333, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0))},
		{128, 332, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0))},
		{127, 331, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0))},
		{127, 330, TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{127, 329, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0))},
		{127, 328, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0))},
		{127, 327, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0))},
		{128, 326, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0))},
		{128, 325, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0))},
		{128, 324, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0))},
		{128, 323, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0))},
		{128, 322, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0))},
		{129, 321, TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(50.0)
		{129, 320, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{130, 319, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{130, 318, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{131, 317, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{131, 316, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{132, 315, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{133, 314, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{134, 313, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0))},
		{135, 312, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0))},
		{136, 311, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0))},
		{137, 310, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0))},
		{138, 310, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0))},
		{139, 309, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0))},
		{140, 309, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0))},
		{141, 308, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0))},
		{142, 308, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0))},
		{143, 308, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0))},
		{144, 307, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0))},
		{145, 307, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0))},
		{146, 307, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0))},
		{147, 307, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0))},
		{148, 307, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0))},
		{149, 307, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{150, 307, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0))},
		{151, 307, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0))},
		{152, 307, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0))},
		{153, 307, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0))},
		{154, 307, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0))},
		{155, 307, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0))},
		{156, 308, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0))},
		{157, 308, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0))},
		{158, 308, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0))},
		{159, 309, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0))},
		{160, 309, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0))},
		{161, 310, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0))},
		{162, 310, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0))},
		{163, 311, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0))},
		{164, 312, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{165, 313, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0))},
		{166, 314, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0))},
		{167, 315, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0))},
		{168, 316, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0))},
		{169, 317, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0))},
		{169, 318, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0))},
		{170, 319, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0))},
		{170, 320, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0))},
		{170, 321, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0))},
		{171, 322, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0))},
		{171, 323, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0))},
		{171, 324, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0))},
		{172, 325, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0))},
		{172, 326, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0))},
		{172, 327, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0))},
		{172, 328, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(50.0)
		{172, 329, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{172, 330, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{172, 331, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{172, 332, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{172, 333, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{171, 334, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{171, 335, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{171, 336, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(450.0)
		#define TICK_INCREMENT	(0.0)
		{170, 337, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	airspeed_indicator_slip_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 150, y = 329

		#define TICK_VALUE		(-100.0)
		#define TICK_INCREMENT	(50.0)
		{134, 345, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{135, 346, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{136, 347, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{137, 347, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{138, 348, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{139, 348, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{140, 349, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-50.0)
		#define TICK_INCREMENT	(50.0)
		{141, 349, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0))},
		{142, 350, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0))},
		{143, 350, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0))},
		{144, 350, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0))},
		{145, 351, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0))},
		{146, 351, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0))},
		{147, 351, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0))},
		{148, 351, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0))},
		{149, 351, TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{150, 351, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{151, 351, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{152, 351, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{153, 351, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{154, 351, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{155, 350, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{156, 350, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{157, 350, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(50.0)
		{158, 350, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{159, 349, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{160, 349, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{161, 348, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{162, 347, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{163, 346, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{164, 345, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(0.0)
		{165, 344, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	airspeed_indicator_airspeed_needle_scale_down_20_left_30[] =
	{
		// dial centred at x = 415, y = 320

		#define TICK_VALUE		(-50.0)
		#define TICK_INCREMENT	(50.0)
		{395, 323, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{395, 322, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{395, 321, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{395, 320, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{395, 319, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{395, 318, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{395, 317, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{395, 316, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{395, 315, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{395, 314, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{395, 313, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{396, 312, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{396, 311, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{396, 310, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{397, 309, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{397, 308, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(50.0)
		{398, 307, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{398, 306, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{399, 305, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{400, 304, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{401, 303, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{402, 302, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{403, 302, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{404, 301, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0))},
		{405, 300, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0))},
		{406, 300, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0))},
		{407, 299, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0))},
		{408, 299, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0))},
		{409, 299, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0))},
		{410, 299, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0))},
		{411, 298, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0))},
		{412, 298, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0))},
		{413, 298, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0))},
		{414, 298, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0))},
		{415, 298, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0))},
		{416, 298, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0))},
		{417, 298, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0))},
		{418, 298, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{419, 299, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{420, 299, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{421, 299, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{422, 300, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{423, 300, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{424, 301, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{425, 301, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{426, 302, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{427, 302, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{428, 303, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{429, 304, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{430, 305, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{431, 306, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{431, 307, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{432, 308, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0))},
		{433, 309, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0))},
		{433, 310, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0))},
		{434, 311, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0))},
		{434, 312, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0))},
		{435, 313, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0))},
		{435, 314, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0))},
		{435, 315, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0))},
		{436, 316, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0))},
		{436, 317, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0))},
		{436, 318, TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0))},
		{436, 319, TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0))},
		{436, 320, TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0))},
		{436, 321, TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0))},
		{436, 322, TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0))},
		{436, 323, TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0))},
		{436, 324, TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(50.0)
		{436, 325, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{435, 326, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{435, 327, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{435, 328, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{435, 329, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{434, 330, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{434, 331, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{433, 332, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(450.0)
		#define TICK_INCREMENT	(0.0)
		{433, 333, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	airspeed_indicator_slip_needle_scale_down_20_left_30[] =
	{
		// dial centred at x = 415, y = 320

		#define TICK_VALUE		(-100.0)
		#define TICK_INCREMENT	(50.0)
		{398, 331, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0))},
		{399, 332, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0))},
		{399, 333, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0))},
		{400, 334, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0))},
		{401, 335, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0))},
		{402, 336, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-50.0)
		#define TICK_INCREMENT	(50.0)
		{403, 337, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0))},
		{404, 337, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0))},
		{405, 338, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0))},
		{406, 339, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0))},
		{407, 339, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0))},
		{408, 340, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0))},
		{409, 340, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0))},
		{410, 340, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0))},
		{411, 340, TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{412, 341, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{413, 341, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{414, 341, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{415, 341, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{416, 341, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{417, 341, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{418, 341, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(50.0)
		{419, 341, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{420, 341, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{421, 341, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{422, 341, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{423, 340, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{424, 340, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{425, 340, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{426, 339, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(0.0)
		{427, 339, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
