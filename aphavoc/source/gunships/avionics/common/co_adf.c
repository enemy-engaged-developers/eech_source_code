/*
 * co_adf.c
 *
 *  Created on: 27.sep.2009
 *      Author: arneh
 */

#include "project.h"

#include "co_adf.h"

#define MAX_TRANSMITTERS 32
#define MAX_INSTRUMENT_TRANSMITTERS 10

#define MAX_ADF_RANGE  (40000.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static ndb_transmitter transmitters[NUM_ENTITY_SIDES][MAX_TRANSMITTERS];
static ndb_instrument_transmitter instrument_transmitters[MAX_INSTRUMENT_TRANSMITTERS];

static unsigned number_of_transmitters[NUM_ENTITY_SIDES];

static unsigned current_frequency, last_frequency;
static unsigned adf_enabled, play_adf_tone, has_signal;
static ndb_transmitter* current_ndb_transmitter;
static ndb_instrument_transmitter* current_instrument_transmitter, *last_instrument_transmitter;
static adf_modes current_adf_mode;

static float test_timer = 0.0;

// Frequencies we'll use
static unsigned frequency_list[MAX_TRANSMITTERS] =
{
	195000,
	301000,
	248000,
	384000,
	212000,
	492000,
	288000,
	520000,

	451000,
	361000,
	271000,
	404000,
	262000,
	390000,
	414000,
	303000,

	281000,
	248000,
	310000,
	397000,
	286000,
	276000,
	468000,
	343000,

	276000,
	258000,
	398000,
	427000,
	275000,
	361000,
	199000,
	262000
};

static const char* num_morse_codes[] =
{
	"-----",	// 0
	".----",	// 1
	"..---", 	// 2
	"...--",	// 3
	"....-",	// 4
	".....",	// 5
	"-....", 	// 6
	"--...",	// 7
	"---..",	// 8
	"----.",	// 9
};

static const char* alpha_morse_codes[] =
{
	".-", 		// A
	"-...", 	// B
	"-.-.",		// C
	"-..",		// D
	".",		// E
	"..-.",		// F
	"--.",		// G
	"....",		// H
	"..",		// I
	".---",		// J
	"-.-",		// K
	".-..",		// L
	"--",		// M
	"-.",		// N
	"---",		// O
	".--.",		// P
	"--.-",		// Q
	".-.",		// R
	"...",		// S
	"-",		// T
	"..-",		// U
	"...-",		// V
	".--",		// W
	"-..-",		// X
	"-.--",		// Y
	"--..",		// Z
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialize_common_adf(void)
{
	entity* en;
	entity_sides own_side = get_local_entity_int_value(get_gunship_entity(), INT_TYPE_SIDE);
	unsigned next_instr_channel = 0;

	memset(number_of_transmitters, 0, sizeof(number_of_transmitters));

	current_ndb_transmitter = NULL;
	current_instrument_transmitter = last_instrument_transmitter = NULL;
	current_frequency = last_frequency = 0;

	current_adf_mode = ADF_MODE_ADF;
	play_adf_tone = FALSE;
	adf_enabled = !command_line_dynamics_engine_startup;

	memset(transmitters, 0, sizeof(transmitters));
	memset(instrument_transmitters, 0, sizeof(instrument_transmitters));

	// Iterate through all airbases and carriers and add one NDB transmitter to each
	// Use separate lists for each side
	en = get_local_entity_first_child (get_update_entity (), LIST_TYPE_UPDATE);
	while (en)
	{
		entity_sub_types sub_type = get_local_entity_int_value(en, INT_TYPE_ENTITY_SUB_TYPE);

		set_update_succ (get_local_entity_child_succ (en, LIST_TYPE_UPDATE));

		if (en->type == ENTITY_TYPE_KEYSITE && (sub_type == ENTITY_SUB_TYPE_KEYSITE_AIRBASE || sub_type == ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE))
		{
			const char* name = get_local_entity_string(en, STRING_TYPE_KEYSITE_NAME);

			if (name)
			{
				entity_sides side = get_local_entity_int_value(en, INT_TYPE_SIDE);
				int is_first_char = TRUE;
				const char* c;
				char* morse_buffer;
				char* name_buffer;
				unsigned ind = number_of_transmitters[side];

				if (ind >= MAX_TRANSMITTERS)
				{
					ASSERT(FALSE);
					continue;
				}

				// skip USS prefix for ship names
				if (strncmp(name, "USS", 3) == 0)
					name += 3;

				transmitters[side][ind].en = en;
				transmitters[side][ind].radio_frequency = frequency_list[ind];

				// Use 3 first letters of name as code (skipping spaces)
				// The morse code is the code for each of those letters
				name_buffer = &transmitters[side][ind].code;
				morse_buffer = &transmitters[side][ind].morse_code;
				for (c = name; *c; c++)
				{
					const char* code;
					if (*c >= '0' && *c <= '9')
						code = num_morse_codes[*c - '0'];
					else if (toupper(*c) >= 'A' && toupper(*c) <= 'Z')
						code = alpha_morse_codes[toupper(*c) - 'A'];
					else
						continue;

					*name_buffer = toupper(*c);
					name_buffer++;

					if (is_first_char)
					{
						sprintf(morse_buffer, "%s", code);
						morse_buffer += strlen(code);
					}
					else
					{
						sprintf(morse_buffer, " %s", code);
						morse_buffer += strlen(code) + 1;
					}

					if (name_buffer - &transmitters[side][ind].code >= 3)
						break;

					is_first_char = FALSE;
				}
				*name_buffer = 0;
				*morse_buffer = 0;
				ASSERT(strlen(transmitters[side][ind].code) < 4);
				ASSERT(strlen(transmitters[side][ind].morse_code) < sizeof(transmitters[side][ind].morse_code));

				// Copy first ten transmitters for side to the instruments
				if (side == own_side)
				{
					instrument_transmitters[next_instr_channel].transmitter = &transmitters[side][ind];
					strcpy(instrument_transmitters[next_instr_channel].code, transmitters[side][ind].code);
					strcpy(instrument_transmitters[next_instr_channel].morse_code, transmitters[side][ind].morse_code);
					instrument_transmitters[next_instr_channel].radio_frequency = transmitters[side][ind].radio_frequency;

					next_instr_channel++;
				}

				number_of_transmitters[side]++;
			}
		}
		en = get_update_succ ();
	}

	set_update_succ (NULL);
}

void update_common_adf(void)
{
	has_signal = FALSE;

	// Check if we have signal
	if (adf_enabled && current_ndb_transmitter)
	{
		vec3d
			*own_pos = get_local_entity_vec3d_ptr(get_gunship_entity(), VEC3D_TYPE_POSITION),
			*to_pos = get_transmitter_position(current_ndb_transmitter);

		if (get_sqr_2d_range(own_pos, to_pos) < (MAX_ADF_RANGE * MAX_ADF_RANGE))
		{
			has_signal = get_los_clear(NULL, own_pos, to_pos);
		}
	}

	if (test_timer > 0.0)
		test_timer -= get_delta_time();

	// TODO: use separate sound channel
	if (play_adf_tone && has_signal)
		resume_local_entity_sound_type(get_gunship_entity(), ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED);
	else
		pause_local_entity_sound_type(get_gunship_entity(), ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED, 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_adf_enabled(void)
{
	return adf_enabled;
}

void toggle_adf_enabled(void)
{
	adf_enabled = !adf_enabled;
}

void toggle_adf_tone(void)
{
	play_adf_tone = !play_adf_tone;
}

int get_adf_tone_enabled(void)
{
	return play_adf_tone;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ndb_transmitter* get_ndb_transmitter_from_frequency(unsigned frequency)
{
	entity_sides side = get_local_entity_int_value(get_gunship_entity(), INT_TYPE_SIDE);
	unsigned i;

	for (i=0; i < number_of_transmitters[side]; i++)
		if (transmitters[side][i].radio_frequency == frequency)
			return &transmitters[side][i];

	return NULL;
}

ndb_instrument_transmitter* get_instrument_transmitters(unsigned* ntransmitters)
{
	entity* source = get_gunship_entity ();

	*ntransmitters = MAX_INSTRUMENT_TRANSMITTERS;
	return instrument_transmitters;
}

vec3d* get_transmitter_position(ndb_transmitter* transmitter)
{
	return get_local_entity_vec3d_ptr(transmitter->en, VEC3D_TYPE_POSITION);
}

ndb_instrument_transmitter* get_current_adf_station(void)
{
	return current_instrument_transmitter;
}

void set_current_adf_station(ndb_instrument_transmitter* transmitter)
{
	if (transmitter == current_instrument_transmitter)
		return;

	last_instrument_transmitter = current_instrument_transmitter;
	last_frequency = current_frequency;

	current_instrument_transmitter = transmitter;
	if (transmitter)
	{
		current_frequency = transmitter->radio_frequency;
		current_ndb_transmitter = get_ndb_transmitter_from_frequency(current_frequency);
	}
	else
	{
		current_frequency = 0;
		current_ndb_transmitter = NULL;
	}
}

void swap_to_last_adf_frequency(void)
{
	ndb_instrument_transmitter* temp_trans = current_instrument_transmitter;
	unsigned temp_freq = current_frequency;

	current_instrument_transmitter = last_instrument_transmitter;
	current_frequency = last_frequency;

	last_instrument_transmitter = temp_trans;
	last_frequency = temp_freq;

	if (current_instrument_transmitter)
		current_ndb_transmitter = current_instrument_transmitter->transmitter;
	else
		current_ndb_transmitter = get_ndb_transmitter_from_frequency(current_frequency);
}

unsigned get_current_adf_frequency(void)
{
	return current_frequency;
}

void set_current_adf_frequency(unsigned frequency)
{
	if (frequency == current_frequency)
		return;

	last_instrument_transmitter = current_instrument_transmitter;
	last_frequency = current_frequency;

	current_frequency = frequency;
	current_ndb_transmitter = get_ndb_transmitter_from_frequency(frequency);
	current_instrument_transmitter = NULL;
}

adf_modes get_adf_mode(void)
{
	return current_adf_mode;
}

void set_adf_mode(adf_modes mode)
{
	current_adf_mode = mode;
}

void set_adf_test_mode(void)
{
	test_timer = 2.0;
}

int has_ndb_signal(void)
{
	return current_ndb_transmitter && has_signal;
}

int has_adf_bearing(void)
{
	return current_adf_mode == ADF_MODE_ADF && has_ndb_signal();
}

float get_adf_bearing(void)
{
	vec3d
		relative_position,
		*source_position,
		*ndb_position;

	float bearing;

	if (!adf_enabled || !current_ndb_transmitter || !current_ndb_transmitter->en || current_adf_mode != ADF_MODE_ADF)
	{
		ASSERT(FALSE);
		return 0.0;
	}

	source_position = get_local_entity_vec3d_ptr(get_gunship_entity(), VEC3D_TYPE_POSITION);
	ndb_position = get_local_entity_vec3d_ptr(current_ndb_transmitter->en, VEC3D_TYPE_POSITION);

	relative_position.x = ndb_position->x - source_position->x;
	relative_position.y = 0.0;
	relative_position.z = ndb_position->z - source_position->z;

	bearing = atan2(relative_position.x, relative_position.z);

	if (test_timer > 0.0)  // is in test mode
		bearing += rad(90.0);

	return bearing;
}
