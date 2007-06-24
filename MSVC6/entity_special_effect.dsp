# Microsoft Developer Studio Project File - Name="entity_special_effect" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=entity_special_effect - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "entity_special_effect.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "entity_special_effect.mak" CFG="entity_special_effect - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "entity_special_effect - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "entity_special_effect - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "entity_special_effect - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\entity_special_effect"
# PROP Intermediate_Dir "Release\entity_special_effect"
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

!ELSEIF  "$(CFG)" == "entity_special_effect - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "entity_special_effect___Win32_Debug"
# PROP BASE Intermediate_Dir "entity_special_effect___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\entity_special_effect"
# PROP Intermediate_Dir "Debug\entity_special_effect"
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

# Name "entity_special_effect - Win32 Release"
# Name "entity_special_effect - Win32 Debug"
# Begin Group "effect"

# PROP Default_Filter ""
# Begin Group "explosion"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\explosn.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\explosn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_dbase.c
# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_wpn.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\explosn\xp_wpn.h
# End Source File
# End Group
# Begin Group "smokelst"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_dbase.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_draw.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_float.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_list.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_meta.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_meta.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_move.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_move.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_smokefuncs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_smokefuncs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_updt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_vec3d.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\sl_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\smokelst.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\smokelst\smokelst.h
# End Source File
# End Group
# Begin Group "soundeff"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_move.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_move.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_proto.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_snd.c
# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_snd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\se_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\soundeff.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\soundeff.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_atc.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_cal.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_cpg.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_dis.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_fac.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_gc.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_hdg.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_num.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_sys.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\spch_wmn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\speech.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\soundeff\speech.h
# End Source File
# End Group
# Begin Group "downwash"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\downwash\downwash.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\downwash\downwash.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\downwash\dw_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\downwash\dw_dbase.h
# End Source File
# End Group
# Begin Group "particle"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\pa_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\particle\particle.h
# End Source File
# End Group
# Begin Group "sprite"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sp_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sprite.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\sprite\sprite.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\ef_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\special\effect\effect.h
# End Source File
# End Group
# End Target
# End Project
