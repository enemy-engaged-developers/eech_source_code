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
	barometric_altimeter_large_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 75, y = 394

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{ 75, 372, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{ 76, 372, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{ 77, 372, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{ 78, 372, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{ 79, 372, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{ 80, 372, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{ 81, 373, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{ 82, 373, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{ 83, 373, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{ 84, 374, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{ 85, 374, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{ 86, 375, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{ 87, 375, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{ 88, 376, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0))},
		{ 89, 377, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0))},
		{ 90, 378, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0))},
		{ 91, 379, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0))},
		{ 92, 380, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0))},
		{ 93, 381, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0))},
		{ 93, 382, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0))},
		{ 94, 383, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0))},
		{ 95, 384, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0))},
		{ 95, 385, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0))},
		{ 95, 386, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{ 96, 387, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{ 96, 388, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{ 96, 389, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{ 97, 390, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{ 97, 391, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{ 97, 392, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{ 97, 393, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{ 97, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{ 97, 395, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{ 97, 396, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{ 97, 397, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{ 97, 398, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{ 96, 399, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{ 96, 400, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{ 96, 401, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0))},
		{ 95, 402, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0))},
		{ 95, 403, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0))},
		{ 95, 404, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0))},
		{ 94, 405, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0))},
		{ 93, 406, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0))},
		{ 93, 407, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0))},
		{ 92, 408, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0))},
		{ 91, 409, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0))},
		{ 90, 410, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0))},
		{ 89, 411, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{ 88, 412, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{ 87, 413, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{ 86, 413, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{ 85, 414, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{ 84, 414, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{ 83, 415, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{ 82, 415, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{ 81, 415, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{ 80, 416, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{ 79, 416, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{ 78, 416, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{ 77, 416, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{ 76, 416, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{ 75, 416, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{ 74, 416, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{ 73, 416, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{ 72, 416, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{ 71, 416, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{ 70, 416, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{ 69, 416, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{ 68, 415, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{ 67, 415, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{ 66, 415, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{ 65, 414, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{ 64, 414, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{ 63, 413, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{ 62, 412, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{ 61, 412, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0))},
		{ 60, 411, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0))},
		{ 59, 410, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0))},
		{ 58, 409, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0))},
		{ 57, 408, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0))},
		{ 56, 407, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0))},
		{ 56, 406, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0))},
		{ 55, 405, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0))},
		{ 55, 404, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0))},
		{ 54, 403, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0))},
		{ 54, 402, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{ 54, 401, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{ 53, 400, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{ 53, 399, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{ 53, 398, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{ 53, 397, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{ 52, 396, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{ 52, 395, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{ 52, 394, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{ 52, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{ 52, 392, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{ 53, 391, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{ 53, 390, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{ 53, 389, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{ 53, 388, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{ 53, 387, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0))},
		{ 54, 386, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0))},
		{ 54, 385, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0))},
		{ 55, 384, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0))},
		{ 55, 383, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0))},
		{ 56, 382, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0))},
		{ 56, 381, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0))},
		{ 57, 380, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0))},
		{ 58, 379, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0))},
		{ 59, 378, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0))},
		{ 60, 377, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{ 61, 376, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{ 62, 376, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{ 63, 375, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{ 64, 374, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{ 65, 374, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{ 66, 373, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{ 67, 373, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{ 68, 373, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{ 69, 372, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{ 70, 372, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{ 71, 372, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{ 72, 372, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{ 73, 372, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{ 74, 372, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	barometric_altimeter_small_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 75, y = 394

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1000.0)
		{ 75, 381, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{ 76, 381, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{ 77, 381, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{ 78, 381, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{ 79, 381, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{ 80, 382, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{ 81, 382, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{ 82, 383, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 83, 383, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{ 84, 384, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{ 85, 385, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{ 86, 386, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{ 86, 387, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{ 87, 388, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{ 87, 389, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 88, 390, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{ 89, 391, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{ 89, 392, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{ 89, 393, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{ 89, 394, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{ 89, 395, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{ 89, 396, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{ 89, 397, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 88, 398, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{ 87, 399, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{ 87, 400, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{ 86, 401, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{ 86, 402, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{ 85, 403, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{ 84, 404, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 83, 405, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{ 82, 405, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{ 81, 406, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{ 80, 406, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{ 79, 407, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{ 78, 407, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{ 77, 407, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{ 76, 407, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(5000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 75, 407, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{ 74, 407, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{ 73, 407, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{ 72, 407, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{ 71, 407, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{ 70, 407, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{ 69, 406, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{ 68, 406, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(6000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 67, 405, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{ 66, 405, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{ 65, 404, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{ 64, 403, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{ 64, 402, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{ 63, 401, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{ 62, 400, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{ 62, 399, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(7000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 62, 398, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{ 61, 397, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{ 61, 396, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{ 61, 395, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{ 61, 394, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{ 61, 393, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{ 61, 392, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{ 61, 391, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(8000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 62, 390, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{ 62, 389, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{ 62, 388, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{ 63, 387, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{ 64, 386, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{ 64, 385, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{ 65, 384, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{ 66, 383, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(9000.0)
		#define TICK_INCREMENT	(1000.0)
		{ 67, 383, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{ 68, 382, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{ 69, 382, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{ 70, 381, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{ 71, 381, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{ 72, 381, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{ 73, 381, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{ 74, 381, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	barometric_altimeter_large_needle_scale_down_20_left_30[] =
	{
		// dial centred at x = 340, y = 361

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{343, 341, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0))},
		{344, 342, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0))},
		{345, 342, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0))},
		{346, 343, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0))},
		{347, 343, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0))},
		{348, 344, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0))},
		{349, 344, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0))},
		{350, 345, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0))},
		{351, 346, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0))},
		{352, 347, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{353, 348, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0))},
		{354, 349, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0))},
		{354, 350, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0))},
		{355, 351, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0))},
		{356, 352, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0))},
		{356, 353, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0))},
		{357, 354, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0))},
		{357, 355, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0))},
		{357, 356, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0))},
		{358, 357, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0))},
		{358, 358, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0))},
		{358, 359, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{358, 360, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{358, 361, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{358, 362, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{358, 363, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{358, 364, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{358, 365, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{358, 366, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{358, 367, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{358, 368, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{358, 369, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{357, 370, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{357, 371, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{356, 372, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{356, 373, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0))},
		{355, 374, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0))},
		{355, 375, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0))},
		{354, 376, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0))},
		{353, 377, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0))},
		{352, 378, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0))},
		{351, 379, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0))},
		{350, 379, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0))},
		{349, 380, TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{348, 381, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0))},
		{347, 381, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0))},
		{346, 381, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0))},
		{345, 381, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0))},
		{344, 382, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0))},
		{343, 382, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0))},
		{342, 382, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0))},
		{341, 382, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0))},
		{340, 382, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0))},
		{339, 382, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0))},
		{338, 381, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0))},
		{337, 381, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{336, 381, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0))},
		{335, 380, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0))},
		{334, 380, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0))},
		{333, 379, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0))},
		{332, 379, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0))},
		{331, 378, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0))},
		{330, 377, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0))},
		{329, 377, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0))},
		{328, 376, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0))},
		{328, 375, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{327, 374, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0))},
		{326, 373, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0))},
		{326, 372, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0))},
		{325, 371, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0))},
		{324, 370, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0))},
		{324, 369, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0))},
		{324, 368, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0))},
		{323, 367, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0))},
		{323, 366, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0))},
		{323, 365, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0))},
		{322, 364, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0))},
		{322, 363, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{322, 362, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0))},
		{322, 361, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0))},
		{322, 360, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0))},
		{322, 359, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0))},
		{322, 358, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0))},
		{322, 357, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0))},
		{322, 356, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0))},
		{323, 355, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0))},
		{323, 354, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0))},
		{323, 353, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0))},
		{323, 352, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0))},
		{324, 351, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{324, 350, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0))},
		{325, 349, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0))},
		{325, 348, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0))},
		{326, 347, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0))},
		{327, 346, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0))},
		{328, 345, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0))},
		{329, 344, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0))},
		{330, 343, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0))},
		{331, 343, TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{332, 342, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0))},
		{333, 342, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0))},
		{334, 342, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0))},
		{335, 341, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0))},
		{336, 341, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0))},
		{337, 341, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0))},
		{338, 341, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0))},
		{339, 341, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0))},
		{340, 341, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0))},
		{341, 341, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0))},
		{342, 341, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	barometric_altimeter_small_needle_scale_down_20_left_30[] =
	{
		// dial centred at x = 340, y = 361

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1000.0)
		{342, 349, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0))},
		{343, 350, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0))},
		{344, 350, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0))},
		{345, 351, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0))},
		{346, 351, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0))},
		{347, 352, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(1000.0)
		{348, 353, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{348, 354, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{349, 355, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{350, 356, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{350, 357, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{350, 358, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{351, 359, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2000.0)
		#define TICK_INCREMENT	(1000.0)
		{351, 360, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{351, 361, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{351, 362, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{351, 363, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{351, 364, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{351, 365, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{350, 366, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{350, 367, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3000.0)
		#define TICK_INCREMENT	(1000.0)
		{350, 368, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0))},
		{349, 369, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0))},
		{349, 370, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0))},
		{348, 371, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0))},
		{347, 372, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0))},
		{346, 372, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4000.0)
		#define TICK_INCREMENT	(1000.0)
		{345, 373, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{344, 373, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{343, 373, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{342, 374, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{341, 374, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{340, 374, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{339, 374, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(5000.0)
		#define TICK_INCREMENT	(1000.0)
		{338, 373, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0))},
		{337, 373, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0))},
		{336, 373, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0))},
		{335, 372, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0))},
		{334, 371, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0))},
		{333, 370, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(6000.0)
		#define TICK_INCREMENT	(1000.0)
		{332, 369, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{331, 368, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{331, 367, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{330, 366, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{330, 365, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{330, 364, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{329, 363, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(7000.0)
		#define TICK_INCREMENT	(1000.0)
		{329, 362, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{329, 361, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{329, 360, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{329, 359, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{329, 358, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{329, 357, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{330, 356, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{330, 355, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(8000.0)
		#define TICK_INCREMENT	(1000.0)
		{330, 354, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  5.0))},
		{331, 353, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  5.0))},
		{332, 352, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  5.0))},
		{333, 351, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  5.0))},
		{334, 350, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  5.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(9000.0)
		#define TICK_INCREMENT	(1000.0)
		{335, 349, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{336, 349, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{337, 349, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{338, 349, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{339, 349, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{340, 349, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{341, 349, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	barometric_altimeter_large_needle_scale_down_20_left_60[] =
	{
		// dial centred at x = 614, y = 407

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{623, 387, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{624, 388, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{625, 388, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{626, 389, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{627, 390, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{628, 390, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{629, 391, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{630, 392, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{631, 393, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{632, 394, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{633, 395, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{633, 396, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{634, 397, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{635, 398, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{635, 399, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0))},
		{636, 400, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0))},
		{636, 401, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0))},
		{637, 402, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0))},
		{637, 403, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0))},
		{637, 404, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0))},
		{638, 405, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0))},
		{638, 406, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0))},
		{638, 407, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0))},
		{638, 408, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0))},
		{638, 409, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0))},
		{638, 410, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0))},
		{639, 411, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0))},
		{639, 412, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0))},
		{639, 413, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{639, 414, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{638, 415, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{638, 416, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{638, 417, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{638, 418, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{638, 419, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{637, 420, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{637, 421, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{636, 422, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{636, 423, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{635, 424, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{635, 425, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{634, 426, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{633, 427, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{632, 428, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{631, 429, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{630, 429, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{629, 430, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{628, 431, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{627, 431, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{626, 431, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{625, 432, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{624, 432, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{623, 432, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{622, 432, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{621, 432, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{620, 433, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{619, 433, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{618, 433, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{617, 432, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{616, 432, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{615, 432, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{614, 432, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{613, 432, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{612, 432, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{611, 431, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{610, 431, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{609, 430, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{608, 430, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{607, 429, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{606, 429, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{605, 428, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{604, 428, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{603, 427, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{602, 426, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{601, 425, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{600, 424, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{599, 423, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{598, 422, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{597, 421, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{597, 420, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{596, 419, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{596, 418, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{595, 417, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{594, 416, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{594, 415, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{594, 414, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{593, 413, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{593, 412, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{593, 411, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{592, 410, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{592, 409, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{592, 408, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{592, 407, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{592, 406, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{592, 405, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{592, 404, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{592, 403, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0))},
		{592, 402, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0))},
		{592, 401, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0))},
		{592, 400, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0))},
		{593, 399, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0))},
		{593, 398, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0))},
		{593, 397, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0))},
		{593, 396, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0))},
		{594, 395, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0))},
		{594, 394, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0))},
		{595, 393, TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0))},
		{596, 392, TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0))},
		{596, 391, TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{597, 390, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0))},
		{598, 389, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0))},
		{599, 388, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0))},
		{600, 388, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0))},
		{601, 387, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0))},
		{602, 386, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0))},
		{603, 386, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0))},
		{604, 385, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0))},
		{605, 385, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0))},
		{606, 385, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0))},
		{607, 385, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0))},
		{608, 384, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{609, 384, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0))},
		{610, 384, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0))},
		{611, 384, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0))},
		{612, 384, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0))},
		{613, 384, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0))},
		{614, 384, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0))},
		{615, 384, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0))},
		{616, 385, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0))},
		{617, 385, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0))},
		{618, 385, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0))},
		{619, 385, TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0))},
		{620, 386, TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0))},
		{621, 386, TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0))},
		{622, 387, TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	barometric_altimeter_small_needle_scale_down_20_left_60[] =
	{
		// dial centred at x = 614, y = 407

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1000.0)
		{619, 395, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{620, 396, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{621, 396, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{622, 397, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{623, 398, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{624, 399, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{625, 400, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{626, 401, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(1000.0)
		{627, 402, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0))},
		{627, 403, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0))},
		{628, 404, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0))},
		{628, 405, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0))},
		{628, 406, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0))},
		{629, 407, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0))},
		{629, 408, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0))},
		{629, 409, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0))},
		{629, 410, TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2000.0)
		#define TICK_INCREMENT	(1000.0)
		{629, 411, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{629, 412, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{629, 413, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{629, 414, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{628, 415, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{628, 416, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{627, 417, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{626, 418, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3000.0)
		#define TICK_INCREMENT	(1000.0)
		{625, 419, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{625, 420, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{624, 421, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{623, 421, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{622, 422, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{621, 422, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{620, 423, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{619, 423, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4000.0)
		#define TICK_INCREMENT	(1000.0)
		{618, 423, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0))},
		{617, 423, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0))},
		{616, 423, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0))},
		{615, 423, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0))},
		{614, 423, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0))},
		{613, 422, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0))},
		{612, 422, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0))},
		{611, 422, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0))},
		{610, 421, TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(5000.0)
		#define TICK_INCREMENT	(1000.0)
		{609, 421, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{608, 420, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{607, 419, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{606, 418, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{605, 417, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{604, 416, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{603, 415, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{603, 414, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(6000.0)
		#define TICK_INCREMENT	(1000.0)
		{602, 413, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{602, 412, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{601, 411, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{601, 410, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{601, 409, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{601, 408, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{601, 407, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{601, 406, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(7000.0)
		#define TICK_INCREMENT	(1000.0)
		{601, 405, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{601, 404, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{601, 403, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{601, 402, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{601, 401, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{602, 400, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{602, 399, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{603, 398, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(8000.0)
		#define TICK_INCREMENT	(1000.0)
		{604, 397, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0))},
		{605, 396, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0))},
		{606, 395, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0))},
		{607, 395, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0))},
		{608, 394, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0))},
		{609, 394, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0))},
		{610, 394, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(9000.0)
		#define TICK_INCREMENT	(1000.0)
		{611, 393, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0))},
		{612, 393, TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0))},
		{613, 393, TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0))},
		{614, 394, TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0))},
		{615, 394, TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0))},
		{616, 394, TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0))},
		{617, 394, TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0))},
		{618, 395, TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
