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
	barometric_altimeter_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 599, y = 440

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{599, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{600, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{601, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{602, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{603, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{604, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{605, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{606, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{607, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{608, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{609, 414, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{610, 414, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{611, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{612, 415, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{613, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{614, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{615, 417, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{616, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{617, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{618, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{619, 420, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{620, 421, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{621, 422, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{621, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{622, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{623, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{623, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{624, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{624, 428, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{625, 429, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{625, 430, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{626, 431, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{626, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{626, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{626, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{627, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{627, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{627, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{627, 438, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{627, 439, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{627, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{627, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{627, 442, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{627, 443, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{627, 444, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{627, 445, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{627, 446, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{626, 447, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{626, 448, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{626, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{625, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{625, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{625, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{624, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{624, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{623, 455, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{622, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{622, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{621, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{620, 459, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{619, 460, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{618, 461, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{617, 462, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{616, 463, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{615, 464, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{614, 464, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{613, 465, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{612, 465, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{611, 466, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{610, 466, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{609, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{608, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{607, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{606, 468, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{605, 468, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{604, 468, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{603, 468, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{602, 468, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{601, 468, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{600, 468, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{599, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{598, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{597, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{596, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{595, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{594, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{593, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{592, 468, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{591, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{590, 467, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{589, 467, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{588, 466, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{587, 466, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{586, 465, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{585, 465, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{584, 464, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{583, 464, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{582, 463, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{581, 462, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{580, 461, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{579, 460, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{578, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{577, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{576, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{575, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{575, 455, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{574, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{574, 453, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{573, 452, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{573, 451, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{572, 450, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{572, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{572, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{572, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{571, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{571, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{571, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{571, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{571, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{571, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{571, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{571, 439, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{571, 438, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{571, 437, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{571, 436, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{571, 435, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{571, 434, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{572, 433, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{572, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{572, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{573, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{573, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{574, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{574, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{575, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{575, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{576, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{577, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{577, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{578, 421, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{579, 420, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{580, 419, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{581, 418, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{582, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{583, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{584, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{585, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{586, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{587, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{588, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{589, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{590, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{591, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{592, 413, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{593, 413, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{594, 413, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{595, 412, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{596, 412, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{597, 412, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{598, 412, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	barometric_altimeter_needle_scale_down_20_right_30[] =
	{
		// dial centred at x = 333, y = 393

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{329, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{330, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{331, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{332, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{333, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{334, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{335, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{336, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{337, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{338, 368, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{339, 368, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{340, 368, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{341, 369, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{342, 369, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{343, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{344, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{345, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{346, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{347, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{348, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{349, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{350, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{350, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{351, 377, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{351, 378, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{352, 379, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{352, 380, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{353, 381, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{353, 382, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{353, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{354, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{354, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{354, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{354, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{354, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{354, 389, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{354, 390, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{354, 391, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{354, 392, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{354, 393, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{354, 394, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{354, 395, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{354, 396, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{353, 397, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{353, 398, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{353, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{353, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{352, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{352, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{351, 403, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{351, 404, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{350, 405, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{350, 406, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{349, 407, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{349, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{348, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{347, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{346, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{345, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{344, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{343, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{342, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{341, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{340, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{339, 416, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{338, 417, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{337, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{336, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{335, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{334, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{333, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{332, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{331, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{330, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{329, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{328, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{327, 418, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{326, 418, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{325, 417, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{324, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0)))},
		{323, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0)))},
		{322, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0)))},
		{321, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0)))},
		{320, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0)))},
		{319, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0)))},
		{318, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0)))},
		{317, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0)))},
		{316, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0)))},
		{315, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0)))},
		{315, 409, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{314, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{314, 407, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{313, 406, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{313, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{312, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{312, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{312, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{312, 401, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{311, 400, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{311, 399, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{311, 398, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{311, 397, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{311, 396, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{311, 395, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{311, 394, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{311, 393, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{311, 392, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{311, 391, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{312, 390, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{312, 389, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{312, 388, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{312, 387, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{313, 386, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{313, 385, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{313, 384, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{314, 383, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{314, 382, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{315, 381, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{315, 380, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{316, 379, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{317, 378, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{317, 377, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0)))},
		{318, 376, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0)))},
		{319, 375, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0)))},
		{320, 374, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0)))},
		{321, 373, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0)))},
		{322, 372, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0)))},
		{323, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0)))},
		{324, 371, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0)))},
		{325, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0)))},
		{326, 370, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0)))},
		{327, 369, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0)))},
		{328, 369, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	barometric_altimeter_needle_scale_down_20_right_60[] =
	{
		// dial centred at x = 73, y = 430

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(100.0)
		{ 63, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{ 64, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{ 65, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{ 66, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{ 67, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{ 68, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{ 69, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{ 70, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{ 71, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{ 72, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{ 73, 402, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{ 74, 402, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{ 75, 401, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{ 76, 401, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{ 77, 401, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{ 78, 401, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(100.0)
		{ 79, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 13.0)))},
		{ 80, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 13.0)))},
		{ 81, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 13.0)))},
		{ 82, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 13.0)))},
		{ 83, 402, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 13.0)))},
		{ 84, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 13.0)))},
		{ 85, 403, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 13.0)))},
		{ 86, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 13.0)))},
		{ 87, 404, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 13.0)))},
		{ 88, 405, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 13.0)))},
		{ 89, 405, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 13.0)))},
		{ 90, 406, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 13.0)))},
		{ 91, 407, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 13.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(100.0)
		{ 92, 408, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{ 93, 409, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{ 93, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{ 94, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{ 95, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{ 95, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{ 96, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{ 96, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{ 96, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{ 97, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{ 97, 418, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{ 97, 419, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{ 97, 420, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{ 98, 421, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{ 98, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(300.0)
		#define TICK_INCREMENT	(100.0)
		{ 98, 423, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{ 98, 424, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{ 98, 425, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{ 98, 426, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{ 98, 427, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{ 98, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{ 98, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{ 98, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{ 97, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{ 97, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{ 97, 433, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{ 97, 434, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{ 96, 435, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{ 96, 436, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{ 96, 437, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{ 95, 438, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{ 95, 439, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(400.0)
		#define TICK_INCREMENT	(100.0)
		{ 95, 440, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{ 94, 441, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{ 94, 442, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{ 93, 443, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{ 93, 444, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{ 92, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{ 91, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{ 91, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{ 90, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{ 89, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{ 88, 450, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{ 87, 451, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{ 86, 452, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{ 85, 453, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{ 84, 454, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(500.0)
		#define TICK_INCREMENT	(100.0)
		{ 83, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 16.0)))},
		{ 82, 455, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 16.0)))},
		{ 81, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 16.0)))},
		{ 80, 456, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 16.0)))},
		{ 79, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 16.0)))},
		{ 78, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 16.0)))},
		{ 77, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 16.0)))},
		{ 76, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 16.0)))},
		{ 75, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 16.0)))},
		{ 74, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 16.0)))},
		{ 73, 459, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 16.0)))},
		{ 72, 459, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 16.0)))},
		{ 71, 459, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 16.0)))},
		{ 70, 459, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 16.0)))},
		{ 69, 459, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 16.0)))},
		{ 68, 460, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 16.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(600.0)
		#define TICK_INCREMENT	(100.0)
		{ 67, 460, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 14.0)))},
		{ 66, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 14.0)))},
		{ 65, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 14.0)))},
		{ 64, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 14.0)))},
		{ 63, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 14.0)))},
		{ 62, 459, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 14.0)))},
		{ 61, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 14.0)))},
		{ 60, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 14.0)))},
		{ 59, 458, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 14.0)))},
		{ 58, 457, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 14.0)))},
		{ 57, 457, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 14.0)))},
		{ 56, 456, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 14.0)))},
		{ 55, 455, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 14.0)))},
		{ 54, 455, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 14.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(700.0)
		#define TICK_INCREMENT	(100.0)
		{ 53, 454, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 17.0)))},
		{ 52, 453, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 17.0)))},
		{ 52, 452, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 17.0)))},
		{ 51, 451, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 17.0)))},
		{ 50, 450, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 17.0)))},
		{ 50, 449, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 17.0)))},
		{ 49, 448, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 17.0)))},
		{ 49, 447, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 17.0)))},
		{ 48, 446, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 17.0)))},
		{ 48, 445, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 17.0)))},
		{ 48, 444, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 17.0)))},
		{ 47, 443, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 17.0)))},
		{ 47, 442, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 17.0)))},
		{ 47, 441, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 17.0)))},
		{ 47, 440, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 17.0)))},
		{ 47, 439, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 17.0)))},
		{ 47, 438, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 17.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(800.0)
		#define TICK_INCREMENT	(100.0)
		{ 46, 437, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 18.0)))},
		{ 46, 436, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 18.0)))},
		{ 46, 435, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 18.0)))},
		{ 46, 434, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 18.0)))},
		{ 47, 433, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 18.0)))},
		{ 47, 432, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 18.0)))},
		{ 47, 431, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 18.0)))},
		{ 47, 430, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 18.0)))},
		{ 47, 429, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 18.0)))},
		{ 47, 428, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 18.0)))},
		{ 48, 427, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 18.0)))},
		{ 48, 426, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 18.0)))},
		{ 48, 425, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 18.0)))},
		{ 48, 424, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 18.0)))},
		{ 49, 423, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 18.0)))},
		{ 49, 422, (float)(TICK_VALUE + (TICK_INCREMENT * (15.0 / 18.0)))},
		{ 50, 421, (float)(TICK_VALUE + (TICK_INCREMENT * (16.0 / 18.0)))},
		{ 50, 420, (float)(TICK_VALUE + (TICK_INCREMENT * (17.0 / 18.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(900.0)
		#define TICK_INCREMENT	(100.0)
		{ 51, 419, (float)(TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0)))},
		{ 51, 418, (float)(TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0)))},
		{ 52, 417, (float)(TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0)))},
		{ 52, 416, (float)(TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0)))},
		{ 53, 415, (float)(TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0)))},
		{ 54, 414, (float)(TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0)))},
		{ 54, 413, (float)(TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0)))},
		{ 55, 412, (float)(TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0)))},
		{ 56, 411, (float)(TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0)))},
		{ 57, 410, (float)(TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0)))},
		{ 58, 409, (float)(TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0)))},
		{ 59, 408, (float)(TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0)))},
		{ 60, 408, (float)(TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0)))},
		{ 61, 407, (float)(TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0)))},
		{ 62, 406, (float)(TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0)))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
