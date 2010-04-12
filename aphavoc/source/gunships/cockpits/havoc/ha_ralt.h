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
	radar_altimeter_needle_scale_level_ahead[] =
	{
		// dial centred at x = 102, y = 430

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(20.0)
		{105, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{106, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{107, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{108, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{109, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{110, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{111, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{112, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{113, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{114, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{115, 410, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{116, 411, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{117, 412, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{118, 413, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(20.0)
		{119, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{120, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{121, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{121, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{122, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{122, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{122, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{123, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{123, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{123, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{123, 424, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{123, 425, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{124, 426, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{124, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{124, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{124, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(20.0)
		{123, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{123, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{123, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{123, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{123, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{122, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{122, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{122, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{121, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{121, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{120, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{120, 441, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{119, 442, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{118, 443, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{118, 444, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{117, 445, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(20.0)
		{116, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{115, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{114, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{113, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{112, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{111, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{110, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{109, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{108, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{107, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{106, 452, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{105, 452, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{104, 453, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{103, 453, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{102, 453, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{101, 453, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{100, 453, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{ 99, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{ 98, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{ 97, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{ 96, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{ 95, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{ 94, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{ 93, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{ 92, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{ 91, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{ 90, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{ 89, 450, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{ 88, 450, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{ 87, 449, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{ 86, 448, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{ 85, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{ 84, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{ 83, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{ 83, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{ 82, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{ 82, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{ 81, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{ 81, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{ 81, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{ 81, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{ 80, 437, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{ 80, 436, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{ 80, 435, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{ 80, 434, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{ 80, 433, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{ 80, 432, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{ 80, 431, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{ 80, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{ 81, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{ 81, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{ 81, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{ 81, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{ 82, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{ 82, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{ 82, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{ 83, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{ 83, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{ 84, 420, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{ 85, 419, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{ 85, 418, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{ 86, 417, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{ 87, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{ 88, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(0.0)
		{ 89, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	radar_altimeter_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 114, y = 229

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(20.0)
		{114, 209, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{115, 209, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{116, 209, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{117, 209, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{118, 209, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{119, 210, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{120, 210, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{121, 210, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{122, 211, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{123, 211, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{124, 212, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{125, 212, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{126, 213, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{127, 214, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(20.0)
		{128, 215, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{129, 216, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{130, 217, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{131, 218, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{131, 219, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{132, 220, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{132, 221, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{133, 222, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{133, 223, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{133, 224, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{134, 225, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{134, 226, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{134, 227, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{134, 228, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(20.0)
		{134, 229, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{134, 230, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{134, 231, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{134, 232, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{134, 233, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{133, 234, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{133, 235, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{133, 236, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{132, 237, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{132, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{132, 239, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{131, 240, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{130, 241, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{130, 242, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{129, 243, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(20.0)
		{128, 244, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{127, 245, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{126, 245, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{125, 246, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{124, 247, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{123, 247, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{122, 248, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{121, 248, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{120, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{119, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{118, 249, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{117, 249, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{116, 249, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{115, 249, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{114, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{113, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{112, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{111, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{110, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{109, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{108, 249, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{107, 248, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{106, 248, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{105, 248, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{104, 247, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{103, 247, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{102, 246, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{101, 245, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{100, 244, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{ 99, 243, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{ 98, 242, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{ 97, 241, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{ 96, 240, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{ 96, 239, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{ 95, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{ 95, 237, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{ 95, 236, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{ 94, 235, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{ 94, 234, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{ 94, 233, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{ 94, 232, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{ 93, 231, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{ 93, 230, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{ 93, 229, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{ 93, 228, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{ 93, 227, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{ 94, 226, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{ 94, 225, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{ 94, 224, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{ 94, 223, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{ 95, 222, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{ 95, 221, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{ 95, 220, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{ 96, 219, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{ 97, 218, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{ 97, 217, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{ 98, 216, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(0.0)
		{ 99, 215, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	radar_altimeter_needle_scale_level_left_30[] =
	{
		// dial centred at x = 404, y = 419

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(20.0)
		{406, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{407, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{408, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{409, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{410, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{411, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{412, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{413, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{414, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{415, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{416, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{417, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{418, 405, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(20.0)
		{419, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{419, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{420, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{421, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{421, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{421, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{422, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{422, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{422, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{423, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{423, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{423, 417, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{423, 418, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{423, 419, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{423, 420, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{423, 421, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(20.0)
		{423, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{423, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{423, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{422, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{422, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{422, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{422, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{421, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{421, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{420, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{420, 432, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{419, 433, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{418, 434, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{417, 435, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(20.0)
		{416, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{415, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{414, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{413, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{412, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{411, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{410, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{409, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{408, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{407, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{406, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{405, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{404, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{403, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{402, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{401, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{400, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{399, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{398, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{397, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{396, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{395, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{394, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{393, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{392, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{391, 435, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{390, 434, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{389, 433, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{388, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{388, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{387, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{387, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{386, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{386, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{386, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{385, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{385, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{385, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{385, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{385, 421, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{385, 420, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{385, 419, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{385, 418, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{385, 417, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{385, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{385, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{385, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{385, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{386, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{386, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{386, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{387, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{387, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{388, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{389, 406, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{389, 405, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{390, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{391, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(0.0)
		{392, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	radar_altimeter_needle_scale_down_20_left_30[] =
	{
		// dial centred at x = 400, y = 219

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(20.0)
		{403, 200, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{404, 200, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{405, 201, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{406, 201, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{407, 201, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{408, 202, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{409, 202, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{410, 203, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{411, 203, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{412, 204, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{413, 205, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{414, 206, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{414, 207, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(20.0)
		{415, 208, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{416, 209, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{416, 210, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{417, 211, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{417, 212, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{417, 213, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{418, 214, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{418, 215, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{418, 216, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{418, 217, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{418, 218, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{418, 219, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{418, 220, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{418, 221, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(20.0)
		{418, 222, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{418, 223, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{417, 224, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{417, 225, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{417, 226, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{416, 227, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{416, 228, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{415, 229, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{415, 230, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{414, 231, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{413, 232, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{412, 233, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{411, 234, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(20.0)
		{410, 235, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{409, 236, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{408, 236, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{407, 237, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{406, 237, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{405, 237, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{404, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{403, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{402, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{401, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{400, 238, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{399, 238, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{398, 238, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{397, 238, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{396, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{395, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{394, 238, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{393, 237, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{392, 237, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{391, 236, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{390, 236, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{389, 235, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{388, 234, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{387, 233, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{386, 232, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{385, 231, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{384, 230, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{384, 229, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{383, 228, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{383, 227, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{383, 226, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{382, 225, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{382, 224, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{382, 223, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{382, 222, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{382, 221, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{382, 220, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{382, 219, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{382, 218, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{382, 217, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{382, 216, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{382, 215, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{382, 214, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{383, 213, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{383, 212, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{384, 211, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{384, 210, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{385, 209, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{385, 208, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{386, 207, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{387, 206, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{388, 205, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(0.0)
		{389, 204, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
