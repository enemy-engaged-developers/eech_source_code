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
// 1 - long watch messages
// 2 - short watch messages
//

#define COMMS_STATS  2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COMMS_MODEL_TYPES
{

   COMMS_MODEL_SERVER,
   COMMS_MODEL_CLIENT,
   NUM_COMMS_MODEL_TYPES
};

typedef enum COMMS_MODEL_TYPES comms_model_types;

extern char
	*comms_model_string,
	*comms_model_names [],
	*send_type_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum SEND_TYPES
{

   SEND_TYPE_PERSONAL,
   SEND_TYPE_GROUP,
   NUM_SEND_TYPES
};

typedef enum SEND_TYPES send_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum COMMS_DATA_FLOW_TYPES
{

   COMMS_DATA_FLOW_TX,
   COMMS_DATA_FLOW_RX,
   NUM_COMMS_DATA_FLOW_TYPES
};

typedef enum COMMS_DATA_FLOW_TYPES comms_data_flow_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum PACKET_TYPES
{

   //
   // System packets, used internally
   //

   PACKET_TYPE_INVALID = 0,

	//
	// Personal Packets
	//

	PACKET_TYPE_FIRST_PERSONAL_PACKET,

   PACKET_TYPE_RESEND_PACKET,
	PACKET_TYPE_SESSION_INFO,
   PACKET_TYPE_CLIENT_PILOT_REQUEST,
   PACKET_TYPE_CLIENT_GUNSHIP_REQUEST,
   PACKET_TYPE_CLIENT_CAMPAIGN_DATA_REQUEST,
   PACKET_TYPE_PILOT_REQUEST_ACCEPTED,
   PACKET_TYPE_GUNSHIP_REQUEST_REFUSED,
   PACKET_TYPE_GUNSHIP_REQUEST_ACCEPTED,
   PACKET_TYPE_MISSION_DATA,
   PACKET_TYPE_FRAME_ID,
	PACKET_TYPE_CLIENT_FRAME_ID,
   PACKET_TYPE_SERVER_REJECTED,				
   PACKET_TYPE_END_GAME,
   PACKET_TYPE_CONNECTION_VALIDATION,
   PACKET_TYPE_CONNECTION_RESPONSE,

	//
	// Group Packets
	//

	PACKET_TYPE_FIRST_GROUP_PACKET,

   PACKET_TYPE_SESSION_QUERY,
   PACKET_TYPE_AI_DATA,

	//
	//
	//

	NUM_PACKET_TYPES
};

typedef enum PACKET_TYPES packet_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern comms_model_types
   system_comms_model;

extern comms_data_flow_types
   system_comms_data_flow;

extern DPID
   system_server_id;

extern int
   send_group_frame_id,
	resend_packet_list_counter,
	group_packet_list_counter,
	personal_packet_list_counter;

struct STUB_PACKET_TYPE
{

	int
		send_type,		// group or personal
		packet_id, 		// used for rerequest list
		frame_id, 		// used for rerequest list
		actual_time,	// used for rerequest list
		received_time;

	struct PACKET_HEADER_TYPE
		*packet;

	struct STUB_PACKET_TYPE
		*prev,
		*next;
};

typedef struct STUB_PACKET_TYPE stub_packet_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern stub_packet_type
	*rerequest_packet_list,
	*resend_packet_list,
	*received_group_packets,
	*received_personal_packets;

extern int
	comms_weapon_lag_timing;

extern float
	comms_weapon_lag_time;

#if COMMS_STATS

extern float
	av_packet_size_sent,
	av_packet_size_received,
	instant_packet_size_sent;

extern int
	packet_record_data_count;

#define zero_average_pack_size() (av_packet_size_sent = 0.0, av_packet_size_received = 0.0)

#else

#define zero_average_pack_size() (TRUE)

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void set_comms_data_flow (comms_data_flow_types data_flow);

extern void set_comms_model (comms_model_types model);

#define get_comms_model() (system_comms_model)

#define get_comms_data_flow() (system_comms_data_flow)

#define set_server_id(SERVER_ID) (system_server_id = (SERVER_ID))

#define get_server_id() (system_server_id)

#define set_group_frame_id(FRAME_ID) (send_group_frame_id = (FRAME_ID))

#define get_group_frame_id() (send_group_frame_id)

#define get_packet_send_type(PACKET) (((PACKET)->type > PACKET_TYPE_FIRST_GROUP_PACKET) ? SEND_TYPE_GROUP : SEND_TYPE_PERSONAL)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define add_stub_packet_to_receive_list(LIST,PACKET) (((LIST) == SEND_TYPE_GROUP) ? (add_stub_packet_to_list (&received_group_packets, (PACKET)), group_packet_list_counter ++) : (add_stub_packet_to_list (&received_personal_packets, (PACKET)), personal_packet_list_counter ++))

#define add_stub_packet_to_resend_list(PACKET) (add_stub_packet_to_list (&resend_packet_list, (PACKET)), resend_packet_list_counter ++)

#define remove_stub_packet_from_resend_list(PACKET) (remove_stub_packet_from_list (&resend_packet_list, (PACKET)), resend_packet_list_counter --)

#define remove_stub_packet_from_receive_list(LIST,PACKET) (((LIST) == SEND_TYPE_GROUP) ? (remove_stub_packet_from_list (&received_group_packets, (PACKET)), group_packet_list_counter --) : (remove_stub_packet_from_list (&received_personal_packets, (PACKET)), personal_packet_list_counter --))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PACKET_HEADER_TYPE
{

   packet_types
      type;

   DPID
      player_id;

   int
      frame_id;

   short int
      number_of_packets,
      packet_id,
      data_size;

	int
		check_sum;
};

typedef struct PACKET_HEADER_TYPE packet_header_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* forward declarations for types used below */
struct CONNECTION_LIST_TYPE;
/*********************************************/

extern void initialise_comms (void);

extern void reset_comms_data (void);

extern void initialise_comms_debug (void);

extern void deinitialise_comms (void);

extern void send_packet (DPID player_id, packet_types type, char *data, int size, send_types send_type);

extern void receive_packets (void);

extern int process_packet_list (send_types send_type, struct CONNECTION_LIST_TYPE *connection, DPID *player_id, char **data, int *size);

extern DPID get_packet_destination (void);

extern stub_packet_type *resend_packet (DPID player_id, int frame_id, int packet_id, send_types send_type);

extern void free_connection_packets (DPID connection_id);

extern void remove_stub_packet_from_list (stub_packet_type **list, stub_packet_type *packet);

extern void update_resend_packet_list (int packet_limit);

#if COMMS_STATS

extern void debug_comms_stats (void);

#endif

extern void reset_comms_stats (void);

extern void reset_receive_packet_list_time_stamps (void);

extern void display_comms_stats (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "comm_man.h"

// JB 030311 VC rename source files
#include "commsserver.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
