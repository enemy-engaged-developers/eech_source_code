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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define DEBUG_MEDALS 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MEDALS_AREA_FADE_TIME 500

#define MEDALS_AREA_OFFSET_TIME 0

#define NUMBER_OF_MEDAL_GRAPHICS (NUM_MEDAL_TYPES + 2)

#define NUMBER_OF_VALOUR_MEDALS 4

#define NUM_NEEDED_TO_AWARD_AIR_MEDAL 3

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PLAYER_MEDAL_INFO
{
	const char
		*name,
		*info;

	float
		x1,
		y1,
		x2,
		y2;
};

typedef struct PLAYER_MEDAL_INFO player_medal_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PLAYER_MEDAL_CRITERIA
{
	int
		points_req,
		pilot_rank,
		wings_medal,
		num_campaign_medals,
		medal_required,
		medal_multiplier;
};

typedef struct PLAYER_MEDAL_CRITERIA player_medal_criteria;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ui_object
	*player_medals_screen,
	*medals_title_text,
	*medals_text_name,
	*medals_text_info,
	*us_area,
	*russian_area,
	*exit_button;

static ui_object
	*russian_medal_objects [NUMBER_OF_MEDAL_GRAPHICS],
	*us_medal_objects [NUMBER_OF_MEDAL_GRAPHICS];
	
texture_graphic
	*medals_screen_texture,
	*medal_graphics [NUMBER_OF_MEDAL_GRAPHICS];

// info arrays: Medal title, info text, hilite x & y offset, hilite x & y size

player_medal_info
	us_medal_info_array [NUM_MEDAL_TYPES] = 
							{	{	"",	"",	0.000, 0.000, 0.000, 0.000}, //MEDAL_TYPE_NONE,
								{	"",	"",	0.617, 0.000, 0.111, 0.319}, //MEDAL_SAUDI,
								{	"",	"",	0.743, 0.026, 0.108, 0.345}, //MEDAL_LEBANON,
								{	"",	"",	0.852, 0.094, 0.103, 0.324}, //MEDAL_TAIWAN,
								{	"",	"",	0.761, 0.803, 0.163,	0.109}, //MEDAL_ARMY_AVIATOR,
								{	"",	"",	0.732, 0.638, 0.209,	0.147}, //MEDAL_SENIOR_AVIATOR,
								{	"",	"",	0.698, 0.431, 0.260, 0.194}, //MEDAL_MASTER_AVIATOR,
								{	"",	"",	0.361, 0.634, 0.134, 0.242}, //MEDAL_PURPLE_HEART,
								{	"",	"",	0.501, 0.568, 0.134, 0.211}, //MEDAL_AIR_MEDAL,
								{	"",	"",	0.187, 0.464, 0.166, 0.383}, //MEDAL_FLYING_CROSS,
								{	"",	"",	0.010, 0.469, 0.175, 0.238}, //MEDAL_SILVER_STAR,
								{	"",	"",	0.072, 0.079, 0.231, 0.384}, //MEDAL_DISTINGUISHED_SERVICE,
								{	"",	"",	0.324, 0.049, 0.256, 0.512}	}; //MEDAL_MEDAL_OF_HONOUR,

player_medal_info
	russian_medal_info_array [NUM_MEDAL_TYPES] =
							{	{	"",	"",	0.000, 0.000, 0.000, 0.000}, //MEDAL_TYPE_NONE,
								{	"",	"",	0.616, 0.000, 0.116, 0.315}, //MEDAL_SAUDI,
								{	"",	"",	0.739, 0.006, 0.112, 0.363}, //MEDAL_LEBANON,
								{	"",	"",	0.850, 0.068, 0.113, 0.360}, //MEDAL_TAIWAN,
								{	"",	"",	0.876, 0.618, 0.080, 0.292}, //MEDAL_ARMY_AVIATOR,
								{	"",	"",	0.686, 0.561, 0.091, 0.328}, //MEDAL_SENIOR_AVIATOR,
								{	"",	"",	0.778, 0.432, 0.093, 0.315}, //MEDAL_MASTER_AVIATOR,
								{	"",	"",	0.385, 0.555, 0.153, 0.325}, //MEDAL_PURPLE_HEART,
								{	"",	"",	0.544, 0.552, 0.112, 0.228}, //MEDAL_AIR_MEDAL,
								{	"",	"",	0.209, 0.440, 0.154, 0.398}, //MEDAL_FLYING_CROSS,
								{	"",	"",	0.017, 0.440, 0.190, 0.271}, //MEDAL_SILVER_STAR,
								{	"",	"",	0.054, 0.108, 0.269, 0.349}, //MEDAL_DISTINGUISHED_SERVICE,
								{	"",	"",	0.364, 0.000, 0.234, 0.553}	}; //MEDAL_MEDAL_OF_HONOUR,

// graphic arrays: Medal file name, unused text field, x & y offset, x & y size

player_medal_info
	us_medal_graphic_array [NUMBER_OF_MEDAL_GRAPHICS] =
							{	{"",													"",	0.000, 0.000, 0.000, 0.000}, //MEDAL_TYPE_NONE
								{"graphics\\ui\\cohokum\\USSaudi.psd",		"",	0.605, 0.000, 0.133, 0.338}, //MEDAL_SAUDI
								{"graphics\\ui\\cohokum\\USLeb.psd",		"",	0.735, 0.021, 0.122, 0.371}, //MEDAL_LEBANON
								{"graphics\\ui\\cohokum\\USTaiwan.psd",	"",	0.845, 0.082, 0.120, 0.354}, //MEDAL_TAIWAN
								{"graphics\\ui\\cohokum\\armaviat.psd",	"",	0.752, 0.794, 0.180, 0.137}, //MEDAL_ARMY_AVIATOR
								{"graphics\\ui\\cohokum\\senaviat.psd",	"",	0.723, 0.627, 0.227, 0.174}, //MEDAL_SENIOR_AVIATOR
								{"graphics\\ui\\cohokum\\masaviat.psd",	"",	0.688, 0.423, 0.278, 0.217}, //MEDAL_MASTER_AVIATOR
								{"graphics\\ui\\cohokum\\purheart.psd",	"",	0.352, 0.418, 0.151, 0.478}, //MEDAL_PURPLE_HEART
								{"graphics\\ui\\cohokum\\airmedal.psd",	"",	0.495, 0.380, 0.145, 0.411}, //MEDAL_AIR_MEDAL
								{"graphics\\ui\\cohokum\\distfly.psd",		"",	0.164, 0.307, 0.208, 0.560}, //MEDAL_FLYING_CROSS
								{"graphics\\ui\\cohokum\\silvstar.psd",	"",	0.000, 0.146, 0.226, 0.577}, //MEDAL_SILVER_STAR
								{"graphics\\ui\\cohokum\\distser2.psd",	"",	0.060, 0.000, 0.254, 0.495}, //MEDAL_DISTINGUISHED_SERVICE
								{"graphics\\ui\\cohokum\\medhon2.psd",		"",	0.315, 0.000, 0.271, 0.612}, //MEDAL_MEDAL_OF_HONOUR
								{"graphics\\ui\\cohokum\\distser1.psd",	"",	0.060, 0.000, 0.254, 0.495}, //distinguished service medal bdrop
								{"graphics\\ui\\cohokum\\medhon1.psd",		"",	0.315, 0.000, 0.271, 0.612}	}; //medal of honour bdrop

player_medal_info
	russian_medal_graphic_array [NUMBER_OF_MEDAL_GRAPHICS] =
							{	{"",													"",	0.000, 0.000, 0.000, 0.000}, //MEDAL_TYPE_NONE
								{"graphics\\ui\\cohokum\\SVLeb.psd",		"",	0.604, 0.000, 0.142, 0.344}, //MEDAL_SAUDI
								{"graphics\\ui\\cohokum\\SVYemen.psd",		"",	0.727, 0.000, 0.134, 0.394}, //MEDAL_LEBANON
								{"graphics\\ui\\cohokum\\SVTaiwan.psd",	"",	0.837, 0.065, 0.138, 0.391}, //MEDAL_TAIWAN
								{"graphics\\ui\\cohokum\\3rdServ.psd",		"",	0.863, 0.609, 0.104, 0.325}, //MEDAL_ARMY_AVIATOR
								{"graphics\\ui\\cohokum\\2ndServ.psd",		"",	0.672, 0.549, 0.122, 0.365}, //MEDAL_SENIOR_AVIATOR
								{"graphics\\ui\\cohokum\\1StServ.psd",		"",	0.749, 0.366, 0.132, 0.406}, //MEDAL_MASTER_AVIATOR
								{"graphics\\ui\\cohokum\\OrdGlory.psd",	"",	0.371, 0.441, 0.173, 0.458}, //MEDAL_PURPLE_HEART
								{"graphics\\ui\\cohokum\\RdBanner.psd",	"",	0.527, 0.386, 0.136, 0.415}, //MEDAL_AIR_MEDAL
								{"graphics\\ui\\cohokum\\Lenin.psd",		"",	0.200, 0.411, 0.186, 0.468}, //MEDAL_FLYING_CROSS
								{"graphics\\ui\\cohokum\\OrdServ.psd",		"",	0.008, 0.434, 0.220, 0.298}, //MEDAL_SILVER_STAR
								{"graphics\\ui\\cohokum\\OrdVic2.psd",		"",	0.040, 0.096, 0.298, 0.405}, //MEDAL_DISTINGUISHED_SERVICE
								{"graphics\\ui\\cohokum\\GldStar2.psd",	"",	0.344, 0.000, 0.266, 0.579}, //MEDAL_MEDAL_OF_HONOUR
								{"graphics\\ui\\cohokum\\OrdVic1.psd",		"",	0.040, 0.096, 0.298, 0.405}, //distinguished service medal bdrop
								{"graphics\\ui\\cohokum\\GldStar1.psd",	"",	0.344, 0.000, 0.266, 0.579}	};//medal of honour bdrop

// medals must be kept listed in order of most important first

player_medal_criteria
	valour_medal_award_criteria [4] =
	{
		// Criteria for Medal of Honour
		{
			5000,									// points required in mission
			PILOT_RANK_MAJOR,					// pilot rank
			MEDAL_SENIOR_AVIATOR,			// level of aviator medal required
			2,										// number of campaign medals required
			MEDAL_DISTINGUISHED_SERVICE,	// medal required
			2,										// multiplier
		},

		// Criteria for Distinguished Service Medal
		{
			4000,									// points required in mission
			PILOT_RANK_CAPTAIN,				// pilot rank
			MEDAL_ARMY_AVIATOR,				// level of aviator medal required
			1,										// number of campaign medals required
			MEDAL_SILVER_STAR,				// medal required
			3,										// multiplier
		},

		// Criteria for Silver Star
		{
			3200,									// points required in mission
			PILOT_RANK_LIEUTENANT,			// pilot rank
			MEDAL_TYPE_NONE,					// level of aviator medal required
			0,										// number of campaign medals required
			MEDAL_FLYING_CROSS,				// medal required
			2,										// multiplier
		},

		// Criteria for Flying Cross
		{
			2600,									// points required in mission
			PILOT_RANK_LIEUTENANT,			// pilot rank
			MEDAL_TYPE_NONE,					// level of aviator medal required
			0,										// number of campaign medals required
			MEDAL_TYPE_NONE,					// medal required
			0,										// multiplier
		},
	};
								
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void notify_medals_screen_exit_button (ui_object *obj, void *arg);

void set_medal_states (ui_object *medal_objects[]);

void notify_medals_screen (ui_object *obj);

void medals_highlight_off_function (ui_object *obj);

void highlight_us_medal_info (ui_object *obj, void *arg);

void highlight_russian_medal_info (ui_object *obj, void *arg);

void define_us_medal_objects (void);

void define_russian_medal_objects (void);

void notify_award_clicked_medal (ui_object *obj, void *arg);

int query_award_medal (player_log_type *log, int *medals, player_medal_criteria *criteria, int medal_type, int side);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_medal_states (ui_object *medal_objects[])
{
	int
		*medals,
		i;
		
	player_log_type
		*player;

	player = get_current_player_log ();

	medals = player->side_log[player_log_current_side].medals;

	for (i = 1; i < (NUM_MEDAL_TYPES); i++)
	{
		if (medals [i])
		{
			set_ui_object_drawable (medal_objects [i], TRUE);
		}
		else
		{
			set_ui_object_drawable (medal_objects [i], FALSE);
		}
	}

	// always draw medal backdrops for dist.service & medal of honour

	if (medals [MEDAL_DISTINGUISHED_SERVICE])
	{
		set_ui_object_drawable (medal_objects [MEDAL_DISTINGUISHED_SERVICE + 2], FALSE);
	}
	else
	{
		set_ui_object_drawable (medal_objects [MEDAL_DISTINGUISHED_SERVICE + 2], TRUE);
	}
	
	if (medals [MEDAL_MEDAL_OF_HONOUR])
	{
		set_ui_object_drawable (medal_objects [MEDAL_MEDAL_OF_HONOUR + 2], FALSE);
	}
	else
	{
		set_ui_object_drawable (medal_objects [MEDAL_MEDAL_OF_HONOUR + 2], TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_medals_screen (ui_object *obj)
{

	int
		i;

	if ( get_ui_object_drawable (obj) )
	{

		if (medals_screen_texture)
		{
			for (i = 1; i < NUMBER_OF_MEDAL_GRAPHICS; i++)
			{
				destroy_texture_graphic (medal_graphics [i]);
	
				medal_graphics [i] = NULL;
			}
	
			destroy_texture_graphic (medals_screen_texture);

			medals_screen_texture = NULL;
		}

		if (player_log_current_side == ENTITY_SIDE_BLUE_FORCE)
		{	
			set_ui_object_text (medals_title_text, get_trans("US"));

			medals_screen_texture = create_texture_graphic ( "graphics\\ui\\cohokum\\medalsUS.psd" );

			set_ui_object_drawable (russian_area, FALSE);
			
			set_ui_object_drawable (us_area, TRUE);
			
			// create medal texture graphic objects, except MEDAL_TYPE_NONE
			for (i = 1; i < NUMBER_OF_MEDAL_GRAPHICS; i++)
			{
				medal_graphics [i] = create_texture_graphic (us_medal_graphic_array[i].name);

				set_ui_object_texture_graphic (us_medal_objects [i], medal_graphics [i]);
			}

			medal_graphics [0] = NULL;
			
			// set medal states
			set_medal_states (us_medal_objects);
		}
		else
		{
			set_ui_object_text (medals_title_text, get_trans("Russian"));

			medals_screen_texture = create_texture_graphic ( "graphics\\ui\\cohokum\\medalsSV.psd" );

			set_ui_object_drawable (russian_area, TRUE);
			
			set_ui_object_drawable (us_area, FALSE);

			// create medal texture graphic objects, except MEDAL_TYPE_NONE
			for (i = 1; i < NUMBER_OF_MEDAL_GRAPHICS; i++)
			{			
				medal_graphics [i] = create_texture_graphic (russian_medal_graphic_array[i].name);

				set_ui_object_texture_graphic (russian_medal_objects [i], medal_graphics [i]);
			}
			
			medal_graphics [0] = NULL;
			
			// set medal states
			set_medal_states (russian_medal_objects);	
		}

		set_ui_object_texture_graphic (player_medals_screen, medals_screen_texture);
	
		recursively_set_object_time (player_medals_screen, MEDALS_AREA_FADE_TIME, MEDALS_AREA_OFFSET_TIME);

		reset_time_values (player_medals_screen);

		blit_front_buffer_to_render_buffer ();
	}
	else
	{

		if (medals_screen_texture )
		{	
			for (i = 1; i < NUMBER_OF_MEDAL_GRAPHICS; i++)
			{
				destroy_texture_graphic (medal_graphics [i]);
	
				medal_graphics [i] = NULL;
			}
	
			destroy_texture_graphic (medals_screen_texture);

			medals_screen_texture = NULL;
		}
	}

	#if DEBUG_MODULE
		debug_filtered_log("Inside show_medals_screen");
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_medals_page_objects (void)
{
	ui_object
		*temp_obj,
		*option_bdrop;

	float
		x1,
		y1,
		x2,
		y2;

	/////////////////////////////////////////////////////////////////
	// medal Log Area

	x1 = 0.0;
	y1 = 0.0;
	x2 = 1.0;
	y2 = 1.0;

   player_medals_screen = create_ui_object
									(
										UI_TYPE_SCREEN,
										UI_ATTR_VIRTUAL_POSITION (x1, y1),
										UI_ATTR_VIRTUAL_SIZE (x2, y2),
										UI_ATTR_COLOUR_START (255, 255, 255,0),
										UI_ATTR_COLOUR_END (255,255,255,255),
										UI_ATTR_TIME_LENGTH (500),
										UI_ATTR_OFFSET_TIME (0),
										UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
										UI_ATTR_FUNCTION (notify_medals_screen),
										UI_ATTR_END
									);

   medals_title_text = create_ui_object
            (
               UI_TYPE_TEXT,
               UI_ATTR_PARENT (player_medals_screen),
					UI_ATTR_TIME_LENGTH (0),
					UI_ATTR_OFFSET_TIME (0),
               UI_ATTR_VIRTUAL_POSITION (TITLE_TEXT_POSITION_X, TITLE_TEXT_POSITION_Y),
					UI_ATTR_VIRTUAL_SIZE (TITLE_TEXT_WIDTH, TITLE_TEXT_HEIGHT),
					UI_ATTR_TEXT (""),
					UI_ATTR_FONT_TYPE (UI_FONT_IMPACT_22),
					UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_BOTTOM),
               UI_ATTR_FONT_COLOUR_START (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 0),
               UI_ATTR_FONT_COLOUR_END (ui_screen_title_text_colour.r, ui_screen_title_text_colour.g, ui_screen_title_text_colour.b, 255),
					UI_ATTR_HIGHLIGHTABLE (FALSE),
					UI_ATTR_CLEAR (TRUE),
               UI_ATTR_END
            );

	/////////////////////////////////////////////////////////////////
	// Medal Text Areas

	x1 = 0.096;
	y1 = 0.905;
//	x2 = 0.508;
	x2 = 0.808;
	y2 = 0.052;

   medals_text_name = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (player_medals_screen),
		UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_18),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	x1 = 0.086;
	y1 = 0.958;
//	x2 = 0.628;
	x2 = 0.828;
	y2 = 0.034;

   medals_text_info = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (player_medals_screen),
		UI_ATTR_FONT_TYPE (UI_FONT_ARIAL_14),
		UI_ATTR_VIRTUAL_POSITION (x1, y1),
		UI_ATTR_VIRTUAL_SIZE (x2, y2),
      UI_ATTR_FONT_COLOUR_START (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 0),
      UI_ATTR_FONT_COLOUR_END (ui_option_title_text_colour.r, ui_option_title_text_colour.g, ui_option_title_text_colour.b, 255),
		UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_CENTRE),
		UI_ATTR_TEXT (""),
		UI_ATTR_CLEAR (TRUE),
		UI_ATTR_END
	);

	/////////////////////////////////////////////////////////////////
	// Medals

	define_us_medal_objects ();

	define_russian_medal_objects ();

	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	// Ok Button

	option_bdrop = create_ui_object
	(
		UI_TYPE_AREA,
		UI_ATTR_PARENT (player_medals_screen),
		UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
		UI_ATTR_VIRTUAL_SIZE (TEXT_OPTION_BDROP_WIDTH, TEXT_OPTION_BDROP_HEIGHT),
		UI_ATTR_COLOUR_START (255, 255, 255, 255),
		UI_ATTR_COLOUR_END (255, 255, 255, 255),
		UI_ATTR_TEXTURE_GRAPHIC (text_option_bdrop),
		UI_ATTR_END
	);

	temp_obj = create_ui_object
			(
				UI_TYPE_BUTTON,
				UI_ATTR_PARENT (player_medals_screen),
				UI_ATTR_VIRTUAL_POSITION (OPTIONS_OK_BUTTON_POS_X, OPTIONS_OK_BUTTON_POS_Y),
				UI_ATTR_VIRTUAL_SIZE (OPTIONS_OK_BUTTON_X, OPTIONS_OK_BUTTON_Y),
				UI_ATTR_TEXT (get_trans("UI_OK")),
				UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
				UI_ATTR_FUNCTION (notify_medals_screen_exit_button),
				UI_ATTR_FONT_TYPE (UI_FONT_THICK_ITALIC_ARIAL_18),
				UI_ATTR_TEXT_JUSTIFY (TEXT_JUSTIFY_LEFT_CENTRE),
		      UI_ATTR_FONT_COLOUR_START (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 0),
   		   UI_ATTR_FONT_COLOUR_END (ui_option_text_default_colour.r, ui_option_text_default_colour.g, ui_option_text_default_colour.b, 255),
      		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_START (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 0),
      		UI_ATTR_HIGHLIGHTED_FONT_COLOUR_END (ui_option_text_hilite_colour.r, ui_option_text_hilite_colour.g, ui_option_text_hilite_colour.b, 255),
				UI_ATTR_HIGHLIGHTABLE (TRUE),
				UI_ATTR_CLEAR (TRUE),
				UI_ATTR_END
			);
			
	// special case - reduce option bdrop width so it doesn't overlap the medal shadow on russian page...

	set_text_option_backdrop_object (option_bdrop, temp_obj);

	set_ui_object_x_size (option_bdrop, 0.336);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_us_medal_objects (void)
{

	int
		i;

	// don't bother with text for object MEDAL_TYPE_NONE
	
	us_medal_info_array[MEDAL_SAUDI].name = get_trans ("Medal Saudi");
	us_medal_info_array[MEDAL_SAUDI].info = get_trans ("Medal Campaign");

	us_medal_info_array[MEDAL_LEBANON].name = get_trans ("Medal Lebanon");
	us_medal_info_array[MEDAL_LEBANON].info =	get_trans ("Medal Campaign");

	us_medal_info_array[MEDAL_TAIWAN].name = get_trans ("Medal Taiwan");
	us_medal_info_array[MEDAL_TAIWAN].info = get_trans ("Medal Campaign");

	us_medal_info_array[MEDAL_ARMY_AVIATOR].name = get_trans ("Medal Army Wings");
	us_medal_info_array[MEDAL_ARMY_AVIATOR].info = get_trans ("Medal Army Aviator");

	us_medal_info_array[MEDAL_SENIOR_AVIATOR].name = get_trans ("Medal Senior Wings");
	us_medal_info_array[MEDAL_SENIOR_AVIATOR].info = get_trans ("Medal Senior Aviator");

	us_medal_info_array[MEDAL_MASTER_AVIATOR].name = get_trans ("Medal Master Wings");
	us_medal_info_array[MEDAL_MASTER_AVIATOR].info = get_trans ("Medal Master Aviator");

	us_medal_info_array[MEDAL_PURPLE_HEART].name = get_trans ("Medal Purple");
	us_medal_info_array[MEDAL_PURPLE_HEART].info = get_trans ("Medal Injury");

	us_medal_info_array[MEDAL_AIR_MEDAL].name = get_trans ("Medal Air");
	us_medal_info_array[MEDAL_AIR_MEDAL].info = get_trans ("Medal Valour");

	us_medal_info_array[MEDAL_FLYING_CROSS].name = get_trans ("Medal Distinguished");
	us_medal_info_array[MEDAL_FLYING_CROSS].info = get_trans ("Medal Valour");

	us_medal_info_array[MEDAL_SILVER_STAR].name = get_trans ("Medal Silver");
	us_medal_info_array[MEDAL_SILVER_STAR].info = get_trans ("Medal Valour");

	us_medal_info_array[MEDAL_DISTINGUISHED_SERVICE].name = get_trans ("Medal Service");
	us_medal_info_array[MEDAL_DISTINGUISHED_SERVICE].info = get_trans ("Medal Valour");

	us_medal_info_array[MEDAL_MEDAL_OF_HONOUR].name = get_trans ("Medal Honour");
	us_medal_info_array[MEDAL_MEDAL_OF_HONOUR].info = get_trans ("Medal Valour");

	/////////////////////////////////////////////////////////////////
	// Medals Areas

	us_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (player_medals_screen),
			UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
			UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
			UI_ATTR_COLOUR_START (255,255,255,0),
			UI_ATTR_COLOUR_END (255,255,255,255),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	// create basic medal ui objects
	for (i = 0; i < NUMBER_OF_MEDAL_GRAPHICS; i++)
	{
		us_medal_objects [i] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (us_area),
			UI_ATTR_VIRTUAL_POSITION (us_medal_graphic_array[i].x1, us_medal_graphic_array[i].y1),
			UI_ATTR_VIRTUAL_SIZE (us_medal_graphic_array[i].x2, us_medal_graphic_array[i].y2),
			UI_ATTR_COLOUR_START (255,255,255,0),
			UI_ATTR_COLOUR_END (255,255,255,255),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_END
		);

	}

	// create highlight areas
	
	for (i = MEDAL_TYPE_NONE; i < NUM_MEDAL_TYPES; i++)
	{
		create_ui_object
				(
					UI_TYPE_AREA,
					UI_ATTR_PARENT (us_area),
					UI_ATTR_VIRTUAL_POSITION (us_medal_info_array [i].x1, us_medal_info_array [i].y1),
					UI_ATTR_VIRTUAL_SIZE (us_medal_info_array [i].x2, us_medal_info_array [i].y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_ITEM_NUMBER ( i ),
					UI_ATTR_ASSOCIATION (medals_text_info),
					UI_ATTR_HIGHLIGHTED_FUNCTION (highlight_us_medal_info),
					UI_ATTR_HIGHLIGHTED_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
#if DEBUG_MODULE
					UI_ATTR_FUNCTION (notify_award_clicked_medal),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
#endif
					UI_ATTR_END
	
				);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void define_russian_medal_objects (void)
{
	int
		i;
	
	// don't bother with text for object MEDAL_TYPE_NONE

	russian_medal_info_array [MEDAL_LEBANON].name = get_trans ("Medal SV Lebanon");
	russian_medal_info_array [MEDAL_LEBANON].info = get_trans ("Medal Campaign");

	russian_medal_info_array [MEDAL_SAUDI].name = get_trans ("Medal SV Yemen");
	russian_medal_info_array [MEDAL_SAUDI].info = get_trans ("Medal Campaign");

	russian_medal_info_array [MEDAL_TAIWAN].name = get_trans ("Medal SV Taiwan");
	russian_medal_info_array [MEDAL_TAIWAN].info = get_trans ("Medal Campaign");

	russian_medal_info_array [MEDAL_ARMY_AVIATOR].name = get_trans ("Medal SV Army Wings");
	russian_medal_info_array [MEDAL_ARMY_AVIATOR].info = get_trans ("Medal Army Aviator");

	russian_medal_info_array [MEDAL_SENIOR_AVIATOR].name = get_trans ("Medal SV Senior Wings");
	russian_medal_info_array [MEDAL_SENIOR_AVIATOR].info = get_trans ("Medal Senior Aviator");

	russian_medal_info_array [MEDAL_MASTER_AVIATOR].name = get_trans ("Medal SV Master Wings");
	russian_medal_info_array [MEDAL_MASTER_AVIATOR].info = get_trans ("Medal Master Aviator");

	russian_medal_info_array [MEDAL_PURPLE_HEART].name = get_trans ("Medal SV Glory");
	russian_medal_info_array [MEDAL_PURPLE_HEART].info = get_trans ("Medal Injury");

	russian_medal_info_array [MEDAL_AIR_MEDAL].name = get_trans ("Medal SV Banner");
	russian_medal_info_array [MEDAL_AIR_MEDAL].info = get_trans ("Medal Valour");

	russian_medal_info_array [MEDAL_FLYING_CROSS].name = get_trans ("Medal SV Lenin");
	russian_medal_info_array [MEDAL_FLYING_CROSS].info = get_trans ("Medal Valour");

	russian_medal_info_array [MEDAL_SILVER_STAR].name = get_trans ("Medal SV Service");
	russian_medal_info_array [MEDAL_SILVER_STAR].info = get_trans ("Medal Valour");

	russian_medal_info_array [MEDAL_DISTINGUISHED_SERVICE].name = get_trans ("Medal SV Victory");
	russian_medal_info_array [MEDAL_DISTINGUISHED_SERVICE].info = get_trans ("Medal Valour");

	russian_medal_info_array [MEDAL_MEDAL_OF_HONOUR].name = get_trans ("Medal SV Star");
	russian_medal_info_array [MEDAL_MEDAL_OF_HONOUR].info = get_trans ("Medal Valour");

	/////////////////////////////////////////////////////////////////
	// Medals Areas

	russian_area = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (player_medals_screen),
			UI_ATTR_VIRTUAL_POSITION (0.0, 0.0),
			UI_ATTR_VIRTUAL_SIZE (1.0, 1.0),
			UI_ATTR_COLOUR_START (255,255,255,0),
			UI_ATTR_COLOUR_END (255,255,255,255),
			UI_ATTR_DRAWABLE (FALSE),
			UI_ATTR_CLEAR (TRUE),
			UI_ATTR_END
		);

	// create basic medal ui objects
	for (i = 0; i < NUMBER_OF_MEDAL_GRAPHICS; i++)
	{
		russian_medal_objects [i] = create_ui_object
		(
			UI_TYPE_AREA,
			UI_ATTR_PARENT (russian_area),
			UI_ATTR_VIRTUAL_POSITION (russian_medal_graphic_array[i].x1, russian_medal_graphic_array[i].y1),
			UI_ATTR_VIRTUAL_SIZE (russian_medal_graphic_array[i].x2, russian_medal_graphic_array[i].y2),
			UI_ATTR_COLOUR_START (255,255,255,0),
			UI_ATTR_COLOUR_END (255,255,255,255),
			UI_ATTR_END
		);
	}

	// create highlight areas
	
	for (i = MEDAL_TYPE_NONE; i < NUM_MEDAL_TYPES; i++)
	{
		create_ui_object
				(
					UI_TYPE_AREA,
					UI_ATTR_PARENT (russian_area),
					UI_ATTR_VIRTUAL_POSITION (russian_medal_info_array [i].x1, russian_medal_info_array [i].y1),
					UI_ATTR_VIRTUAL_SIZE (russian_medal_info_array [i].x2, russian_medal_info_array [i].y2),
					UI_ATTR_CLEAR (TRUE),
					UI_ATTR_HIGHLIGHTABLE (TRUE),
					UI_ATTR_ITEM_NUMBER ( i ),
					UI_ATTR_ASSOCIATION (medals_text_info),
					UI_ATTR_HIGHLIGHTED_FUNCTION (highlight_russian_medal_info),
					UI_ATTR_HIGHLIGHTED_NOTIFY_ON (NOTIFY_TYPE_BUTTON_EITHER),
#if DEBUG_MODULE
					UI_ATTR_FUNCTION (notify_award_clicked_medal),
					UI_ATTR_NOTIFY_ON (NOTIFY_TYPE_BUTTON_UP),
#endif
					UI_ATTR_END
	
				);
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_medals_screen_exit_button (ui_object *obj, void *arg)
{

	obj;
	arg;

	if ((int) arg == BUTTON_STATE_DOWN)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_SELECTED));
	}
	else if ((int) arg == BUTTON_STATE_UP)
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		set_ui_object_redraw (player_medals_screen, TRUE);

		pop_ui_screen (SCREEN_POP_ACTUAL);
	}
	else 
	{

		set_ui_object_graphic (obj, (unsigned short int *) get_graphics_file_data (GRAPHICS_UI_APACHE_PLANNER_BACK_BUTTON_UNSELECTED));

		set_ui_object_redraw (player_medals_screen, TRUE);
	}

	set_ui_object_graphic_type (obj, UI_OBJECT_ALPHA_GRAPHIC);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void medals_highlight_off_function (ui_object *obj)
{

	set_ui_object_text (obj, "");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void highlight_us_medal_info (ui_object *obj, void *arg)
{

	player_log_type
		*player;
		
	char
		name_text [128],
		info_text [128];

	int
		medal_number,
		medal_count;

	player = get_current_player_log ();

	medal_number = get_ui_object_item_number (obj);
	
	medal_count = player->side_log [player_log_current_side].medals [medal_number];

	if (	(medal_number != MEDAL_MASTER_AVIATOR) &&
			(medal_number != MEDAL_SENIOR_AVIATOR) &&
			(medal_number != MEDAL_ARMY_AVIATOR) )
	{
		sprintf (name_text, "(%d) %s", medal_count, us_medal_info_array [medal_number].name);
	}
	else
	{
		sprintf (name_text, "%s", us_medal_info_array [medal_number].name);
	}

	sprintf (info_text, "%s", us_medal_info_array [medal_number].info);

	if ((int) arg == BUTTON_STATE_DOWN)
	{
		set_ui_object_text (medals_text_name, name_text);

		set_ui_object_text (medals_text_info, info_text);
	}
	else
	{
		set_ui_object_text (medals_text_name, "");

		set_ui_object_text (medals_text_info, "");
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void highlight_russian_medal_info (ui_object *obj, void *arg)
{

	player_log_type
		*player;
		
	char
		name_text [128],
		info_text [128];

	int
		medal_number,
		medal_count;

	player = get_current_player_log ();

	medal_number = get_ui_object_item_number (obj);

	medal_count = player->side_log [player_log_current_side].medals [medal_number];

	if (	(medal_number != MEDAL_MASTER_AVIATOR) &&
			(medal_number != MEDAL_SENIOR_AVIATOR) &&
			(medal_number != MEDAL_ARMY_AVIATOR) )
	{
		sprintf (name_text, "(%d) %s", medal_count, russian_medal_info_array [medal_number].name);
	}
	else
	{
		sprintf (name_text, "%s", russian_medal_info_array [medal_number].name);
	}

	sprintf (info_text, "%s", russian_medal_info_array [medal_number].info);

	if ((int) arg == BUTTON_STATE_DOWN)
	{
		set_ui_object_text (medals_text_name, name_text);

		set_ui_object_text (medals_text_info, info_text);
	}
	else
	{
		set_ui_object_text (medals_text_name, "");

		set_ui_object_text (medals_text_info, "");
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// debug function to award medals if clicked on in player log //

#if DEBUG_MODULE

void notify_award_clicked_medal (ui_object *obj, void *arg)
{
	player_log_type
		*player;

	int
		*medals,
		medal_number,
		graphic_number;
		
	player = get_current_player_log ();

	medals = player->side_log[player_log_current_side].medals;

	medal_number = graphic_number = get_ui_object_item_number (obj);

	// account for double graphics on last 2 medals
	if (graphic_number == 10)
	{
		graphic_number = 11;
	}
	else if (graphic_number == 11)
	{
		graphic_number = 13;
	}
	
	if (player_log_current_side == ENTITY_SIDE_RED_FORCE)
	{
		if (medals [medal_number] == 0)
		{
			set_ui_object_drawable (us_medal_objects [graphic_number], TRUE);
	
			medals [medal_number] = 1;
		}
		else
		{
			set_ui_object_drawable (us_medal_objects [graphic_number], FALSE);
	
			medals [medal_number] = 0;
		}
	}
	else
	{
		if (medals [medal_number] == 0)
		{
			set_ui_object_drawable (russian_medal_objects [graphic_number], TRUE);
	
			medals [medal_number] = 1;
		}
		else
		{
			set_ui_object_drawable (russian_medal_objects [graphic_number], FALSE);
	
			medals [medal_number] = 0;
		}
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int award_aviator_wings (int side)
{
	player_log_type
		*player;

	int
		*medals,
		medal_type,
		award_medal;

	float
		hours;

	ASSERT ((side >= 0) && (side <= NUM_ENTITY_SIDES));

	award_medal = 1;
	
	player = get_current_player_log ();

	medals = player->side_log[side].medals;

	hours = get_player_log_flying_seconds (side, player) / ONE_HOUR;

	if (hours >= MEDAL_HOURS_TO_BECOME_MASTER_AVIATOR)
	{
		medal_type = MEDAL_MASTER_AVIATOR;
	}
	else if (hours >= MEDAL_HOURS_TO_BECOME_SENIOR_AVIATOR)
	{
		medal_type = MEDAL_SENIOR_AVIATOR;
	}
	else if (hours >= MEDAL_HOURS_TO_BECOME_ARMY_AVIATOR)
	{
		medal_type = MEDAL_ARMY_AVIATOR;
	}
	else
	{
		award_medal = 0;
	}

	// aviator badges only awarded once

	if (award_medal)
	{
		if (medals [medal_type])
		{
			return MEDAL_TYPE_NONE;
		}
		else
		{
			medals [medal_type] = 1;
	
			return medal_type;
		}
	}
	else
	{
		return MEDAL_TYPE_NONE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void award_campaign_medal (int side, int medal)
{
	
	player_log_type
		*player;

	int
		*medals;
		
	ASSERT ((side >= 0) && (side <= NUM_ENTITY_SIDES));

	player = get_current_player_log ();
	
	medals = player->side_log [side].medals;
	
	if ((medal > MEDAL_TYPE_NONE) && (medal <= MEDAL_TAIWAN))
	{
		medals [medal] += 1;
	}

	#if DEBUG_MEDALS

	// clear medals
	memset (medals, 0, sizeof (int) * (NUM_MEDAL_TYPES - 1));

	if (check_key (DIK_F1))
	{
		medals [MEDAL_SAUDI] = 1;
	}

	if (check_key (DIK_F2))
	{
		medals [MEDAL_LEBANON] = 1;
	}

	if (check_key (DIK_F3))
	{
		medals [MEDAL_TAIWAN] = 1;
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int query_award_medal (player_log_type *log, int *medals, player_medal_criteria *criteria, int medal_type, int side)
{
	//
	// ensure players rank is high enough
	//
	
	if (criteria->pilot_rank > log->side_log[side].rank)
	{
		return FALSE;
	}

	//
	// test to see if the log has enough flight hours
	//

	if (criteria->wings_medal != MEDAL_TYPE_NONE)
	{
		if (!(medals [criteria->wings_medal]))
		{
			return FALSE;
		}
	}

	//
	// test for enough campaign medals
	//

	if (criteria->num_campaign_medals)
	{
		int
			num_medals;

		num_medals = 0;

		num_medals += medals [MEDAL_SAUDI];

		num_medals += medals [MEDAL_LEBANON];

		num_medals += medals [MEDAL_TAIWAN];

		if (num_medals < criteria->num_campaign_medals)
		{
			return FALSE;
		}
	}

	//
	// test for medal required
	//

	if (criteria->medal_required != MEDAL_TYPE_NONE)
	{
		int
			num_medals_required;

		num_medals_required = (medals [medal_type] + 1) * criteria->medal_multiplier;

		if (medals [criteria->medal_required] < num_medals_required)
		{
			return FALSE;
		}
	}

	return TRUE;	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int award_valour_medal (int side, int points)
{

	player_log_type
		*player;

	player_medal_criteria
		*criteria;

	int
		*medals,
		award,
		i;

	medal_types
		medal_type;

	// find out which medal the mission points qualify the player for

	ASSERT ((side >= 0) && (side <= NUM_ENTITY_SIDES));

	i = award = 0;
	
	player = get_current_player_log ();

	medals = player->side_log[side].medals;

	criteria = valour_medal_award_criteria;

	medal_type = MEDAL_MEDAL_OF_HONOUR;

	while ((!award) && (i < NUMBER_OF_VALOUR_MEDALS))
	{
		if (points > criteria->points_req)
		{
			award = query_award_medal (player, medals, criteria, medal_type, side);
		}

		if (!award)
		{
			i++;
	
			criteria++;
	
			medal_type = (medal_types)((int)medal_type - 1);
		}
	}

	if (award)
	{
		medals [medal_type] += 1;

		return medal_type;
	}
	else
	{
		return MEDAL_TYPE_NONE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// awards purple heart if player lands helicopter when damaged

int award_purple_heart_medal (int side)
{
	player_log_type
		*player;

	int
		*medals,
		damage;

	ASSERT ((side >= 0) && (side <= NUM_ENTITY_SIDES));

	player = get_current_player_log ();

	medals = player->side_log[side].medals;

	// get helicopter damage

	damage = get_dynamics_damage_type (DYNAMICS_DAMAGE_MAIN_ROTOR |
													DYNAMICS_DAMAGE_TAIL_ROTOR |
													DYNAMICS_DAMAGE_LEFT_ENGINE |
													DYNAMICS_DAMAGE_RIGHT_ENGINE |
													DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE |
													DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE |
													DYNAMICS_DAMAGE_LOW_HYDRAULICS |
													DYNAMICS_DAMAGE_LOW_OIL_PRESSURE |
													DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE |
													DYNAMICS_DAMAGE_STABILISER);

	if ((get_gunship_entity ()) && (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE)))
	{
		if (damage)
		{
			medals [MEDAL_PURPLE_HEART] += 1;
	
			#if DEBUG_MODULE

			debug_filtered_log ("Awarded Purple Heart Medal");

			#endif
	
			return MEDAL_PURPLE_HEART;
		}
	}

	#if DEBUG_MODULE

	debug_filtered_log ("Purple Heart Medal Not Awarded");	

	#endif

	return MEDAL_TYPE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// awards air medal if player gets a hat-trick of successful missons

int award_air_medal_medal (int side, int success)
{
	player_log_type
		*player;
	
	int
		*medals;
	
	ASSERT ((side >= 0) && (side <= NUM_ENTITY_SIDES));
	
	player = get_current_player_log ();
	
	medals = player->side_log[side].medals;
	
	if (success)
	{
		player->side_log [side].air_medal_counter++;
		
		if (player->side_log [side].air_medal_counter >= NUM_NEEDED_TO_AWARD_AIR_MEDAL)
		{
			medals [MEDAL_AIR_MEDAL] += 1;
			
			player->side_log [side].air_medal_counter = 0;
			
			#if DEBUG_MODULE

			debug_filtered_log ("Awarded Air Medal, reset counter");

			#endif
			
			return MEDAL_AIR_MEDAL;
		}
		else
		{
			#if DEBUG_MODULE

			debug_filtered_log ("Air Medal Not Awarded (count = %d)", player->side_log[side].air_medal_counter);

			#endif
			
			return MEDAL_TYPE_NONE;
		}
	}
	else
	{
		#if DEBUG_MODULE

		debug_filtered_log ("Air Medal Not Awarded: resetting	air_medal_counter");

		#endif
		
		player->side_log [side].air_medal_counter = 0;
	}
	
	return MEDAL_TYPE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int award_player_rank (int side)
{
	player_log_type
		*player;

	int
		new_rank;

	ASSERT ((side >= 0) && (side <= NUM_ENTITY_SIDES));

	player = get_current_player_log ();

	new_rank = get_player_rank_from_points (player->side_log[side].experience);

	if (new_rank != player->side_log[side].rank)
	{
		player->side_log[side].rank = new_rank;

		return new_rank;
	}
	else
	{
		return PILOT_RANK_NONE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


