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

#include "system.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int process_modifiers (event *ev);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int process_joystick_event (event *ev)
{

   int
      loop;

	process_modifiers (ev);

	for (loop = MODIFIER_NONE; loop < NUM_MODIFIER_TYPES; loop ++)
	{

		if ((current_modifier_states & (1 << loop)) || ((current_modifier_states | loop) == 0) || (ev->state == BUTTON_STATE_UP))
		{

			if (registered_events [ev->button][loop].current_state == ev->state)
			{

				continue;
			}

			if (registered_events [ev->button][loop].in_use)
			{

				#if EVENT_DEBUG

				debug_log ("JOYSTICK_EVENT: button %d, modifier %d, current_state = %d, notify_state = %d, event state = %d", ev->button, loop, registered_events [ev->button][loop].current_state, registered_events [ev->button][loop].notify_state, ev->state);

				#endif

				registered_events [ev->button][loop].current_state = ev->state;

				if ((registered_events [ev->button][loop].notify_state == ev->state) ||
					(registered_events [ev->button][loop].notify_state == BUTTON_STATE_EITHER))
				{
		
					if (registered_events [ev->button][loop].function)
					{
		
						#if EVENT_DEBUG
			
						debug_log ("JOYSTICK_EVENT: button event called");
			
						#endif

						ev->modifier = loop;

						registered_events [ev->button][loop].function ((void *) ev);
					}
				}
			}
		}
	}

   return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int process_modifiers (event *ev)
{

   int
      loop,
		button,
      modifier;

   switch (ev->button)
   {

      case DIK_LSHIFT:
      {

         modifier = 1 << MODIFIER_LEFT_SHIFT;

         button = MODIFIER_LEFT_SHIFT;

         break;
      }
   
      case DIK_LCONTROL:
      {
   
         modifier = 1 << MODIFIER_LEFT_CONTROL;

         button = MODIFIER_LEFT_CONTROL;

         break;
      }
   
      case DIK_LMENU:
      {
   
         modifier = 1 << MODIFIER_LEFT_ALT;

         button = MODIFIER_LEFT_ALT;

         break;
      }
   
      case DIK_RSHIFT:
      {
   
         modifier = 1 << MODIFIER_RIGHT_SHIFT;

         button = MODIFIER_RIGHT_SHIFT;
   
         break;
      }
   
      case DIK_RCONTROL:
      {
   
         modifier = 1 << MODIFIER_RIGHT_CONTROL;

         button = MODIFIER_RIGHT_CONTROL;
   
         break;
      }
   
      case DIK_RMENU:
      {
   
         modifier = 1 << MODIFIER_RIGHT_ALT;

         button = MODIFIER_RIGHT_ALT;

         break;
      }
   
      default:
      {

         return FALSE;
      }
   }

   if (ev->state == BUTTON_STATE_UP)
   {

      for (loop = 0; loop < MAX_NUMBER_REGISTERED_EVENTS; loop ++)
      {

         if ((registered_events [loop][button].in_use) && (registered_events [loop][button].current_state != BUTTON_STATE_UP))
         {

				registered_events [loop][button].current_state = BUTTON_STATE_UP;

            if ((registered_events [loop][button].notify_state == BUTTON_STATE_UP) ||
               (registered_events [loop][button].notify_state == BUTTON_STATE_EITHER))
            {

               if (registered_events [loop][button].function)
               {

                  registered_events [loop][button].function ((void *) ev);

						#if EVENT_DEBUG

                  debug_log ("JOYSTICK_EVENT button %d, modifier %d, current_state = %d, notify_state = %d", loop, button, registered_events [loop][button].current_state, registered_events [loop][button].notify_state);

						#endif
               }
            }
         }
      }

      current_modifier_states ^= modifier;
   }
   else
   {

      current_modifier_states |= modifier;
   }

	#if EVENT_DEBUG

   debug_log ("modifier states %d", current_modifier_states);

	#endif

   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
