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
		{499, 454, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{499, 453, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{499, 452, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{499, 451, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{499, 450, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{499, 449, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{499, 448, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{499, 447, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{499, 446, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{499, 445, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{499, 444, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{499, 443, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{499, 442, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{499, 441, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{499, 440, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{499, 439, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{499, 438, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{499, 437, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{499, 436, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{499, 435, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{499, 434, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{499, 433, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{499, 432, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{499, 431, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{499, 430, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{499, 429, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{499, 428, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{499, 427, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{499, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{499, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{499, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{499, 423, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{499, 422, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{499, 421, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{499, 420, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{499, 419, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{499, 418, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{499, 417, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{499, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{499, 415, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{499, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{499, 413, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{499, 412, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{499, 411, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{499, 410, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{499, 409, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{499, 408, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{499, 407, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{499, 406, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{499, 405, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{499, 404, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{499, 403, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{499, 402, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{499, 401, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{499, 400, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{499, 399, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{499, 398, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{499, 397, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{499, 396, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{499, 395, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{499, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{499, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{499, 392, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{499, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{499, 390, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{499, 389, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{499, 388, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{499, 387, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{499, 386, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{499, 385, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{499, 384, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{499, 383, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{499, 382, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{499, 381, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{499, 380, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{499, 379, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{499, 378, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{499, 377, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{500, 454, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{500, 453, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{500, 452, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{500, 451, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{500, 450, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{500, 449, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{500, 448, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{500, 447, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{500, 446, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{500, 445, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{500, 444, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{500, 443, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{500, 442, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{500, 441, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{500, 440, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{500, 439, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{500, 438, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{500, 437, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{500, 436, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{500, 435, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{500, 434, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{500, 433, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{500, 432, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{500, 431, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{500, 430, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{500, 429, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{500, 428, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{500, 427, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{500, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{500, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{500, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{500, 423, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{500, 422, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{500, 421, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{500, 420, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{500, 419, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{500, 418, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{500, 417, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{500, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{500, 415, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{500, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{500, 413, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{500, 412, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{500, 411, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{500, 410, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{500, 409, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{500, 408, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{500, 407, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{500, 406, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{500, 405, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{500, 404, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{500, 403, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{500, 402, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{500, 401, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{500, 400, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{500, 399, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{500, 398, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{500, 397, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{500, 396, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{500, 395, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{500, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{500, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{500, 392, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{500, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{500, 390, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{500, 389, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{500, 388, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{500, 387, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{500, 386, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{500, 385, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{500, 384, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{500, 383, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{500, 382, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{500, 381, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{500, 380, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{500, 379, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{500, 378, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{500, 377, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{501, 454, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{501, 453, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{501, 452, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{501, 451, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{501, 450, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{501, 449, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{501, 448, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{501, 447, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{501, 446, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{501, 445, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{501, 444, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{501, 443, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{501, 442, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{501, 441, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{501, 440, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{501, 439, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{501, 438, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{501, 437, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{501, 436, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{501, 435, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{501, 434, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{501, 433, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{501, 432, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{501, 431, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{501, 430, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{501, 429, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{501, 428, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{501, 427, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{501, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{501, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{501, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{501, 423, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{501, 422, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{501, 421, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{501, 420, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{501, 419, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{501, 418, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{501, 417, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{501, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{501, 415, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{501, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{501, 413, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{501, 412, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{501, 411, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{501, 410, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{501, 409, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{501, 408, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{501, 407, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{501, 406, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{501, 405, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{501, 404, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{501, 403, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{501, 402, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{501, 401, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{501, 400, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{501, 399, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{501, 398, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{501, 397, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{501, 396, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{501, 395, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{501, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{501, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{501, 392, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{501, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{501, 390, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{501, 389, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{501, 388, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{501, 387, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{501, 386, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{501, 385, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{501, 384, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{501, 383, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{501, 382, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{501, 381, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{501, 380, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{501, 379, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{501, 378, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{501, 377, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{515, 454, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{515, 453, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{515, 452, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{515, 451, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{515, 450, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{515, 449, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{515, 448, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{515, 447, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{515, 446, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{515, 445, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{515, 444, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{515, 443, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{515, 442, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{515, 441, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{515, 440, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{515, 439, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{515, 438, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{515, 437, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{515, 436, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{515, 435, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{515, 434, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{515, 433, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{515, 432, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{515, 431, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{515, 430, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{515, 429, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{515, 428, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{515, 427, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{515, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{515, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{515, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{515, 423, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{515, 422, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{515, 421, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{515, 420, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{515, 419, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{515, 418, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{515, 417, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{515, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{515, 415, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{515, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{515, 413, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{515, 412, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{515, 411, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{515, 410, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{515, 409, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{515, 408, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{515, 407, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{515, 406, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{515, 405, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{515, 404, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{515, 403, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{515, 402, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{515, 401, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{515, 400, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{515, 399, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{515, 398, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{515, 397, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{515, 396, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{515, 395, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{515, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{515, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{515, 392, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{515, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{515, 390, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{515, 389, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{515, 388, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{515, 387, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{515, 386, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{515, 385, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{515, 384, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{515, 383, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{515, 382, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{515, 381, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{515, 380, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{515, 379, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{515, 378, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{515, 377, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{516, 454, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{516, 453, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{516, 452, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{516, 451, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{516, 450, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{516, 449, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{516, 448, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{516, 447, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{516, 446, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{516, 445, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{516, 444, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{516, 443, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{516, 442, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{516, 441, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{516, 440, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{516, 439, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{516, 438, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{516, 437, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{516, 436, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{516, 435, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{516, 434, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{516, 433, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{516, 432, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{516, 431, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{516, 430, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{516, 429, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{516, 428, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{516, 427, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{516, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{516, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{516, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{516, 423, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{516, 422, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{516, 421, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{516, 420, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{516, 419, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{516, 418, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{516, 417, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{516, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{516, 415, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{516, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{516, 413, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{516, 412, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{516, 411, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{516, 410, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{516, 409, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{516, 408, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{516, 407, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{516, 406, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{516, 405, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{516, 404, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{516, 403, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{516, 402, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{516, 401, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{516, 400, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{516, 399, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{516, 398, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{516, 397, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{516, 396, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{516, 395, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{516, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{516, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{516, 392, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{516, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{516, 390, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{516, 389, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{516, 388, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{516, 387, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{516, 386, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{516, 385, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{516, 384, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{516, 383, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{516, 382, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{516, 381, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{516, 380, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{516, 379, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{516, 378, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{516, 377, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{517, 454, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{517, 453, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{517, 452, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{517, 451, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{517, 450, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{517, 449, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{517, 448, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{517, 447, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{517, 446, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{517, 445, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{517, 444, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{517, 443, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{517, 442, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{517, 441, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{517, 440, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{517, 439, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{517, 438, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{517, 437, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{517, 436, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{517, 435, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{517, 434, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{517, 433, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{517, 432, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{517, 431, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{517, 430, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{517, 429, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{517, 428, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{517, 427, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{517, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{517, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{517, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{517, 423, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{517, 422, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{517, 421, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{517, 420, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{517, 419, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{517, 418, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{517, 417, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{517, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{517, 415, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{517, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{517, 413, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{517, 412, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{517, 411, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{517, 410, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{517, 409, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{517, 408, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{517, 407, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{517, 406, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{517, 405, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{517, 404, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{517, 403, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{517, 402, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{517, 401, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{517, 400, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{517, 399, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{517, 398, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{517, 397, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{517, 396, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{517, 395, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{517, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{517, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{517, 392, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{517, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{517, 390, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{517, 389, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{517, 388, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{517, 387, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{517, 386, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{517, 385, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{517, 384, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{517, 383, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{517, 382, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{517, 381, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{517, 380, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{517, 379, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{517, 378, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{517, 377, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{254, 433, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{254, 432, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{253, 431, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{253, 430, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{253, 429, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{253, 428, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{253, 427, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{253, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{252, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{252, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{252, 423, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{252, 422, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{252, 421, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{251, 420, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{251, 419, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{251, 418, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{251, 417, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{251, 416, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{251, 415, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{250, 414, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{250, 413, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{250, 412, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{250, 411, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{250, 410, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{249, 409, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{249, 408, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{249, 407, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{249, 406, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{249, 405, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{249, 404, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{248, 403, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{248, 402, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{248, 401, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{248, 400, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{248, 399, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{247, 398, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{247, 397, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{247, 396, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{247, 395, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{247, 394, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{247, 393, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{246, 392, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{246, 391, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{246, 390, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{246, 389, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{246, 388, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{245, 387, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{245, 386, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{245, 385, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{245, 384, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{245, 383, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{245, 382, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{244, 381, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{244, 380, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{244, 379, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{244, 378, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{244, 377, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{243, 376, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{243, 375, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{243, 374, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{243, 373, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{243, 372, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{243, 371, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{242, 370, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{242, 369, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{242, 368, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{242, 367, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{242, 366, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{241, 365, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{241, 364, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{241, 363, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{241, 362, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{241, 361, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{255, 433, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{255, 432, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{254, 431, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{254, 430, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{254, 429, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{254, 428, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{253, 427, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{253, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{253, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{253, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{253, 423, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{253, 422, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{252, 421, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{252, 420, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{252, 419, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{252, 418, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{252, 417, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{252, 416, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{252, 415, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{251, 414, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{251, 413, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{251, 412, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{251, 411, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{250, 410, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{250, 409, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{250, 408, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{250, 407, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{250, 406, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{250, 405, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{250, 404, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{249, 403, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{249, 402, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{249, 401, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{249, 400, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{248, 399, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{248, 398, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{248, 397, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{248, 396, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{248, 395, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{248, 394, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{248, 393, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{247, 392, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{247, 391, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{247, 390, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{247, 389, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{247, 388, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{246, 387, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{246, 386, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{246, 385, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{246, 384, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{246, 383, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{246, 382, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{245, 381, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{245, 380, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{245, 379, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{245, 378, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{245, 377, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{244, 376, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{244, 375, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{244, 374, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{244, 373, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{244, 372, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{243, 371, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{243, 370, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{243, 369, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{243, 368, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{243, 367, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{242, 366, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{242, 365, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{242, 364, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{242, 363, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{242, 362, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{242, 361, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{256, 433, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{255, 432, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{255, 431, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{255, 430, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{255, 429, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{255, 428, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{254, 427, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{254, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{254, 425, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{254, 424, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{254, 423, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{254, 422, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{253, 421, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{253, 420, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{253, 419, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{253, 418, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{253, 417, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{252, 416, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{252, 415, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{252, 414, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{252, 413, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{252, 412, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{252, 411, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{251, 410, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{251, 409, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{251, 408, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{251, 407, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{251, 406, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{250, 405, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{250, 404, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{250, 403, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{250, 402, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{250, 401, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{250, 400, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{249, 399, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{249, 398, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{249, 397, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{249, 396, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{249, 395, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{248, 394, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{248, 393, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{248, 392, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{248, 391, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{248, 390, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{248, 389, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{247, 388, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{247, 387, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{247, 386, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{247, 385, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{247, 384, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{247, 383, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{246, 382, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{246, 381, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{246, 380, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{246, 379, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{246, 378, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{245, 377, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{245, 376, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{245, 375, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{245, 374, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{245, 373, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{245, 372, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{244, 371, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{244, 370, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{244, 369, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{244, 368, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{244, 367, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{243, 366, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{243, 365, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{243, 364, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{243, 363, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{243, 362, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{243, 361, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{268, 430, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{268, 429, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{268, 428, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{268, 427, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{268, 426, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{267, 425, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{267, 424, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{267, 423, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{267, 422, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{267, 421, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{267, 420, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{266, 419, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{266, 418, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{266, 417, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{266, 416, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{266, 415, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{265, 414, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{265, 413, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{265, 412, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{265, 411, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{265, 410, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{265, 409, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{264, 408, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{264, 407, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{264, 406, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{264, 405, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{264, 404, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{263, 403, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{263, 402, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{263, 401, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{263, 400, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{263, 399, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{263, 398, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{262, 397, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{262, 396, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{262, 395, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{262, 394, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{262, 393, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{262, 392, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{261, 391, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{261, 390, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{261, 389, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{261, 388, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{261, 387, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{260, 386, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{260, 385, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{260, 384, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{260, 383, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{260, 382, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{260, 381, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{259, 380, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{259, 379, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{259, 378, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{259, 377, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{259, 376, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{258, 375, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{258, 374, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{258, 373, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{258, 372, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{258, 371, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{258, 370, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{257, 369, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{257, 368, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{257, 367, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{257, 366, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{257, 365, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{256, 364, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{256, 363, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{256, 362, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{256, 361, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{256, 360, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{256, 359, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{255, 358, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{269, 430, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{269, 429, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{269, 428, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{269, 427, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{268, 426, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{268, 425, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{268, 424, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{268, 423, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{268, 422, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{267, 421, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{267, 420, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{267, 419, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{267, 418, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{267, 417, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{267, 416, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{266, 415, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{266, 414, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{266, 413, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{266, 412, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{266, 411, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{265, 410, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{265, 409, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{265, 408, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{265, 407, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{265, 406, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{265, 405, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{264, 404, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{264, 403, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{264, 402, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{264, 401, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{264, 400, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{263, 399, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{263, 398, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{263, 397, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{263, 396, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{263, 395, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{263, 394, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{262, 393, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{262, 392, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{262, 391, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{262, 390, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{262, 389, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{262, 388, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{262, 387, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{261, 386, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{261, 385, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{261, 384, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{261, 383, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{260, 382, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{260, 381, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{260, 380, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{260, 379, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{260, 378, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{260, 377, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{259, 376, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{259, 375, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{259, 374, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{259, 373, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{259, 372, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{258, 371, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{258, 370, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{258, 369, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{258, 368, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{258, 367, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{258, 366, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{257, 365, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{257, 364, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{257, 363, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{257, 362, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{257, 361, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{256, 360, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{256, 359, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{256, 358, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
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
		{270, 430, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{270, 429, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{270, 428, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{270, 427, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{269, 426, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{269, 425, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{269, 424, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{269, 423, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{269, 422, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{268, 421, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{268, 420, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{268, 419, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{268, 418, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{268, 417, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  2.0)))},
		{268, 416, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  2.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{267, 415, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{267, 414, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{267, 413, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{267, 412, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{267, 411, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{266, 410, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{266, 409, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{266, 408, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{266, 407, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{266, 406, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{266, 405, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{265, 404, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{265, 403, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{265, 402, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{265, 401, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{265, 400, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{264, 399, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{264, 398, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{264, 397, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{264, 396, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{264, 395, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{264, 394, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(10.0)
		{263, 393, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{263, 392, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{263, 391, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{263, 390, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{263, 389, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{263, 388, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{262, 387, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{262, 386, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{262, 385, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{262, 384, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{262, 383, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{261, 382, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(90.0)
		#define TICK_INCREMENT	(10.0)
		{261, 381, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{261, 380, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{261, 379, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{261, 378, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{261, 377, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{260, 376, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{260, 375, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{260, 374, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{260, 373, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{260, 372, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{259, 371, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(10.0)
		{259, 370, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{259, 369, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{259, 368, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{259, 367, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{259, 366, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{258, 365, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{258, 364, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{258, 363, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{258, 362, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{258, 361, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{257, 360, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{257, 359, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(110.0)
		#define TICK_INCREMENT	(0.0)
		{257, 358, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
