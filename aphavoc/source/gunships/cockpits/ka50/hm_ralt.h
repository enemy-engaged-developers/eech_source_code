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
		{105, 408, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{106, 408, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{107, 408, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{108, 408, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{109, 408, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{110, 408, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{111, 409, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{112, 409, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{113, 409, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{114, 410, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{115, 410, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{116, 411, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{117, 412, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{118, 413, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(20.0)
		{119, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0))},
		{120, 415, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0))},
		{121, 416, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0))},
		{121, 417, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0))},
		{122, 418, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0))},
		{122, 419, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0))},
		{122, 420, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0))},
		{123, 421, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0))},
		{123, 422, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0))},
		{123, 423, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0))},
		{123, 424, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0))},
		{123, 425, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0))},
		{124, 426, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0))},
		{124, 427, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0))},
		{124, 428, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0))},
		{124, 429, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(20.0)
		{123, 430, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0))},
		{123, 431, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0))},
		{123, 432, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0))},
		{123, 433, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0))},
		{123, 434, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0))},
		{122, 435, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0))},
		{122, 436, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0))},
		{122, 437, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0))},
		{121, 438, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0))},
		{121, 439, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0))},
		{120, 440, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0))},
		{120, 441, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0))},
		{119, 442, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0))},
		{118, 443, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0))},
		{118, 444, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0))},
		{117, 445, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(20.0)
		{116, 446, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0))},
		{115, 447, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0))},
		{114, 448, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0))},
		{113, 448, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0))},
		{112, 449, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0))},
		{111, 450, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0))},
		{110, 450, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0))},
		{109, 451, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0))},
		{108, 451, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0))},
		{107, 452, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0))},
		{106, 452, TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0))},
		{105, 452, TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0))},
		{104, 453, TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0))},
		{103, 453, TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0))},
		{102, 453, TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0))},
		{101, 453, TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0))},
		{100, 453, TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{ 99, 453, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{ 98, 453, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{ 97, 453, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{ 96, 453, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{ 95, 453, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{ 94, 453, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{ 93, 452, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{ 92, 452, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{ 91, 452, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{ 90, 451, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{ 89, 450, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{ 88, 450, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{ 87, 449, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{ 86, 448, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{ 85, 447, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0))},
		{ 84, 446, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0))},
		{ 83, 445, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0))},
		{ 83, 444, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0))},
		{ 82, 443, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0))},
		{ 82, 442, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0))},
		{ 81, 441, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0))},
		{ 81, 440, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0))},
		{ 81, 439, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0))},
		{ 81, 438, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0))},
		{ 80, 437, TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0))},
		{ 80, 436, TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0))},
		{ 80, 435, TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0))},
		{ 80, 434, TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0))},
		{ 80, 433, TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0))},
		{ 80, 432, TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0))},
		{ 80, 431, TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{ 80, 430, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0))},
		{ 81, 429, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0))},
		{ 81, 428, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0))},
		{ 81, 427, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0))},
		{ 81, 426, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0))},
		{ 82, 425, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0))},
		{ 82, 424, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0))},
		{ 82, 423, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0))},
		{ 83, 422, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0))},
		{ 83, 421, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0))},
		{ 84, 420, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0))},
		{ 85, 419, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0))},
		{ 85, 418, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0))},
		{ 86, 417, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0))},
		{ 87, 416, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0))},
		{ 88, 415, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(0.0)
		{ 89, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
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
		{114, 209, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{115, 209, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{116, 209, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{117, 209, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{118, 209, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{119, 210, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{120, 210, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{121, 210, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{122, 211, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{123, 211, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{124, 212, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{125, 212, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{126, 213, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{127, 214, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(20.0)
		{128, 215, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{129, 216, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{130, 217, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{131, 218, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{131, 219, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{132, 220, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{132, 221, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{133, 222, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{133, 223, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{133, 224, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{134, 225, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{134, 226, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{134, 227, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{134, 228, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(20.0)
		{134, 229, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0))},
		{134, 230, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0))},
		{134, 231, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0))},
		{134, 232, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0))},
		{134, 233, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0))},
		{133, 234, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0))},
		{133, 235, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0))},
		{133, 236, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0))},
		{132, 237, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0))},
		{132, 238, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0))},
		{132, 239, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0))},
		{131, 240, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0))},
		{130, 241, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0))},
		{130, 242, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0))},
		{129, 243, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(20.0)
		{128, 244, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{127, 245, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{126, 245, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{125, 246, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{124, 247, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{123, 247, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{122, 248, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{121, 248, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{120, 249, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{119, 249, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{118, 249, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{117, 249, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{116, 249, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{115, 249, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{114, 249, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0))},
		{113, 249, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0))},
		{112, 249, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0))},
		{111, 249, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0))},
		{110, 249, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0))},
		{109, 249, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0))},
		{108, 249, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0))},
		{107, 248, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0))},
		{106, 248, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0))},
		{105, 248, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0))},
		{104, 247, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0))},
		{103, 247, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0))},
		{102, 246, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0))},
		{101, 245, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0))},
		{100, 244, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{ 99, 243, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{ 98, 242, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{ 97, 241, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{ 96, 240, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{ 96, 239, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{ 95, 238, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{ 95, 237, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{ 95, 236, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{ 94, 235, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{ 94, 234, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{ 94, 233, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{ 94, 232, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{ 93, 231, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{ 93, 230, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{ 93, 229, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{ 93, 228, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{ 93, 227, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{ 94, 226, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{ 94, 225, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{ 94, 224, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{ 94, 223, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{ 95, 222, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{ 95, 221, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{ 95, 220, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{ 96, 219, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{ 97, 218, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{ 97, 217, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{ 98, 216, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(0.0)
		{ 99, 215, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
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
		{406, 398, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{407, 398, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{408, 399, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{409, 399, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{410, 399, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{411, 400, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{412, 400, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{413, 401, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{414, 401, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{415, 402, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{416, 403, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{417, 404, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{418, 405, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(20.0)
		{419, 406, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0))},
		{419, 407, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0))},
		{420, 408, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0))},
		{421, 409, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0))},
		{421, 410, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0))},
		{421, 411, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0))},
		{422, 412, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0))},
		{422, 413, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0))},
		{422, 414, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0))},
		{423, 415, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0))},
		{423, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0))},
		{423, 417, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0))},
		{423, 418, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0))},
		{423, 419, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0))},
		{423, 420, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0))},
		{423, 421, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(20.0)
		{423, 422, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{423, 423, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{423, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{422, 425, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{422, 426, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{422, 427, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{422, 428, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{421, 429, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{421, 430, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{420, 431, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{420, 432, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{419, 433, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{418, 434, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{417, 435, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(20.0)
		{416, 436, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0))},
		{415, 437, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0))},
		{414, 438, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0))},
		{413, 438, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0))},
		{412, 439, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0))},
		{411, 439, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0))},
		{410, 440, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0))},
		{409, 440, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0))},
		{408, 440, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0))},
		{407, 440, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0))},
		{406, 440, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0))},
		{405, 440, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0))},
		{404, 440, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0))},
		{403, 440, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0))},
		{402, 440, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{401, 440, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{400, 440, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{399, 440, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{398, 439, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{397, 439, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{396, 439, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{395, 438, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{394, 437, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{393, 437, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{392, 436, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{391, 435, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{390, 434, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{389, 433, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{388, 432, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0))},
		{388, 431, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0))},
		{387, 430, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0))},
		{387, 429, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0))},
		{386, 428, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0))},
		{386, 427, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0))},
		{386, 426, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0))},
		{385, 425, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0))},
		{385, 424, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0))},
		{385, 423, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0))},
		{385, 422, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0))},
		{385, 421, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0))},
		{385, 420, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0))},
		{385, 419, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0))},
		{385, 418, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0))},
		{385, 417, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{385, 416, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{385, 415, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{385, 414, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{385, 413, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{386, 412, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{386, 411, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{386, 410, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{387, 409, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{387, 408, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{388, 407, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{389, 406, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{389, 405, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{390, 404, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{391, 403, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(0.0)
		{392, 402, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
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
		{403, 200, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{404, 200, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{405, 201, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{406, 201, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{407, 201, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{408, 202, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{409, 202, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{410, 203, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{411, 203, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{412, 204, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{413, 205, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{414, 206, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{414, 207, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(20.0)
		{415, 208, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{416, 209, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{416, 210, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{417, 211, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{417, 212, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{417, 213, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{418, 214, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{418, 215, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{418, 216, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{418, 217, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{418, 218, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{418, 219, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{418, 220, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{418, 221, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(20.0)
		{418, 222, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{418, 223, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{417, 224, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{417, 225, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{417, 226, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{416, 227, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{416, 228, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{415, 229, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{415, 230, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{414, 231, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{413, 232, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{412, 233, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{411, 234, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(20.0)
		{410, 235, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{409, 236, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{408, 236, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{407, 237, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{406, 237, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{405, 237, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{404, 238, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{403, 238, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{402, 238, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{401, 238, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{400, 238, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{399, 238, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{398, 238, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{397, 238, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{396, 238, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0))},
		{395, 238, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0))},
		{394, 238, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0))},
		{393, 237, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0))},
		{392, 237, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0))},
		{391, 236, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0))},
		{390, 236, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0))},
		{389, 235, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0))},
		{388, 234, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0))},
		{387, 233, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0))},
		{386, 232, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0))},
		{385, 231, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{384, 230, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{384, 229, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{383, 228, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{383, 227, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{383, 226, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{382, 225, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{382, 224, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{382, 223, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{382, 222, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{382, 221, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{382, 220, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{382, 219, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{382, 218, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{382, 217, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{382, 216, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0))},
		{382, 215, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0))},
		{382, 214, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0))},
		{383, 213, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0))},
		{383, 212, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0))},
		{384, 211, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0))},
		{384, 210, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0))},
		{385, 209, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0))},
		{385, 208, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0))},
		{386, 207, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0))},
		{387, 206, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0))},
		{388, 205, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(0.0)
		{389, 204, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
