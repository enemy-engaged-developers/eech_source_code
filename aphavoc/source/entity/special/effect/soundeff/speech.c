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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_SYSTEM_QUEUE_TYPE
{
	entity
		*parent;

	entity_sub_types
		sub_type;

	speech_category_types
		category;

	sound_channel_types
		channel;

	sound_locality_types
		locality;

	vec3d
		pos;

	float
		delay,
		priority,
		expire_time,
		category_silence_timer;

	int
		sample_count;

	sound_sample_indices
		*sample_list;

	struct SPEECH_SYSTEM_QUEUE_TYPE
		*next,
		*prev;
};

typedef struct SPEECH_SYSTEM_QUEUE_TYPE speech_system_queue_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_SYSTEM_EXCLUDE_TYPE
{
	float
		timer;
};

typedef struct SPEECH_SYSTEM_EXCLUDE_TYPE speech_system_exclude_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_SYSTEM_CURRENT_TYPE
{
	float
		timer;
};

typedef struct SPEECH_SYSTEM_CURRENT_TYPE speech_system_current_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_SYSTEM_TYPE
{
	speech_system_queue_type
		*queue;

	speech_system_exclude_type
		exclude_list [NUM_SPEECH_CATEGORY_TYPES];

	speech_system_current_type
		current;
};

typedef struct SPEECH_SYSTEM_TYPE speech_system_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

speech_index_list_type
	speech_index_table[NUM_SPEECH_ARRAY_TYPES][NUM_SPEECH_ORIGINATOR_TYPES][NUM_ENTITY_SIDES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static speech_system_type
	speech_buffer [NUM_ENTITY_SIDES][NUM_SPEECH_ORIGINATOR_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	speech_sector_coordinates [6];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const sound_channel_types
	speech_originator_sound_channel_table [NUM_SPEECH_ORIGINATOR_TYPES] =
	{
		SOUND_CHANNEL_SYSTEM,							//SPEECH_ORIGINATOR_SYSTEM
		SOUND_CHANNEL_CO_PILOT,							//SPEECH_ORIGINATOR_CO_PILOT
		SOUND_CHANNEL_WINGMAN,							//SPEECH_ORIGINATOR_WINGMAN1
		SOUND_CHANNEL_WINGMAN,							//SPEECH_ORIGINATOR_WINGMAN2
		SOUND_CHANNEL_AIR_TRAFFIC_CONTROLLER,		//SPEECH_ORIGINATOR_AIR_TRAFFIC_CONTROLLER
		SOUND_CHANNEL_FORWARD_AIR_CONTROLLER,		//SPEECH_ORIGINATOR_FORWARD_AIR_CONTROLLER
		SOUND_CHANNEL_GROUND_CONTROLLER				//SPEECH_ORIGINATOR_GROUND_CONTROLLER
	};

static sound_channel_types get_speech_originator_sound_channel (speech_originator_types originator)
{
	return speech_originator_sound_channel_table [originator];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_client_server_speech_entity (entity *parent, entity_sides side, entity_sub_types sub_type, sound_channel_types channel, sound_locality_types locality, vec3d *pos, int count, sound_sample_indices *sample_list)
{
	entity
		*en;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (parent);

	ASSERT (sample_list);

	ASSERT (count >= 1);

	en = create_client_server_sound_effect_entity
	(
		parent,
		side,
		sub_type,
		channel,
		locality,
		pos,
		1.0,
		TRUE,
		FALSE,
		count,
		sample_list
	);

	return en;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int add_speech_to_list
					(
						entity *parent,
						entity_sides side,
						speech_originator_types originator,
						entity_sub_types sub_type,
						speech_category_types category,
						sound_locality_types locality,
						vec3d *pos,
						float delay,
						float priority,
						float expire_time,
						float category_silence_timer,
						int sample_count,
						sound_sample_indices *sample_list
					)
{
	speech_system_queue_type
		*queue,
		*new_item;

	int
		count;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (sample_count > 0);

	//
	// Create new queue entry
	//

	new_item = malloc_fast_mem (sizeof (speech_system_queue_type));

	ASSERT (new_item);

	new_item->parent = parent;

	new_item->sub_type = sub_type;

	new_item->category = category;

	new_item->channel = get_speech_originator_sound_channel (originator);

	new_item->locality = locality;

	if (pos)
	{
		new_item->pos = *pos;
	}
	else
	{
		new_item->pos.x = -1;
		new_item->pos.y = -1;
		new_item->pos.z = -1;
	}

	new_item->delay = delay;
	new_item->priority = priority;
	new_item->expire_time = expire_time;
	new_item->category_silence_timer = category_silence_timer;

	new_item->sample_count = sample_count;

	new_item->sample_list = malloc_fast_mem (sizeof (sound_sample_indices) * sample_count);

	memcpy (new_item->sample_list, sample_list, (sizeof (sound_sample_indices) * sample_count));

	//
	// Insert into queue
	//

	new_item->next = NULL;

	queue = speech_buffer [side][originator].queue;

	if (queue)
	{
		count = 0;

		while (queue->next)
		{
			count ++;

			queue = queue->next;
		}

		ASSERT (queue);

		if (count > 20)
		{
			debug_log ("SPEECH: Warning side %s originator %d queue reached %d items", entity_side_short_names [side], originator, count);
		}

		queue->next = new_item;

		new_item->prev = queue;
	}
	else
	{
		new_item->prev = NULL;

		speech_buffer [side][originator].queue = new_item;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void remove_speech_from_list (entity_sides side, speech_originator_types originator, speech_system_queue_type *item)
{
	speech_system_type
		*buffer;

	speech_system_queue_type
		*next,
		*prev;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	buffer = &speech_buffer [side][originator];

	ASSERT (buffer);

	ASSERT (item);

	next = item->next;
	prev = item->prev;

	if (next)
	{
		next->prev = prev;
	}

	if (prev)
	{
		prev->next = next;
	}
	else
	{
		buffer->queue = next;
	}

	ASSERT (item->sample_list);

	free_mem (item->sample_list);

	free_mem (item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *play_buffered_speech (entity_sides side, speech_originator_types originator)
{
	entity
		*en;

	vec3d
		*pos;

	speech_system_type
		*buffer;

	speech_system_queue_type
		*item,
		*best;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	en = NULL;

	buffer = &speech_buffer [side][originator];

	ASSERT (buffer);

	item = buffer->queue;

	if (!item)
	{
		return en;
	}

	//
	// find next speech to play
	//

	best = NULL;

	while (item)
	{
		if (item->delay > 0.0)
		{
			item = item->next;

			continue;
		}

		if (buffer->exclude_list [item->category].timer > 0.0)
		{
			item = item->next;

			continue;
		}

		if (!best)
		{
			best = item;
		}
		else
		{
			if (item->priority > best->priority)
			{
				best = item;
			}
		}

		item = item->next;
	}

	//
	// Found speech ?
	//

	item = best;

	if (item)
	{
		if (point_inside_map_area (&(item->pos)))
		{
			pos = &(item->pos);
		}
		else
		{
			pos = NULL;
		}

		//
		// play speech
		//

		en = create_client_server_speech_entity (item->parent, side, item->sub_type, item->channel, item->locality, pos, item->sample_count, item->sample_list);

		ASSERT (en);

		buffer->current.timer = get_local_entity_float_value (en, FLOAT_TYPE_EFFECT_LIFETIME);

		buffer->exclude_list [item->category].timer = item->category_silence_timer;

		//
		// remove item from list
		//

		remove_speech_from_list (side, originator, item);
	}

	return en;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_speech_buffers (void)
{
	int
		side,
		originator,
		category;

	speech_system_type
		*buffer;

	speech_system_queue_type
		*item,
		*next;

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (originator = 0; originator < NUM_SPEECH_ORIGINATOR_TYPES; originator ++)
		{
			buffer = &speech_buffer [side][originator];

			ASSERT (buffer);

			//
			// Check to see if current speech finished...
			//

			buffer->current.timer -= get_delta_time ();

			if (buffer->current.timer < 0.0)
			{
				buffer->current.timer = 0.0;

				//
				// play next speech
				//

				play_buffered_speech (side, originator);
			}

			//
			// update queue timers
			//

			item = buffer->queue;

			while (item)
			{
				next = item->next;

				if (item->expire_time < buffer->exclude_list [item->category].timer)
				{
					remove_speech_from_list (side, originator, item);
				}
				else
				{
					item->delay -= get_delta_time ();

					item->delay = max (item->delay, 0.0);

					item->expire_time -= get_delta_time ();

					if (item->category_silence_timer > 0.0)
					{
						item->category_silence_timer = max (0.0, item->category_silence_timer - get_delta_time ());
					}

					if (item->expire_time < 0.0)
					{
						remove_speech_from_list (side, originator, item);
					}
				}

				item = next;
			}

			//
			// update exclude timers
			//

			for (category = 0; category < NUM_SPEECH_CATEGORY_TYPES; category ++)
			{
				buffer->exclude_list [category].timer -= get_delta_time ();

				buffer->exclude_list [category].timer = max (buffer->exclude_list [category].timer, 0.0);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove_speech_category_from_buffers (entity_sides side, speech_originator_types originator, speech_category_types category)
{
	speech_system_type
		*buffer;

	speech_system_queue_type
		*item,
		*next;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	buffer = &speech_buffer [side][originator];

	ASSERT (buffer);

	item = buffer->queue;

	while (item)
	{
		next = item->next;

		if (item->category == category)
		{
			remove_speech_from_list (side, originator, item);
		}

		item = next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_speech_buffers (void)
{
	int
		originator,
		side;

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (originator = 0; originator < NUM_SPEECH_ORIGINATOR_TYPES; originator ++)
		{
			speech_buffer [side][originator].queue = NULL;

			memset (speech_buffer [side][originator].exclude_list, 0, sizeof (speech_system_exclude_type) * NUM_SPEECH_CATEGORY_TYPES);

			speech_buffer [side][originator].current.timer = 0.0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_speech_buffers (void)
{
	int
		originator,
		side;

	speech_system_queue_type
		*item,
		*next;

	for (side = 0; side < NUM_ENTITY_SIDES; side ++)
	{
		for (originator = 0; originator < NUM_SPEECH_ORIGINATOR_TYPES; originator ++)
		{
			item = speech_buffer [side][originator].queue;

			while (item)
			{
				next = item->next;

				if (item->sample_list)
				{
					free_mem (item->sample_list);
				}

				free_mem (item);

				item = next;
			}

			speech_buffer [side][originator].queue = NULL;

			memset (speech_buffer [side][originator].exclude_list, 0, sizeof (speech_system_exclude_type) * NUM_SPEECH_CATEGORY_TYPES);

			speech_buffer [side][originator].current.timer = 0.0;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_speech_buffers_entity_killed (entity *en)
{
	int
		side,
		originator;

	speech_system_type
		*buffer;

	speech_system_queue_type
		*item,
		*next;

	ASSERT (en);

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);

	for (originator = 0; originator < NUM_SPEECH_ORIGINATOR_TYPES; originator ++)
	{
		buffer = &speech_buffer [side][originator];

		ASSERT (buffer);

		item = buffer->queue;

		while (item)
		{
			next = item->next;

			if (item->parent == en)
			{
				remove_speech_from_list (side, originator, item);
			}

			item = next;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int play_client_server_speech
(
	entity *parent,
	entity *sender,
	entity_sides side,
	entity_sub_types sub_type,
	sound_locality_types locality,
	float delay,
	float priority,
	float expire_time,
	speech_originator_types originator,
	speech_category_types category,
	float category_silence_timer,
	...
)
{
	va_list
		pargs;

	int
		count,
		speech_index;

	vec3d
		*pos;

	sound_sample_indices
		sample_list [MAX_SEQUENCED_SAMPLES];

	speech_array_types
		array_type;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (parent);

	ASSERT (side < NUM_ENTITY_SIDES);

	ASSERT (locality < NUM_SOUND_LOCALITY_TYPES);

	ASSERT (originator < NUM_SPEECH_ORIGINATOR_TYPES);

	ASSERT (category < NUM_SPEECH_CATEGORY_TYPES);

	count = 0;

	if (sender)
	{
		pos = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);
	}
	else
	{
		pos = NULL;
	}

	va_start (pargs, category_silence_timer);

	array_type = va_arg (pargs, int);

	while (array_type != -1)
	{
		ASSERT (array_type < NUM_SPEECH_ARRAY_TYPES);

		speech_index = va_arg (pargs, int);

		ASSERT (speech_index >= 0);

		ASSERT (speech_index < speech_index_table [array_type][originator][side].num_items);

		sample_list [count] = speech_index_table [array_type][originator][side].sample_indices [speech_index];

		if (sample_list [count] != SOUND_SAMPLE_INDEX_NONE)
		{
			if (application_sound_effects [sample_list [count]].size > 0)
			{
				count ++;
			}
		}

		if (count >= MAX_SEQUENCED_SAMPLES)
		{
			debug_fatal ("SPEECH : More than %d samples in speech list", MAX_SEQUENCED_SAMPLES);
		}

		array_type = va_arg (pargs, int);
	}

	va_end (pargs);

	if (count == 0)
	{
		return FALSE;
	}

	//
	// Biggest Bodge In The Whole World Ever.....
	//

	if (originator == SPEECH_ORIGINATOR_WINGMAN2)
	{
		originator = SPEECH_ORIGINATOR_WINGMAN1;
	}

	//
	// Insert into queue
	//

	if (add_speech_to_list (parent, side, originator, sub_type, category, locality, pos, delay, priority, expire_time, category_silence_timer, count, sample_list))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_speech_index_table (void)
{
	//
	// clear table
	//

	deinitialise_speech_index_table ();

	//
	// load in the data
	//

	initialise_speech_number_data ();
	initialise_speech_headings_data ();
	initialise_speech_distances_data ();
	initialise_speech_callsign_data ();
	initialise_speech_atc_data ();
	initialise_speech_gc_data ();
	initialise_speech_fac_data ();
	initialise_speech_wingman_data ();
	initialise_speech_system_data ();
	initialise_speech_cpg_data ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_sample_index_array (speech_array_types array_type, speech_originator_types originator, int max_items)
{
	speech_index_list_type
		*blue_force_entry,
		*red_force_entry;

	ASSERT ((array_type >= 0) && (array_type < NUM_SPEECH_ARRAY_TYPES));
	ASSERT ((originator >= 0) && (originator < NUM_SPEECH_ORIGINATOR_TYPES));

	blue_force_entry = &(speech_index_table [array_type][originator][ENTITY_SIDE_BLUE_FORCE]);
	red_force_entry = &(speech_index_table [array_type][originator][ENTITY_SIDE_RED_FORCE]);

	//
	// clear data
	//

	blue_force_entry->num_items = max_items;
	blue_force_entry->sample_indices = safe_malloc (sizeof (sound_sample_indices) * max_items);
	memset (blue_force_entry->sample_indices, 0, (sizeof (sound_sample_indices) * max_items));

	red_force_entry->num_items = max_items;
	red_force_entry->sample_indices = safe_malloc (sizeof (sound_sample_indices) * max_items);
	memset (red_force_entry->sample_indices, 0, (sizeof (sound_sample_indices) * max_items));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_speech_data (speech_array_types array_type, speech_originator_types originator, int speech_index, sound_sample_indices blue_force_sample_index, sound_sample_indices red_force_sample_index)
{
	speech_index_list_type
		*blue_force_entry,
		*red_force_entry;

	ASSERT ((array_type >= 0) && (array_type < NUM_SPEECH_ARRAY_TYPES));
	ASSERT ((originator >= 0) && (originator < NUM_SPEECH_ORIGINATOR_TYPES));

	blue_force_entry = &(speech_index_table [array_type][originator][ENTITY_SIDE_BLUE_FORCE]);
	red_force_entry = &(speech_index_table [array_type][originator][ENTITY_SIDE_RED_FORCE]);

	ASSERT (blue_force_sample_index != red_force_sample_index);

	ASSERT (speech_index < blue_force_entry->num_items);
	ASSERT (speech_index < red_force_entry->num_items);

	blue_force_entry->sample_indices [speech_index] = blue_force_sample_index;
	red_force_entry->sample_indices [speech_index] = red_force_sample_index;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_speech_index_table (void)
{
	int
		array_loop,
		originator_loop,
		side_loop;

	#if DEBUG_MODULE

	check_speech_index_table ();

	#endif

	for (array_loop = 0; array_loop < NUM_SPEECH_ARRAY_TYPES; array_loop ++)
	{
		for (originator_loop = 0; originator_loop < NUM_SPEECH_ORIGINATOR_TYPES; originator_loop ++)
		{
			for (side_loop = 0; side_loop < NUM_ENTITY_SIDES; side_loop ++)
			{
				speech_index_table [array_loop][originator_loop][side_loop].num_items = 0;

				if (speech_index_table [array_loop][originator_loop][side_loop].sample_indices)
				{
					safe_free (speech_index_table [array_loop][originator_loop][side_loop].sample_indices);

					speech_index_table [array_loop][originator_loop][side_loop].sample_indices = NULL;
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// DEBUG FUNCTION TO CHECK SFX USAGE
//

#if DEBUG_MODULE

void check_speech_index_table (void)
{
	int
		*sample_info,
		array_loop,
		originator_loop,
		side_loop,
		sample_loop,
		sample_index;

	speech_index_list_type
		*sample_list;

	sample_info = malloc_heap_mem (sizeof (int) * NUM_SOUND_SAMPLE_INDICES);

	memset (sample_info, 0, sizeof (int) * NUM_SOUND_SAMPLE_INDICES);

	//
	// mark all used samples
	//

	for (array_loop = 0; array_loop < NUM_SPEECH_ARRAY_TYPES; array_loop ++)
	{
		for (originator_loop = 0; originator_loop < NUM_SPEECH_ORIGINATOR_TYPES; originator_loop ++)
		{
			for (side_loop = 0; side_loop < NUM_ENTITY_SIDES; side_loop ++)
			{
				sample_list = &(speech_index_table [array_loop][originator_loop][side_loop]);

				if (sample_list->num_items > 0)
				{
					for (sample_loop = 0; sample_loop < sample_list->num_items; sample_loop ++)
					{
						sample_index = sample_list->sample_indices [sample_loop];

						if (sample_index != SOUND_SAMPLE_INDEX_NONE)
						{
							sample_info [sample_index] |= 1;
						}
					}
				}
			}
		}
	}

	//
	// mark all loaded samples
	//

	for (sample_loop = 0; sample_loop < NUM_SOUND_SAMPLE_INDICES; sample_loop ++)
	{
		if (application_sound_effects [sample_loop].size > 0)
		{
			sample_info [sample_loop] |= 2;
		}
	}

	//
	// display sample info
	//

	debug_filtered_log ("---SAMPLES LOADED---");

	for (sample_loop = 0; sample_loop < NUM_SOUND_SAMPLE_INDICES; sample_loop ++)
	{
		if (application_sound_effects [sample_loop].size > 0)
		{
			debug_filtered_log ("%d - %s", application_sound_effects [sample_loop].size, application_sound_effects [sample_loop].name);
		}
	}

	debug_filtered_log ("");

	//
	// display loaded but not used....
	//

	debug_filtered_log ("---SAMPLES LOADED BUT NOT USED---");

	for (sample_loop = 0; sample_loop < NUM_SOUND_SAMPLE_INDICES; sample_loop ++)
	{
		if (sample_info [sample_loop] == 2)
		{
			debug_filtered_log ("%d - %s", sample_loop, application_sound_effects [sample_loop].name);
		}
	}

	debug_filtered_log ("");

	//
	// display used but not loaded....
	//

	debug_filtered_log ("---SAMPLES USED BUT NOT LOADED---");

	for (sample_loop = 0; sample_loop < NUM_SOUND_SAMPLE_INDICES; sample_loop ++)
	{
		if (sample_info [sample_loop] == 1)
		{
			debug_filtered_log ("%d", sample_loop);
		}
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_speech_random_value (speech_instance_type *speech_list, int num_choices, int last_played)
{
	int
		n,
		total;

	ASSERT (num_choices > 0);

	total = 0;

	for (n = 0; n < num_choices; n ++)
	{
		total += speech_list [n].frequency;
	}

	ASSERT (total > 0);

	total -= speech_list [last_played].frequency;

	total *= rand16 ();

	total = total >> 15;

	n = last_played + 1;

	if (n >= num_choices) n -= num_choices;

	while (total > speech_list [n].frequency)
	{
		total -= speech_list [n].frequency;

		n ++;

		if (n >= num_choices) n -= num_choices;
	}

	return n;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int play_speech_introduction (int val)
{
	switch (val)
	{
		case SPEECH_INTRODUCTION_NEVER:
		{
			return FALSE;
		}
		case SPEECH_INTRODUCTION_SOMETIMES:
		{
			return (rand16 () & 1);
		}
		case SPEECH_INTRODUCTION_ALWAYS:
		{
			return TRUE;
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int play_client_server_radio_message
(
	entity *en,
	entity_sides side,
	float priority,
	float expire_time,
	speech_originator_types originator,
	speech_category_types category,
	float category_silence_timer,
	speech_intro_types play_intro,
	speech_array_types main_array_type,
	int main_speech_index
)
{
	entity
		*group_en;

	int
		result,
		member_number;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if ((main_speech_index == -1) || (main_array_type == -1))
	{
		return FALSE;
	}

	group_en = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	member_number = get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_ID);

	//
	// TEMPORARY FIX - group member number can be 1..31, but we only have speech for numbers 0..9
	// so only announce number for valid members...
	//
	if (member_number >= 10)
	{
		play_intro = SPEECH_INTRODUCTION_NEVER;
	}
	//
	// END
	//

	if ((play_speech_introduction (play_intro)) && (group_en))
	{
		result = play_client_server_speech
						(
							get_session_entity (),
							en,
							side,
							ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
							SOUND_LOCALITY_RADIO,
							0.0,
							priority,
							expire_time,
							originator,
							category,
							category_silence_timer,
							SPEECH_ARRAY_WINGMAN_MESSAGES, SPEECH_WINGMAN_INTRODUCTION,
							SPEECH_ARRAY_CALLSIGNS, get_local_entity_int_value (group_en, INT_TYPE_GROUP_CALLSIGN),
							SPEECH_ARRAY_NUMBERS, 1,
							SPEECH_ARRAY_NUMBERS, member_number,
							main_array_type, main_speech_index,
							-1
						);
	}
	else
	{
		result = play_client_server_speech
						(
							get_session_entity (),
							en,
							side,
							ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
							SOUND_LOCALITY_RADIO,
							0.0,
							priority,
							expire_time,
							originator,
							category,
							category_silence_timer,
							main_array_type, main_speech_index,
							-1
						);
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int play_client_server_personal_message
(
	entity *en,
	float priority,
	float expire_time,
	entity_sub_types sub_type,
	speech_originator_types originator,
	speech_category_types category,
	float category_silence_timer,
	speech_array_types main_array_type,
	int main_speech_index
)
{
	int
		result;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
	{
		return FALSE;
	}

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return FALSE;
	}

	if ((main_speech_index == -1) || (main_array_type == -1))
	{
		return FALSE;
	}

	result = play_client_server_speech
						(
							en,
							en,
							get_local_entity_int_value (en, INT_TYPE_SIDE),
							sub_type,
							SOUND_LOCALITY_RADIO,
							0.0,
							priority,
							expire_time,
							originator,
							category,
							category_silence_timer,
							main_array_type,
							main_speech_index,
							-1
						);

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int play_client_server_cpg_message (entity *en, float priority, float expire_time, int speech_category, float category_silence_timer, int speech_index)
{
	int
		result;

	ASSERT (en);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		result = play_client_server_personal_message
						(
							en,
							priority,
							expire_time,
							ENTITY_SUB_TYPE_EFFECT_SOUND_CPG_MESSAGE,
							SPEECH_ORIGINATOR_CO_PILOT,
							speech_category,
							category_silence_timer,
							SPEECH_ARRAY_CPG_MESSAGES, speech_index
						);

		return result;
	}
	else
	{
		transmit_entity_comms_message (ENTITY_COMMS_PLAY_CPG_MESSAGE, en, priority, expire_time, speech_category, category_silence_timer, speech_index);

		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int play_client_server_cpg_contact_message (entity *en, int target_speech_index, int heading_speech_index, int range_speech_index)
{
	int
		result;

	float
		silence_timer;

	ASSERT (en);

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return FALSE;
	}

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		silence_timer = 3.0 + (frand1 () * 4.0);

		result = play_client_server_speech
		(
			en,
			en,
			get_local_entity_int_value (en, INT_TYPE_SIDE),
			ENTITY_SUB_TYPE_EFFECT_SOUND_CPG_MESSAGE,
			SOUND_LOCALITY_RADIO,
			0.0,
			0.8,
			2.0,
			SPEECH_ORIGINATOR_CO_PILOT,
			SPEECH_CATEGORY_TARGET_LOCK,
			silence_timer,
			SPEECH_ARRAY_CPG_MESSAGES, target_speech_index,
			SPEECH_ARRAY_HEADINGS, heading_speech_index,
			SPEECH_ARRAY_DISTANCES, range_speech_index,
			-1
		);

		return result;
	}
	else
	{
		transmit_entity_comms_message (ENTITY_COMMS_PLAY_CPG_CONTACT_MESSAGE, en, target_speech_index, heading_speech_index, range_speech_index);

		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int play_client_server_warning_message (entity *en, int speech_index)
{
	int
		result;

	ASSERT (en);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		result = play_client_server_personal_message
						(
							en,
							1.0,
							5.0,
							ENTITY_SUB_TYPE_EFFECT_SOUND_WARNING_MESSAGE,
							SPEECH_ORIGINATOR_SYSTEM,
							SPEECH_CATEGORY_WARNING_SYSTEM, -1.0,
							SPEECH_ARRAY_SYSTEM_MESSAGES, speech_index
						);

		return result;
	}
	else
	{
		transmit_entity_comms_message (ENTITY_COMMS_PLAY_WARNING_MESSAGE, en, speech_index);

		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEMO_VERSION

speech_originator_types get_wingman_speech_originator (entity *en)
{
	return SPEECH_ORIGINATOR_WINGMAN1;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#else

speech_originator_types get_wingman_speech_originator (entity *en)
{
	entity
		*group;
		
	int
		group_index,
		member_number;

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);
	
	ASSERT (group);
	
	group_index = get_local_entity_safe_index (group);
	
	member_number = get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);
	
	if ((group_index + member_number) & 0x01)
	{
		return SPEECH_ORIGINATOR_WINGMAN1;
	}
	else
	{
		return SPEECH_ORIGINATOR_WINGMAN2;
	}
}

#endif
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int play_client_server_wingman_message
(
	entity *en,
	float priority,
	float expire_time,
	speech_category_types category,
	float category_silence_timer,
	speech_intro_types play_intro,
	speech_array_types main_array_type,
	int main_speech_index
)
{
	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return play_client_server_radio_message
					(
						en,
						get_local_entity_int_value (en, INT_TYPE_SIDE),
						priority,
						expire_time,
						get_wingman_speech_originator (en),
						category,
						category_silence_timer,
						play_intro,
						main_array_type,
						main_speech_index
					);
	}
	else
	{
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int *get_speech_sector_coordinates (vec3d *pos)
{
	entity
		*sec;

	int
		sx,
		sz;

	ASSERT (pos);

	sec = get_local_sector_entity (pos);

	ASSERT (sec);

	//
	// get z sector coords
	//

	sz = get_local_entity_int_value (sec, INT_TYPE_Z_SECTOR);

	speech_sector_coordinates [5] = sz % 10;
	sz /= 10;

	speech_sector_coordinates [4] = sz % 10;
	sz /= 10;

	speech_sector_coordinates [3] = sz % 10;

	//
	// get x sector coords
	//

	sx = get_local_entity_int_value (sec, INT_TYPE_X_SECTOR);

	speech_sector_coordinates [2] = sx % 10;
	sx /= 10;

	speech_sector_coordinates [1] = sx % 10;
	sx /= 10;

	speech_sector_coordinates [0] = sx % 10;

	return speech_sector_coordinates;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

speech_heading_types get_speech_heading_type (entity *source, entity *target)
{
	speech_heading_types
		type;

	float
		relative_bearing;

	ASSERT (source);
	ASSERT (target);

	relative_bearing = get_local_entity_target_relative_bearing (source, target);

	if (relative_bearing < 0.0)
	{
		relative_bearing += rad (360.0);
	}

	if (relative_bearing < rad (15.0))
	{
		type = SPEECH_HEADING_TWELVE_O_CLOCK;
	}
	else if (relative_bearing < rad (45.0))
	{
		type = SPEECH_HEADING_ONE_O_CLOCK;
	}
	else if (relative_bearing < rad (75.0))
	{
		type = SPEECH_HEADING_TWO_O_CLOCK;
	}
	else if (relative_bearing < rad (105.0))
	{
		type = SPEECH_HEADING_THREE_O_CLOCK;
	}
	else if (relative_bearing < rad (135.0))
	{
		type = SPEECH_HEADING_FOUR_O_CLOCK;
	}
	else if (relative_bearing < rad (165.0))
	{
		type = SPEECH_HEADING_FIVE_O_CLOCK;
	}
	else if (relative_bearing < rad (195.0))
	{
		type = SPEECH_HEADING_SIX_O_CLOCK;
	}
	else if (relative_bearing < rad (225.0))
	{
		type = SPEECH_HEADING_SEVEN_O_CLOCK;
	}
	else if (relative_bearing < rad (255.0))
	{
		type = SPEECH_HEADING_EIGHT_O_CLOCK;
	}
	else if (relative_bearing < rad (285.0))
	{
		type = SPEECH_HEADING_NINE_O_CLOCK;
	}
	else if (relative_bearing < rad (315.0))
	{
		type = SPEECH_HEADING_TEN_O_CLOCK;
	}
	else if (relative_bearing < rad (345.0))
	{
		type = SPEECH_HEADING_ELEVEN_O_CLOCK;
	}
	else
	{
		type = SPEECH_HEADING_TWELVE_O_CLOCK;
	}

	return (type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

speech_distance_types get_speech_distance_type (entity *source, entity *target)
{
	speech_distance_types
		type;

	vec3d
		*source_pos,
		*target_pos;

	float
		dx,
		dz,
		range;

	ASSERT (source);
	ASSERT (target);

	source_pos = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);
	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	dx = target_pos->x - source_pos->x;
	dz = target_pos->z - source_pos->z;

	range = sqrt ((dx * dx) + (dz * dz));

	if (range < 500.0)
	{
		type = SPEECH_DISTANCE_HALF_KILOMETRE;
	}
	else if (range < 1500.0)
	{
		type = SPEECH_DISTANCE_ONE_KILOMETRE;
	}
	else if (range < 2500.0)
	{
		type = SPEECH_DISTANCE_TWO_KILOMETRE;
	}
	else if (range < 3500.0)
	{
		type = SPEECH_DISTANCE_THREE_KILOMETRE;
	}
	else if (range < 4500.0)
	{
		type = SPEECH_DISTANCE_FOUR_KILOMETRE;
	}
	else if (range < 5500.0)
	{
		type = SPEECH_DISTANCE_FIVE_KILOMETRE;
	}
	else if (range < 6500.0)
	{
		type = SPEECH_DISTANCE_SIX_KILOMETRE;
	}
	else if (range < 7500.0)
	{
		type = SPEECH_DISTANCE_SEVEN_KILOMETRE;
	}
	else if (range < 8500.0)
	{
		type = SPEECH_DISTANCE_EIGHT_KILOMETRE;
	}
	else if (range < 9500.0)
	{
		type = SPEECH_DISTANCE_NINE_KILOMETRE;
	}
	else if (range < 10500.0)
	{
		type = SPEECH_DISTANCE_TEN_KILOMETRE;
	}
	else if (range < 11500.0)
	{
		type = SPEECH_DISTANCE_ELEVEN_KILOMETRE;
	}
	else
	{
		type = SPEECH_DISTANCE_TWELVE_KILOMETRE;
	}

	return (type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

speech_atc_message_types get_speech_atc_wind_speed (entity *en)
{
	vec3d
		*pos;

	float
		speed;

	ASSERT (en);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	speed = get_session_wind_velocity_at_point (pos, NULL);

	speed = knots (speed);

	if (speed < 6.0)
	{
		return SPEECH_ATC_AT_5_KNOTS;
	}
	else if (speed < 11.0)
	{
		return SPEECH_ATC_AT_10_KNOTS;
	}
	else if (speed < 16.0)
	{
		return SPEECH_ATC_AT_15_KNOTS;
	}
	else if (speed < 21.0)
	{
		return SPEECH_ATC_AT_20_KNOTS;
	}
	else if (speed < 26.0)
	{
		return SPEECH_ATC_AT_25_KNOTS;
	}

	return SPEECH_ATC_AT_30_KNOTS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



