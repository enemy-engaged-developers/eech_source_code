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
	clock_large_hand_scale_down_20_ahead[] =
	{
		// dial centred at x = 290, y = 436

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(5.0)
		{290, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{291, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{292, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{293, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{294, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{295, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{296, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{297, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{298, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(5.0)
		#define TICK_INCREMENT	(5.0)
		{299, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{300, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{301, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{302, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{303, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{304, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{305, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(5.0)
		{305, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{306, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{306, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{307, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{307, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{307, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{307, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{307, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{307, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(15.0)
		#define TICK_INCREMENT	(5.0)
		{307, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0)))},
		{307, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0)))},
		{307, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0)))},
		{307, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0)))},
		{307, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0)))},
		{307, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0)))},
		{306, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0)))},
		{306, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(5.0)
		{305, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{305, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{304, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{303, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{302, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{301, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{300, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(25.0)
		#define TICK_INCREMENT	(5.0)
		{299, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{298, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{297, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{296, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{295, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{294, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{293, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{292, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{291, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(5.0)
		{290, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{289, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{288, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{287, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{286, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{285, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{284, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{283, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{282, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(35.0)
		#define TICK_INCREMENT	(5.0)
		{281, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{280, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{279, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{278, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{277, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{276, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{276, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(5.0)
		{275, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0)))},
		{275, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0)))},
		{274, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0)))},
		{274, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0)))},
		{274, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0)))},
		{273, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0)))},
		{273, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0)))},
		{273, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(45.0)
		#define TICK_INCREMENT	(5.0)
		{273, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{273, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{273, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{273, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{273, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{274, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{274, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{274, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{275, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(5.0)
		{275, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{276, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{276, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{277, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{278, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{279, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{280, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(55.0)
		#define TICK_INCREMENT	(5.0)
		{281, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{282, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{283, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{284, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{285, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{286, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{287, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{288, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{289, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	clock_small_hand_scale_down_20_ahead[] =
	{
		// dial centred at x = 290, y = 436

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{290, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{291, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{292, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{293, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{294, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{295, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{296, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{297, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{298, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{299, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{300, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{301, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{301, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{301, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{302, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{302, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{302, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{302, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{302, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{302, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{302, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{302, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{301, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{301, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(1.0)
		{301, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  5.0)))},
		{300, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  5.0)))},
		{299, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  5.0)))},
		{298, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  5.0)))},
		{297, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  5.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(5.0)
		#define TICK_INCREMENT	(1.0)
		{296, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{295, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{294, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{293, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{292, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{291, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(6.0)
		#define TICK_INCREMENT	(1.0)
		{290, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{289, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{288, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{287, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{286, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{285, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(7.0)
		#define TICK_INCREMENT	(1.0)
		{284, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  4.0)))},
		{283, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  4.0)))},
		{282, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  4.0)))},
		{281, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  4.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(8.0)
		#define TICK_INCREMENT	(1.0)
		{280, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{280, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{279, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{279, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{279, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{278, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(9.0)
		#define TICK_INCREMENT	(1.0)
		{278, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{278, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{278, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{279, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{279, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{279, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(1.0)
		{280, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  5.0)))},
		{280, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  5.0)))},
		{281, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  5.0)))},
		{282, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  5.0)))},
		{283, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  5.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(11.0)
		#define TICK_INCREMENT	(1.0)
		{284, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{285, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{286, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{287, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{288, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{289, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	clock_large_hand_scale_down_20_left_30[] =
	{
		// dial centred at x = 539, y = 469

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(5.0)
		{542, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0)))},
		{543, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0)))},
		{544, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0)))},
		{545, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0)))},
		{546, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0)))},
		{547, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0)))},
		{548, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0)))},
		{549, 455, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0)))},
		{550, 455, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0)))},
		{551, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(5.0)
		#define TICK_INCREMENT	(5.0)
		{552, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{553, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{554, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{555, 460, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{555, 461, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{556, 462, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{556, 463, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{557, 464, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{557, 465, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(5.0)
		{558, 466, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0)))},
		{558, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0)))},
		{558, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0)))},
		{559, 469, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0)))},
		{559, 470, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0)))},
		{559, 471, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0)))},
		{559, 472, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0)))},
		{559, 473, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0)))},
		{559, 474, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0)))},
		{559, 475, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(15.0)
		#define TICK_INCREMENT	(5.0)
		{559, 476, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{559, 477, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{558, 478, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{557, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{556, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{555, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{554, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{553, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{552, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{551, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{550, 479, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{549, 479, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(5.0)
		{548, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{547, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{546, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{545, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{544, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{543, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(25.0)
		#define TICK_INCREMENT	(5.0)
		{542, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  5.0)))},
		{541, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  5.0)))},
		{540, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  5.0)))},
		{539, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  5.0)))},
		{538, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  5.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(5.0)
		{537, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0)))},
		{536, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0)))},
		{535, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0)))},
		{534, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0)))},
		{533, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0)))},
		{532, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0)))},
		{531, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0)))},
		{530, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(35.0)
		#define TICK_INCREMENT	(5.0)
		{529, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{528, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{527, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{526, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{525, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{524, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{523, 478, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{522, 477, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{522, 476, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{521, 475, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{521, 474, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{520, 473, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(5.0)
		{520, 472, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{520, 471, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{519, 470, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{519, 469, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{519, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{519, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{519, 466, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{519, 465, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{519, 464, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(45.0)
		#define TICK_INCREMENT	(5.0)
		{519, 463, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0)))},
		{519, 462, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0)))},
		{520, 461, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0)))},
		{520, 460, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0)))},
		{520, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0)))},
		{521, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0)))},
		{521, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0)))},
		{522, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(5.0)
		{523, 455, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{524, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{525, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{526, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{527, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{528, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{529, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{530, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{531, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(55.0)
		#define TICK_INCREMENT	(5.0)
		{532, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0)))},
		{533, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0)))},
		{534, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0)))},
		{535, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0)))},
		{536, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0)))},
		{537, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0)))},
		{538, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0)))},
		{539, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0)))},
		{540, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0)))},
		{541, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	clock_small_hand_scale_down_20_left_30[] =
	{
		// dial centred at x = 539, y = 469

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(1.0)
		{541, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{542, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{543, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{544, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{545, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{546, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{547, 460, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(1.0)
		#define TICK_INCREMENT	(1.0)
		{548, 461, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{549, 462, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{550, 463, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{550, 464, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{551, 465, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{551, 466, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(2.0)
		#define TICK_INCREMENT	(1.0)
		{552, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{552, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{552, 469, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{553, 470, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{553, 471, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{553, 472, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{553, 473, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(3.0)
		#define TICK_INCREMENT	(1.0)
		{553, 474, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{552, 475, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{552, 476, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{551, 477, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{550, 478, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{549, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(4.0)
		#define TICK_INCREMENT	(1.0)
		{548, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{547, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{546, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{545, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{544, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{543, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(5.0)
		#define TICK_INCREMENT	(1.0)
		{542, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  5.0)))},
		{541, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  5.0)))},
		{540, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  5.0)))},
		{539, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  5.0)))},
		{538, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  5.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(6.0)
		#define TICK_INCREMENT	(1.0)
		{537, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{536, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{535, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{534, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{533, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{532, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{531, 479, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(7.0)
		#define TICK_INCREMENT	(1.0)
		{530, 478, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{529, 477, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{528, 476, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{527, 475, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{527, 474, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{526, 473, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(8.0)
		#define TICK_INCREMENT	(1.0)
		{526, 472, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{526, 471, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{525, 470, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{525, 469, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{525, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{525, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{525, 466, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(9.0)
		#define TICK_INCREMENT	(1.0)
		{525, 465, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{525, 464, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{526, 463, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{526, 462, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{526, 461, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{527, 460, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(1.0)
		{528, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  6.0)))},
		{529, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  6.0)))},
		{530, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  6.0)))},
		{531, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  6.0)))},
		{532, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  6.0)))},
		{533, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  6.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(11.0)
		#define TICK_INCREMENT	(1.0)
		{534, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  7.0)))},
		{535, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  7.0)))},
		{536, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  7.0)))},
		{537, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  7.0)))},
		{538, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  7.0)))},
		{539, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  7.0)))},
		{540, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  7.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
