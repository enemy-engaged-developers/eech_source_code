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

int main(int m_argc, char **m_argv);

#define NULL ((void*)0)

//#define __STRICT_ANSI__ 1

/* Time is often seen as a flow in one direction. But I have seen the face
* of time, and I can say "They are wrong". This game has one file in
* modules/system that is called time.h. This interfers with the system wide
* file with the same name (time.h). The reason of this is that gcc includes
* all files with apostrophes first ("file") and global files last (<file>)
* There are two solutions to this:
* 1. Change name of the file in modules/system to something else (aphc_time.h)
* 2. Add -I- (dash I dash) to the gcc command line. */

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <float.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <malloc.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include <ctype.h>
/* SDL must allways be included above any #pragma pack(1) */
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define LOWORD(l)           ((unsigned short int )(l))
#define HIWORD(l)           ((unsigned short int )(((unsigned int)(l) >> 16) & 0xFFFF))

#define DI_DEGREES                  100

#define DIK_ESCAPE          0x01
#define DIK_1               0x02
#define DIK_2               0x03
#define DIK_3               0x04
#define DIK_4               0x05
#define DIK_5               0x06
#define DIK_6               0x07
#define DIK_7               0x08
#define DIK_8               0x09
#define DIK_9               0x0A
#define DIK_0               0x0B
#define DIK_MINUS           0x0C    /* - on main keyboard */
#define DIK_EQUALS          0x0D
#define DIK_BACK            0x0E    /* backspace */
#define DIK_TAB             0x0F
#define DIK_Q               0x10
#define DIK_W               0x11
#define DIK_E               0x12
#define DIK_R               0x13
#define DIK_T               0x14
#define DIK_Y               0x15
#define DIK_U               0x16
#define DIK_I               0x17
#define DIK_O               0x18
#define DIK_P               0x19
#define DIK_LBRACKET        0x1A
#define DIK_RBRACKET        0x1B
#define DIK_RETURN          0x1C    /* Enter on main keyboard */
#define DIK_LCONTROL        0x1D
#define DIK_A               0x1E
#define DIK_S               0x1F
#define DIK_D               0x20
#define DIK_F               0x21
#define DIK_G               0x22
#define DIK_H               0x23
#define DIK_J               0x24
#define DIK_K               0x25
#define DIK_L               0x26
#define DIK_SEMICOLON       0x27
#define DIK_APOSTROPHE      0x28
#define DIK_GRAVE           0x29    /* accent grave */
#define DIK_LSHIFT          0x2A
#define DIK_BACKSLASH       0x2B
#define DIK_Z               0x2C
#define DIK_X               0x2D
#define DIK_C               0x2E
#define DIK_V               0x2F
#define DIK_B               0x30
#define DIK_N               0x31
#define DIK_M               0x32
#define DIK_COMMA           0x33
#define DIK_PERIOD          0x34    /* . on main keyboard */
#define DIK_SLASH           0x35    /* / on main keyboard */
#define DIK_RSHIFT          0x36
#define DIK_MULTIPLY        0x37    /* * on numeric keypad */
#define DIK_LMENU           0x38    /* left Alt */
#define DIK_SPACE           0x39
#define DIK_CAPITAL         0x3A
#define DIK_F1              0x3B
#define DIK_F2              0x3C
#define DIK_F3              0x3D
#define DIK_F4              0x3E
#define DIK_F5              0x3F
#define DIK_F6              0x40
#define DIK_F7              0x41
#define DIK_F8              0x42
#define DIK_F9              0x43
#define DIK_F10             0x44
#define DIK_NUMLOCK         0x45
#define DIK_SCROLL          0x46    /* Scroll Lock */
#define DIK_NUMPAD7         0x47
#define DIK_NUMPAD8         0x48
#define DIK_NUMPAD9         0x49
#define DIK_SUBTRACT        0x4A    /* - on numeric keypad */
#define DIK_NUMPAD4         0x4B
#define DIK_NUMPAD5         0x4C
#define DIK_NUMPAD6         0x4D
#define DIK_ADD             0x4E    /* + on numeric keypad */
#define DIK_NUMPAD1         0x4F
#define DIK_NUMPAD2         0x50
#define DIK_NUMPAD3         0x51
#define DIK_NUMPAD0         0x52
#define DIK_DECIMAL         0x53    /* . on numeric keypad */
#define DIK_OEM_102         0x56    /* < > | on UK/Germany keyboards */
#define DIK_F11             0x57
#define DIK_F12             0x58

#define DIK_F13             0x64    /*                     (NEC PC98) */
#define DIK_F14             0x65    /*                     (NEC PC98) */
#define DIK_F15             0x66    /*                     (NEC PC98) */

#define DIK_KANA            0x70    /* (Japanese keyboard)            */
#define DIK_ABNT_C1         0x73    /* / ? on Portugese (Brazilian) keyboards */
#define DIK_CONVERT         0x79    /* (Japanese keyboard)            */
#define DIK_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define DIK_YEN             0x7D    /* (Japanese keyboard)            */
#define DIK_ABNT_C2         0x7E    /* Numpad . on Portugese (Brazilian) keyboards */
#define DIK_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define DIK_CIRCUMFLEX      0x90    /* (Japanese keyboard)            */
#define DIK_AT              0x91    /*                     (NEC PC98) */
#define DIK_COLON           0x92    /*                     (NEC PC98) */
#define DIK_UNDERLINE       0x93    /*                     (NEC PC98) */
#define DIK_KANJI           0x94    /* (Japanese keyboard)            */
#define DIK_STOP            0x95    /*                     (NEC PC98) */
#define DIK_AX              0x96    /*                     (Japan AX) */
#define DIK_UNLABELED       0x97    /*                        (J3100) */
#define DIK_NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define DIK_RCONTROL        0x9D
#define DIK_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define DIK_DIVIDE          0xB5    /* / on numeric keypad */
#define DIK_SYSRQ           0xB7
#define DIK_RMENU           0xB8    /* right Alt */
#define DIK_PAUSE           0xC5    /* Pause */
#define DIK_HOME            0xC7    /* Home on arrow keypad */
#define DIK_UP              0xC8    /* UpArrow on arrow keypad */
#define DIK_PRIOR           0xC9    /* PgUp on arrow keypad */
#define DIK_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define DIK_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define DIK_END             0xCF    /* End on arrow keypad */
#define DIK_DOWN            0xD0    /* DownArrow on arrow keypad */
#define DIK_NEXT            0xD1    /* PgDn on arrow keypad */
#define DIK_INSERT          0xD2    /* Insert on arrow keypad */
#define DIK_DELETE          0xD3    /* Delete on arrow keypad */
#define DIK_LWIN            0xDB    /* Left Windows key */
#define DIK_RWIN            0xDC    /* Right Windows key */
#define DIK_APPS            0xDD    /* AppMenu key */
#define DIK_POWER           0xDE
#define DIK_SLEEP           0xDF

#define DIK_WAKE            0xE3

/*
 *  Alternate names for keys, to facilitate transition from DOS.
 */
#define DIK_BACKSPACE       DIK_BACK            /* backspace */
#define DIK_NUMPADSTAR      DIK_MULTIPLY        /* * on numeric keypad */
#define DIK_LALT            DIK_LMENU           /* left Alt */
#define DIK_CAPSLOCK        DIK_CAPITAL         /* CapsLock */
#define DIK_NUMPADMINUS     DIK_SUBTRACT        /* - on numeric keypad */
#define DIK_NUMPADPLUS      DIK_ADD             /* + on numeric keypad */
#define DIK_NUMPADPERIOD    DIK_DECIMAL         /* . on numeric keypad */
#define DIK_NUMPADSLASH     DIK_DIVIDE          /* / on numeric keypad */
#define DIK_RALT            DIK_RMENU           /* right Alt */
#define DIK_UPARROW         DIK_UP              /* UpArrow on arrow keypad */
#define DIK_PGUP            DIK_PRIOR           /* PgUp on arrow keypad */
#define DIK_LEFTARROW       DIK_LEFT            /* LeftArrow on arrow keypad */
#define DIK_RIGHTARROW      DIK_RIGHT           /* RightArrow on arrow keypad */
#define DIK_DOWNARROW       DIK_DOWN            /* DownArrow on arrow keypad */
#define DIK_PGDN            DIK_NEXT            /* PgDn on arrow keypad */

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} GUID, *LPGUID;

#endif /* GUID_DEFINED */

typedef unsigned int HDC;

typedef struct tagKERNINGPAIR {
   unsigned short int	wFirst;
   unsigned short int	wSecond;
   int						iKernAmount;
} KERNINGPAIR, *LPKERNINGPAIR;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NO_INTERNAL_MODULES

#include "system/external/assert.h"

#include "system/external/cdrom.h"

#include "system/external/cpuclock.h"

#include "system/external/startup.h"

#include "system/external/filedir.h"

#include "system/external/fpu.h"

#include "system/external/debug.h"

#include "system/external/input.h"

#include "system/external/keyboard.h"

#include "system/external/mouse.h"

#include "system/external/event.h"

#include "system/external/joyevent.h"

#include "system/external/joystick.h"

// crh 030320 quick hack to provide prototypes
#include "system/external/trackir.h"

#include "system/external/ev_stack.h"

#include "system/external/ev_alpha.h"

#include "system/external/keyevent.h"

#include "system/external/time.h"

#include "system/external/timer.h"

#include "system/external/safemem.h"

#include "system/external/files.h"

#include "system/external/memblock.h"

#include "system/external/memcmp.h"

#include "system/external/memory.h"

#include "system/external/sysmess.h"

#include "system/external/ascii.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#else /* INTERNAL_MODULES */

#pragma pack (8)


#include <sys/sysinfo.h>

#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef enum {
  TRUE = 1,
  FALSE = 0
} BOOL;

typedef short SHORT;

#pragma pack (4)


#define RGB(r,b,g) ((SDL_Color) { r, b, g, 0 })

#include "system/unix/unix_cdrom.h"
#include "system/unix/unix_startup.h"
#include "system/unix/unix_filedir.h"
#include "system/unix/unix_debug.h"
#include "system/unix/unix_timer.h"
#include "system/unix/unix_sysmess.h"
#include "system/unix/unix_keyboard.h"
#include "system/unix/unix_time.h"
#include "system/unix/unix_assert.h"
#include "system/unix/unix_mouse.h"
#include "system/unix/unix_joystick.h"
#include "system/unix/unix_files.h"
#include "system/unix/unix_memory.h"
//#include "system/unix/unix_sysinput.h" // sysinput is not used under linux.
#include "system/memblock.h" /* No unix-prefix beacuse file is unchanged */
#include "system/event.h" /* No unix-prefix beacuse file is unchanged */
#include "system/keyevent.h" /* No unix-prefix beacuse file is unchanged */
#include "system/joyevent.h" /* No unix-prefix beacuse file is unchanged */
#include "system/fpu.h" /* No unix-prefix beacuse file is unchanged */
#include "system/safemem.h" /* No unix-prefix beacuse file is mostly unchanged */
#include "system/memcmp.h" /* No unix-prefix beacuse file is unchanged */
#include "system/cpuclock.h" /* No unix-prefix beacuse file is unchanged */
#include "system/trackir.h" /* No unix-prefix beacuse file is unchanged */
#include "system/ev_stack.h" /* No unix-prefix beacuse file is unchanged */
#include "system/ev_alpha.h" /* No unix-prefix beacuse file is unchanged */
#include "system/ascii.h" /* No unix-prefix beacuse file is unchanged */

#endif /* NO_INTERNAL_MODULES */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

