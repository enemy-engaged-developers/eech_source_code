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
	airspeed_indicator_needle_scale_down_20_ahead[] =
	{
		// dial centred at x = 533, y = 440

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{533, 412, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 26.0))},
		{534, 412, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 26.0))},
		{535, 412, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 26.0))},
		{536, 412, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 26.0))},
		{537, 412, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 26.0))},
		{538, 413, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 26.0))},
		{539, 413, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 26.0))},
		{540, 413, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 26.0))},
		{541, 413, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 26.0))},
		{542, 414, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 26.0))},
		{543, 414, TICK_VALUE + (TICK_INCREMENT * (10.0 / 26.0))},
		{544, 414, TICK_VALUE + (TICK_INCREMENT * (11.0 / 26.0))},
		{545, 415, TICK_VALUE + (TICK_INCREMENT * (12.0 / 26.0))},
		{546, 415, TICK_VALUE + (TICK_INCREMENT * (13.0 / 26.0))},
		{547, 416, TICK_VALUE + (TICK_INCREMENT * (14.0 / 26.0))},
		{548, 416, TICK_VALUE + (TICK_INCREMENT * (15.0 / 26.0))},
		{549, 417, TICK_VALUE + (TICK_INCREMENT * (16.0 / 26.0))},
		{550, 418, TICK_VALUE + (TICK_INCREMENT * (17.0 / 26.0))},
		{551, 418, TICK_VALUE + (TICK_INCREMENT * (18.0 / 26.0))},
		{552, 419, TICK_VALUE + (TICK_INCREMENT * (19.0 / 26.0))},
		{553, 420, TICK_VALUE + (TICK_INCREMENT * (20.0 / 26.0))},
		{554, 421, TICK_VALUE + (TICK_INCREMENT * (21.0 / 26.0))},
		{555, 422, TICK_VALUE + (TICK_INCREMENT * (22.0 / 26.0))},
		{555, 423, TICK_VALUE + (TICK_INCREMENT * (23.0 / 26.0))},
		{556, 424, TICK_VALUE + (TICK_INCREMENT * (24.0 / 26.0))},
		{557, 425, TICK_VALUE + (TICK_INCREMENT * (25.0 / 26.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(50.0)
		{557, 426, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 40.0))},
		{558, 427, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 40.0))},
		{558, 428, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 40.0))},
		{559, 429, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 40.0))},
		{559, 430, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 40.0))},
		{560, 431, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 40.0))},
		{560, 432, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 40.0))},
		{560, 433, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 40.0))},
		{560, 434, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 40.0))},
		{561, 435, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 40.0))},
		{561, 436, TICK_VALUE + (TICK_INCREMENT * (10.0 / 40.0))},
		{561, 437, TICK_VALUE + (TICK_INCREMENT * (11.0 / 40.0))},
		{561, 438, TICK_VALUE + (TICK_INCREMENT * (12.0 / 40.0))},
		{561, 439, TICK_VALUE + (TICK_INCREMENT * (13.0 / 40.0))},
		{561, 440, TICK_VALUE + (TICK_INCREMENT * (14.0 / 40.0))},
		{561, 441, TICK_VALUE + (TICK_INCREMENT * (15.0 / 40.0))},
		{561, 442, TICK_VALUE + (TICK_INCREMENT * (16.0 / 40.0))},
		{561, 443, TICK_VALUE + (TICK_INCREMENT * (17.0 / 40.0))},
		{561, 444, TICK_VALUE + (TICK_INCREMENT * (18.0 / 40.0))},
		{561, 445, TICK_VALUE + (TICK_INCREMENT * (19.0 / 40.0))},
		{561, 446, TICK_VALUE + (TICK_INCREMENT * (20.0 / 40.0))},
		{560, 447, TICK_VALUE + (TICK_INCREMENT * (21.0 / 40.0))},
		{560, 448, TICK_VALUE + (TICK_INCREMENT * (22.0 / 40.0))},
		{560, 449, TICK_VALUE + (TICK_INCREMENT * (23.0 / 40.0))},
		{560, 450, TICK_VALUE + (TICK_INCREMENT * (24.0 / 40.0))},
		{559, 451, TICK_VALUE + (TICK_INCREMENT * (25.0 / 40.0))},
		{559, 452, TICK_VALUE + (TICK_INCREMENT * (26.0 / 40.0))},
		{558, 453, TICK_VALUE + (TICK_INCREMENT * (27.0 / 40.0))},
		{558, 454, TICK_VALUE + (TICK_INCREMENT * (28.0 / 40.0))},
		{557, 455, TICK_VALUE + (TICK_INCREMENT * (29.0 / 40.0))},
		{557, 456, TICK_VALUE + (TICK_INCREMENT * (30.0 / 40.0))},
		{556, 457, TICK_VALUE + (TICK_INCREMENT * (31.0 / 40.0))},
		{555, 458, TICK_VALUE + (TICK_INCREMENT * (32.0 / 40.0))},
		{554, 459, TICK_VALUE + (TICK_INCREMENT * (33.0 / 40.0))},
		{553, 460, TICK_VALUE + (TICK_INCREMENT * (34.0 / 40.0))},
		{552, 461, TICK_VALUE + (TICK_INCREMENT * (35.0 / 40.0))},
		{551, 462, TICK_VALUE + (TICK_INCREMENT * (36.0 / 40.0))},
		{550, 463, TICK_VALUE + (TICK_INCREMENT * (37.0 / 40.0))},
		{549, 464, TICK_VALUE + (TICK_INCREMENT * (38.0 / 40.0))},
		{548, 464, TICK_VALUE + (TICK_INCREMENT * (39.0 / 40.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(50.0)
		{547, 465, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 28.0))},
		{546, 465, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 28.0))},
		{545, 466, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 28.0))},
		{544, 466, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 28.0))},
		{543, 467, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 28.0))},
		{542, 467, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 28.0))},
		{541, 467, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 28.0))},
		{540, 468, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 28.0))},
		{539, 468, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 28.0))},
		{538, 468, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 28.0))},
		{537, 468, TICK_VALUE + (TICK_INCREMENT * (10.0 / 28.0))},
		{536, 468, TICK_VALUE + (TICK_INCREMENT * (11.0 / 28.0))},
		{535, 468, TICK_VALUE + (TICK_INCREMENT * (12.0 / 28.0))},
		{534, 468, TICK_VALUE + (TICK_INCREMENT * (13.0 / 28.0))},
		{533, 468, TICK_VALUE + (TICK_INCREMENT * (14.0 / 28.0))},
		{532, 468, TICK_VALUE + (TICK_INCREMENT * (15.0 / 28.0))},
		{531, 468, TICK_VALUE + (TICK_INCREMENT * (16.0 / 28.0))},
		{530, 468, TICK_VALUE + (TICK_INCREMENT * (17.0 / 28.0))},
		{529, 468, TICK_VALUE + (TICK_INCREMENT * (18.0 / 28.0))},
		{528, 468, TICK_VALUE + (TICK_INCREMENT * (19.0 / 28.0))},
		{527, 468, TICK_VALUE + (TICK_INCREMENT * (20.0 / 28.0))},
		{526, 468, TICK_VALUE + (TICK_INCREMENT * (21.0 / 28.0))},
		{525, 467, TICK_VALUE + (TICK_INCREMENT * (22.0 / 28.0))},
		{524, 467, TICK_VALUE + (TICK_INCREMENT * (23.0 / 28.0))},
		{523, 467, TICK_VALUE + (TICK_INCREMENT * (24.0 / 28.0))},
		{522, 466, TICK_VALUE + (TICK_INCREMENT * (25.0 / 28.0))},
		{521, 466, TICK_VALUE + (TICK_INCREMENT * (26.0 / 28.0))},
		{520, 465, TICK_VALUE + (TICK_INCREMENT * (27.0 / 28.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(150.0)
		#define TICK_INCREMENT	(50.0)
		{519, 465, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 26.0))},
		{518, 464, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 26.0))},
		{517, 464, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 26.0))},
		{516, 463, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 26.0))},
		{515, 462, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 26.0))},
		{514, 461, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 26.0))},
		{513, 460, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 26.0))},
		{512, 459, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 26.0))},
		{511, 458, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 26.0))},
		{510, 457, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 26.0))},
		{510, 456, TICK_VALUE + (TICK_INCREMENT * (10.0 / 26.0))},
		{509, 455, TICK_VALUE + (TICK_INCREMENT * (11.0 / 26.0))},
		{508, 454, TICK_VALUE + (TICK_INCREMENT * (12.0 / 26.0))},
		{508, 453, TICK_VALUE + (TICK_INCREMENT * (13.0 / 26.0))},
		{507, 452, TICK_VALUE + (TICK_INCREMENT * (14.0 / 26.0))},
		{507, 451, TICK_VALUE + (TICK_INCREMENT * (15.0 / 26.0))},
		{507, 450, TICK_VALUE + (TICK_INCREMENT * (16.0 / 26.0))},
		{506, 449, TICK_VALUE + (TICK_INCREMENT * (17.0 / 26.0))},
		{506, 448, TICK_VALUE + (TICK_INCREMENT * (18.0 / 26.0))},
		{506, 447, TICK_VALUE + (TICK_INCREMENT * (19.0 / 26.0))},
		{505, 446, TICK_VALUE + (TICK_INCREMENT * (20.0 / 26.0))},
		{505, 445, TICK_VALUE + (TICK_INCREMENT * (21.0 / 26.0))},
		{505, 444, TICK_VALUE + (TICK_INCREMENT * (22.0 / 26.0))},
		{505, 443, TICK_VALUE + (TICK_INCREMENT * (23.0 / 26.0))},
		{505, 442, TICK_VALUE + (TICK_INCREMENT * (24.0 / 26.0))},
		{505, 441, TICK_VALUE + (TICK_INCREMENT * (25.0 / 26.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(50.0)
		{505, 440, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 26.0))},
		{505, 439, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 26.0))},
		{505, 438, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 26.0))},
		{505, 437, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 26.0))},
		{505, 436, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 26.0))},
		{505, 435, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 26.0))},
		{506, 434, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 26.0))},
		{506, 433, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 26.0))},
		{506, 432, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 26.0))},
		{506, 431, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 26.0))},
		{507, 430, TICK_VALUE + (TICK_INCREMENT * (10.0 / 26.0))},
		{507, 429, TICK_VALUE + (TICK_INCREMENT * (11.0 / 26.0))},
		{508, 428, TICK_VALUE + (TICK_INCREMENT * (12.0 / 26.0))},
		{508, 427, TICK_VALUE + (TICK_INCREMENT * (13.0 / 26.0))},
		{509, 426, TICK_VALUE + (TICK_INCREMENT * (14.0 / 26.0))},
		{509, 425, TICK_VALUE + (TICK_INCREMENT * (15.0 / 26.0))},
		{510, 424, TICK_VALUE + (TICK_INCREMENT * (16.0 / 26.0))},
		{511, 423, TICK_VALUE + (TICK_INCREMENT * (17.0 / 26.0))},
		{511, 422, TICK_VALUE + (TICK_INCREMENT * (18.0 / 26.0))},
		{512, 421, TICK_VALUE + (TICK_INCREMENT * (19.0 / 26.0))},
		{513, 420, TICK_VALUE + (TICK_INCREMENT * (20.0 / 26.0))},
		{514, 419, TICK_VALUE + (TICK_INCREMENT * (21.0 / 26.0))},
		{515, 419, TICK_VALUE + (TICK_INCREMENT * (22.0 / 26.0))},
		{516, 418, TICK_VALUE + (TICK_INCREMENT * (23.0 / 26.0))},
		{517, 417, TICK_VALUE + (TICK_INCREMENT * (24.0 / 26.0))},
		{518, 416, TICK_VALUE + (TICK_INCREMENT * (25.0 / 26.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(250.0)
		#define TICK_INCREMENT	(0.0)
		{519, 416, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	airspeed_indicator_needle_scale_down_20_right_30[] =
	{
		// dial centred at x = 281, y = 411

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{276, 386, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 23.0))},
		{277, 386, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 23.0))},
		{278, 385, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 23.0))},
		{279, 385, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 23.0))},
		{280, 385, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 23.0))},
		{281, 385, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 23.0))},
		{282, 385, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 23.0))},
		{283, 385, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 23.0))},
		{284, 385, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 23.0))},
		{285, 385, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 23.0))},
		{286, 385, TICK_VALUE + (TICK_INCREMENT * (10.0 / 23.0))},
		{287, 385, TICK_VALUE + (TICK_INCREMENT * (11.0 / 23.0))},
		{288, 385, TICK_VALUE + (TICK_INCREMENT * (12.0 / 23.0))},
		{289, 385, TICK_VALUE + (TICK_INCREMENT * (13.0 / 23.0))},
		{290, 386, TICK_VALUE + (TICK_INCREMENT * (14.0 / 23.0))},
		{291, 386, TICK_VALUE + (TICK_INCREMENT * (15.0 / 23.0))},
		{292, 387, TICK_VALUE + (TICK_INCREMENT * (16.0 / 23.0))},
		{293, 387, TICK_VALUE + (TICK_INCREMENT * (17.0 / 23.0))},
		{294, 388, TICK_VALUE + (TICK_INCREMENT * (18.0 / 23.0))},
		{295, 388, TICK_VALUE + (TICK_INCREMENT * (19.0 / 23.0))},
		{296, 389, TICK_VALUE + (TICK_INCREMENT * (20.0 / 23.0))},
		{297, 390, TICK_VALUE + (TICK_INCREMENT * (21.0 / 23.0))},
		{298, 391, TICK_VALUE + (TICK_INCREMENT * (22.0 / 23.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(50.0)
		{299, 392, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 37.0))},
		{300, 393, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 37.0))},
		{300, 394, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 37.0))},
		{301, 395, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 37.0))},
		{301, 396, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 37.0))},
		{302, 397, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 37.0))},
		{302, 398, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 37.0))},
		{303, 399, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 37.0))},
		{303, 400, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 37.0))},
		{303, 401, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 37.0))},
		{304, 402, TICK_VALUE + (TICK_INCREMENT * (10.0 / 37.0))},
		{304, 403, TICK_VALUE + (TICK_INCREMENT * (11.0 / 37.0))},
		{304, 404, TICK_VALUE + (TICK_INCREMENT * (12.0 / 37.0))},
		{304, 405, TICK_VALUE + (TICK_INCREMENT * (13.0 / 37.0))},
		{304, 406, TICK_VALUE + (TICK_INCREMENT * (14.0 / 37.0))},
		{304, 407, TICK_VALUE + (TICK_INCREMENT * (15.0 / 37.0))},
		{304, 408, TICK_VALUE + (TICK_INCREMENT * (16.0 / 37.0))},
		{304, 409, TICK_VALUE + (TICK_INCREMENT * (17.0 / 37.0))},
		{304, 410, TICK_VALUE + (TICK_INCREMENT * (18.0 / 37.0))},
		{304, 411, TICK_VALUE + (TICK_INCREMENT * (19.0 / 37.0))},
		{304, 412, TICK_VALUE + (TICK_INCREMENT * (20.0 / 37.0))},
		{304, 413, TICK_VALUE + (TICK_INCREMENT * (21.0 / 37.0))},
		{304, 414, TICK_VALUE + (TICK_INCREMENT * (22.0 / 37.0))},
		{303, 415, TICK_VALUE + (TICK_INCREMENT * (23.0 / 37.0))},
		{303, 416, TICK_VALUE + (TICK_INCREMENT * (24.0 / 37.0))},
		{303, 417, TICK_VALUE + (TICK_INCREMENT * (25.0 / 37.0))},
		{302, 418, TICK_VALUE + (TICK_INCREMENT * (26.0 / 37.0))},
		{302, 419, TICK_VALUE + (TICK_INCREMENT * (27.0 / 37.0))},
		{302, 420, TICK_VALUE + (TICK_INCREMENT * (28.0 / 37.0))},
		{301, 421, TICK_VALUE + (TICK_INCREMENT * (29.0 / 37.0))},
		{301, 422, TICK_VALUE + (TICK_INCREMENT * (30.0 / 37.0))},
		{300, 423, TICK_VALUE + (TICK_INCREMENT * (31.0 / 37.0))},
		{300, 424, TICK_VALUE + (TICK_INCREMENT * (32.0 / 37.0))},
		{299, 425, TICK_VALUE + (TICK_INCREMENT * (33.0 / 37.0))},
		{299, 426, TICK_VALUE + (TICK_INCREMENT * (34.0 / 37.0))},
		{298, 427, TICK_VALUE + (TICK_INCREMENT * (35.0 / 37.0))},
		{297, 428, TICK_VALUE + (TICK_INCREMENT * (36.0 / 37.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(50.0)
		{296, 429, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 23.0))},
		{295, 430, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 23.0))},
		{294, 431, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 23.0))},
		{293, 432, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 23.0))},
		{292, 433, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 23.0))},
		{291, 434, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 23.0))},
		{290, 434, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 23.0))},
		{289, 435, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 23.0))},
		{288, 435, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 23.0))},
		{287, 436, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 23.0))},
		{286, 436, TICK_VALUE + (TICK_INCREMENT * (10.0 / 23.0))},
		{285, 437, TICK_VALUE + (TICK_INCREMENT * (11.0 / 23.0))},
		{284, 437, TICK_VALUE + (TICK_INCREMENT * (12.0 / 23.0))},
		{283, 437, TICK_VALUE + (TICK_INCREMENT * (13.0 / 23.0))},
		{282, 437, TICK_VALUE + (TICK_INCREMENT * (14.0 / 23.0))},
		{281, 438, TICK_VALUE + (TICK_INCREMENT * (15.0 / 23.0))},
		{280, 438, TICK_VALUE + (TICK_INCREMENT * (16.0 / 23.0))},
		{279, 438, TICK_VALUE + (TICK_INCREMENT * (17.0 / 23.0))},
		{278, 438, TICK_VALUE + (TICK_INCREMENT * (18.0 / 23.0))},
		{277, 438, TICK_VALUE + (TICK_INCREMENT * (19.0 / 23.0))},
		{276, 438, TICK_VALUE + (TICK_INCREMENT * (20.0 / 23.0))},
		{275, 438, TICK_VALUE + (TICK_INCREMENT * (21.0 / 23.0))},
		{274, 438, TICK_VALUE + (TICK_INCREMENT * (22.0 / 23.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(150.0)
		#define TICK_INCREMENT	(50.0)
		{273, 438, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 23.0))},
		{272, 437, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 23.0))},
		{271, 437, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 23.0))},
		{270, 437, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 23.0))},
		{269, 436, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 23.0))},
		{268, 436, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 23.0))},
		{267, 435, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 23.0))},
		{266, 435, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 23.0))},
		{265, 434, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 23.0))},
		{264, 433, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 23.0))},
		{263, 432, TICK_VALUE + (TICK_INCREMENT * (10.0 / 23.0))},
		{262, 431, TICK_VALUE + (TICK_INCREMENT * (11.0 / 23.0))},
		{261, 430, TICK_VALUE + (TICK_INCREMENT * (12.0 / 23.0))},
		{261, 429, TICK_VALUE + (TICK_INCREMENT * (13.0 / 23.0))},
		{260, 428, TICK_VALUE + (TICK_INCREMENT * (14.0 / 23.0))},
		{259, 427, TICK_VALUE + (TICK_INCREMENT * (15.0 / 23.0))},
		{259, 426, TICK_VALUE + (TICK_INCREMENT * (16.0 / 23.0))},
		{258, 425, TICK_VALUE + (TICK_INCREMENT * (17.0 / 23.0))},
		{258, 424, TICK_VALUE + (TICK_INCREMENT * (18.0 / 23.0))},
		{258, 423, TICK_VALUE + (TICK_INCREMENT * (19.0 / 23.0))},
		{257, 422, TICK_VALUE + (TICK_INCREMENT * (20.0 / 23.0))},
		{257, 421, TICK_VALUE + (TICK_INCREMENT * (21.0 / 23.0))},
		{257, 420, TICK_VALUE + (TICK_INCREMENT * (22.0 / 23.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(50.0)
		{257, 419, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 26.0))},
		{257, 418, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 26.0))},
		{257, 417, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 26.0))},
		{257, 416, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 26.0))},
		{256, 415, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 26.0))},
		{256, 414, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 26.0))},
		{257, 413, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 26.0))},
		{257, 412, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 26.0))},
		{257, 411, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 26.0))},
		{257, 410, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 26.0))},
		{257, 409, TICK_VALUE + (TICK_INCREMENT * (10.0 / 26.0))},
		{257, 408, TICK_VALUE + (TICK_INCREMENT * (11.0 / 26.0))},
		{257, 407, TICK_VALUE + (TICK_INCREMENT * (12.0 / 26.0))},
		{258, 406, TICK_VALUE + (TICK_INCREMENT * (13.0 / 26.0))},
		{258, 405, TICK_VALUE + (TICK_INCREMENT * (14.0 / 26.0))},
		{258, 404, TICK_VALUE + (TICK_INCREMENT * (15.0 / 26.0))},
		{259, 403, TICK_VALUE + (TICK_INCREMENT * (16.0 / 26.0))},
		{259, 402, TICK_VALUE + (TICK_INCREMENT * (17.0 / 26.0))},
		{260, 401, TICK_VALUE + (TICK_INCREMENT * (18.0 / 26.0))},
		{260, 400, TICK_VALUE + (TICK_INCREMENT * (19.0 / 26.0))},
		{261, 399, TICK_VALUE + (TICK_INCREMENT * (20.0 / 26.0))},
		{261, 398, TICK_VALUE + (TICK_INCREMENT * (21.0 / 26.0))},
		{262, 397, TICK_VALUE + (TICK_INCREMENT * (22.0 / 26.0))},
		{263, 396, TICK_VALUE + (TICK_INCREMENT * (23.0 / 26.0))},
		{263, 395, TICK_VALUE + (TICK_INCREMENT * (24.0 / 26.0))},
		{264, 394, TICK_VALUE + (TICK_INCREMENT * (25.0 / 26.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(250.0)
		#define TICK_INCREMENT	(1.0)
		{265, 393, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static scale_data
	airspeed_indicator_needle_scale_down_20_right_60[] =
	{
		// dial centred at x = 12, y = 471

		#define TICK_VALUE		(0.0)
		#define TICK_INCREMENT	(50.0)
		{  0, 444, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 31.0))},
		{  1, 444, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 31.0))},
		{  2, 443, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 31.0))},
		{  3, 443, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 31.0))},
		{  4, 442, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 31.0))},
		{  5, 442, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 31.0))},
		{  6, 441, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 31.0))},
		{  7, 441, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 31.0))},
		{  8, 440, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 31.0))},
		{  9, 440, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 31.0))},
		{ 10, 440, TICK_VALUE + (TICK_INCREMENT * (10.0 / 31.0))},
		{ 11, 440, TICK_VALUE + (TICK_INCREMENT * (11.0 / 31.0))},
		{ 12, 439, TICK_VALUE + (TICK_INCREMENT * (12.0 / 31.0))},
		{ 13, 439, TICK_VALUE + (TICK_INCREMENT * (13.0 / 31.0))},
		{ 14, 439, TICK_VALUE + (TICK_INCREMENT * (14.0 / 31.0))},
		{ 15, 439, TICK_VALUE + (TICK_INCREMENT * (15.0 / 31.0))},
		{ 16, 439, TICK_VALUE + (TICK_INCREMENT * (16.0 / 31.0))},
		{ 17, 439, TICK_VALUE + (TICK_INCREMENT * (17.0 / 31.0))},
		{ 18, 439, TICK_VALUE + (TICK_INCREMENT * (18.0 / 31.0))},
		{ 19, 439, TICK_VALUE + (TICK_INCREMENT * (19.0 / 31.0))},
		{ 20, 439, TICK_VALUE + (TICK_INCREMENT * (20.0 / 31.0))},
		{ 21, 439, TICK_VALUE + (TICK_INCREMENT * (21.0 / 31.0))},
		{ 22, 439, TICK_VALUE + (TICK_INCREMENT * (22.0 / 31.0))},
		{ 23, 439, TICK_VALUE + (TICK_INCREMENT * (23.0 / 31.0))},
		{ 24, 439, TICK_VALUE + (TICK_INCREMENT * (24.0 / 31.0))},
		{ 25, 439, TICK_VALUE + (TICK_INCREMENT * (25.0 / 31.0))},
		{ 26, 440, TICK_VALUE + (TICK_INCREMENT * (26.0 / 31.0))},
		{ 27, 440, TICK_VALUE + (TICK_INCREMENT * (27.0 / 31.0))},
		{ 28, 440, TICK_VALUE + (TICK_INCREMENT * (28.0 / 31.0))},
		{ 29, 441, TICK_VALUE + (TICK_INCREMENT * (29.0 / 31.0))},
		{ 30, 441, TICK_VALUE + (TICK_INCREMENT * (30.0 / 31.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(50.0)
		#define TICK_INCREMENT	(44.0)
		{ 31, 442, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 38.0))},
		{ 32, 443, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 38.0))},
		{ 33, 443, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 38.0))},
		{ 34, 444, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 38.0))},
		{ 35, 445, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 38.0))},
		{ 36, 446, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 38.0))},
		{ 37, 447, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 38.0))},
		{ 37, 448, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 38.0))},
		{ 38, 449, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 38.0))},
		{ 39, 450, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 38.0))},
		{ 39, 451, TICK_VALUE + (TICK_INCREMENT * (10.0 / 38.0))},
		{ 40, 452, TICK_VALUE + (TICK_INCREMENT * (11.0 / 38.0))},
		{ 40, 453, TICK_VALUE + (TICK_INCREMENT * (12.0 / 38.0))},
		{ 40, 454, TICK_VALUE + (TICK_INCREMENT * (13.0 / 38.0))},
		{ 41, 455, TICK_VALUE + (TICK_INCREMENT * (14.0 / 38.0))},
		{ 41, 456, TICK_VALUE + (TICK_INCREMENT * (15.0 / 38.0))},
		{ 41, 457, TICK_VALUE + (TICK_INCREMENT * (16.0 / 38.0))},
		{ 41, 458, TICK_VALUE + (TICK_INCREMENT * (17.0 / 38.0))},
		{ 42, 459, TICK_VALUE + (TICK_INCREMENT * (18.0 / 38.0))},
		{ 42, 460, TICK_VALUE + (TICK_INCREMENT * (19.0 / 38.0))},
		{ 42, 461, TICK_VALUE + (TICK_INCREMENT * (20.0 / 38.0))},
		{ 42, 462, TICK_VALUE + (TICK_INCREMENT * (21.0 / 38.0))},
		{ 42, 463, TICK_VALUE + (TICK_INCREMENT * (22.0 / 38.0))},
		{ 42, 464, TICK_VALUE + (TICK_INCREMENT * (23.0 / 38.0))},
		{ 42, 465, TICK_VALUE + (TICK_INCREMENT * (24.0 / 38.0))},
		{ 42, 466, TICK_VALUE + (TICK_INCREMENT * (25.0 / 38.0))},
		{ 42, 467, TICK_VALUE + (TICK_INCREMENT * (26.0 / 38.0))},
		{ 42, 468, TICK_VALUE + (TICK_INCREMENT * (27.0 / 38.0))},
		{ 41, 469, TICK_VALUE + (TICK_INCREMENT * (28.0 / 38.0))},
		{ 41, 470, TICK_VALUE + (TICK_INCREMENT * (29.0 / 38.0))},
		{ 41, 471, TICK_VALUE + (TICK_INCREMENT * (30.0 / 38.0))},
		{ 41, 472, TICK_VALUE + (TICK_INCREMENT * (31.0 / 38.0))},
		{ 41, 473, TICK_VALUE + (TICK_INCREMENT * (32.0 / 38.0))},
		{ 40, 474, TICK_VALUE + (TICK_INCREMENT * (33.0 / 38.0))},
		{ 40, 475, TICK_VALUE + (TICK_INCREMENT * (34.0 / 38.0))},
		{ 40, 476, TICK_VALUE + (TICK_INCREMENT * (35.0 / 38.0))},
		{ 39, 477, TICK_VALUE + (TICK_INCREMENT * (36.0 / 38.0))},
		{ 39, 478, TICK_VALUE + (TICK_INCREMENT * (37.0 / 38.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(94.0)
		#define TICK_INCREMENT	(6.0)
		{ 38, 479, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 11.0))},
		{ 37, 479, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 11.0))},
		{ 36, 479, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 11.0))},
		{ 35, 479, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 11.0))},
		{ 34, 479, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 11.0))},
		{ 33, 479, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 11.0))},
		{ 32, 479, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 11.0))},
		{ 31, 479, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 11.0))},
		{ 30, 479, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 11.0))},
		{ 29, 479, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 11.0))},
		{ 28, 479, TICK_VALUE + (TICK_INCREMENT * (10.0 / 11.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(100.0)
		#define TICK_INCREMENT	(50.0)
		{ 27, 479, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0))},
		{ 26, 479, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0))},
		{ 25, 479, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0))},
		{ 24, 479, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0))},
		{ 23, 479, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0))},
		{ 22, 479, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0))},
		{ 21, 479, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0))},
		{ 20, 479, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0))},
		{ 19, 479, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0))},
		{ 18, 479, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0))},
		{ 17, 479, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0))},
		{ 16, 479, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0))},
		{ 15, 479, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0))},
		{ 14, 479, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0))},
		{ 13, 479, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(150.0)
		#define TICK_INCREMENT	(50.0)
		{ 12, 479, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 12.0))},
		{ 11, 479, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 12.0))},
		{ 10, 479, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 12.0))},
		{  9, 479, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 12.0))},
		{  8, 479, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 12.0))},
		{  7, 479, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 12.0))},
		{  6, 479, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 12.0))},
		{  5, 479, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 12.0))},
		{  4, 479, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 12.0))},
		{  3, 479, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 12.0))},
		{  2, 479, TICK_VALUE + (TICK_INCREMENT * (10.0 / 12.0))},
		{  1, 479, TICK_VALUE + (TICK_INCREMENT * (11.0 / 12.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(200.0)
		#define TICK_INCREMENT	(50.0)
		{  0, 478, TICK_VALUE + (TICK_INCREMENT * ( 0.0 / 15.0))},
		{  0, 477, TICK_VALUE + (TICK_INCREMENT * ( 1.0 / 15.0))},
		{  0, 476, TICK_VALUE + (TICK_INCREMENT * ( 2.0 / 15.0))},
		{  0, 475, TICK_VALUE + (TICK_INCREMENT * ( 3.0 / 15.0))},
		{  0, 474, TICK_VALUE + (TICK_INCREMENT * ( 4.0 / 15.0))},
		{  0, 473, TICK_VALUE + (TICK_INCREMENT * ( 5.0 / 15.0))},
		{  0, 472, TICK_VALUE + (TICK_INCREMENT * ( 6.0 / 15.0))},
		{  0, 471, TICK_VALUE + (TICK_INCREMENT * ( 7.0 / 15.0))},
		{  0, 470, TICK_VALUE + (TICK_INCREMENT * ( 8.0 / 15.0))},
		{  0, 469, TICK_VALUE + (TICK_INCREMENT * ( 9.0 / 15.0))},
		{  0, 468, TICK_VALUE + (TICK_INCREMENT * (10.0 / 15.0))},
		{  0, 467, TICK_VALUE + (TICK_INCREMENT * (11.0 / 15.0))},
		{  0, 466, TICK_VALUE + (TICK_INCREMENT * (12.0 / 15.0))},
		{  0, 465, TICK_VALUE + (TICK_INCREMENT * (13.0 / 15.0))},
		{  0, 464, TICK_VALUE + (TICK_INCREMENT * (14.0 / 15.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		#define TICK_VALUE		(250.0)
		#define TICK_INCREMENT	(1.0)
		{  0, 463, TICK_VALUE + (TICK_INCREMENT * ( 0.0 /  1.0))},
		#undef TICK_VALUE
		#undef TICK_INCREMENT
		{0, 0, FLT_MAX},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
