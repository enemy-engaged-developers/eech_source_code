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
		{100, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{100, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{100, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{100, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{100, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{101, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{101, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{101, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{101, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{102, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{102, 368, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{103, 367, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{103, 366, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{104, 365, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{105, 364, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-1.0)
		#define TICK_INCREMENT	(1.0)
		{106, 363, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{107, 362, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{108, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{109, 360, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{110, 359, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{111, 359, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{112, 358, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{113, 358, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{114, 358, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{115, 357, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{116, 357, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{117, 357, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{118, 357, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{119, 357, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{120, 357, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{121, 357, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{122, 357, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{123, 357, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{124, 357, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{125, 358, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{126, 358, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{127, 359, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{128, 359, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{129, 360, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{130, 361, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{131, 362, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{132, 363, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{133, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{133, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{133, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{134, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{134, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{134, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{134, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{134, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{134, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{134, 373, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{134, 374, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{134, 375, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{134, 376, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{134, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{133, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{133, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{133, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{132, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{132, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{131, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{130, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{129, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{128, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{127, 387, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{126, 388, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{125, 389, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{124, 389, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{123, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{122, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{121, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{120, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{119, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{118, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{117, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{116, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{115, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{114, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{113, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{112, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{111, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{110, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{109, 390, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(0.0)
		{108, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{106, 181, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{106, 180, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{105, 179, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{105, 178, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{105, 177, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{105, 176, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{105, 175, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{106, 174, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{106, 173, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{106, 172, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{106, 171, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{107, 170, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{107, 169, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{108, 168, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-1.0)
		#define TICK_INCREMENT	(1.0)
		{109, 167, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{109, 166, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{110, 165, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{111, 164, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{112, 164, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{113, 163, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{114, 163, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{115, 162, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{116, 162, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{117, 161, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{118, 161, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{119, 161, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{120, 161, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{121, 161, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{122, 161, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{123, 161, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{124, 161, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{125, 161, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{126, 161, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{127, 161, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{128, 162, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{129, 162, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{130, 163, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{131, 163, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{132, 164, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{133, 165, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{134, 166, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{135, 167, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{136, 168, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{136, 169, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{137, 170, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{137, 171, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{138, 172, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{138, 173, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{138, 174, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{138, 175, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{138, 176, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{138, 177, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{138, 178, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{138, 179, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{138, 180, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{138, 181, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{138, 182, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{137, 183, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{137, 184, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{137, 185, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{136, 186, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{135, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{135, 188, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{134, 189, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{133, 190, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{132, 190, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{131, 191, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{130, 192, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{129, 192, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{128, 193, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{127, 193, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{126, 193, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{125, 193, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{124, 194, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{123, 194, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{122, 194, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{121, 194, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{120, 194, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{119, 193, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{118, 193, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{117, 193, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{116, 193, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(0.0)
		{115, 192, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{402, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{402, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{402, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{402, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{402, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{403, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{403, 363, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{403, 362, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{404, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{404, 360, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{405, 359, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{405, 358, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{406, 357, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-1.0)
		#define TICK_INCREMENT	(1.0)
		{407, 356, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{408, 355, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{409, 354, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{410, 354, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{411, 353, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{412, 353, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{413, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{414, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{415, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{416, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{417, 352, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{418, 351, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{419, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{420, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{421, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{422, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{423, 352, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{424, 353, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{425, 353, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{426, 354, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{427, 355, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{428, 355, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{429, 356, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{430, 357, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{430, 358, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{431, 359, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{431, 360, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{432, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{432, 362, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{433, 363, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{433, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{433, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{433, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{433, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{433, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{433, 369, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{433, 370, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{433, 371, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{433, 372, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{432, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{432, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{432, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{431, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{431, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{430, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{429, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{428, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{427, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{426, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{425, 382, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{424, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{423, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{422, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{421, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{420, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{419, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{418, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{417, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{416, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{415, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{414, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{413, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{412, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{411, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{410, 382, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(0.0)
		{409, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{401, 173, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{401, 172, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{401, 171, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{401, 170, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{401, 169, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{401, 168, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{402, 167, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{402, 166, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{402, 165, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{403, 164, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{403, 163, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{404, 162, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{405, 161, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-1.0)
		#define TICK_INCREMENT	(1.0)
		{406, 160, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{407, 159, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{408, 158, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{409, 158, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{410, 157, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{411, 157, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{412, 156, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{413, 156, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{414, 156, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{415, 156, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{416, 155, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{417, 155, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{418, 155, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{419, 156, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{420, 156, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{421, 156, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{422, 156, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{423, 157, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{424, 157, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{425, 158, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{426, 159, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{427, 159, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{428, 160, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{428, 161, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{429, 162, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{430, 163, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{430, 164, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{430, 165, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{431, 166, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{431, 167, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{431, 168, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{431, 169, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{431, 170, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{431, 171, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{431, 172, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{431, 173, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{431, 174, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{430, 175, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{430, 176, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{430, 177, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{429, 178, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{429, 179, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{428, 180, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{427, 181, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{426, 182, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{425, 183, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{424, 184, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{423, 185, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{422, 185, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{421, 186, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{420, 186, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{419, 186, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{418, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{417, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{416, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{415, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{414, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{413, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{412, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{411, 187, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{410, 186, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{409, 186, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{408, 185, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(0.0)
		{407, 185, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
