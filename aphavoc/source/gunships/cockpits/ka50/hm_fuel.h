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
	fuel_gauge_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 419, y = 436

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(500.0)
		{409, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 19.0)))},
		{408, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 19.0)))},
		{407, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 19.0)))},
		{406, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 19.0)))},
		{406, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 19.0)))},
		{406, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 19.0)))},
		{406, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 19.0)))},
		{405, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 19.0)))},
		{405, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 19.0)))},
		{405, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 19.0)))},
		{405, 435, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 19.0)))},
		{405, 434, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 19.0)))},
		{405, 433, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 19.0)))},
		{405, 432, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 19.0)))},
		{406, 431, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 19.0)))},
		{406, 430, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 19.0)))},
		{407, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 19.0)))},
		{407, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 19.0)))},
		{408, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (18.0 / 19.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(500.0)
		{409, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 20.0)))},
		{410, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 20.0)))},
		{411, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 20.0)))},
		{412, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 20.0)))},
		{413, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 20.0)))},
		{414, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 20.0)))},
		{415, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 20.0)))},
		{416, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 20.0)))},
		{417, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 20.0)))},
		{418, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 20.0)))},
		{419, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 20.0)))},
		{420, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 20.0)))},
		{421, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 20.0)))},
		{422, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 20.0)))},
		{423, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 20.0)))},
		{424, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 20.0)))},
		{425, 423, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 20.0)))},
		{426, 423, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 20.0)))},
		{427, 424, (float)(TICK_VALUE + (TICK_INCREMENT * (18.0 / 20.0)))},
		{428, 425, (float)(TICK_VALUE + (TICK_INCREMENT * (19.0 / 20.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(500.0)
		{429, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 19.0)))},
		{430, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 19.0)))},
		{430, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 19.0)))},
		{431, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 19.0)))},
		{432, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 19.0)))},
		{432, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 19.0)))},
		{433, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 19.0)))},
		{433, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 19.0)))},
		{433, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 19.0)))},
		{433, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 19.0)))},
		{433, 436, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 19.0)))},
		{433, 437, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 19.0)))},
		{433, 438, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 19.0)))},
		{432, 439, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 19.0)))},
		{432, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 19.0)))},
		{432, 441, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 19.0)))},
		{431, 442, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 19.0)))},
		{431, 443, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 19.0)))},
		{430, 444, (float)(TICK_VALUE + (TICK_INCREMENT * (18.0 / 19.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1500.0)
		#define TICK_INCREMENT	(100.0)
		{429, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  3.0)))},
		{428, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  3.0)))},
		{427, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  3.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1600.0)
		#define TICK_INCREMENT	(0.0)
		{426, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	fuel_gauge_needle_scale_down_20_right_30[] =
	{
		// dial centred at x = 176, y = 443

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(500.0)
		{167, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 20.0)))},
		{166, 455, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 20.0)))},
		{165, 455, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 20.0)))},
		{164, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 20.0)))},
		{163, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 20.0)))},
		{163, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 20.0)))},
		{162, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 20.0)))},
		{162, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 20.0)))},
		{162, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 20.0)))},
		{161, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 20.0)))},
		{161, 447, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 20.0)))},
		{161, 446, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 20.0)))},
		{161, 445, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 20.0)))},
		{161, 444, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 20.0)))},
		{161, 443, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 20.0)))},
		{162, 442, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 20.0)))},
		{162, 441, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 20.0)))},
		{162, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 20.0)))},
		{163, 439, (float)(TICK_VALUE + (TICK_INCREMENT * (18.0 / 20.0)))},
		{163, 438, (float)(TICK_VALUE + (TICK_INCREMENT * (19.0 / 20.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(500.0)
		{164, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 21.0)))},
		{164, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 21.0)))},
		{165, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 21.0)))},
		{166, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 21.0)))},
		{167, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 21.0)))},
		{168, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 21.0)))},
		{169, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 21.0)))},
		{170, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 21.0)))},
		{171, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 21.0)))},
		{172, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 21.0)))},
		{173, 430, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 21.0)))},
		{174, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 21.0)))},
		{175, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 21.0)))},
		{176, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 21.0)))},
		{177, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 21.0)))},
		{178, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 21.0)))},
		{179, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 21.0)))},
		{180, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 21.0)))},
		{181, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (18.0 / 21.0)))},
		{182, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (19.0 / 21.0)))},
		{183, 430, (float)(TICK_VALUE + (TICK_INCREMENT * (20.0 / 21.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1000.0)
		#define TICK_INCREMENT	(500.0)
		{184, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 19.0)))},
		{185, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 19.0)))},
		{186, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 19.0)))},
		{187, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 19.0)))},
		{188, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 19.0)))},
		{188, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 19.0)))},
		{189, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 19.0)))},
		{189, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 19.0)))},
		{189, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 19.0)))},
		{190, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 19.0)))},
		{190, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 19.0)))},
		{190, 441, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 19.0)))},
		{190, 442, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 19.0)))},
		{189, 443, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 19.0)))},
		{189, 444, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 19.0)))},
		{189, 445, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 19.0)))},
		{189, 446, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 19.0)))},
		{188, 447, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 19.0)))},
		{188, 448, (float)(TICK_VALUE + (TICK_INCREMENT * (18.0 / 19.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1500.0)
		#define TICK_INCREMENT	(100.0)
		{187, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{187, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{186, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{185, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1600.0)
		#define TICK_INCREMENT	(0.0)
		{184, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
