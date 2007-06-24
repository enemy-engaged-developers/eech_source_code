# Microsoft Developer Studio Project File - Name="entity_special" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=entity_special - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "entity_special.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "entity_special.mak" CFG="entity_special - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "entity_special - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "entity_special - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "entity_special - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\entity_special"
# PROP Intermediate_Dir "Release\entity_special"
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

!ELSEIF  "$(CFG)" == "entity_special - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\entity_special"
# PROP Intermediate_Dir "Debug\entity_special"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /I "..\aphavoc\source" /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "WIN32" /D "_DEBUG" /D "DEBUG" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
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

# Name "entity_special - Win32 Release"
# Name "entity_special - Win32 Debug"
# Begin Group "special"

# PROP Default_Filter ""
# Begin Group "bridge"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\bridge.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\bridge.h
# End Source File
# End Group
# Begin Group "division"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\division.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\division.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_creat.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_dbase.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_dstry.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_list.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "force"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_updt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\force.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\force.h
# End Source File
# End Group
# Begin Group "group"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_dbase.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\group.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\group.h
# End Source File
# End Group
# Begin Group "guide"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\aa_attck.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\ag_attck.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_attck.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_cover.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_list.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_vec3d.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\guide.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\guide.h
# End Source File
# End Group
# Begin Group "keysite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\keysite.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\keysite.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_creat.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_dbase.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_dstry.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "landing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\landing.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\landing.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "pilot"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_draw.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_list.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_name.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_str.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_vec3d.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pilot.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pilot.h
# End Source File
# End Group
# Begin Group "regen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\regen.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\regen.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\regen_private.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_creat.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_dstry.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_float.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_list.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_updt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_vec3d.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "session"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\session.c

!IF  "$(CFG)" == "entity_special - Win32 Release"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_special - Win32 Debug"

# ADD CPP /Zi
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\session.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_creat.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_dstry.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_float.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_list.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_updt.c
# ADD CPP /Zi
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_vec3d.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "task"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\task.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\task.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_dbase.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "waypoint"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\waypoint.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\waypoint.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_dbase.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "sector"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_seccreat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_seccreat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_secfuncs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sc_secfuncs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sector.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\sector\sector.h
# End Source File
# End Group
# Begin Group "update"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_update.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\update\up_update.h
# End Source File
# End Group
# End Group
# End Target
# End Project
