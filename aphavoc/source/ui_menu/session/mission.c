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

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define INTERNAL_MODULES 1

#include "ai/faction/faction.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void leave_mission (void)
{

	int
		index_number;

	connection_list_type
		*destroy_connection,
		*connection;

   connection_data_type
      *comms_connection;

	#if DEBUG_MODULE

	debug_log ("MISSION: leaving");

	#endif

        if (get_valid_current_game_session ())
	{

		//
		// comms stuff
		//

		if (get_comms_model () == COMMS_MODEL_CLIENT)
		{

			index_number = get_local_entity_index (get_gunship_entity ());

			#if DEBUG_MODULE

			debug_log ("MISSION: Sending END GAME to server");

			#endif


////Moje 040618	Leave the player removal to cvc ;)
	send_packet (get_server_id (), PACKET_TYPE_END_GAME, (unsigned char *) &index_number, 4, SEND_TYPE_PERSONAL);
// Jabberwock 050320 - Restored, should work now
		}

      connection = get_connection_list_head ();

      while (connection)
      {

         destroy_connection = connection;

         connection = connection->next;

         if (get_comms_model () == COMMS_MODEL_SERVER)
         {

            send_packet (destroy_connection->connection_id, PACKET_TYPE_SERVER_REJECTED, NULL, 0, SEND_TYPE_PERSONAL);
         }

         unregister_connection (destroy_connection->connection_id);


      }

		comms_connection = direct_play_get_connection_data ();

		if ( ( comms_connection ) && ( comms_connection->is_initialised ) )
		{

			if ( !comms_connection->one_way_hosting_setup )
			{
			// Jabberwock 050303 Remove DP groups
			//	direct_play_leave_group ();

				direct_play_destroy_player ();

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
				// Jabberwock 050303 Remove DP groups
				//	direct_play_destroy_group ();
				}

				direct_play_close_session ();
			}
			else
			{

				direct_play_set_session_type_and_name ( GAME_TYPE_INVALID );
			}
		}

		//
		// Deinit stuff,
		//

		set_current_game_session_invalid ();

		set_valid_helicopter (FALSE);

      destroy_local_entities ();

		destroy_local_only_entities ();

		reset_comms_data ();

		comms_clear_data_record ();

		destroy_campaign ();

      //
      // Stop the game loop
      //

		set_exit_flight_loop (TRUE);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
