//**********************************************************************
//	Filename:	KEYMAPPING.C
//	Authors:	Lukas "Retro" Friembichler
//	Date:		20. Mar 2003
//	Update:
//
//	Description:	Well.. hmm... uuuug... rrrriiight...
//					New user-configurable keymapping
//	Developers!:	if you add a key, use set_configurable_event
//					instead of set_event, you can use whatever string you
//					want to 'name' that function (well... please keep it short,
//					50 chars at max) - that´s all you have to do, it might
//					be a good idea telling the users this string, so that
//					they can map it..
//*********************************************************************/
#include "system.h"

#include "cmndline.h"

#include "keymapping.h"

//#define SHOW_COMMENT_LINES	// prints comment-lines into "comment.txt"

//#define TELL_ME_WHAT_YOU_SEE	// prints other lines into "echo.txt"

//#define TIGHT_ARSE_DEBUG	// less forgiving version...

#define SHOW_UNKNOWNS	// if there´s a command registered (by using set_configurable_event () that is NOT in
						// the keymaps.cfg file, I get an error-output file (hopefully)

#define MAXMAPPINGS 300		// Max number of mappings, no real reason for 300 (just a number)

#define MAX_LINE_LENGTH 1024

#define SLIZE 50	// max length one command, keycombo or modifier can have.. (I´m still unconfortable using malloc())

//**********************************************************************
//	this struct represents one key;
//	the name as it is represented in the config file, and the assigned
//	direct-input-keypress (DIK)
//*********************************************************************/
typedef struct {
	char* key_name;
	int dik_val;
} key;

#define NUM_OF_KEYS 142

	key all_keys[NUM_OF_KEYS] = {

	{"ESCAPE",		0x01},
	{"1",			0x02},
	{"2",			0x03},
	{"3",			0x04},
	{"4",			0x05},
	{"5",			0x06},
	{"6",			0x07},
	{"7",			0x08},
	{"8",			0x09},
	{"9",			0x0A},
	{"0",			0x0B},
	{"MINUS",		0x0C},	  /* - on main keyboard */
	{"EQUALS",		0x0D},
	{"BACK",		0x0E},    /* backspace */
	{"BACKSPACE",	0x0E},    /* backspace */
	{"TAB",			0x0F},
	{"Q",			0x10},
	{"W",			0x11},
	{"E",			0x12},
	{"R",			0x13},
	{"T",			0x14},
	{"Y",			0x15},
	{"U",			0x16},
	{"I",			0x17},
	{"O",			0x18},
	{"P",			0x19},
	{"LBRACKET",	0x1A},
	{"RBRACKET",	0x1B},
	{"RETURN",		0x1C},    /* Enter on main keyboard */
	{"LCONTROL",	0x1D},
	{"A",			0x1E},
	{"S",			0x1F},
	{"D",			0x20},
	{"F",			0x21},
	{"G",			0x22},
	{"H",			0x23},
	{"J",			0x24},
	{"K",			0x25},
	{"L",			0x26},
	{"SEMICOLON",	0x27},
	{"APOSTROPHE",	0x28},
	{"GRAVE",		0x29},    /* accent grave */
	{"LSHIFT",		0x2A},
	{"BACKSLASH",	0x2B},
	{"Z",			0x2C},
	{"X",			0x2D},
	{"C",			0x2E},
	{"V",			0x2F},
	{"B",			0x30},
	{"N",			0x31},
	{"M",			0x32},
	{"COMMA",		0x33},
	{"PERIOD",		0x34},    /* . on main keyboard */
	{"SLASH",		0x35},    /* / on main keyboard */
	{"RSHIFT",		0x36},
	{"MULTIPLY",	0x37},
	{"NUMPADSTAR",	0x37},    /* * on numeric keypad */
	{"LMENU",		0x38},
	{"LALT",		0x38},    /* left Alt */
	{"SPACE",		0x39},
	{"CAPITAL",		0x3A},
	{"CAPSLOCK",	0x3A},
	{"F1",			0x3B},
	{"F2",			0x3C},
	{"F3",			0x3D},
	{"F4",			0x3E},
	{"F5",			0x3F},
	{"F6",			0x40},
	{"F7",			0x41},
	{"F8",			0x42},
	{"F9",			0x43},
	{"F10",			0x44},
	{"NUMLOCK",		0x45},
	{"SCROLL",		0x46},    /* Scroll Lock */
	{"NUMPAD7",		0x47},
	{"NUMPAD8",		0x48},
	{"NUMPAD9",		0x49},
	{"SUBTRACT",	0x4A},
	{"NUMPADMINUS",	0x4A},    /* - on numeric keypad */
	{"NUMPAD4",		0x4B},
	{"NUMPAD5",		0x4C},
	{"NUMPAD6",		0x4D},
	{"ADD",			0x4E},
	{"NUMPADPLUS",	0x4E},    /* + on numeric keypad */
	{"NUMPAD1",		0x4F},
	{"NUMPAD2",		0x50},
	{"NUMPAD3",		0x51},
	{"NUMPAD0",		0x52},
	{"DECIMAL",		0x53},
	{"NUMPADPERIOD",0x53},    /* . on numeric keypad */
	{"OEM_102",		0x56},    /* < > | on UK/Germany keyboards */
	{"F11",			0x57},
	{"F12",			0x58},
	{"F13",			0x64},    /*                     (NEC PC98) */
	{"F14",			0x65},    /*                     (NEC PC98) */
	{"F15",			0x66},    /*                     (NEC PC98) */
	{"KANA",		0x70},    /* (Japanese keyboard)            */
	{"ABNT_C1",		0x73},    /* / ? on Portugese (Brazilian) keyboards */
	{"CONVERT",		0x79},    /* (Japanese keyboard)            */
	{"NOCONVERT",	0x7B},    /* (Japanese keyboard)            */
	{"YEN",			0x7D},    /* (Japanese keyboard)            */
	{"ABNT_C2",		0x7E},    /* Numpad . on Portugese (Brazilian) keyboards */
	{"NUMPADEQUALS",0x8D},    /* = on numeric keypad (NEC PC98) */
	{"CIRCUMFLEX",	0x90},    /* (Japanese keyboard)            */
	{"AT",			0x91},    /*                     (NEC PC98) */
	{"COLON",		0x92},    /*                     (NEC PC98) */
	{"UNDERLINE",	0x93},    /*                     (NEC PC98) */
	{"KANJI",		0x94},    /* (Japanese keyboard)            */
	{"STOP",		0x95},    /*                     (NEC PC98) */
	{"AX",			0x96},    /*                     (Japan AX) */
	{"UNLABELED",	0x97},    /*                        (J3100) */
	{"NUMPADENTER",	0x9C},    /* Enter on numeric keypad */
	{"RCONTROL",	0x9D},
	{"NUMPADCOMMA",	0xB3},    /* , on numeric keypad (NEC PC98) */
	{"DIVIDE",		0xB5},
	{"NUMPADSLASH",	0xB5},    /* / on numeric keypad */
	{"SYSRQ",		0xB7},
	{"RMENU",		0xB8},
	{"RALT",		0xB8},    /* right Alt */
	{"PAUSE",		0xC5},    /* Pause */
	{"HOME",		0xC7},    /* Home on arrow keypad */
	{"UP",			0xC8},
	{"UPARROW",		0xC8},
	{"PRIOR",		0xC9},
	{"PGUP",		0xC9},   /* PgUp on arrow keypad */
	{"LEFT",		0xCB},
	{"LEFTARROW",	0xCB},    /* LeftArrow on arrow keypad */
	{"RIGHT",		0xCD},
	{"RIGHTARROW",	0xCD},    /* RightArrow on arrow keypad */
	{"END",			0xCF},    /* End on arrow keypad */
	{"DOWN",		0xD0},
	{"DOWNARROW",	0xD0},    /* DownArrow on arrow keypad */
	{"NEXT",		0xD1},
	{"PGDN",		0xD1},    /* PgDn on arrow keypad */
	{"INSERT",		0xD2},    /* Insert on arrow keypad */
	{"DELETE",		0xD3},    /* Delete on arrow keypad */
	{"LWIN",		0xDB},    /* Left Windows key */
	{"RWIN",		0xDC},    /* Right Windows key */
	{"APPS",		0xDD},    /* AppMenu key */
	{"POWER",		0xDE},
	{"SLEEP",		0xDF},
	{"WAKE",		0xE3}
	};

//**********************************************************************
//	this struct represents one line of the config-file;
//	functionID, key, modifer and state
//*********************************************************************/
typedef struct {
	char	functionID[SLIZE];
	int		key,		// This is actually the DIK of the key..
			modifier,	// I guess with multiple modifiers per key this could become a bitfield..
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
//					not yet used
//
//*********************************************************************/
int check_for_validity ( void )
{
	int i = 0;
	int j = 0;
	int numOfDuplicates = 0;

	int tmp_key;
	int tmp_mod;

	for ( i = 0; i < number_of_commands; i++)
	{
		tmp_key = keymaps[i].key;
		tmp_mod = keymaps[i].modifier;

		for ( j = 0; j < number_of_commands; j++)
		{
			if ((keymaps[i].key = tmp_key)&&(keymaps[i].modifier = tmp_mod))
			{
				numOfDuplicates++;
				if (numOfDuplicates > 1)
					debug_fatal ( "Duplicate key+modifier combination (%i) (%i)",tmp_key,tmp_mod );
			}
		}
		numOfDuplicates = 0;
	}

	return 0;
}

//**********************************************************************
//
// Function:    get_DIK_from_string
// Date:		21.3.2003
// Author:		Retro
//
// Description:		returns direct-input-keypress (DIK) on input-string.
//					uses the all_keys array defined above
//
//*********************************************************************/
int get_DIK_from_string ( char* keystring )
{
	int i;
	int retval = 0;

	for ( i = 0; i < NUM_OF_KEYS; i++ )
	{
		if ( strcmp(all_keys[i].key_name,keystring) == 0 )
		{
			retval = all_keys[i].dik_val;
			break;
		}
	}
	if ( retval == 0 )	// kinda crappy way of error checking.. if reval is still 0, obviously no string matched.
	{
		debug_fatal ( "Don´t know key %s",keystring );
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
// Function:    CleanUpString
// Date:		24.4.2003
// Author:		Wolfram "Osram" Kuss (Retro took this from the
//					Battle of Britain Source)
//
// Description:		removes trailing white space.
//					returns pointer to first non-whitespace char
//
//*********************************************************************/
char * CleanUpString(char *s)
{ char *ret = s, *t; 
  while ((*ret != 0) && ((*ret == ' ') || (*ret == 9 /* Tab */)))
	  ret++;
  t = &ret[ strlen(ret) ]; // t points to the 0 now
  t--;
  while ( (t >= ret) && ((*t == ' ') || (*t == 9 /* Tab */) || (*t == 10) || (*t == 13)))
  { *t = 0;
    t--;
  }
  return ret;
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
	char	command[SLIZE],
			key[SLIZE],
			modifier[SLIZE],
			state[SLIZE];

	FILE* fp;

	int line = 0;	// represents number of read lines
	char myString [ MAX_LINE_LENGTH ], *myStrPtr, *res = 0;

	assert ( filename );

	fp = fopen(filename, "r");

	if (fp == NULL)
	{
		//**********************************************************************
		//	No Keymapping file is present, create one
		//*********************************************************************/
		fp = fopen(filename, "w");
		if (fp != NULL)
		{
			int i;

			for (i = 0; i < origcount; i++)
			{
				fprintf(fp,"%s",standard_key_mapping[i]);
			}
		
		}
		//**********************************************************************
		//	Ooops..
		//*********************************************************************/
		else
		{
//			command_line_key_mapping = FALSE;	// pointless, as we don´t go any further anyway..
			debug_fatal ( "Could not open or create file %s",filename );
		}
	}
	else
	{

		fseek(fp,0,SEEK_SET);	// go to begin of file..

		//**********************************************************************
		//	main loop.. I read one line, then 4 strings from this line
		//*********************************************************************/
		while ((!feof(fp))&&(line < MAXMAPPINGS))
		{
			res = fgets(myString, 1024, fp);
			if ( res == NULL )
				break;
			myStrPtr = CleanUpString ( myString );
			if (myStrPtr[0] != 0)
			{
				if (myStrPtr[0] != '#')
				// found non-empty, non-comment line. Parse it
				{
					//**********************************************************************
					//	file-syntax: command \t key \t modifier \t state\n
					//*********************************************************************/
					if (sscanf(myStrPtr,"%s %s %s %s",command,key,modifier,state) != 4)
					{
#ifdef TIGHT_ARSE_DEBUG
						debug_fatal ( "Remember to salt the fries: less than 4 strings in a line" );
#else
						continue;	// This makes us just disregard that line..
#endif
					}

					sprintf((keymaps[line]).functionID,"%s",command);
					(keymaps[line]).key = get_DIK_from_string(key);
					(keymaps[line]).modifier = get_modifier_from_string(modifier);
					(keymaps[line]).state = get_key_state_from_string(state);
#ifdef TELL_ME_WHAT_YOU_SEE
					{
						FILE* fp = fopen("echo.txt","at");
						fprintf(fp,"%s %i %i %i\n",(keymaps[line]).functionID,(keymaps[line]).key,(keymaps[line]).modifier,(keymaps[line]).state);
						fclose(fp);
					}
#endif
					line++;
				}
#ifdef SHOW_COMMENT_LINES
				else
				{
					FILE* fp = fopen("comment.txt","at");
					fprintf(fp,"comment: %s\n",myStrPtr);
					fclose(fp);
				}
#endif
			}
		}
		fclose(fp);

		number_of_commands = line;
	}

//	check_for_validity ();
}

//**********************************************************************
//
// Function:    configurable_event
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
void configurable_event (char* functionID, void (*func) ( struct EVENT *ev))
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
				FILE* fp = fopen("unknown.txt","at");
				fprintf(fp,"dunno %s\n",functionID);
				fclose(fp);
			}
		}
		number_of_matches = 0;
#endif
	}
}