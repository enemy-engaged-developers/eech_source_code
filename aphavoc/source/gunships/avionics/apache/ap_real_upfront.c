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

#define VIEWPORT_WIDTH		(84.0)
#define VIEWPORT_HEIGHT		(40.0)

#define LINE_LENGTH  36

#define MAX_STRING_LENGTH	(12)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	text_colour,
	clear_colour;

static screen
	*texture_screen;

static char
	warnings[5][MAX_STRING_LENGTH + 1],
	cautions[5][MAX_STRING_LENGTH + 1],
	advisories[5][MAX_STRING_LENGTH + 1];

static int
	last_warning,
	last_caution,
	last_advisory;

static const char* radio_freqs[] =
{
	"<>VH 126.950* MAN            123.000",
	"<>UH 244.800* OPS       G LI 348.000",
	"<>F1  40.250* OPS       N LI  36.550",
	"<>F2  36.550* OPS         LI  26.550",
	"2850    XP 1200    STBY  "
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_messages (float x_org, float y_org)
{
	float y = 1.0;
	int i=0;
	char buffer[64];

	set_mono_font_type(MONO_FONT_TYPE_6X10);
	set_mono_font_colour(text_colour);

	for (i=0; i<5; i++)
	{
		snprintf(buffer, LINE_LENGTH+1, "%-11s|%-11s|%-12s",
			warnings[(last_warning + i) % 5], cautions[(last_caution + i) % 5], advisories[(last_advisory + i) % 5]);

		set_mono_font_position(0.0, y);
		set_mono_font_rel_position(0.0, 0.0);

		print_mono_font_string(buffer);
		y += 10;
	}

	for (i=0; i<4; i++)
	{
		set_mono_font_position(0.0, y);
		set_mono_font_rel_position(0.0, 0.0);

		print_mono_font_string(radio_freqs[i]);
		y += 10;
	}

	{
		float hours, minutes, seconds;
		float time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
		get_digital_clock_values (time_of_day, &hours, &minutes, &seconds);

		snprintf(buffer, LINE_LENGTH+1, "%s %02d:%02d:%02d L", radio_freqs[4], (int) hours, (int) minutes, (int) seconds);

		set_mono_font_position(0.0, y);
		set_mono_font_rel_position(0.0, 0.0);

		print_mono_font_string(buffer);
	}
#if 0
	float
		x_min,
		y_min,
		x_max,
		y_max,
		y_line1,
		y_line2,
		y_line3,
		y_line4;

	if (!electrical_system_active())
		return;

	x_min = x_org;
	y_min = y_org;
	x_max = x_org + VIEWPORT_WIDTH - 0.001;
	y_max = y_org + VIEWPORT_HEIGHT - 0.001;

	set_viewport (x_min, y_min, x_max, y_max);

	y_line1 = y_org;
	y_line2 = y_org + 10.0;
	y_line3 = y_org + 20.0;
	y_line4 = y_org + 30.0;

	set_mono_font_type (MONO_FONT_TYPE_5X9);

	set_mono_font_colour (text_colour);

	set_mono_font_position (x_min, y_line1);

	print_mono_font_string (line1);

	set_mono_font_position (x_min, y_line2);

	print_mono_font_string (line2);

	set_mono_font_position (x_min, y_line3);

	print_mono_font_string (line3);

	set_mono_font_position (x_min, y_line4);

	print_mono_font_string (line4);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_upfront_display (void)
{
	texture_screen = create_system_texture_screen (256, 128, TEXTURE_INDEX_AVCKPT_DISPLAY_UPFRONT, TEXTURE_TYPE_SINGLEALPHA);

	clear_apache_upfront_display(TRUE, TRUE, TRUE);

	set_rgb_colour (text_colour, 180, 240, 0, 255);

	set_rgb_colour (clear_colour,180, 240, 0, 0);

	add_apache_advisory("BATT PWR");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_apache_upfront_display (void)
{
	destroy_screen (texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_apache_upfront_display (void)
{

//	if (!electrical_system_active())
//		return;
#if 0
	time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);

	get_digital_clock_values (time_of_day, &hours, &minutes, &seconds);

	sprintf (s1, "%02d:%02d:%02d", (int) hours, (int) minutes, (int) seconds);

	sprintf (s2, "FUEL %04d LBS", (int) (bound (kilograms_to_pounds (current_flight_dynamics->fuel_weight.value), 0.0, 2500.0)));

	set_apache_upfront_display_text (NULL, NULL, s1, s2);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_upfront_display_on_cockpit (float x_org, float y_org)
{
	if (lock_screen (active_screen))
	{
		display_messages (x_org, y_org);

		unlock_screen (active_screen);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_upfront_display_on_texture (void)
{
	set_active_screen (texture_screen);

	if (lock_screen (texture_screen))
	{
		set_block (0, 0, 255, 127, clear_colour);

		display_messages (0.0, 0.0);

//		draw_line(0.0, 0.0, 255.0, 127.0, text_colour);
//		draw_line(1.0, 1.0, -1.0, -1.0, text_colour);

		flush_screen_texture_graphics (texture_screen);

		unlock_screen (texture_screen);
	}

	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// note: NULL == do not overwrite, "" == overwrite with blank message
//

void set_apache_upfront_display_text (char *s1, char *s2, char *s3, char *s4)
{
#if 0
	if (s1)
	{
		strncpy (line1, s1, MAX_STRING_LENGTH);

		line1[MAX_STRING_LENGTH] = '\0';
	}

	if (s2)
	{
		strncpy (line2, s2, MAX_STRING_LENGTH);

		line2[MAX_STRING_LENGTH] = '\0';
	}

	if (s3)
	{
		strncpy (line3, s3, MAX_STRING_LENGTH);

		line3[MAX_STRING_LENGTH] = '\0';
	}

	if (s4)
	{
		strncpy (line4, s4, MAX_STRING_LENGTH);

		line4[MAX_STRING_LENGTH] = '\0';
	}

	if (command_line_shared_mem_export != 0)
		update_upfront_display_shared_mem(s1, s2, s3, s4); // Retro 14Aug2006
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_apache_ufd_warning(const char* warning)
{

}

void add_apache_ufd_caution(const char* warning)
{

}

void add_apache_advisory(const char* warning)
{
	last_advisory--;

	if (last_advisory < 0)
		last_advisory = 4;

	strncpy(advisories[last_advisory], warning, MAX_STRING_LENGTH+1);
	advisories[last_advisory][MAX_STRING_LENGTH] = '\0';
}

void clear_apache_upfront_display(int clear_warnings, int clear_cautions, int clear_advisories)
{
	int i;

	for (i=0; i<5; i++)
	{
		if (clear_warnings)
			warnings[i][0] = '\0';
		if (clear_cautions)
			cautions[i][0] = '\0';
		if (clear_advisories)
			advisories[i][0] = '\0';
	}

	last_warning = last_caution = last_advisory = 0;
}
