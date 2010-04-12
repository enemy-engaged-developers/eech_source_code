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
	lh_engine_temperature_indicator_line_down_20_ahead[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{496, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{496, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{496, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{496, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{496, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{496, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{496, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{496, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{496, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{496, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{496, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{496, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{496, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{496, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{496, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{496, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{496, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{496, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{496, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{496, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{496, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{496, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{496, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{496, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{496, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{496, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{496, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{496, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{496, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{496, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{496, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{496, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{496, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{496, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{496, 420, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{496, 419, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{496, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{496, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{496, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{496, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{496, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{496, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{496, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{496, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{496, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{496, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{496, 408, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{496, 407, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{496, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{496, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{496, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{496, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{496, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{496, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{496, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{496, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{496, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{496, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{496, 396, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{496, 395, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{496, 394, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{496, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{496, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{496, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{496, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{496, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{496, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{496, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{496, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{496, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{496, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{496, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{496, 382, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(0.0)
		{496, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	rh_engine_temperature_indicator_line_down_20_ahead[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{520, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{520, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{520, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{520, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{520, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{520, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{520, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{520, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{520, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{520, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{520, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{520, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{520, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{520, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{520, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{520, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{520, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{520, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{520, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{520, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{520, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{520, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{520, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{520, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{520, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{520, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{520, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{520, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{520, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{520, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{520, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{520, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{520, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{520, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{520, 420, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{520, 419, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{520, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{520, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{520, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{520, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{520, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{520, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{520, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{520, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{520, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{520, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{520, 408, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{520, 407, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{520, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{520, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{520, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{520, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{520, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{520, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{520, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{520, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{520, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{520, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{520, 396, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{520, 395, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{520, 394, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{520, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{520, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{520, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{520, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{520, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{520, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{520, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{520, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{520, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{520, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{520, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{520, 382, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(0.0)
		{520, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	lh_engine_temperature_indicator_line_down_20_right_30[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{251, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{251, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{251, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{251, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{251, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{251, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{250, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{250, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{250, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{250, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{250, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{250, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{249, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{249, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{249, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{249, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{249, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{248, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{248, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{248, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{248, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{248, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{248, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{247, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{247, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{247, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{247, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{247, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{246, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{246, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{246, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{246, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{246, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{246, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{245, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{245, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{245, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{245, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{245, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{244, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{244, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{244, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{244, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{244, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{244, 392, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{243, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{243, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{243, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{243, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{243, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{242, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{242, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{242, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{242, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{242, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{242, 381, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{241, 380, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{241, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{241, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{241, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{241, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{240, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{240, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{240, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{240, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{240, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{240, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{239, 369, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(0.0)
		{239, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	rh_engine_temperature_indicator_line_down_20_right_30[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{272, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{272, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{272, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{272, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{271, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{271, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{271, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{271, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{271, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{271, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{270, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{270, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{270, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{270, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{270, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{270, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{269, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{269, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{269, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{269, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{269, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{268, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{268, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{268, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{268, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{268, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{268, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{267, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{267, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{267, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{267, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{267, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{266, 395, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{266, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{266, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{266, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{266, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{266, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{265, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{265, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{265, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{265, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{265, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{264, 384, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{264, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{264, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{264, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{264, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{264, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{263, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{263, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{263, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{263, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{263, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{262, 373, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{262, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{262, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{262, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{262, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{262, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{261, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{261, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{261, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{261, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{261, 363, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{261, 362, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(0.0)
		{260, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
