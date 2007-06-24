# Microsoft Developer Studio Project File - Name="modules" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=modules - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "modules.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "modules.mak" CFG="modules - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modules - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "modules - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "modules - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\modules"
# PROP Intermediate_Dir "Release\modules"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\modules" /I "..\aphavoc\source" /I "$(DX_SDK_PATH)\include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x417 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "modules - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "modules___Win32_Debug"
# PROP BASE Intermediate_Dir "modules___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\modules"
# PROP Intermediate_Dir "Debug\modules"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /I "..\modules" /I "..\aphavoc\source" /I "$(DX_SDK_PATH)\include" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x417 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "modules - Win32 Release"
# Name "modules - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "2D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\2d\2dart.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modules\2d\2dview.c
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\modules\2d\2dwrap.c
# SUBTRACT CPP /YX
# End Source File
# End Group
# Begin Group "maths Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\maths\constant.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\fixedpt.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\fixedpt.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\initmath.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\initmath.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\invsqrt.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\invsqrt.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\matrix.c

!IF  "$(CFG)" == "modules - Win32 Release"

!ELSEIF  "$(CFG)" == "modules - Win32 Debug"

# ADD CPP /Od

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\modules\maths\miscmath.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\projtile.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\projtile.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\qternion.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\maths\random.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\range.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\range.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\reciptab.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\reciptab.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\tevent.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\tevent.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\trig.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\trig.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\vector.c
# End Source File
# Begin Source File

SOURCE=..\modules\maths\vertex.h
# End Source File
# End Group
# Begin Group "misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\misc\file_tag.c
# End Source File
# Begin Source File

SOURCE=..\modules\misc\file_tag.h
# End Source File
# Begin Source File

SOURCE=..\modules\misc\IFF.c
# End Source File
# Begin Source File

SOURCE=..\modules\misc\IFF.h
# End Source File
# Begin Source File

SOURCE=..\modules\misc\listitem.h
# End Source File
# End Group
# Begin Group "multi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\multi\directp.c
# End Source File
# Begin Source File

SOURCE=..\modules\multi\dpguid.c
# End Source File
# End Group
# Begin Group "physics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\PHYSICS\BODY.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\BODY.H
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\CONNECT.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\CONNECT.H
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\CONSTRNT.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\CONSTRNT.H
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\DAMPER.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\DAMPER.H
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\FRICTION.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\FRICTION.H
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\OBJECT.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\OBJECT.H
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\SPRING.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS\SPRING.H
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "sound Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\sound\dirsound.c
# End Source File
# Begin Source File

SOURCE=..\modules\sound\dirsound.h
# End Source File
# Begin Source File

SOURCE=..\modules\sound\dsound.c
# End Source File
# Begin Source File

SOURCE=..\modules\sound\dsound3d.c
# End Source File
# Begin Source File

SOURCE=..\modules\sound\soundhlp.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\sound\soundman.c
# End Source File
# Begin Source File

SOURCE=..\modules\sound\soundman.h
# End Source File
# End Group
# Begin Group "system Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\system\ascii.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\assert.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\assert.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\cdrom.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\cpuclock.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\cpuclock.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\debug.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\debug.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\ev_alpha.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\ev_stack.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\ev_stack.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\event.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\event.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\filedir.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\files.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\fpu.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\fpu.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\joyevent.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\joystick.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\joystick.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\keyboard.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\keyboard.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\keyevent.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\memblock.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\memblock.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\memcmp.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\memcmp.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\memory.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\mouse.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\safemem.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\startup.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\startup.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\sysinput.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\sysinput.h
# End Source File
# Begin Source File

SOURCE=..\modules\system\sysmess.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\time.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\timer.c
# End Source File
# Begin Source File

SOURCE=..\modules\system\trackir.c
# ADD CPP /GX
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "3D Header Files"

# PROP Default_Filter ""
# Begin Group "terrain header files"

# PROP Default_Filter ""
# Begin Group "terrain_external"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\3d\terrain\external\terrtype.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "maths Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\maths\constant.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\convert.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\matrix.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\miscmath.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\qternion.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\maths\random.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths\vector.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\modules\2d.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d.h
# End Source File
# Begin Source File

SOURCE=..\modules\CoHokum_d3d.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics.h
# End Source File
# Begin Source File

SOURCE=..\modules\internal_DIK.h
# End Source File
# Begin Source File

SOURCE=..\modules\maths.h
# End Source File
# Begin Source File

SOURCE=..\modules\misc.h
# End Source File
# Begin Source File

SOURCE=..\modules\multi.h
# End Source File
# Begin Source File

SOURCE=..\MODULES\multi_dplay_junk.h
# End Source File
# Begin Source File

SOURCE=..\modules\PHYSICS.H
# End Source File
# Begin Source File

SOURCE=..\modules\sound.h
# End Source File
# Begin Source File

SOURCE=..\modules\system.h
# End Source File
# Begin Source File

SOURCE=..\modules\terrain.h
# End Source File
# Begin Source File

SOURCE=..\modules\TMN_Macros.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2.h
# End Source File
# End Group
# End Target
# End Project
