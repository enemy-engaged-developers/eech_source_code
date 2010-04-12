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
	vertical_speed_indicator_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 135, y = 394

		#define TICK_VALUE		(-300.0)
		#define TICK_INCREMENT	(100.0)
		{157, 395, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{157, 396, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{157, 397, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{157, 398, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{156, 399, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{156, 400, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{156, 401, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{156, 402, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{155, 403, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{155, 404, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{154, 405, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{154, 406, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{153, 407, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{152, 408, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{151, 409, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-200.0)
		#define TICK_INCREMENT	(100.0)
		{150, 410, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{149, 411, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{148, 412, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{147, 413, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{146, 413, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{145, 414, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{144, 414, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{143, 415, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{142, 415, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{141, 415, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{140, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{139, 416, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{138, 416, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{137, 416, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{136, 416, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-100.0)
		#define TICK_INCREMENT	(50.0)
		{135, 416, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{134, 416, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{133, 416, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{132, 416, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{131, 416, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{130, 416, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{129, 416, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{128, 415, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{127, 415, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{126, 414, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{125, 414, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{124, 414, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{123, 413, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{122, 412, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{121, 412, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{120, 411, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-50.0)
		#define TICK_INCREMENT	(50.0)
		{119, 410, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{118, 409, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{117, 408, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{117, 407, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{116, 406, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{115, 405, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{115, 404, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{114, 403, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{114, 402, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{114, 401, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{113, 400, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{113, 399, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{113, 398, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{113, 397, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{113, 396, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{113, 395, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{112, 394, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{112, 393, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{113, 392, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{113, 391, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{113, 390, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{113, 389, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{113, 388, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{114, 387, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{114, 386, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{114, 385, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{115, 384, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{115, 383, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{116, 382, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{117, 381, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{117, 380, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{118, 379, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(50.0)
		{119, 378, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{120, 377, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{121, 376, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{122, 376, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{123, 375, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{124, 374, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{125, 374, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{126, 373, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{127, 373, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{128, 373, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{129, 372, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{130, 372, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{131, 372, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{132, 372, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{133, 372, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{134, 372, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{135, 372, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{136, 372, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{137, 372, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{138, 372, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{139, 372, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{140, 372, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{141, 373, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{142, 373, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{143, 373, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{144, 374, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{145, 374, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{146, 375, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{147, 375, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{148, 376, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{149, 377, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{150, 378, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{151, 379, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{152, 380, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{153, 381, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{154, 382, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{154, 383, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{155, 384, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{155, 385, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{156, 386, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{156, 387, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{156, 388, TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{156, 389, TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{157, 390, TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{157, 391, TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{157, 392, TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{157, 393, TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{157, 394, TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	vertical_speed_indicator_needle_scale_down_20_left_30[] =
	{
		// dial centred at x = 391, y = 377

		#define TICK_VALUE		(-300.0)
		#define TICK_INCREMENT	(100.0)
		{410, 384, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{410, 385, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{410, 386, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{409, 387, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{409, 388, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{408, 389, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{408, 390, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{407, 391, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{407, 392, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{406, 393, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{405, 394, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{404, 395, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{403, 395, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-200.0)
		#define TICK_INCREMENT	(100.0)
		{402, 396, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{401, 397, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{400, 397, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{399, 397, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{398, 398, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{397, 398, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{396, 398, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{395, 398, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{394, 399, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{393, 399, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{392, 399, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{391, 398, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{390, 398, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{389, 398, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{388, 398, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-100.0)
		#define TICK_INCREMENT	(50.0)
		{387, 398, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{386, 397, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{385, 397, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{384, 396, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{383, 396, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{382, 395, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{381, 395, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{380, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{379, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{378, 392, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{377, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{376, 390, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{375, 389, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{375, 388, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(-50.0)
		#define TICK_INCREMENT	(50.0)
		{374, 387, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{374, 386, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{373, 385, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{373, 384, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{372, 383, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{372, 382, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{372, 381, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{371, 380, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{371, 379, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{371, 378, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{371, 377, TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{371, 376, TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{371, 375, TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{371, 374, TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{371, 373, TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{371, 372, TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{371, 371, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{371, 370, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{372, 369, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{372, 368, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{372, 367, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{373, 366, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{373, 365, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{374, 364, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{374, 363, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{375, 362, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{376, 361, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{377, 360, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{378, 359, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(50.0)
		{379, 358, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{380, 358, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{381, 357, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{382, 357, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{383, 356, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{384, 356, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{385, 356, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{386, 356, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{387, 356, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{388, 356, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{389, 356, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{390, 356, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{391, 356, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{392, 356, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{393, 356, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{394, 356, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{395, 357, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{396, 357, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{397, 357, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{398, 358, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{399, 358, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{400, 359, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{401, 360, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{402, 360, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{403, 361, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{404, 362, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{405, 363, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{405, 364, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{406, 365, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{407, 366, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 18.0)))},
		{407, 367, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 18.0)))},
		{408, 368, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 18.0)))},
		{408, 369, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 18.0)))},
		{409, 370, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 18.0)))},
		{409, 371, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 18.0)))},
		{410, 372, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 18.0)))},
		{410, 373, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 18.0)))},
		{410, 374, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 18.0)))},
		{410, 375, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 18.0)))},
		{411, 376, TICK_VALUE + (TICK_INCREMENT * (10.0 / 18.0)))},
		{411, 377, TICK_VALUE + (TICK_INCREMENT * (11.0 / 18.0)))},
		{411, 378, TICK_VALUE + (TICK_INCREMENT * (12.0 / 18.0)))},
		{411, 379, TICK_VALUE + (TICK_INCREMENT * (13.0 / 18.0)))},
		{411, 380, TICK_VALUE + (TICK_INCREMENT * (14.0 / 18.0)))},
		{411, 381, TICK_VALUE + (TICK_INCREMENT * (15.0 / 18.0)))},
		{411, 382, TICK_VALUE + (TICK_INCREMENT * (16.0 / 18.0)))},
		{410, 383, TICK_VALUE + (TICK_INCREMENT * (17.0 / 18.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
