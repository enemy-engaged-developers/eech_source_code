# Microsoft Developer Studio Project File - Name="entity_mobile" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=entity_mobile - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "entity_mobile.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "entity_mobile.mak" CFG="entity_mobile - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "entity_mobile - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "entity_mobile - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\entity_mobile"
# PROP Intermediate_Dir "Release\entity_mobile"
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

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\entity_mobile"
# PROP Intermediate_Dir "Debug\entity_mobile"
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

# Name "entity_mobile - Win32 Release"
# Name "entity_mobile - Win32 Debug"
# Begin Group "entity"

# PROP Default_Filter ""
# Begin Group "mobile"

# PROP Default_Filter ""
# Begin Group "aircraft"

# PROP Default_Filter ""
# Begin Group "fixwing"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fixwing.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fixwing.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_anim.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_creat.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_dstry.c
# ADD CPP /Zi
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_float.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_move.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_msgs.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\fixwing\fw_updt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "helicop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_anim.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_creat.c
# ADD CPP /Zi
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_draw.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_dstry.c
# ADD CPP /Zi
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_float.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_list.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_move.c
# ADD CPP /Zi
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_msgs.c
# ADD CPP /Zi
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_proto.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_snd.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_tgt.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_updt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_vec3d.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\hc_wpn.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\helicop.c
# ADD CPP /Zi
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\helicop\helicop.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_anim.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_anim.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_dbase.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_float.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_list.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_msgs.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_str.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_tgt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_vec3d.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\ac_wpn.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\aircraft.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\aircraft\aircraft.h
# End Source File
# End Group
# Begin Group "weapon"

# PROP Default_Filter ""
# Begin Group "configs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\2s19.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\abrams.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\aist.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\apache.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\apache_a.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\avenger.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\blckhawk.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\bmp2.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\bmp3.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\bradley.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\brdm2.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\btr80.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\candid.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\chaparrl.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\chinook.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\comanche.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\cub.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\falcon.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\flanker.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\freestyl.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\frogfoot.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\fulcrum.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\globe.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\gopher.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\grad.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\grison.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\harrier.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\havoc.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\helix.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\hercules.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\hind.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\hip.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\hokum.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\hook.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\hornet.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\jolly.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\kiev.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\kiowa.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\krivak.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\m109a2.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\m113a2.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\mlrs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\ohp.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\osprey.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\rs_inf_k.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\rs_inf_s.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\seacobra.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\seaknght.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\stallion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\supcobra.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\t80u.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\tarawa.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\thndrblt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\unarmed.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\us_inf_k.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\us_inf_s.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\vulcan.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\configs\werewolf.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\damage.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\damage.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\TMN_weapon_misc.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\weapon.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\weapon.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_anim.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_cllsn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_decoy.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_load.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_misc.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_move.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_selct.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_spch.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\weapon\wn_vec3d.c
# End Source File
# End Group
# Begin Group "vehicle"

# PROP Default_Filter ""
# Begin Group "anti_air"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\anti_air\aa_creat.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\anti_air\aa_dstry.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\anti_air\aa_move.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\anti_air\aa_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\anti_air\AA_WPN.C
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\anti_air\anti_air.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\anti_air\anti_air.h
# End Source File
# End Group
# Begin Group "person"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\person\person.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\person\person.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\person\ps_anim.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\person\ps_creat.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\person\ps_dstry.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\person\ps_move.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\person\ps_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "routed"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\routed.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\routed.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_anim.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_creat.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_dstry.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_float.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_move.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_msgs.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_pack.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_snd.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_tgt.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_updt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\routed\rv_wpn.c
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "ship"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\sh_anim.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\sh_creat.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\sh_dstry.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\sh_move.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\sh_msgs.c

!IF  "$(CFG)" == "entity_mobile - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "entity_mobile - Win32 Debug"

# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\sh_snd.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\sh_tgt.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\sh_wpn.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\ship.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\ship\ship.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vehicle.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vehicle.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_anim.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_float.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_int.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\vehicle\vh_wpn.c
# End Source File
# End Group
# Begin Group "cargo"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cargo.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_move.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_move.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\cargo\cg_updt.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_att.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_att.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_move.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_move.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_tgt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mb_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mobile.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\mobile\mobile.h
# End Source File
# End Group
# End Group
# End Target
# End Project
