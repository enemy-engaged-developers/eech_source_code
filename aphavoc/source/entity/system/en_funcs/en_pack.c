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

#define DEBUG_MODULE 	0

#define PACKING_STATS	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	signed_int_pack_stats [33],
	unsigned_int_pack_stats [33];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_pack_local_entity_data[NUM_ENTITY_TYPES]) (entity *en, pack_modes mode);

void (*fn_unpack_local_entity_data[NUM_ENTITY_TYPES]) (entity *en, entity_types type, pack_modes mode);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_pack_entity_data (entity *en, pack_modes mode)
{
	debug_fatal ("default_pack_entity_data invoked: %s (index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_unpack_entity_data (entity *en, entity_types type, pack_modes mode)
{
	if (mode == PACK_MODE_UPDATE_ENTITY)
	{
		debug_fatal ("default_unpack_entity_data invoked: %s (index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));
	}
	else 
	{
		debug_fatal ("default_unpack_entity_data invoked: %s", get_entity_type_name (type));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_pack_default_functions (void)
{
	int
		i;

	memset (signed_int_pack_stats, 0, sizeof (signed_int_pack_stats));

	memset (unsigned_int_pack_stats, 0, sizeof (unsigned_int_pack_stats));

	for (i = 0; i < NUM_ENTITY_TYPES; i++)
	{
		fn_pack_local_entity_data[i]	  	= default_pack_entity_data;

		fn_unpack_local_entity_data[i] 	= default_unpack_entity_data;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//	PACK_MODE_SERVER_SESSION:	unpack_local_entity_data (NULL, type, mode)
//	PACK_MODE_CLIENT_SESSION:	unpack_local_entity_data (NULL, type, mode)
//	PACK_MODE_BROWSE_SESSION:	unpack_local_entity_data (NULL, type, mode)
//	PACK_MODE_UPDATE_ENTITY	:	unpack_local_entity_data (en, type, mode)

void unpack_local_entity_data (entity *en, entity_types type, pack_modes mode)
{
	if ((mode == PACK_MODE_SERVER_SESSION) || (mode ==	PACK_MODE_CLIENT_SESSION))
	{
		update_create_entity_statistics (type);
	}

	fn_unpack_local_entity_data[type] (en, type, mode);

	#if DEBUG_MODULE

	debug_log ("EN_PACK: unpacking data for %s", entity_type_names [type]);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function 'short-circuits' the standard client/server system in that the data is already in the local database
// of the machine that transmits the data (therefore a client will always ignore the data echoed from the server).
//
// The packing and unpacking of 'update' data allows entities to transmit their update data more efficiently, that is,
// using a single comms message, entity index and no data 'type' values.
//
// ***** THE UPDATE MECHANISM MUST ONLY BE USED TO BROADCAST VALUES THAT THE CLIENT IS ALLOWED TO BROADCAST *****

void unpack_client_server_entity_data (entity *en)
{
	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		unpack_local_entity_data (en, get_local_entity_type (en), PACK_MODE_UPDATE_ENTITY);

		transmit_entity_comms_message (ENTITY_COMMS_UPDATE, en);
	}
	else
	{
		ASSERT (get_comms_model () == COMMS_MODEL_CLIENT);

		unpack_local_entity_data (en, get_local_entity_type (en), PACK_MODE_UPDATE_ENTITY);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PACK FUNCTIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

pack_buffer
	pack_buffer_1 = {NULL, NULL, 0, 8, FALSE},
	pack_buffer_2 = {NULL, NULL, 0, 8, FALSE};

pack_buffer
	*current_pack_buffer = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void open_pack_buffer (char *buffer, int buffer_size)
{
	ASSERT (buffer);

	ASSERT (buffer_size > 0);

	if (!pack_buffer_1.buffer)
	{
		#if DEBUG_MODULE

		debug_log ("Open pack buffer 1 (address = %x, size = %d)", buffer, buffer_size);

		#endif

		current_pack_buffer = &pack_buffer_1;
	}
	else if (!pack_buffer_2.buffer)
	{
		#if DEBUG_MODULE

		debug_log ("Open pack buffer 2 (address = %x, size = %d)", buffer, buffer_size);

		#endif

		current_pack_buffer = &pack_buffer_2;
	}
	else
	{
		debug_fatal ("Exhausted pack buffers");
	}

	current_pack_buffer->buffer = buffer;

	current_pack_buffer->ptr = buffer;

	current_pack_buffer->size = buffer_size;

	current_pack_buffer->bit_counter = 8;

	current_pack_buffer->overflow = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int close_pack_buffer (void)
{
	int
		buffer_size;

	ASSERT (current_pack_buffer);

	ASSERT (current_pack_buffer->buffer);

	//
	// close current pack buffer
	//

	if (current_pack_buffer->bit_counter < 8)
	{
		//
		// position bits in last byte
		//

		*current_pack_buffer->ptr <<= current_pack_buffer->bit_counter;
	}
	else
	{
		//
		// last byte unused (only happens if the buffer is empty or an overflow has occurred)
		//

		current_pack_buffer->ptr--;
	}

	buffer_size = current_pack_buffer->ptr - current_pack_buffer->buffer + 1;

	#if DEBUG_MODULE
	{
		int
			buffer_num;

		buffer_num = (current_pack_buffer == &pack_buffer_1) ? 1 : 2;

		debug_log
		(
			"Close pack buffer %d: address = %x, packed size = %d, overflow = %d",
			buffer_num,
			current_pack_buffer->buffer,
			buffer_size,
			current_pack_buffer->overflow
		);
	}
	#endif

	current_pack_buffer->buffer = NULL;

	//
	// revert to previously opened pack buffer (if any)
	//

	if (pack_buffer_1.buffer)
	{
		current_pack_buffer = &pack_buffer_1;
	}
	else if (pack_buffer_2.buffer)
	{
		current_pack_buffer = &pack_buffer_2;
	}
	else
	{
		current_pack_buffer = NULL;
	}

	return (buffer_size);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_current_pack_buffer_bit_size (void)
{

	if (current_pack_buffer)
	{

		return (8 * (current_pack_buffer->ptr - current_pack_buffer->buffer)) + (8 - current_pack_buffer->bit_counter);
	}
	else
	{

		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// JB 030311 From Gotcha (Victor Jetten)
// Bug makes it impossible to load saved campaigns with builds made with VC/gcc or anything that is not watcom.
// Faulty function is unpack_bit and pack_bit

#ifdef __WATCOMC__

void pack_bit (int *unpacked_data, unsigned char *pack_ptr);

#pragma aux pack_bit = \
"shr dword ptr [eax],1" \
"rcl byte ptr [edx],1" \
parm [eax] [edx] \
modify exact [];

#else

// VC Intel version
#if defined(_MSC_VER) && defined(_M_IX86)

static __inline void pack_bit (int *unpacked_data, unsigned char *pack_ptr)
{
__asm
{
mov eax, unpacked_data
shr dword ptr[eax],1
mov eax, pack_ptr
rcl byte ptr[eax],1
}
}

#else

// generic C version

void pack_bit (int *unpacked_data, unsigned char *pack_ptr)
{
int
unpacked_value;

unsigned char
packed_value;

packed_value = *pack_ptr;

packed_value <<= 1;

unpacked_value = *unpacked_data;

packed_value |= (unpacked_value & 1);

unpacked_value >>= 1;

*unpacked_data = unpacked_value;

*pack_ptr = packed_value;
}
#endif

#endif 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_signed_data (int unpacked_data, int number_of_bits_to_pack)
{
	int
		count;

	#if PACKING_STATS

	todd_signed_int_pack_stats [number_of_bits_to_pack] ++;

	#endif

	//
	// pre-amble
	//

	ASSERT ((number_of_bits_to_pack > 0) && (number_of_bits_to_pack <= 32));

	ASSERT (current_pack_buffer);

	ASSERT (current_pack_buffer->buffer);

	if (current_pack_buffer->overflow)
	{
		return;
	}

	//
	// check data can be packed into given number of bits
	//

	#ifdef DEBUG
	{
		int
			residue;

		residue = unpacked_data >> (number_of_bits_to_pack - 1);

		if ((residue != 0) && (residue != -1))
		{
			debug_fatal ("pack_signed_data: exceeded pack width (value = %d, width = %d)", unpacked_data, number_of_bits_to_pack);
		}
	}
	#endif

	//
	// pack data
	//

	count = number_of_bits_to_pack;

	while (count--)
	{
		if (current_pack_buffer->bit_counter == 0)
		{
			current_pack_buffer->ptr++;

			current_pack_buffer->bit_counter = 8;

			if ((current_pack_buffer->ptr - current_pack_buffer->buffer + 1) > current_pack_buffer->size)
			{
				current_pack_buffer->overflow = TRUE;

				return;
			}
		}

		pack_bit (&unpacked_data, current_pack_buffer->ptr);

		current_pack_buffer->bit_counter--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_unsigned_data (unsigned int unpacked_data, int number_of_bits_to_pack)
{
	int
		count;

	#if PACKING_STATS

	todd_unsigned_int_pack_stats [number_of_bits_to_pack] ++;

	#endif

	//
	// pre-amble
	//

	ASSERT ((number_of_bits_to_pack > 0) && (number_of_bits_to_pack <= 32));

	ASSERT (current_pack_buffer);

	ASSERT (current_pack_buffer->buffer);

	if (current_pack_buffer->overflow)
	{
		return;
	}

	//
	// check data can be packed into given number of bits
	//

	#ifdef DEBUG
	{
		unsigned int
			residue;

		if (number_of_bits_to_pack < 32)
		{
			residue = unpacked_data >> number_of_bits_to_pack;

			if (residue != 0)
			{
				debug_fatal ("pack_unsigned_data: exceeded pack width (value = %u, width = %d)", unpacked_data, number_of_bits_to_pack);
			}
		}
	}
	#endif

	//
	// pack data
	//

	count = number_of_bits_to_pack;

	while (count--)
	{
		if (current_pack_buffer->bit_counter == 0)
		{
			current_pack_buffer->ptr++;

			current_pack_buffer->bit_counter = 8;

			if ((current_pack_buffer->ptr - current_pack_buffer->buffer + 1) > current_pack_buffer->size)
			{
				current_pack_buffer->overflow = TRUE;

				return;
			}
		}

		pack_bit ((int *) &unpacked_data, current_pack_buffer->ptr);

		current_pack_buffer->bit_counter--;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// UNPACK FUNCTIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unpack_buffer
	unpack_buffer_1 = {NULL, NULL, 0, 8, FALSE},
	unpack_buffer_2 = {NULL, NULL, 0, 8, FALSE};

unpack_buffer
	*current_unpack_buffer = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void open_unpack_buffer (char *buffer, int buffer_size)
{
	ASSERT (buffer);

	ASSERT (buffer_size > 0);

	if (!unpack_buffer_1.buffer)
	{
		#if DEBUG_MODULE

		debug_log ("Open unpack buffer 1 (address = %x, size = %d)", buffer, buffer_size);

		#endif

		current_unpack_buffer = &unpack_buffer_1;
	}
	else if (!unpack_buffer_2.buffer)
	{
		#if DEBUG_MODULE

		debug_log ("Open unpack buffer 2 (address = %x, size = %d)", buffer, buffer_size);

		#endif

		current_unpack_buffer = &unpack_buffer_2;
	}
	else
	{
		debug_fatal ("Exhausted unpack buffers");
	}

	current_unpack_buffer->buffer = buffer;

	current_unpack_buffer->ptr = buffer;

	current_unpack_buffer->size = buffer_size;

	current_unpack_buffer->bit_counter = 8;

	current_unpack_buffer->overflow = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void close_unpack_buffer (void)
{
	ASSERT (current_unpack_buffer);

	ASSERT (current_unpack_buffer->buffer);

	#if DEBUG_MODULE
	{
		int
			buffer_num;

		buffer_num = (current_unpack_buffer == &unpack_buffer_1) ? 1 : 2;

		debug_log
		(
			"Close unpack buffer %d: address = %x, overflow = %d",
			buffer_num,
			current_unpack_buffer->buffer,
			current_unpack_buffer->overflow
		);
	}
	#endif

	//
	// close current unpack buffer
	//

	current_unpack_buffer->buffer = NULL;

	//
	// revert to previously opened unpack buffer (if any)
	//

	if (unpack_buffer_1.buffer)
	{
		current_unpack_buffer = &unpack_buffer_1;
	}
	else if (unpack_buffer_2.buffer)
	{
		current_unpack_buffer = &unpack_buffer_2;
	}
	else
	{
		current_unpack_buffer = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// JB 030311 From Gotcha (Victor Jetten)
// Bug makes it impossible to load saved campaigns with builds made with VC/gcc or anything that is not watcom.
// Faulty function is unpack_bit and pack_bit

#ifdef __WATCOMC__

void unpack_bit (int *unpacked_data, unsigned char *unpack_ptr);

#pragma aux unpack_bit = \
"shl byte ptr [edx],1" \
"rcr dword ptr [eax],1" \
parm [eax] [edx] \
modify exact [];

#else

// VC Intel version
#if defined(_MSC_VER) && defined(_M_IX86)

static __inline void unpack_bit (int *unpacked_data, unsigned char *unpack_ptr)
{
__asm
{
mov eax, [unpack_ptr]
shl byte ptr [eax],1
mov eax, [unpacked_data]
rcr dword ptr [eax],1
}
}

#else

// generic C version
void unpack_bit (int *unpacked_data, unsigned char *unpack_ptr)
{
unsigned int // changed from RW's signed
unpacked_value,
temp;

unsigned char
packed_value;

packed_value = *unpack_ptr;

temp = packed_value;

temp <<= 24; // changed from RW's 23

temp &= 0x80000000;

unpacked_value = *unpacked_data;

unpacked_value >>= 1;

unpacked_value |= temp;

packed_value <<= 1;

*unpacked_data = unpacked_value;

*unpack_ptr = packed_value;
}
#endif

#endif 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int unpack_signed_data (int number_of_bits_to_unpack)
{
	int
		count,
		unpacked_data;

	//
	// pre-amble
	//

	ASSERT ((number_of_bits_to_unpack > 0) && (number_of_bits_to_unpack <= 32));

	ASSERT (current_unpack_buffer);

	ASSERT (current_unpack_buffer->buffer);

	if (current_unpack_buffer->overflow)
	{
		return (0);
	}

	//
	// unpack data
	//

	count = number_of_bits_to_unpack;

	while (count--)
	{
		if (current_unpack_buffer->bit_counter == 0)
		{
			current_unpack_buffer->ptr++;

			current_unpack_buffer->bit_counter = 8;

			if ((current_unpack_buffer->ptr - current_unpack_buffer->buffer + 1) > current_unpack_buffer->size)
			{
				current_unpack_buffer->overflow = TRUE;

				return (0);
			}
		}

		unpack_bit (&unpacked_data, current_unpack_buffer->ptr);

		current_unpack_buffer->bit_counter--;
	}

	unpacked_data = unpacked_data >> (32 - number_of_bits_to_unpack);

	return (unpacked_data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int unpack_unsigned_data (int number_of_bits_to_unpack)
{
	int
		count;

	unsigned int
		unpacked_data;

	//
	// pre-amble
	//

	ASSERT ((number_of_bits_to_unpack > 0) && (number_of_bits_to_unpack <= 32));

	ASSERT (current_unpack_buffer);

	ASSERT (current_unpack_buffer->buffer);

	if (current_unpack_buffer->overflow)
	{
		return (0);
	}

	//
	// unpack data
	//

	count = number_of_bits_to_unpack;

	while (count--)
	{
		if (current_unpack_buffer->bit_counter == 0)
		{
			current_unpack_buffer->ptr++;

			current_unpack_buffer->bit_counter = 8;

			if ((current_unpack_buffer->ptr - current_unpack_buffer->buffer + 1) > current_unpack_buffer->size)
			{
				current_unpack_buffer->overflow = TRUE;

				return (0);
			}
		}

		unpack_bit ((int *) &unpacked_data, current_unpack_buffer->ptr);

		current_unpack_buffer->bit_counter--;
	}

	unpacked_data = unpacked_data >> (32 - number_of_bits_to_unpack);

	return (unpacked_data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_current_pack_buffer_size (void)
{

	ASSERT (current_pack_buffer);

	return (current_pack_buffer->ptr - current_pack_buffer->buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debug_print_int_pack_stats (void)
{

	int
		loop;

	debug_log ("===========================================================");

	debug_log ("PACKING STATS");

	for (loop = 0; loop <= 32; loop ++)
	{

		debug_log ("Packing %d bits		signed %d		unsigned %d", loop, signed_int_pack_stats [loop], unsigned_int_pack_stats [loop]);
	}

	debug_log ("===========================================================");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
