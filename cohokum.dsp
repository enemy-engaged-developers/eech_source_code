# Microsoft Developer Studio Project File - Name="cohokum" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=cohokum - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cohokum.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cohokum.mak" CFG="cohokum - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cohokum - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "cohokum - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cohokum - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Output/Release"
# PROP Intermediate_Dir "Output/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /w /W0 /GX /O1 /I "C:\Data\Projects\eech\APHAVOC\SOURCE\\" /I "C:\Data\Projects\eech\MODULES" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fr /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib d3dx.lib d3dxd.lib d3dxof.lib DDRAW.LIB DINPUT.LIB DPLAYX.LIB DSETUP.LIB DSOUND.LIB DXGUID.LIB AMSTRMID.LIB Winmm.lib /nologo /subsystem:windows /machine:I386 /libpath:"C:\Data\Projects\eech\APHAVOC\SOURCE\\" /libpath:"C:\Data\Projects\eech\MODULES"

!ELSEIF  "$(CFG)" == "cohokum - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Output/Debug"
# PROP Intermediate_Dir "Output/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /w /W0 /Gm /GX /ZI /Od /I "\Data\Projects\eech\APHAVOC\SOURCE\\" /I "\Data\Projects\eech\MODULES" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib d3dx.lib d3dxd.lib d3dxof.lib DDRAW.LIB DINPUT.LIB DPLAYX.LIB DSETUP.LIB DSOUND.LIB DXGUID.LIB AMSTRMID.LIB Winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "cohokum - Win32 Release"
# Name "cohokum - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "MODULES"

# PROP Default_Filter ""
# Begin Group "System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\SYSTEM\ASCII.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\ASSERT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\CDROM.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\CPUCLOCK.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\DEBUG.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\EV_ALPHA.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\EV_STACK.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\EVENT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\FILEDIR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\FILES.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\FPU.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\JOYEVENT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\JOYSTICK.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\KEYBOARD.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\KEYEVENT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\MEMBLOCK.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\MEMCMP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\MEMORY.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\MOUSE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\SAFEMEM.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\STARTUP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\SYSINPUT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\SYSMESS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\TIME.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\TIMER.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SYSTEM\trackir.C
# End Source File
# End Group
# Begin Group "Graphics"

# PROP Default_Filter "*.c"
# Begin Group "External"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\3DINST.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\BLOCK.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\CIRCLE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\CLIP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\COLOUR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\D3D.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\D3DFOG.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\D3DPOLY.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\D3DSTATE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\D3DVERT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\DASSESS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\DIRDRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\DITHER.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\DRESOL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\GFXZOOM.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\HECKFILL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\LBM.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\LINE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\MIPMAP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\MONOFONT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\MONOSPRT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\MOUSEPTR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\PALETTE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\PIXEL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\PIXELTXT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\POLYD3D.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\POLYLINE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\POLYTEXT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\PSDREAD.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\PSDWRITE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\RENDER.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\RGB.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\RLE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\SCREENS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\SHADFILL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\TEMPBUF.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\TEXTSCRN.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\TEXTSYS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\TEXTURES.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\TEXTUSER.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\TGA.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\TRANBUF.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\VCACHE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\VIEWPORT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\GRAPHICS\ZBUFFER.C
# End Source File
# End Group
# Begin Group "Maths"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\MATHS\CONSTANT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\FIXEDPT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\INITMATH.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\INVSQRT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\MATRIX.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\MISCMATH.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\PROJTILE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\QTERNION.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\RANDOM.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\RANGE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\RECIPTAB.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\TEVENT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\TRIG.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MATHS\VECTOR.C
# End Source File
# End Group
# Begin Group "Misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\MISC\FILE_TAG.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MISC\IFF.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MISC\INT_LIST.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MISC\STRING.C
# End Source File
# End Group
# Begin Group "Multi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\MULTI\DIRECTP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MULTI\DPGUID.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\MULTI\SERVER.C
# End Source File
# End Group
# Begin Group "USERINT2"

# PROP Default_Filter ""
# Begin Group "UI_SYS"

# PROP Default_Filter ""
# Begin Group "UI_ATTRS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_ATTRS\UI_ATTRS.C
# End Source File
# End Group
# Begin Group "UI_FUNCS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_COLOR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_FNS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_GRAPH.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_LINKS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_NOTIF.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_ORG.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_POS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_PTR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_SIZE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_SLID.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_TXT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_FUNCS\UI_UPDT.C
# End Source File
# End Group
# Begin Group "UI_TYPES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_TYPES\UI_TYPES.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_SYS\UI_SYS.C
# End Source File
# End Group
# Begin Group "UI_DRAW"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UIAREA.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UIBUTTON.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UICLIP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UICOLOUR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UIFONT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UIGRAPH.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UIHILGHT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UIORIGIN.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UISCREEN.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_DRAW\UIWINDOW.C
# End Source File
# End Group
# Begin Group "UI_OBJ"

# PROP Default_Filter ""
# Begin Group "AREA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_COL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_FNS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_GRAPH.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_LINKS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_NOTIF.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_ORG.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_POS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_PTR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_SIZE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_SLID.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_TXT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AR_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\AREA\AREA.C
# End Source File
# End Group
# Begin Group "BUTTON"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\BUTTON\BU_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\BUTTON\BU_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\BUTTON\BU_FUNCS.C
# End Source File
# End Group
# Begin Group "CLOSE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\CLOSE\CL_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\CLOSE\CL_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\CLOSE\CL_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\CLOSE\CLOSE.C
# End Source File
# End Group
# Begin Group "INPUT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\INPUT\IN_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\INPUT\IN_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\INPUT\IN_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\INPUT\IN_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\INPUT\IN_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\INPUT\INPUT.C
# End Source File
# End Group
# Begin Group "LIST"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\LIST\LI_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\LIST\LI_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\LIST\LI_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\LIST\LI_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\LIST\LI_SIZE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\LIST\LI_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\LIST\LIST.C
# End Source File
# End Group
# Begin Group "MENU"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\MENU\ME_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\MENU\ME_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\MENU\ME_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\MENU\ME_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\MENU\MENU.C
# End Source File
# End Group
# Begin Group "NUMBER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\NUMBER\NU_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\NUMBER\NU_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\NUMBER\NU_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\NUMBER\NU_FNS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\NUMBER\NU_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\NUMBER\NU_TXT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\NUMBER\NUMBER.C
# End Source File
# End Group
# Begin Group "RADIO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\RADIO\RA_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\RADIO\RA_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\RADIO\RA_FNS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\RADIO\RA_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\RADIO\RADIO.C
# End Source File
# End Group
# Begin Group "SCREEN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SCREEN\SC_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SCREEN\SC_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SCREEN\SC_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SCREEN\SC_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SCREEN\SCREEN.C
# End Source File
# End Group
# Begin Group "SLIDER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\MS_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\MS_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\MS_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\MS_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\MS_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\MSLIDER.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\SL_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\SL_SLID.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\SLIDER.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\VS_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\VS_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\VS_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\VS_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\SLIDER\VSLIDER.C
# End Source File
# End Group
# Begin Group "TEXT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TEXT\TX_COL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TEXT\TX_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TEXT\TX_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TEXT\TX_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TEXT\TX_FNS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TEXT\TX_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TEXT\TX_TXT.C
# End Source File
# End Group
# Begin Group "TOGGLE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TOGGLE\TO_FLAGS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TOGGLE\TO_FNS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TOGGLE\TO_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\TOGGLE\TOGGLE.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_OBJ\UI_OBJ.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_MAN.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\USERINT2\UI_PAINT.C
# End Source File
# End Group
# Begin Group "2D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\2D\2DART.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\2D\2DVIEW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\2D\2DWRAP.C
# End Source File
# End Group
# Begin Group "3D"

# PROP Default_Filter ""
# Begin Group "CLOUDS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\3D\CLOUDS\3DCLOUDS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\CLOUDS\3DTRUMP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\CLOUDS\CLOUDS.C
# End Source File
# End Group
# Begin Group "TERRAIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRBUF.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRCOL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRCONS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRDATA.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRDR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRDRCL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRELEV.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRGEOM.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRMAP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERROBJS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRRE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRSEL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\TERRAIN\TERRTYPE.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\MODULES\3D\3DANIM.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DCLIP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DCONFIG.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DCONSTR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DDISP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DENVGET.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DENVSET.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DEXPLOS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DFACES.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DFCLIP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DHORIZ.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DKEYFR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DLIGHT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DLINE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DMOON.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJBUF.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJDB.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJDRH.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJDRW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJDRZ.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJECT.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJID.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJVB.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJVIS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DOBJZDR.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DPIXEL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DRAIN.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSCENE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSCON.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSHADOW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSPRITE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSTARS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSTRAIL.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSTRIKE.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSUBOBJ.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DSUN.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DTEMP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DTRANS.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DVIEW.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DWFACE1.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\3D\3DWFACE2.C
# End Source File
# End Group
# Begin Group "SOUND"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MODULES\SOUND\DIRSOUND.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SOUND\DSOUND.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SOUND\DSOUND3D.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SOUND\SOUNDHLP.C
# End Source File
# Begin Source File

SOURCE=.\MODULES\SOUND\SOUNDMAN.C
# End Source File
# End Group
# End Group
# Begin Group "APHAVOC"

# PROP Default_Filter ""
# Begin Group "AI"

# PROP Default_Filter ""
# Begin Group "AI_MISC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\AI_MISC\AI_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\AI_MISC\AI_MISC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\AI_MISC\AI_ROUTE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\AI_MISC\AI_SECT.C
# End Source File
# End Group
# Begin Group "FACTION"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\FACTION\BRIEFING.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\FACTION\FACTION.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\FACTION\PARSER.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\FACTION\POPREAD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\FACTION\ROUTEGEN.C
# End Source File
# End Group
# Begin Group "HIGHLEVL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\HIGHLEVL\HIGHLEVL.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\HIGHLEVL\IMAPS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\HIGHLEVL\ORDER.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\HIGHLEVL\REACTION.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\HIGHLEVL\SETUP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\HIGHLEVL\SUITABLE.C
# End Source File
# End Group
# Begin Group "PARSER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\PARSER\PARSGEN.C
# End Source File
# End Group
# Begin Group "TASKGEN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\TASKGEN\ASSIGN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\TASKGEN\CROUTE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\TASKGEN\ENGAGE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\TASKGEN\TASKGEN.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI\AI.C
# End Source File
# End Group
# Begin Group "APP3D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\APP3D\3D_DATA.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\APP3D\3D_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\APP3D\3D_INIT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\APP3D\3D_MAIN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\APP3D\3D_SND.C
# End Source File
# End Group
# Begin Group "APPSOUND"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\APPSOUND\SND_DATA.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\APPSOUND\SND_INIT.C
# End Source File
# End Group
# Begin Group "COMMS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\COMMS\COMM_MAN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\COMMS\COMMS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\COMMS\COMMSSERVER.C
# End Source File
# End Group
# Begin Group "EVENTS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\EVENTS\EV_DEBUG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\EVENTS\EV_FNS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\EVENTS\USERDEF.C
# End Source File
# End Group
# Begin Group "GAMEFLOW"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GAMEFLOW\GAMEFLOW.C
# End Source File
# End Group
# Begin Group "MISC No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\AIRSPEED.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\GAMEEXIT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\LANGUAGE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\MESSAGE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\MISCELL.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\MSG_IN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\MSG_OUT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\SCRNSHOT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\SECURE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\TAGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\TERR_DB.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\TIMEACCL.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\MISC\TOD.C
# End Source File
# End Group
# Begin Group "ENTITY"

# PROP Default_Filter ""
# Begin Group "EN_MISC"

# PROP Default_Filter ""
# Begin Group "EN_ANIM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\EN_MISC\EN_ANIM\EN_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\EN_MISC\EN_ANIM\KEY_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\EN_MISC\EN_ANIM\SUB_ANIM.C
# End Source File
# End Group
# Begin Group "EN_MATHS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\EN_MISC\EN_MATHS\EN_CLLSN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\EN_MISC\EN_MATHS\EN_MATHS.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\EN_MISC\EN_MISC.C
# End Source File
# End Group
# Begin Group "FIXED"

# PROP Default_Filter ""
# Begin Group "CBUILD"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CBUILD\CB_PACK.C
# End Source File
# End Group
# Begin Group "CITY"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CITY\CT_VEC3D.C
# End Source File
# End Group
# Begin Group "CRATER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\CRATER\CR_UPDT.C
# End Source File
# End Group
# Begin Group "OBJECT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\OBJECT\OB_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\OBJECT\OB_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\OBJECT\OB_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\OBJECT\OB_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\OBJECT\OB_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\OBJECT\OB_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\OBJECT\OB_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\OBJECT\OB_VEC3D.C
# End Source File
# End Group
# Begin Group "PYLON"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PY_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\PYLON\PYLON.C
# End Source File
# End Group
# Begin Group "SCENIC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SCENIC\SN_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SCENIC\SN_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SCENIC\SN_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SCENIC\SN_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SCENIC\SN_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SCENIC\SN_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SCENIC\SN_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SCENIC\SN_PACK.C
# End Source File
# End Group
# Begin Group "SEGMENT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SEGMENT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SEGMENT\SG_UPDT.C
# End Source File
# End Group
# Begin Group "SITE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITE\ST_PACK.C
# End Source File
# End Group
# Begin Group "SITEUPDT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\SITEUPDT\SU_UPDT.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FIXED.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_OBJDB.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\FIXED\FX_VEC3D.C
# End Source File
# End Group
# Begin Group "MOBILE"

# PROP Default_Filter ""
# Begin Group "AIRCRAFT"

# PROP Default_Filter ""
# Begin Group "HELICOP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HC_WPN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\HELICOP\HELICOP.C
# End Source File
# End Group
# Begin Group "FIXWING"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FIXWING.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\FIXWING\FW_WPN.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AC_WPN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\AIRCRAFT\AIRCRAFT.C
# End Source File
# End Group
# Begin Group "CARGO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\CARGO\CG_UPDT.C
# End Source File
# End Group
# Begin Group "VEHICLE"

# PROP Default_Filter ""
# Begin Group "ANTI_AIR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\AA_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ANTI_AIR\ANTI_AIR.C
# End Source File
# End Group
# Begin Group "PERSON"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PERSON.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\PERSON\PS_UPDT.C
# End Source File
# End Group
# Begin Group "ROUTED"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\ROUTED.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\ROUTED\RV_UPDT.C
# End Source File
# End Group
# Begin Group "SHIP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SH_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\SHIP\SHIP.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VEHICLE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\VEHICLE\VH_WPN.C
# End Source File
# End Group
# Begin Group "WEAPON"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\DAMAGE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WEAPON.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_ANIM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_CLLSN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_DECOY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_LOAD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_MISC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_SELCT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_SPCH.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\WEAPON\WN_VEC3D.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_ATT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MB_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\MOBILE\MOBILE.C
# End Source File
# End Group
# Begin Group "SYSTEM No. 1"

# PROP Default_Filter ""
# Begin Group "EN_ATTRS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_ATTRS\EN_ATTRS.C
# End Source File
# End Group
# Begin Group "EN_COMMS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_COMMS\EN_COMMS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_COMMS\EN_SESSN.C
# End Source File
# End Group
# Begin Group "EN_DEBUG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_DEBUG\EN_DBARG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_DEBUG\EN_DBDRW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_DEBUG\EN_DBLST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_DEBUG\EN_DBMSG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_DEBUG\EN_STATS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_DEBUG\EN_VALID.C
# End Source File
# End Group
# Begin Group "EN_FUNCS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_ATT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_CHAR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_SND.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_FUNCS\EN_VEC3D.C
# End Source File
# End Group
# Begin Group "EN_MAIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_MAIN\EN_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_MAIN\EN_HEAP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_MAIN\EN_INIT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_MAIN\EN_WORLD.C
# End Source File
# End Group
# Begin Group "EN_MSGS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_MSGS\EN_MSGS.C
# End Source File
# End Group
# Begin Group "EN_TYPES"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_FORCE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_FORMS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_GROUP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_SBTYP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_SIDE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_STATE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_SUPLY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_TASK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_TYPES.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_VIEW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SYSTEM\EN_TYPES\EN_WP.C
# End Source File
# End Group
# End Group
# Begin Group "SPECIAL"

# PROP Default_Filter ""
# Begin Group "BRIDGE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BR_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\BRIDGE\BRIDGE.C
# End Source File
# End Group
# Begin Group "CAMERA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CAMERA.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_ACTN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_ATT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_AUTO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_BUILD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_CHASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_CINE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_DBRF.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_DROP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_EJECT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_END.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_EXPLO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_FLYBY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_MODE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_OVER.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_RECOG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_RVRS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_STAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_VIEW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\CAMERA\CM_WPN.C
# End Source File
# End Group
# Begin Group "EFFECT"

# PROP Default_Filter ""
# Begin Group "EXPLOSN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\EXPLOSN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EXPLOSN\XP_WPN.C
# End Source File
# End Group
# Begin Group "PARTICLE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\PARTICLE\PA_UPDT.C
# End Source File
# End Group
# Begin Group "SMOKELST"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_META.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_SMOKEFUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SL_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SMOKELST\SMOKELST.C
# End Source File
# End Group
# Begin Group "SOUNDEFF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_MOVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_SND.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SE_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SOUNDEFF.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_ATC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_CAL.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_CPG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_DIS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_FAC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_GC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_HDG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_NUM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_SYS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPCH_WMN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SOUNDEFF\SPEECH.C
# End Source File
# End Group
# Begin Group "SPRITE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SP_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\SPRITE\SPRITE.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EF_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EF_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EF_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EF_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EF_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EF_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\EFFECT\EF_VEC3D.C
# End Source File
# End Group
# Begin Group "DIVISION"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DIVISION.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\DIVISION\DV_STR.C
# End Source File
# End Group
# Begin Group "FORCE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FC_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\FORCE\FORCE.C
# End Source File
# End Group
# Begin Group "GROUP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GP_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GROUP\GROUP.C
# End Source File
# End Group
# Begin Group "GUIDE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\AA_ATTCK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\AG_ATTCK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_ATTCK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_COVER.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_NAV.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GD_VEC3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\GUIDE\GUIDE.C
# End Source File
# End Group
# Begin Group "KEYSITE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KEYSITE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\KEYSITE\KS_VEC3D.C
# End Source File
# End Group
# Begin Group "LANDING"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LANDING.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\LANDING\LD_VEC3D.C
# End Source File
# End Group
# Begin Group "PILOT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_NAME.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PI_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\PILOT\PILOT.C
# End Source File
# End Group
# Begin Group "REGEN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\REGEN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\REGEN\RG_VEC3D.C
# End Source File
# End Group
# Begin Group "SECTOR"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_SECCREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SC_SECFUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SECTOR\SECTOR.C
# End Source File
# End Group
# Begin Group "SESSION"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SESS_FN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SESSION.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\SESSION\SS_VEC3D.C
# End Source File
# End Group
# Begin Group "TASK"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TASK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\TASK\TS_VEC3D.C
# End Source File
# End Group
# Begin Group "UPDATE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\UPDATE\UP_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\UPDATE\UP_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\UPDATE\UP_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\UPDATE\UP_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\UPDATE\UP_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\UPDATE\UP_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\UPDATE\UP_UPDATE.C
# End Source File
# End Group
# Begin Group "WAYPOINT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WAYPOINT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_CHAR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_CREAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_DBASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_DSTRY.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_FLOAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_FUNCS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_INT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_PACK.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_PTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_STR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\ENTITY\SPECIAL\WAYPOINT\WP_VEC3D.C
# End Source File
# End Group
# End Group
# End Group
# Begin Group "UI_MENU"

# PROP Default_Filter ""
# Begin Group "DEDICATE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\DEDICATE\DEDI_SC.C
# End Source File
# End Group
# Begin Group "TITLE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\TITLE\TITL_SC.C
# End Source File
# End Group
# Begin Group "ADVERT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\ADVERT\ADVERT.C
# End Source File
# End Group
# Begin Group "MAIN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\MAIN\MAIN_FN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\MAIN\MAIN_SC.C
# End Source File
# End Group
# Begin Group "PLAYER"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\PLAYER\PLAY_GN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\PLAYER\PLAY_MD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\PLAYER\PLAY_SC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\PLAYER\PLAY_WP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\PLAYER\PLAYER.C
# End Source File
# End Group
# Begin Group "MULTIOP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\MULTIOP\MULT_FN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\MULTIOP\MULT_SC.C
# End Source File
# End Group
# Begin Group "GAMETYPE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\GAMETYPE\GAMETYPE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\GAMETYPE\GMTY_SC.C
# End Source File
# End Group
# Begin Group "EXIT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\EXIT\EXIT_SC.C
# End Source File
# End Group
# Begin Group "SESSION No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\SESSION\MISSION.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\SESSION\SESS_SC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\SESSION\UISESS_FN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\SESSION\UISESSION.C
# End Source File
# End Group
# Begin Group "GUNSHIPS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\GUNSHIPS\GUNS_SC.C
# End Source File
# End Group
# Begin Group "INITSC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INITSC\INIT_SC.C
# End Source File
# End Group
# Begin Group "CZONE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\CZONE\ZONE_SC.C
# End Source File
# End Group
# Begin Group "LOADING"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\LOADING\LOAD_SC.C
# End Source File
# End Group
# Begin Group "SESSPARM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\SESSPARM\SPARM_SC.C
# End Source File
# End Group
# Begin Group "INGAME"

# PROP Default_Filter ""
# Begin Group "COMMON"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\COMMON\COMMON.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\COMMON\INFOBAR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\COMMON\MAP.C
# End Source File
# End Group
# Begin Group "CAMPAIGN"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_3D.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_BASE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_BRIEF.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_CHAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_DBF.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_FSMAP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_GROUP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_HIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_INFO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_LIST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_LOG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_MAP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_MENU.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_MSGS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_SAVE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_SELCT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_SORT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_STAT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CA_WLOAD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\CAMPAIGN\CAMPAIGN.C
# End Source File
# End Group
# Begin Group "FFLIGHT"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\FFLIGHT\FF_INFO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\FFLIGHT\FF_MAP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\FFLIGHT\FF_SELCT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\INGAME\FFLIGHT\FFLIGHT.C
# End Source File
# End Group
# End Group
# Begin Group "OPTIONS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\OPTIONS\OP_COMMN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\OPTIONS\OP_CTRLR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\OPTIONS\OP_DYNAM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\OPTIONS\OP_GRAFX.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\OPTIONS\OP_INSND.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\OPTIONS\OP_REAL.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\OPTIONS\OP_SND.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\OPTIONS\OPTIONS.C
# End Source File
# End Group
# Begin Group "CREDITS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\CREDITS\CREDITS.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UI_MENU\MENUS.C
# End Source File
# End Group
# Begin Group "GUNSHIPS No. 1"

# PROP Default_Filter ""
# Begin Group "VIEWS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_DATA.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_DRAW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_EVENT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_EXTRN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_FIXED.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_INIT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_MAIN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_MENU.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_SAFE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_UPDT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\VIEWS\VM_VCKPT.C
# End Source File
# End Group
# Begin Group "AVIONICS"

# PROP Default_Filter ""
# Begin Group "APACHE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_AVEVN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_AVLMP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_DAM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_EO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_FRONT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_HMS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_HUD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_MFD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_RADAR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_THRT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\APACHE\AP_WPN.C
# End Source File
# End Group
# Begin Group "COMANCHE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_AVEVN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_AVLMP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_COWPN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_DAM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_EO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_HMS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_HUD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_MFD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_RADAR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMANCHE\CM_THRT.C
# End Source File
# End Group
# Begin Group "COMMON No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_AVEVN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_DAM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_EO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_HMS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_HUD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_MFD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_NVS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_RADAR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_SYMBL.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_THRT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_WP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\COMMON\CO_WPN.C
# End Source File
# End Group
# Begin Group "HAVOC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_AVEVN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_AVLMP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_DAM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_EKRAN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_EO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_HMS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_HUD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_MFD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_RADAR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_THRT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HAVOC\HA_WPN.C
# End Source File
# End Group
# Begin Group "HOKUM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_AVEVN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_AVLMP.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_DAM.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_EO.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_HMS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_HUD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_MFD.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_RADAR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_TGT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_THRT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\HOKUM\HK_WPN.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\AVIONICS\AVIONICS.C
# End Source File
# End Group
# Begin Group "COCKPITS"

# PROP Default_Filter ""
# Begin Group "APACHE No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\APACHE\AP_CKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\APACHE\AP_INSTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\APACHE\AP_LAMPS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\APACHE\AP_VCKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\APACHE\AP_WIPER.C
# End Source File
# End Group
# Begin Group "COMANCHE No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMANCHE\CM_CKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMANCHE\CM_CPG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMANCHE\CM_CREW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMANCHE\CM_DOORS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMANCHE\CM_LAMPS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMANCHE\CM_PILOT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMANCHE\CM_VCKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMANCHE\CM_WIPER.C
# End Source File
# End Group
# Begin Group "COMMON No. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMMON\CO_CKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMMON\CO_CREW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMMON\CO_VCKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COMMON\CO_WIPER.C
# End Source File
# End Group
# Begin Group "HAVOC No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HAVOC\HA_CKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HAVOC\HA_INSTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HAVOC\HA_LAMPS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HAVOC\HA_VCKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HAVOC\HA_WIPER.C
# End Source File
# End Group
# Begin Group "HOKUM No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_CKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_CPG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_CREW.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_DOORS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_INSTR.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_LAMPS.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_PILOT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_VCKPT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\HOKUM\HK_WIPER.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\COCKPITS\COCKPITS.C
# End Source File
# End Group
# Begin Group "DYNAMICS"

# PROP Default_Filter ""
# Begin Group "APACHE No. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\APACHE\AP_DYN.C
# End Source File
# End Group
# Begin Group "COMANCHE No. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\COMANCHE\CM_DYN.C
# End Source File
# End Group
# Begin Group "COMMON No. 3"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\COMMON\CO_DMG.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\COMMON\CO_DYN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\COMMON\CO_EVENT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\COMMON\CO_FORCE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\COMMON\COLLECT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\COMMON\CYCLIC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\COMMON\PEDAL.C
# End Source File
# End Group
# Begin Group "HAVOC No. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\HAVOC\HA_DYN.C
# End Source File
# End Group
# Begin Group "HOKUM No. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\HOKUM\HO_DYN.C
# End Source File
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GUNSHIPS\DYNAMICS\DYNAMICS.C
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\AI_EXTRN.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\CDMUSIC.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\CMNDLINE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\DEINIT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\FLIGHT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GAME.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GFXFILES.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\GLOBAL.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\INIT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\INSTALL.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\PROJECT.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\TEST.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\UPDATE.C
# End Source File
# Begin Source File

SOURCE=.\APHAVOC\SOURCE\WUTcfg.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MODULES\SYSTEM.H
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
