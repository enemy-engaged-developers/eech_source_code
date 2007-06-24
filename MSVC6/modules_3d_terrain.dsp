# Microsoft Developer Studio Project File - Name="modules_3d_terrain" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=modules_3d_terrain - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "modules_3d_terrain.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "modules_3d_terrain.mak" CFG="modules_3d_terrain - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modules_3d_terrain - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "modules_3d_terrain - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "modules_3d_terrain - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\modules_3d_terrain"
# PROP Intermediate_Dir "Release\modules_3d_terrain"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\modules\3d" /I "..\modules" /I "..\aphavoc\source" /I "$(DX_SDK_PATH)\include" /D "_LIB" /D "NDEBUG" /D "WIN32" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x417 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "modules_3d_terrain - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\modules_3d_terrain"
# PROP Intermediate_Dir "Debug\modules_3d_terrain"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /I "..\modules\3d" /I "..\modules" /I "..\aphavoc\source" /I "$(DX_SDK_PATH)\include" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
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

# Name "modules_3d_terrain - Win32 Release"
# Name "modules_3d_terrain - Win32 Debug"
# Begin Group "3D terrain Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\3d\terrain\terrbuf.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrcons.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrdata.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrdr.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrdrcl.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrelev.c

!IF  "$(CFG)" == "modules_3d_terrain - Win32 Release"

!ELSEIF  "$(CFG)" == "modules_3d_terrain - Win32 Debug"

# ADD CPP /Ob1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrgeom.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrmap.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrobjs.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrre.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrsel.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrtype.c
# End Source File
# End Group
# Begin Group "3D terrain Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\3d\terrain\terrain.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrdata.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrdr.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrdrcl.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrgeom.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\terrain\terrtype.h
# End Source File
# End Group
# End Target
# End Project
