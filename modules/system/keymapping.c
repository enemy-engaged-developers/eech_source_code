//**********************************************************************
//	Filename:	KEYMAPPING.C
//	Authors:	Lukas "Retro" Friembichler
//	Date:		20. Mar 2003
//	Update:
//
//	Description:	Well.. hmm... uuuug... rrrriiight...
//*********************************************************************/
#include "system.h"

#include "cmndline.h"

#define SHOW_UNKNOWNS	// if there´s a command registerd (by using set_configurable_event () that is NOT in
						// the keymaps.cfg file, I get an error-output file (hopefully)

#define MAXMAPPINGS 300		// Max number of mappings, no real reason for 300 (just a number)

#define SLIZE 50	// max length one command, keycombo or modifier can have.. (I´m wary of malloc())

//**********************************************************************
//	this struct represents one line of the config-file;
//	functionID, key, modifer and state
//*********************************************************************/
typedef struct keymap {
	char	functionID[SLIZE];
	int		key,
			modifier,
			state;
} mapline;

static mapline keymaps[MAXMAPPINGS];

static int number_of_commands = 0;	// number of keymappings in the above array

//**********************************************************************
//
// Function:    check_for_validity
// Date:		21.3.2003
// Author:		Retro
//
// Description:		Should check for duplicate key+modifier combos,
//					and also for typos (?)
//					not yet implemented
//
//*********************************************************************/
int check_for_validity ( void )
{
	return 0;
}

//**********************************************************************
//
// Function:    get_DIK_from_string
// Date:		21.3.2003
// Author:		Retro
//
// Description:		returns direct-input-keypress (DIK) on input-string.
//					there are no else-ifs here, as only 127 else ifs can
//					follow one if.. have the find some other method of
//					checking for wrong input..
//
//*********************************************************************/
int get_DIK_from_string ( char* keystring )
{
	int retval = 0;

	if ( strcmp ( keystring, "ESCAPE" ) == 0 )
		retval = 0x01;
	if ( strcmp ( keystring, "1" ) == 0 )
		retval = 0x02;
	if ( strcmp ( keystring, "2" ) == 0 )
		retval = 0x03;
	if ( strcmp ( keystring, "3" ) == 0 )
		retval = 0x04;
	if ( strcmp ( keystring, "4" ) == 0 )
		retval = 0x05;
	if ( strcmp ( keystring, "5" ) == 0 )
		retval = 0x06;
	if ( strcmp ( keystring, "6" ) == 0 )
		retval = 0x07;
	if ( strcmp ( keystring, "7" ) == 0 )
		retval = 0x08;
	if ( strcmp ( keystring, "8" ) == 0 )
		retval = 0x09;
	if ( strcmp ( keystring, "9" ) == 0 )
		retval = 0x0A;
	if ( strcmp ( keystring, "0" ) == 0 )
		retval = 0x0B;
	if ( strcmp ( keystring, "MINUS" ) == 0 )
		retval =  0x0C;  /* - on main keyboard */
	if ( strcmp ( keystring, "EQUALS" ) == 0 )
		retval = 0x0D;
	if (( strcmp ( keystring, "BACK" ) == 0 ) || ( strcmp ( keystring, "BACKSPACE" ) == 0 ))
		retval = 0x0E;    /* backspace */
	if ( strcmp ( keystring, "TAB" ) == 0 )
		retval = 0x0F;
	if ( strcmp ( keystring, "Q" ) == 0 )
		retval = 0x10;
	if ( strcmp ( keystring, "W" ) == 0 )
		retval = 0x11;
	if ( strcmp ( keystring, "E" ) == 0 )
		retval = 0x12;
	if ( strcmp ( keystring, "R" ) == 0 )
		retval = 0x13;
	if ( strcmp ( keystring, "T" ) == 0 )
		retval = 0x14;
	if ( strcmp ( keystring, "Y" ) == 0 )
		retval = 0x15;
	if ( strcmp ( keystring, "U" ) == 0 )
		retval = 0x16;
	if ( strcmp ( keystring, "I" ) == 0 )
		retval = 0x17;
	if ( strcmp ( keystring, "O" ) == 0 )
		retval = 0x18;
	if ( strcmp ( keystring, "P" ) == 0 )
		retval = 0x19;
	if ( strcmp ( keystring, "LBRACKET" ) == 0 )
		retval = 0x1A;
	if ( strcmp ( keystring, "RBRACKET" ) == 0 )
		retval = 0x1B;
	if ( strcmp ( keystring, "RETURN" ) == 0 )
		retval = 0x1C;    /* Enter on main keyboard */
	if ( strcmp ( keystring, "LCONTROL" ) == 0 )
		retval = 0x1D;
	if ( strcmp ( keystring, "A" ) == 0 )
		retval = 0x1E;
	if ( strcmp ( keystring, "S" ) == 0 )
		retval = 0x1F;
	if ( strcmp ( keystring, "D" ) == 0 )
		retval = 0x20;
	if ( strcmp ( keystring, "F" ) == 0 )
		retval = 0x21;
	if ( strcmp ( keystring, "G" ) == 0 )
		retval = 0x22;
	if ( strcmp ( keystring, "H" ) == 0 )
		retval = 0x23;
	if ( strcmp ( keystring, "J" ) == 0 )
		retval = 0x24;
	if ( strcmp ( keystring, "K" ) == 0 )
		retval = 0x25;
	if ( strcmp ( keystring, "L" ) == 0 )
		retval = 0x26;
	if ( strcmp ( keystring, "SEMICOLON" ) == 0 )
		retval = 0x27;
	if ( strcmp ( keystring, "APOSTROPHE" ) == 0 )
		retval = 0x28;
	if ( strcmp ( keystring, "GRAVE" ) == 0 )
		retval = 0x29;    /* accent grave */
	if ( strcmp ( keystring, "LSHIFT" ) == 0 )
		retval = 0x2A;
	if ( strcmp ( keystring, "BACKSLASH" ) == 0 )
		retval = 0x2B;
	if ( strcmp ( keystring, "Z" ) == 0 )
		retval = 0x2C;
	if ( strcmp ( keystring, "X" ) == 0 )
		retval = 0x2D;
	if ( strcmp ( keystring, "C" ) == 0 )
		retval = 0x2E;
	if ( strcmp ( keystring, "V" ) == 0 )
		retval = 0x2F;
	if ( strcmp ( keystring, "B" ) == 0 )
		retval = 0x30;
	if ( strcmp ( keystring, "N" ) == 0 )
		retval = 0x31;
	if ( strcmp ( keystring, "M" ) == 0 )
		retval = 0x32;
	if ( strcmp ( keystring, "COMMA" ) == 0 )
		retval = 0x33;
	if ( strcmp ( keystring, "PERIOD" ) == 0 )
		retval = 0x34;    /* . on main keyboard */
	if ( strcmp ( keystring, "SLASH" ) == 0 )
		retval = 0x35;    /* / on main keyboard */
	if ( strcmp ( keystring, "RSHIFT" ) == 0 )
		retval = 0x36;
	if (( strcmp ( keystring, "MULTIPLY" ) == 0 ) || ( strcmp ( keystring, "NUMPADSTAR" ) == 0 ))
		retval = 0x37;    /* * on numeric keypad */
	if (( strcmp ( keystring, "LMENU" ) == 0 ) || ( strcmp ( keystring, "LALT" ) == 0 ))
		retval = 0x38;    /* left Alt */
	if ( strcmp ( keystring, "SPACE" ) == 0 )
		retval = 0x39;
	if (( strcmp ( keystring, "CAPITAL" ) == 0 ) || ( strcmp ( keystring, "CAPSLOCK" ) == 0 ))
		retval = 0x3A;
	if ( strcmp ( keystring, "F1" ) == 0 )
		retval = 0x3B;
	if ( strcmp ( keystring, "F2" ) == 0 )
		retval = 0x3C;
	if ( strcmp ( keystring, "F3" ) == 0 )
		retval = 0x3D;
	if ( strcmp ( keystring, "F4" ) == 0 )
		retval = 0x3E;
	if ( strcmp ( keystring, "F5" ) == 0 )
		retval = 0x3F;
	if ( strcmp ( keystring, "F6" ) == 0 )
		retval = 0x40;
	if ( strcmp ( keystring, "F7" ) == 0 )
		retval = 0x41;
	if ( strcmp ( keystring, "F8" ) == 0 )
		retval = 0x42;
	if ( strcmp ( keystring, "F9" ) == 0 )
		retval = 0x43;
	if ( strcmp ( keystring, "F10" ) == 0 )
		retval = 0x44;
	if ( strcmp ( keystring, "NUMLOCK" ) == 0 )
		retval = 0x45;
	if ( strcmp ( keystring, "SCROLL" ) == 0 )
		retval = 0x46;    /* Scroll Lock */
	if ( strcmp ( keystring, "NUMPAD7" ) == 0 )
		retval = 0x47;
	if ( strcmp ( keystring, "NUMPAD8" ) == 0 )
		retval = 0x48;
	if ( strcmp ( keystring, "NUMPAD9" ) == 0 )
		retval = 0x49;
	if (( strcmp ( keystring, "SUBTRACT" ) == 0 ) || ( strcmp ( keystring, "NUMPADMINUS" ) == 0 ))
		retval = 0x4A;    /* - on numeric keypad */
	if ( strcmp ( keystring, "NUMPAD4" ) == 0 )
		retval = 0x4B;
	if ( strcmp ( keystring, "NUMPAD5" ) == 0 )
		retval = 0x4C;
	if ( strcmp ( keystring, "NUMPAD6" ) == 0 )
		retval = 0x4D;
	if (( strcmp ( keystring, "ADD" ) == 0 ) || ( strcmp ( keystring, "NUMPADPLUS" ) == 0 ))
		retval = 0x4E;    /* + on numeric keypad */
	if ( strcmp ( keystring, "NUMPAD1" ) == 0 )
		retval = 0x4F;
	if ( strcmp ( keystring, "NUMPAD2" ) == 0 )
		retval = 0x50;
	if ( strcmp ( keystring, "NUMPAD3" ) == 0 )
		retval = 0x51;
	if ( strcmp ( keystring, "NUMPAD0" ) == 0 )
		retval = 0x52;
	if (( strcmp ( keystring, "DECIMAL" ) == 0 ) || ( strcmp ( keystring, "NUMPADPERIOD" ) == 0 ))
		retval = 0x53;    /* . on numeric keypad */
	if ( strcmp ( keystring, "OEM_102" ) == 0 )
		retval = 0x56;    /* < > | on UK/Germany keyboards */
	if ( strcmp ( keystring, "F11" ) == 0 )
		retval = 0x57;
	if ( strcmp ( keystring, "F12" ) == 0 )
		retval = 0x58;
	if ( strcmp ( keystring, "F13" ) == 0 )
			retval = 0x64;    /*                     (NEC PC98) */
	if ( strcmp ( keystring, "F14" ) == 0 )
			retval = 0x65;    /*                     (NEC PC98) */
	if ( strcmp ( keystring, "F15" ) == 0 )
			retval = 0x66;    /*                     (NEC PC98) */
	if ( strcmp ( keystring, "KANA" ) == 0 )
			retval = 0x70;    /* (Japanese keyboard)            */
	if ( strcmp ( keystring, "ABNT_C1" ) == 0 )
			retval = 0x73;    /* / ? on Portugese (Brazilian) keyboards */
	if ( strcmp ( keystring, "CONVERT" ) == 0 )
			retval = 0x79;    /* (Japanese keyboard)            */
	if ( strcmp ( keystring, "NOCONVERT" ) == 0 )
			retval = 0x7B;    /* (Japanese keyboard)            */
	if ( strcmp ( keystring, "YEN" ) == 0 )
			retval = 0x7D;    /* (Japanese keyboard)            */
	if ( strcmp ( keystring, "ABNT_C2" ) == 0 )
			retval = 0x7E;    /* Numpad . on Portugese (Brazilian) keyboards */
	if ( strcmp ( keystring, "NUMPADEQUALS" ) == 0 )
			retval = 0x8D;    /* = on numeric keypad (NEC PC98) */
	if ( strcmp ( keystring, "CIRCUMFLEX" ) == 0 )
			retval = 0x90;    /* (Japanese keyboard)            */
	if ( strcmp ( keystring, "AT" ) == 0 )
			retval = 0x91;    /*                     (NEC PC98) */
	if ( strcmp ( keystring, "COLON" ) == 0 )
			retval = 0x92;    /*                     (NEC PC98) */
	if ( strcmp ( keystring, "UNDERLINE" ) == 0 )
			retval = 0x93;    /*                     (NEC PC98) */
	if ( strcmp ( keystring, "KANJI" ) == 0 )
			retval = 0x94;    /* (Japanese keyboard)            */
	if ( strcmp ( keystring, "STOP" ) == 0 )
			retval = 0x95;    /*                     (NEC PC98) */
	if ( strcmp ( keystring, "AX" ) == 0 )
			retval = 0x96;    /*                     (Japan AX) */
	if ( strcmp ( keystring, "UNLABELED" ) == 0 )
			retval = 0x97;    /*                        (J3100) */
	if ( strcmp ( keystring, "NUMPADENTER" ) == 0 )
			retval = 0x9C;    /* Enter on numeric keypad */
	if ( strcmp ( keystring, "RCONTROL" ) == 0 )
			retval = 0x9D;
	if ( strcmp ( keystring, "NUMPADCOMMA" ) == 0 )
			retval = 0xB3;    /* , on numeric keypad (NEC PC98) */
	if (( strcmp ( keystring, "DIVIDE" ) == 0 ) || ( strcmp ( keystring, "NUMPADSLASH" ) == 0 ))
			retval = 0xB5;    /* / on numeric keypad */
	if ( strcmp ( keystring, "SYSRQ" ) == 0 )
			retval = 0xB7;
	if (( strcmp ( keystring, "RMENU" ) == 0 ) || ( strcmp ( keystring, "RALT" ) == 0 ))
			retval = 0xB8;    /* right Alt */
	if ( strcmp ( keystring, "PAUSE" ) == 0 )
			retval = 0xC5;    /* Pause */
	if ( strcmp ( keystring, "HOME" ) == 0 )
			retval = 0xC7;    /* Home on arrow keypad */
	if (( strcmp ( keystring, "UP" ) == 0 ) || ( strcmp ( keystring, "UPARROW" ) == 0 ))
			retval = 0xC8;    /* UpArrow on arrow keypad */
	if (( strcmp ( keystring, "PRIOR" ) == 0 ) || ( strcmp ( keystring, "PGUP" ) == 0 ))
			retval = 0xC9;    /* PgUp on arrow keypad */
	if (( strcmp ( keystring, "LEFT" ) == 0 ) || ( strcmp ( keystring, "LEFTARROW" ) == 0 ))
			retval = 0xCB;    /* LeftArrow on arrow keypad */
	if (( strcmp ( keystring, "RIGHT" ) == 0 ) || ( strcmp ( keystring, "RIGHTARROW" ) == 0 ))
			retval = 0xCD;    /* RightArrow on arrow keypad */
	if ( strcmp ( keystring, "END" ) == 0 )
			retval = 0xCF;    /* End on arrow keypad */
	if (( strcmp ( keystring, "DOWN" ) == 0 ) || ( strcmp ( keystring, "DOWNARROW" ) == 0 ))
			retval = 0xD0;    /* DownArrow on arrow keypad */
	if (( strcmp ( keystring, "NEXT" ) == 0 ) || ( strcmp ( keystring, "PGDN" ) == 0 ))
			retval = 0xD1;    /* PgDn on arrow keypad */
	if ( strcmp ( keystring, "INSERT" ) == 0 )
			retval = 0xD2;    /* Insert on arrow keypad */
	if ( strcmp ( keystring, "DELETE" ) == 0 )
			retval = 0xD3;    /* Delete on arrow keypad */
	if ( strcmp ( keystring, "LWIN" ) == 0 )
			retval = 0xDB;    /* Left Windows key */
	if ( strcmp ( keystring, "RWIN" ) == 0 )
			retval = 0xDC;    /* Right Windows key */
	if ( strcmp ( keystring, "APPS" ) == 0 )
			retval = 0xDD;    /* AppMenu key */
	if ( strcmp ( keystring, "POWER" ) == 0 )
			retval = 0xDE;
	if ( strcmp ( keystring, "SLEEP" ) == 0 )
			retval = 0xDF;
	if ( strcmp ( keystring, "WAKE" ) == 0 )
			retval = 0xE3;

	if ( retval == 0 )	// kinda crappy way of error checking.. if reval is still 0, obviously no string matched.
	{
		debug_fatal("Don´t know key %s",keystring);
	}

	return retval;
}

//**********************************************************************
//
// Function:    get_modifier_from_string
// Date:		21.3.2003
// Author:		Retro
//
// Description:		returns modifier enum on input-string
//					note that in non-debug builds, right and left modifiers
//					are considered the same...
//
//*********************************************************************/
int get_modifier_from_string ( char* modifierstring )
{
	int retval = 0;
	
	if ( strcmp ( modifierstring, "MODIFIER_NONE") == 0 )
		retval = MODIFIER_NONE;
	else if ( strcmp ( modifierstring, "MODIFIER_LEFT_SHIFT") == 0 )
		retval = MODIFIER_LEFT_SHIFT;
	else if ( strcmp ( modifierstring, "MODIFIER_LEFT_CONTROL") == 0 )
		retval = MODIFIER_LEFT_CONTROL;
	else if ( strcmp ( modifierstring, "MODIFIER_LEFT_ALT") == 0 )
		retval = MODIFIER_LEFT_ALT;
	else if ( strcmp ( modifierstring, "MODIFIER_RIGHT_SHIFT") == 0 )
		retval = MODIFIER_RIGHT_SHIFT;
    else if ( strcmp ( modifierstring, "MODIFIER_RIGHT_CONTROL") == 0 )
		retval = MODIFIER_RIGHT_CONTROL;
    else if ( strcmp ( modifierstring, "MODIFIER_RIGHT_ALT") == 0 )
		retval = MODIFIER_RIGHT_ALT;
	else
	{
		debug_fatal ( "Don´t know modifier %s",modifierstring );
	}

	return retval;
}

//**********************************************************************
//
// Function:    get_key_state_from_string
// Date:		21.3.2003
// Author:		Retro
//
// Description:		returns key_state (not button or mouse) enum on input-string
//
//*********************************************************************/
int get_key_state_from_string ( char* statestring )
{
	int retval = 0;

	if ( strcmp ( statestring, "KEY_STATE_INVALID") == 0 )
		retval = KEY_STATE_INVALID;
	else if ( strcmp ( statestring, "KEY_STATE_UP") == 0 )
		retval = KEY_STATE_UP;
	else if ( strcmp ( statestring, "KEY_STATE_DOWN") == 0 )
		retval = KEY_STATE_DOWN;
	else if ( strcmp ( statestring, "KEY_STATE_EITHER") == 0 )
		retval = KEY_STATE_EITHER;
	else
	{
		debug_fatal ( "Don´t know key_state %s",statestring );
	}

	return retval;
}

//**********************************************************************
//
// Function:    read_mapping_from_file
// Date:		21.3.2003
// Author:		Retro
//
// Description:		reads the user key mappings from file and puts them
//					into keymaps array
//
//*********************************************************************/
void read_mapping_from_file ( char* filename )
{

	//**********************************************************************
	//	temp strings..
	//*********************************************************************/
	char	buffer[SLIZE*2],
			command[SLIZE],
			key[SLIZE],
			modifier[SLIZE],
			state[SLIZE];

	FILE* fp;

	int i = 0;		// represents number of read strings (3 strings per line)
	int line = 0;	// represents number of read lines

	assert ( filename );

	fp = fopen(filename, "r");

	assert ( fp );

	if (fp == NULL)
	{
//		command_line_key_mapping = FALSE;	// pointless, as we don´t go any further anyway..
		debug_fatal ( "Could not open file %s",filename );
	}
	else
	{

		fseek(fp,0,SEEK_SET);	// got to begin of file..

		//**********************************************************************
		//	main loop.. I read 4 strings per line
		//*********************************************************************/
		while (i%4 < MAXMAPPINGS)
		{
			if ((fscanf(fp,"%s",buffer) != EOF)&&(strlen(buffer) > 0))
			{
				if (strlen(buffer) < SLIZE)
				{
					//**********************************************************************
					//	file-syntax: command \t key \t modifier \n
					//*********************************************************************/
					switch(i%4)
					{
						case 0: sprintf(command,"%s",buffer);break;
						case 1: sprintf(key,"%s",buffer);break;
						case 2: sprintf(modifier,"%s",buffer);break;
						case 3: sprintf(state,"%s",buffer);break;
						default: assert ( 0 );break;
					}
					//**********************************************************************
					//	i%4 == 3 means 'end of line'; copying the data into the struct
					//*********************************************************************/
					if (i%4 == 3)
					{
						sprintf((keymaps[line]).functionID,"%s",command);
						(keymaps[line]).key = get_DIK_from_string(key);
						(keymaps[line]).modifier = get_modifier_from_string(modifier);
						(keymaps[line]).state = get_key_state_from_string(state);
						line++;
					}
				}
				else	// a read string is bigger than SLIZE
				{
					assert ( 0 );
					break;
				}
			}
			else	// EOF or fscanf error.. (nothing read)
				break;
			i++;
		}
		fclose(fp);

		number_of_commands = line;
	}
}

//**********************************************************************
//
// Function:    my_new_set_event
// Date:		21.3.2003
// Author:		Retro
//
// Description:		get´s called from user_configured_event which is
//					to be called instead of set_event. Compares the
//					passed functionID to all ID´s of the keymaps array,
//					if it finds one, it does a set_event call with the
//					key combination specified in the array..
//
//*********************************************************************/
void my_new_set_event (char* functionID, void (*func) ( struct EVENT *ev))
{
	int i = 0;
#ifdef SHOW_UNKNOWNS
	int number_of_matches = 0;
#endif

	//**********************************************************************
	//	just run through the array, compare the functionIDs...
	//*********************************************************************/
	for (i; i < number_of_commands; i++)
	{
		if ( strcmp (functionID, (keymaps[i]).functionID ) == 0 )
		{
			//**********************************************************************
			//	if command is actually mapped..
			//*********************************************************************/
			if ( ( (keymaps[i]).key != 999 ) && ( (keymaps[i]).state != 999 ) )
			{
				set_event ((keymaps[i]).key, (keymaps[i]).modifier, (keymaps[i]).state, func);
#ifdef SHOW_UNKNOWNS
				number_of_matches++;
#endif
//				break;	// would speed up the mapping, however multiple key combinations for ONE function
						// would not work anymore..
			}
		}
#ifdef SHOW_UNKNOWNS
		if (i >= number_of_commands)
		{
			if (number_of_matches == 0)
			{
				FILE* fp = fopen("keyerr.txt","at");
				fprintf(fp,"dunno %s\n",functionID);
				fclose(fp);
			}
		}
		number_of_matches = 0;
#endif
	}
}