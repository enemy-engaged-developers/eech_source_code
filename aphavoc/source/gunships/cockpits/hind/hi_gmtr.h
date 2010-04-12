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
	g_meter_needle_scale_level_ahead[] =
	{
		// dial centred at x = 117, y = 374

		#define TICK_VALUE		(-2.0)
		#define TICK_INCREMENT	(1.0)
		{100, 378, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{100, 377, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{100, 376, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{100, 375, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{100, 374, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{101, 373, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{101, 372, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{101, 371, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{101, 370, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{102, 369, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{102, 368, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{103, 367, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{103, 366, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{104, 365, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{105, 364, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-1.0)
		#define TICK_INCREMENT	(1.0)
		{106, 363, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{107, 362, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{108, 361, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{109, 360, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{110, 359, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{111, 359, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{112, 358, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{113, 358, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{114, 358, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{115, 357, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{116, 357, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{117, 357, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{118, 357, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{119, 357, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{120, 357, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{121, 357, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{122, 357, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{123, 357, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{124, 357, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{125, 358, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{126, 358, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{127, 359, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{128, 359, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{129, 360, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{130, 361, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{131, 362, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{132, 363, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{133, 364, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{133, 365, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{133, 366, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{134, 367, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{134, 368, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{134, 369, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{134, 370, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{134, 371, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{134, 372, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{134, 373, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{134, 374, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{134, 375, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{134, 376, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{134, 377, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{133, 378, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{133, 379, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{133, 380, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{132, 381, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{132, 382, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{131, 383, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{130, 384, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{129, 385, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{128, 386, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{127, 387, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{126, 388, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{125, 389, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{124, 389, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{123, 390, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{122, 390, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{121, 390, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{120, 391, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{119, 391, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{118, 391, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{117, 391, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{116, 391, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{115, 391, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{114, 391, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{113, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{112, 391, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{111, 391, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{110, 391, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{109, 390, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(0.0)
		{108, 390, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	g_meter_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 122, y = 177

		#define TICK_VALUE		(-2.0)
		#define TICK_INCREMENT	(1.0)
		{106, 181, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{106, 180, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{105, 179, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{105, 178, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{105, 177, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{105, 176, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{105, 175, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{106, 174, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{106, 173, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{106, 172, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{106, 171, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{107, 170, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{107, 169, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{108, 168, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-1.0)
		#define TICK_INCREMENT	(1.0)
		{109, 167, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{109, 166, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{110, 165, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{111, 164, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{112, 164, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{113, 163, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{114, 163, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{115, 162, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{116, 162, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{117, 161, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{118, 161, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{119, 161, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{120, 161, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{121, 161, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{122, 161, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{123, 161, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{124, 161, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{125, 161, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{126, 161, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{127, 161, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{128, 162, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{129, 162, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{130, 163, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{131, 163, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{132, 164, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{133, 165, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{134, 166, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{135, 167, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{136, 168, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{136, 169, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{137, 170, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{137, 171, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{138, 172, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{138, 173, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{138, 174, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{138, 175, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{138, 176, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{138, 177, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{138, 178, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{138, 179, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{138, 180, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{138, 181, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{138, 182, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{137, 183, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{137, 184, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{137, 185, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{136, 186, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{135, 187, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{135, 188, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{134, 189, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{133, 190, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{132, 190, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{131, 191, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{130, 192, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{129, 192, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{128, 193, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{127, 193, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{126, 193, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{125, 193, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{124, 194, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{123, 194, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{122, 194, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{121, 194, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{120, 194, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{119, 193, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{118, 193, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{117, 193, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{116, 193, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(0.0)
		{115, 192, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	g_meter_needle_scale_level_left_30[] =
	{
		// dial centred at x = 418, y = 368

		#define TICK_VALUE		(-2.0)
		#define TICK_INCREMENT	(1.0)
		{402, 369, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{402, 368, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{402, 367, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{402, 366, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{402, 365, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{403, 364, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{403, 363, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{403, 362, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{404, 361, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{404, 360, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{405, 359, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{405, 358, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{406, 357, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-1.0)
		#define TICK_INCREMENT	(1.0)
		{407, 356, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{408, 355, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{409, 354, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{410, 354, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{411, 353, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{412, 353, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{413, 352, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{414, 352, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{415, 352, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{416, 352, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{417, 352, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{418, 351, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{419, 352, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{420, 352, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{421, 352, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{422, 352, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{423, 352, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{424, 353, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{425, 353, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{426, 354, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{427, 355, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{428, 355, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{429, 356, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{430, 357, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{430, 358, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{431, 359, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{431, 360, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{432, 361, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{432, 362, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{433, 363, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{433, 364, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{433, 365, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{433, 366, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{433, 367, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{433, 368, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{433, 369, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{433, 370, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{433, 371, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{433, 372, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{432, 373, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{432, 374, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{432, 375, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{431, 376, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{431, 377, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{430, 378, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{429, 379, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{428, 380, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{427, 381, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{426, 382, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{425, 382, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{424, 383, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{423, 383, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{422, 384, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{421, 384, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{420, 384, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{419, 384, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{418, 384, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{417, 384, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{416, 384, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{415, 384, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{414, 384, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{413, 384, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{412, 383, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{411, 383, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{410, 382, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(0.0)
		{409, 382, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	g_meter_needle_scale_down_20_left_30[] =
	{
		// dial centred at x = 416, y = 171

		#define TICK_VALUE		(-2.0)
		#define TICK_INCREMENT	(1.0)
		{401, 173, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{401, 172, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{401, 171, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{401, 170, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{401, 169, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{401, 168, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{402, 167, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{402, 166, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{402, 165, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{403, 164, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{403, 163, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{404, 162, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{405, 161, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-1.0)
		#define TICK_INCREMENT	(1.0)
		{406, 160, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{407, 159, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{408, 158, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{409, 158, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{410, 157, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{411, 157, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{412, 156, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{413, 156, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{414, 156, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{415, 156, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{416, 155, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{417, 155, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{418, 155, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{419, 156, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{420, 156, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{421, 156, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{422, 156, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{423, 157, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{424, 157, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{425, 158, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{426, 159, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{427, 159, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{428, 160, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{428, 161, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{429, 162, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{430, 163, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{430, 164, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{430, 165, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{431, 166, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{431, 167, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{431, 168, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{431, 169, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{431, 170, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{431, 171, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{431, 172, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{431, 173, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{431, 174, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{430, 175, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{430, 176, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{430, 177, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{429, 178, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{429, 179, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{428, 180, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{427, 181, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{426, 182, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{425, 183, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{424, 184, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{423, 185, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{422, 185, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{421, 186, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{420, 186, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{419, 186, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{418, 187, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{417, 187, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{416, 187, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{415, 187, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{414, 187, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{413, 187, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{412, 187, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{411, 187, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{410, 186, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{409, 186, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{408, 185, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(0.0)
		{407, 185, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
