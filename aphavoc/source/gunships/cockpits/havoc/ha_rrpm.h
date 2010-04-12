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
	main_rotor_rpm_indicator_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 88, y = 329

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{107, 318, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{108, 319, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{108, 320, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{109, 321, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{109, 322, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{109, 323, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{110, 324, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{110, 325, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{110, 326, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{110, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{110, 328, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{110, 329, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{110, 330, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{110, 331, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{110, 332, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{110, 333, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{110, 334, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{109, 335, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{109, 336, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{109, 337, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{108, 338, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{108, 339, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{107, 340, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{107, 341, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{106, 342, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{105, 343, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{104, 344, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{103, 345, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{102, 346, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{101, 347, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{100, 348, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{ 99, 348, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{ 98, 349, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{ 97, 349, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{ 96, 350, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{ 95, 350, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{ 94, 350, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{ 93, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{ 92, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{ 91, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{ 90, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{ 89, 351, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{ 88, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{ 87, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{ 86, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{ 85, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{ 84, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{ 83, 351, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{ 82, 350, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{ 81, 350, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{ 80, 350, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{ 79, 349, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{ 78, 349, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{ 77, 348, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0)))},
		{ 76, 348, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0)))},
		{ 75, 347, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0)))},
		{ 74, 346, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0)))},
		{ 73, 346, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0)))},
		{ 72, 345, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0)))},
		{ 71, 344, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0)))},
		{ 71, 343, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0)))},
		{ 70, 342, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0)))},
		{ 69, 341, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{ 69, 340, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{ 68, 339, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{ 68, 338, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{ 67, 337, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{ 67, 336, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{ 67, 335, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{ 66, 334, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{ 66, 333, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{ 66, 332, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{ 66, 331, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{ 66, 330, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{ 66, 329, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{ 66, 328, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{ 66, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{ 66, 326, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{ 66, 325, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{ 66, 324, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{ 66, 323, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{ 67, 322, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{ 67, 321, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{ 68, 320, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{ 68, 319, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{ 68, 318, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 21.0)))},
		{ 69, 317, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 21.0)))},
		{ 70, 316, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 21.0)))},
		{ 70, 315, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 21.0)))},
		{ 71, 314, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 21.0)))},
		{ 72, 313, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 21.0)))},
		{ 73, 312, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 21.0)))},
		{ 74, 311, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 21.0)))},
		{ 75, 310, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 21.0)))},
		{ 76, 310, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 21.0)))},
		{ 77, 309, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 21.0)))},
		{ 78, 309, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 21.0)))},
		{ 79, 308, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 21.0)))},
		{ 80, 308, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 21.0)))},
		{ 81, 308, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 21.0)))},
		{ 82, 307, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 21.0)))},
		{ 83, 307, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 21.0)))},
		{ 84, 307, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 21.0)))},
		{ 85, 307, (float)(TICK_VALUE + (TICK_INCREMENT * (18.0 / 21.0)))},
		{ 86, 307, (float)(TICK_VALUE + (TICK_INCREMENT * (19.0 / 21.0)))},
		{ 87, 307, (float)(TICK_VALUE + (TICK_INCREMENT * (20.0 / 21.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(99.99)
		#define TICK_INCREMENT	(0.0)
		{ 88, 307, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	main_rotor_rpm_indicator_needle_scale_down_20_left_30[] =
	{
		// dial centred at x = 361, y = 307

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(10.0)
		{379, 300, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{379, 301, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{380, 302, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{380, 303, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{380, 304, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{380, 305, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{380, 306, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{380, 307, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{380, 308, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{380, 309, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{380, 310, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(10.0)
		#define TICK_INCREMENT	(10.0)
		{380, 311, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0)))},
		{380, 312, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0)))},
		{379, 313, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0)))},
		{379, 314, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0)))},
		{379, 315, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0)))},
		{378, 316, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0)))},
		{378, 317, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0)))},
		{377, 318, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0)))},
		{377, 319, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0)))},
		{376, 320, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(20.0)
		#define TICK_INCREMENT	(10.0)
		{375, 321, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  8.0)))},
		{374, 322, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  8.0)))},
		{373, 323, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  8.0)))},
		{372, 324, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  8.0)))},
		{371, 324, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  8.0)))},
		{370, 325, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  8.0)))},
		{369, 325, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  8.0)))},
		{368, 326, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  8.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(30.0)
		#define TICK_INCREMENT	(10.0)
		{367, 326, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{366, 326, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{365, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{364, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{363, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{362, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{361, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{360, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{359, 327, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(40.0)
		#define TICK_INCREMENT	(10.0)
		{358, 326, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{357, 326, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{356, 326, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{355, 325, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{354, 325, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{353, 324, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{352, 324, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{351, 323, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{350, 322, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(10.0)
		{349, 321, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  9.0)))},
		{348, 320, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 /  9.0)))},
		{347, 319, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 /  9.0)))},
		{346, 318, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 /  9.0)))},
		{346, 317, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 /  9.0)))},
		{345, 316, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 /  9.0)))},
		{345, 315, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 /  9.0)))},
		{344, 314, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 /  9.0)))},
		{344, 313, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 /  9.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(60.0)
		#define TICK_INCREMENT	(10.0)
		{344, 312, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0)))},
		{343, 311, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0)))},
		{343, 310, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0)))},
		{343, 309, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0)))},
		{343, 308, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0)))},
		{343, 307, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0)))},
		{343, 306, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0)))},
		{343, 305, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0)))},
		{343, 304, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0)))},
		{343, 303, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(70.0)
		#define TICK_INCREMENT	(10.0)
		{343, 302, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 10.0)))},
		{343, 301, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 10.0)))},
		{343, 300, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 10.0)))},
		{344, 299, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 10.0)))},
		{344, 298, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 10.0)))},
		{344, 297, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 10.0)))},
		{345, 296, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 10.0)))},
		{345, 295, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 10.0)))},
		{346, 294, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 10.0)))},
		{346, 293, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 10.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(80.0)
		#define TICK_INCREMENT	(20.0)
		{347, 292, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 18.0)))},
		{348, 291, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 18.0)))},
		{349, 290, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 18.0)))},
		{350, 289, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 18.0)))},
		{351, 289, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 18.0)))},
		{352, 288, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 18.0)))},
		{353, 287, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 18.0)))},
		{354, 287, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 18.0)))},
		{355, 287, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 18.0)))},
		{356, 286, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 18.0)))},
		{357, 286, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 18.0)))},
		{358, 286, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 18.0)))},
		{359, 286, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 18.0)))},
		{360, 286, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 18.0)))},
		{361, 286, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 18.0)))},
		{362, 286, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 18.0)))},
		{363, 286, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 18.0)))},
		{364, 286, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 18.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(99.99)
		#define TICK_INCREMENT	(0.0)
		{365, 286, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
