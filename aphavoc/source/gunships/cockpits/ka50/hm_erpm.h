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
	lh_engine_rpm_indicator_line1_down_20_ahead[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{499, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{499, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{499, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{499, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{499, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{499, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{499, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{499, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{499, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{499, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{499, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{499, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{499, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{499, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{499, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{499, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{499, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{499, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{499, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{499, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{499, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{499, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{499, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{499, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{499, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{499, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{499, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{499, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{499, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{499, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{499, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{499, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{499, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{499, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{499, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{499, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{499, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{499, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{499, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{499, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{499, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{499, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{499, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{499, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{499, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{499, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{499, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{499, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{499, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{499, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{499, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{499, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{499, 402, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{499, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{499, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{499, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{499, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{499, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{499, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{499, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{499, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{499, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{499, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{499, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{499, 390, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{499, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{499, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{499, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{499, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{499, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{499, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{499, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{499, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{499, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{499, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{499, 379, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{499, 378, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{499, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	lh_engine_rpm_indicator_line2_down_20_ahead[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{500, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{500, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{500, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{500, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{500, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{500, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{500, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{500, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{500, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{500, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{500, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{500, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{500, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{500, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{500, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{500, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{500, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{500, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{500, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{500, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{500, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{500, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{500, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{500, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{500, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{500, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{500, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{500, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{500, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{500, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{500, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{500, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{500, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{500, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{500, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{500, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{500, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{500, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{500, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{500, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{500, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{500, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{500, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{500, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{500, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{500, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{500, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{500, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{500, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{500, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{500, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{500, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{500, 402, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{500, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{500, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{500, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{500, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{500, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{500, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{500, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{500, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{500, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{500, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{500, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{500, 390, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{500, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{500, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{500, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{500, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{500, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{500, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{500, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{500, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{500, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{500, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{500, 379, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{500, 378, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{500, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	lh_engine_rpm_indicator_line3_down_20_ahead[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{501, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{501, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{501, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{501, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{501, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{501, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{501, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{501, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{501, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{501, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{501, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{501, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{501, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{501, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{501, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{501, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{501, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{501, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{501, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{501, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{501, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{501, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{501, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{501, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{501, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{501, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{501, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{501, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{501, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{501, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{501, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{501, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{501, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{501, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{501, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{501, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{501, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{501, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{501, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{501, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{501, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{501, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{501, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{501, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{501, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{501, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{501, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{501, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{501, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{501, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{501, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{501, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{501, 402, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{501, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{501, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{501, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{501, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{501, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{501, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{501, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{501, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{501, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{501, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{501, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{501, 390, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{501, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{501, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{501, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{501, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{501, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{501, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{501, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{501, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{501, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{501, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{501, 379, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{501, 378, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{501, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	rh_engine_rpm_indicator_line1_down_20_ahead[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{515, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{515, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{515, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{515, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{515, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{515, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{515, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{515, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{515, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{515, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{515, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{515, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{515, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{515, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{515, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{515, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{515, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{515, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{515, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{515, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{515, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{515, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{515, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{515, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{515, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{515, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{515, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{515, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{515, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{515, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{515, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{515, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{515, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{515, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{515, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{515, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{515, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{515, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{515, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{515, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{515, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{515, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{515, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{515, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{515, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{515, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{515, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{515, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{515, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{515, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{515, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{515, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{515, 402, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{515, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{515, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{515, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{515, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{515, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{515, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{515, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{515, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{515, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{515, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{515, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{515, 390, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{515, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{515, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{515, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{515, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{515, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{515, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{515, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{515, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{515, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{515, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{515, 379, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{515, 378, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{515, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	rh_engine_rpm_indicator_line2_down_20_ahead[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{516, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{516, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{516, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{516, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{516, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{516, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{516, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{516, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{516, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{516, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{516, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{516, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{516, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{516, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{516, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{516, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{516, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{516, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{516, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{516, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{516, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{516, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{516, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{516, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{516, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{516, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{516, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{516, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{516, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{516, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{516, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{516, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{516, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{516, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{516, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{516, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{516, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{516, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{516, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{516, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{516, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{516, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{516, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{516, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{516, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{516, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{516, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{516, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{516, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{516, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{516, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{516, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{516, 402, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{516, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{516, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{516, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{516, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{516, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{516, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{516, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{516, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{516, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{516, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{516, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{516, 390, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{516, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{516, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{516, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{516, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{516, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{516, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{516, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{516, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{516, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{516, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{516, 379, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{516, 378, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{516, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	rh_engine_rpm_indicator_line3_down_20_ahead[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{517, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{517, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{517, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{517, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{517, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{517, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{517, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{517, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{517, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{517, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{517, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{517, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{517, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{517, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{517, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{517, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{517, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{517, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{517, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{517, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{517, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{517, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{517, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{517, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{517, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{517, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{517, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{517, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{517, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{517, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{517, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{517, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{517, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{517, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{517, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{517, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{517, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{517, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{517, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{517, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{517, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{517, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{517, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{517, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{517, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{517, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{517, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{517, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{517, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{517, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{517, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{517, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{517, 402, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{517, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{517, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{517, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{517, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{517, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{517, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{517, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{517, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{517, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{517, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{517, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{517, 390, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{517, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{517, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{517, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{517, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{517, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{517, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{517, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{517, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{517, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{517, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{517, 379, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{517, 378, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{517, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	lh_engine_rpm_indicator_line1_down_20_right_30[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{254, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{254, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{253, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{253, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{253, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{253, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{253, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{253, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{252, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{252, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{252, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{252, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{252, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{251, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{251, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{251, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{251, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{251, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{251, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{250, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{250, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{250, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{250, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{250, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{249, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{249, 408, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{249, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{249, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{249, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{249, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{248, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{248, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{248, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{248, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{248, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{247, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{247, 397, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{247, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{247, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{247, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{247, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{246, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{246, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{246, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{246, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{246, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{245, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{245, 386, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{245, 385, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{245, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{245, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{245, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{244, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{244, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{244, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{244, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{244, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{243, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{243, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{243, 374, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{243, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{243, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{243, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{242, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{242, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{242, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{242, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{242, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{241, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{241, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{241, 363, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{241, 362, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{241, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	lh_engine_rpm_indicator_line2_down_20_right_30[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{255, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{255, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{254, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{254, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{254, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{254, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{253, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{253, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{253, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{253, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{253, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{253, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{252, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{252, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{252, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{252, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{252, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{252, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{252, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{251, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{251, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{251, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{251, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{250, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{250, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{250, 408, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{250, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{250, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{250, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{250, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{249, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{249, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{249, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{249, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{248, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{248, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{248, 397, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{248, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{248, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{248, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{248, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{247, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{247, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{247, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{247, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{247, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{246, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{246, 386, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{246, 385, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{246, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{246, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{246, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{245, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{245, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{245, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{245, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{245, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{244, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{244, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{244, 374, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{244, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{244, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{243, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{243, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{243, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{243, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{243, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{242, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{242, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{242, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{242, 363, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{242, 362, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{242, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	lh_engine_rpm_indicator_line3_down_20_right_30[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{256, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{255, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{255, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{255, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{255, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{255, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{254, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{254, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{254, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{254, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{254, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{254, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{253, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{253, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{253, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{253, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{253, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{252, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{252, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{252, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{252, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{252, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{252, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{251, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{251, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{251, 408, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{251, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{251, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{250, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{250, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{250, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{250, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{250, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{250, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{249, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{249, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{249, 397, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{249, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{249, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{248, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{248, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{248, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{248, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{248, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{248, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{247, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{247, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{247, 386, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{247, 385, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{247, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{247, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{246, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{246, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{246, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{246, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{246, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{245, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{245, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{245, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{245, 374, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{245, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{245, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{244, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{244, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{244, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{244, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{244, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{243, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{243, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{243, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{243, 363, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{243, 362, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{243, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	rh_engine_rpm_indicator_line1_down_20_right_30[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{268, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{268, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{268, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{268, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{268, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{267, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{267, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{267, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{267, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{267, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{267, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{266, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{266, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{266, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{266, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{266, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{265, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{265, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{265, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{265, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{265, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{265, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{264, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{264, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{264, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{264, 405, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{264, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{263, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{263, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{263, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{263, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{263, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{263, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{262, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{262, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{262, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{262, 394, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{262, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{262, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{261, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{261, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{261, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{261, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{261, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{260, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{260, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{260, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{260, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{260, 382, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{260, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{259, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{259, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{259, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{259, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{259, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{258, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{258, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{258, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{258, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{258, 371, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{258, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{257, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{257, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{257, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{257, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{257, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{256, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{256, 363, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{256, 362, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{256, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{256, 360, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{256, 359, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{255, 358, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	rh_engine_rpm_indicator_line2_down_20_right_30[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{269, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{269, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{269, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{269, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{268, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{268, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{268, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{268, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{268, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{267, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{267, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{267, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{267, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{267, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{267, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{266, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{266, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{266, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{266, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{266, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{265, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{265, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{265, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{265, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{265, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{265, 405, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{264, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{264, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{264, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{264, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{264, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{263, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{263, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{263, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{263, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{263, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{263, 394, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{262, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{262, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{262, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{262, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{262, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{262, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{262, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{261, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{261, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{261, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{261, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{260, 382, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{260, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{260, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{260, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{260, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{260, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{259, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{259, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{259, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{259, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{259, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{258, 371, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{258, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{258, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{258, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{258, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{258, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{257, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{257, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{257, 363, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{257, 362, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{257, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{256, 360, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{256, 359, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{256, 358, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	rh_engine_rpm_indicator_line3_down_20_right_30[] =
	{
		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{270, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{270, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{270, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{270, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{269, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{269, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{269, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{269, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{269, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{268, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{268, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{268, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{268, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{268, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{268, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{267, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{267, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{267, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{267, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{267, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{266, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{266, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{266, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{266, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{266, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{266, 405, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{265, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{265, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{265, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{265, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{265, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{264, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{264, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{264, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{264, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{264, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{264, 394, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{263, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{263, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{263, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{263, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{263, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{263, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{262, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{262, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{262, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{262, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{262, 383, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{261, 382, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{261, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{261, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{261, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{261, 378, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{261, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{260, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{260, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{260, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{260, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{260, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{259, 371, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{259, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{259, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{259, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{259, 367, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{259, 366, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{258, 365, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{258, 364, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{258, 363, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{258, 362, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{258, 361, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{257, 360, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{257, 359, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{257, 358, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
