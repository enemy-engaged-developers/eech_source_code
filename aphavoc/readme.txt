Use Of EECH Source Code
-----------------------

Please read LICENSE.TXT for the conditions applying to the use of the EECH source code.



What You Will Need
------------------

To compile the EECH source code you will need: -

Watcom C 11.0c
DirectX 7 SDK



Copy all the .lib files from the Directx7 SDK into the \modules\linklib directory.

GUIDS.LIB
D3DIM.LIB
D3DRM.LIB
D3DU.LIB
D3DX.LIB
D3DXD.LIB
D3DXOF.LIB
DDRAW.LIB
DDRAW16.LIB
DINPUT.LIB
DPLAYX.LIB
DSETUP.LIB
DSOUND.LIB
DXGUID.LIB
AMSTRMID.LIB




Copy all the .h files from the Directx7 SDK into the c:\watcom\h\nt directory (assuming you installed Watcom into that directory).



EECH was developed using Watcom C. We prefer to work from a DOS Prompt and there are several batch files to compile the source code using Watcom C.

We are looking into providing a MS Visual C project file but cannot guarantee when or if we can supply it.



How To Make The Project
-----------------------

The source is split into two main folders APHAVOC (game code) and MODULES (library code).

The compilation batch files are in the root of the APHAVOC folder and the compiled PROJECT.EXE file is written to the same folder.

REMAKE.BAT = Clean build - deletes all .OBJ, .LNK, .PCH, .EXE files.

DMAKE.BAT = Debug make - standard development make.

VMAKE.BAT = Optimised make - ASSERT, debug_log etc. still function. Only use for VTune.

OMAKE.BAT = Optimised make - no ASSERTs or debug_log. Debug_fatal still works. Runs fullscreen all the time. Debug keys still available.

CMAKE.BAT = Commercial make. Same as OMAKE.BAT but installs from the CD and removes the debug keys from the game.



Polish Language Versions
------------------------

In order to make a Polish version you will need to change a #define in modules\userint2\ui_draw\uifont.c

change

#define POLISH_VERSION  0

to

#define POLISH_VERSION  1



Russian Language Versions
-------------------------

The original Russian .EXE file was modified by the distrbutor to make improvements to the localisation. Compiling a Russian .EXE from this source code will exclude those changes.



In order to make a Russian version you will need to change a #define in modules\userint2\ui_draw\uifont.c

change

#define RUSSIAN_VERSION	0

to

#define RUSSIAN_VERSION	1



Support From Razorworks
-----------------------

It is unlikely that we can supply any support for the source code.

We suggest posting on the www.simhq.com EECH forum.



All the best from the Razorworks team.



