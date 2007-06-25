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

SOURCE=..\aphavoc\source\entity\special\bridge\br_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\br_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\bridge.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\bridge\bridge.h
# End Source File
# End Group
# Begin Group "division"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\division.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\division.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\division\dv_str.h
# End Source File
# End Group
# Begin Group "force"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\fc_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\force.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\force\force.h
# End Source File
# End Group
# Begin Group "group"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\gp_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\group.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\group\group.h
# End Source File
# End Group
# Begin Group "guide"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\aa_attck.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\aa_attck.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\ag_attck.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\ag_attck.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_attck.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_attck.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_cover.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_cover.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_nav.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_nav.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\gd_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\guide.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\guide\guide.h
# End Source File
# End Group
# Begin Group "keysite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\keysite.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\keysite.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_draw.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_draw.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\keysite\ks_vec3d.h
# End Source File
# End Group
# Begin Group "landing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\landing.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\landing.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_draw.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_draw.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\landing\ld_vec3d.h
# End Source File
# End Group
# Begin Group "pilot"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_draw.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_name.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_name.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_vec3d.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pi_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pilot.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\pilot\pilot.h
# End Source File
# End Group
# Begin Group "regen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\regen.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\regen.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\regen_private.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_dbase.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_dbase.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\regen\rg_vec3d.h
# End Source File
# End Group
# Begin Group "session"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\sess_fn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\session.c

!IF  "$(CFG)" == "entity_special - Win32 Release"

# ADD CPP /Zd

!ELSEIF  "$(CFG)" == "entity_special - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\session.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_updt.c
# ADD CPP /Zi
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\session\ss_vec3d.h
# End Source File
# End Group
# Begin Group "task"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\task.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\task.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\task\ts_vec3d.h
# End Source File
# End Group
# Begin Group "waypoint"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\waypoint.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\waypoint.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_char.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_char.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\waypoint\wp_vec3d.h
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
