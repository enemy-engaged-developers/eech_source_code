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
//
// IMPORTANT: Update VIEWS\VM_MENU.C if any of these lists change.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*view_group_names[] =
	{
		"VIEW_GROUP_ALL",
		"VIEW_GROUP_WINGMEN",
		"VIEW_GROUP_PLAYERS",
		"VIEW_GROUP_AVAILABLE_GUNSHIPS",
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char
	*view_side_names[] =
	{
		"VIEW_SIDE_ALL",
		"VIEW_SIDE_ALLIED",
		"VIEW_SIDE_ENEMY",
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*view_category_names[] =
	{
		"VIEW_CATEGORY_ALL",
		"VIEW_CATEGORY_COMBAT_HELICOPTERS",
		"VIEW_CATEGORY_TRANSPORT_HELICOPTERS",
		"VIEW_CATEGORY_COMBAT_AIRCRAFT",
		"VIEW_CATEGORY_TRANSPORT_AIRCRAFT",
		"VIEW_CATEGORY_COMBAT_VEHICLES",
		"VIEW_CATEGORY_ARTILLERY",
		"VIEW_CATEGORY_AIR_DEFENCE_UNITS",
		"VIEW_CATEGORY_TRANSPORT_VEHICLES",
		"VIEW_CATEGORY_INFANTRY",
		"VIEW_CATEGORY_WARSHIPS",
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*view_type_names[] =
	{
		"VIEW_TYPE_ALL",
		"VIEW_TYPE_AH1T_SEACOBRA",
		"VIEW_TYPE_AH1W_SUPERCOBRA",
		"VIEW_TYPE_AH64A_APACHE",
		"VIEW_TYPE_AH64D_APACHE_LONGBOW",
		"VIEW_TYPE_CH46E_SEA_KNIGHT",
		"VIEW_TYPE_KA29_HELIX_B",
		"VIEW_TYPE_KA50_HOKUM",
		"VIEW_TYPE_KA52_HOKUM_B",
		"VIEW_TYPE_MI24D_HIND",
		"VIEW_TYPE_MI28N_HAVOC_B",
		"VIEW_TYPE_MV22_OSPREY",
		"VIEW_TYPE_OH58D_KIOWA_WARRIOR",
		"VIEW_TYPE_RAH66_COMANCHE",
		"VIEW_TYPE_UH60_BLACK_HAWK",
		"VIEW_TYPE_CH3_JOLLY_GREEN_GIANT",
		"VIEW_TYPE_CH47D_CHINOOK",
		"VIEW_TYPE_CH53E_SUPER_STALLION",
		"VIEW_TYPE_MI6_HOOK",
		"VIEW_TYPE_MI17_HIP",
		"VIEW_TYPE_A10A_THUNDERBOLT",
		"VIEW_TYPE_AV8B_HARRIER",
		"VIEW_TYPE_F16_FIGHTING_FALCON",
		"VIEW_TYPE_FA18_HORNET",
		"VIEW_TYPE_MIG29_FULCRUM",
		"VIEW_TYPE_SU25_FROGFOOT",
		"VIEW_TYPE_SU33_FLANKER",
		"VIEW_TYPE_SU34_FULLBACK",
		"VIEW_TYPE_YAK41_FREESTYLE",
		"VIEW_TYPE_AN12B_CUB",
		"VIEW_TYPE_C17_GLOBEMASTER_III",
		"VIEW_TYPE_C130J_HERCULES_II",
		"VIEW_TYPE_IL76MD_CANDID_B",
		"VIEW_TYPE_BMP2",
		"VIEW_TYPE_BMP3",
		"VIEW_TYPE_BRDM2",
		"VIEW_TYPE_BTR80",
		"VIEW_TYPE_M1A2_ABRAMS",
		"VIEW_TYPE_M2A2_BRADLEY",
		"VIEW_TYPE_M113A2",
		"VIEW_TYPE_M1025_HUMVEE",
		"VIEW_TYPE_T80U",
		"VIEW_TYPE_2S19",
		"VIEW_TYPE_BM21_GRAD",
		"VIEW_TYPE_M109A2",
		"VIEW_TYPE_M270_MLRS",
		"VIEW_TYPE_M48A1_CHAPARRAL",
		"VIEW_TYPE_M163_VULCAN",
		"VIEW_TYPE_M1037_AVENGER",
		"VIEW_TYPE_SA13_GOPHER",
		"VIEW_TYPE_SA19_GRISON",
		"VIEW_TYPE_M978_HEMTT",
		"VIEW_TYPE_M923A1_BIG_FOOT",
		"VIEW_TYPE_M998_HUMVEE",
		"VIEW_TYPE_UAZ469B",
		"VIEW_TYPE_URAL_4320",
		"VIEW_TYPE_URAL_FUEL_TANKER",
		"VIEW_TYPE_INFANTRY",
		"VIEW_TYPE_INFANTRY_WITH_SAM",
		"VIEW_TYPE_AIST_CLASS",
		"VIEW_TYPE_KIEV_CLASS",
		"VIEW_TYPE_KRIVAK_II_CLASS",
		"VIEW_TYPE_LCU",
		"VIEW_TYPE_LCAC",
		"VIEW_TYPE_OLIVER_HAZARD_PERRY_CLASS",
		"VIEW_TYPE_TARAWA_CLASS",
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
