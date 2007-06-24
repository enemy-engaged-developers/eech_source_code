# Microsoft Developer Studio Project File - Name="entity_special_camera" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=entity_special_camera - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "entity_special_camera.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "entity_special_camera.mak" CFG="entity_special_camera - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "entity_special_camera - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "entity_special_camera - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "entity_special_camera - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\entity_special_camera"
# PROP Intermediate_Dir "Release\entity_special_camera"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\aphavoc\source" /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "_LIB" /D "NDEBUG" /D "WIN32" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x417 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "entity_special_camera - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "entity_special_camera___Win32_Debug"
# PROP BASE Intermediate_Dir "entity_special_camera___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\entity_special_camera"
# PROP Intermediate_Dir "Debug\entity_special_camera"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /I "..\aphavoc\source" /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "WIN32" /D "_DEBUG" /D "DEBUG" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
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

# Name "entity_special_camera - Win32 Release"
# Name "entity_special_camera - Win32 Debug"
# Begin Group "special"

# PROP Default_Filter ""
# Begin Group "camera"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\camera.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\camera.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_actn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_actn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_att.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_att.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_auto.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_auto.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_build.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_build.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_chase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_chase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_cine.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_cine.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_dbrf.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_dbrf.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_drop.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_drop.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_eject.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_eject.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_end.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_end.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_explo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_explo.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_flyby.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_flyby.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_mode.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_mode.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_over.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_over.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_recog.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_recog.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_rvrs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_rvrs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_satel.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_satel.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_stat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_stat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_view.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_view.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_wpn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\camera\cm_wpn.h
# End Source File
# End Group
# End Group
# End Target
# End Project
