# Microsoft Developer Studio Project File - Name="aphavoc_gunships" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=aphavoc_gunships - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "aphavoc_gunships.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "aphavoc_gunships.mak" CFG="aphavoc_gunships - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "aphavoc_gunships - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "aphavoc_gunships - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "aphavoc_gunships - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\aphavoc_gunships"
# PROP Intermediate_Dir "Release\aphavoc_gunships"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\aphavoc\source" /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x417 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "aphavoc_gunships - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "aphavoc_gunships___Win32_Debug"
# PROP BASE Intermediate_Dir "aphavoc_gunships___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\aphavoc_gunships"
# PROP Intermediate_Dir "Debug\aphavoc_gunships"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /I "..\aphavoc\source" /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
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

# Name "aphavoc_gunships - Win32 Release"
# Name "aphavoc_gunships - Win32 Debug"
# Begin Group "gunships"

# PROP Default_Filter ""
# Begin Group "avionics"

# PROP Default_Filter ""
# Begin Group "apache"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_avevn.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_avlmp.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_dam.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_dam.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_eo.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_front.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_hms.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_hud.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_mfd.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_radar.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_radar.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_tgt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_thrt.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\apache\ap_wpn.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "comanche"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_avevn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_avevn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_avlmp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_avlmp.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_cowpn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_cowpn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_dam.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_dam.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_eo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_eo.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_hms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_hms.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_hud.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_hud.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_mfd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_mfd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_radar.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_radar.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_tgt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_thrt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\comanche\cm_thrt.h
# End Source File
# End Group
# Begin Group "common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_avevn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_avevn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_dam.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_dam.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_eo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_eo.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_hms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_hms.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_hud.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_hud.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_mfd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_mfd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_nvs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_nvs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_pfz.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_pfz.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_radar.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_radar.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_symbl.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_symbl.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_tgt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_thrt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_thrt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_tsd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_tsd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_wp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_wp.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_wpn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\common\co_wpn.h
# End Source File
# End Group
# Begin Group "havoc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_avevn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_avlmp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_dam.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_dam.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_ekran.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_eo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_hms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_hud.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_mfd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_radar.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_thrt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\havoc\ha_wpn.c
# End Source File
# End Group
# Begin Group "hokum"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_avevn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_avlmp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_dam.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_eo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_hms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_hud.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_mfd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_radar.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_thrt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hokum\hk_wpn.c
# End Source File
# End Group
# Begin Group "blackhawk avionics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_avevn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_avlmp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_dam.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_eo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_front.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_hms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_hud.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_mfd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_radar.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_thrt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\blackhawk\bh_wpn.c
# End Source File
# End Group
# Begin Group "ah64a avionics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_avevn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_avlmp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_dam.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_dam.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_eo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_front.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_hms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_hud.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_mfd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_radar.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_radar.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_thrt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ah64a\ah_wpn.c
# End Source File
# End Group
# Begin Group "hind avionics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_avevn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_avlmp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_dam.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_ekran.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_eo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_hms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_hud.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_mfd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_radar.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_thrt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\hind\hi_wpn.c
# End Source File
# End Group
# Begin Group "ka50 avionics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_avevn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_avion.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_avlmp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_dam.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_ekran.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_eo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_hms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_hud.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_mfd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_radar.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_tgt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_thrt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\ka50\hm_wpn.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\avionics.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\avionics\avionics.h
# End Source File
# End Group
# Begin Group "dynamics"

# PROP Default_Filter ""
# Begin Group "common dynamics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\bas_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\bas_dyn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\co_dmg.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\co_dmg.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\co_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\co_dyn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\co_event.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\co_event.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\co_force.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\co_force.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\collect.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\collect.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\cyclic.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\cyclic.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\pedal.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\pedal.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\vec_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\common\vec_dyn.h
# End Source File
# End Group
# Begin Group "ah64a dynamics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\ah64a\ah_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\ah64a\ah_dyn.h
# End Source File
# End Group
# Begin Group "apache dynamic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\apache\ap_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\apache\ap_dyn.h
# End Source File
# End Group
# Begin Group "blackhawk dynamics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\blackhawk\bh_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\blackhawk\bh_dyn.h
# End Source File
# End Group
# Begin Group "comanche dynamics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\comanche\cm_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\comanche\cm_dyn.h
# End Source File
# End Group
# Begin Group "havoc dynamics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\havoc\ha_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\havoc\ha_dyn.h
# End Source File
# End Group
# Begin Group "hind dynamics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\hind\hi_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\hind\hi_dyn.h
# End Source File
# End Group
# Begin Group "hokum dynamics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\hokum\ho_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\hokum\ho_dyn.h
# End Source File
# End Group
# Begin Group "ka50 dynamics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\ka50\hm_dyn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\ka50\hm_dyn.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\dynamics.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\dynamics\dynamics.h
# End Source File
# End Group
# Begin Group "views"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\views.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_data.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_data.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_event.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_event.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_extrn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_extrn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_fixed.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_fixed.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_headmovement.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_headmovement.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_init.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_init.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_main.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_main.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_menu.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_menu.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_safe.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_safe.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_satinfo.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_satinfo.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_types.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\views\vm_vckpt.h
# End Source File
# End Group
# Begin Group "cockpits"

# PROP Default_Filter ""
# Begin Group "apache cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap3d_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_aspd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_balt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_clock.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_instr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_instr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_lamps.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_lamps.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\apache\ap_wiper.h
# End Source File
# End Group
# Begin Group "comanche cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_cpg.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_cpg.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_crew.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_crew.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_doors.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_doors.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_lamps.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_lamps.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_pilot.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_pilot.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\comanche\cm_wiper.h
# End Source File
# End Group
# Begin Group "common cockpits"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\common\co_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\common\co_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\common\co_crew.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\common\co_crew.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\common\co_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\common\co_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\common\co_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\common\co_wiper.h
# End Source File
# End Group
# Begin Group "havoc  cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_aspd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_balt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_clock.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_erpm.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_etmp.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_etrq.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_fuel.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_gmtr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_instr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_instr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_lamps.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_lamps.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_ralt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_rrpm.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_vsi.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\havoc\ha_wiper.h
# End Source File
# End Group
# Begin Group "hokum cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_cpg.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_cpg.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_crew.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_crew.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_doors.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_doors.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_instr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_instr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_lamps.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_lamps.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_pilot.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_pilot.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hokum\hk_wiper.h
# End Source File
# End Group
# Begin Group "ah64a cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_aspd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_balt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_clock.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_instr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_instr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_lamps.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_lamps.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ah64a\ah_wiper.h
# End Source File
# End Group
# Begin Group "blackhawk cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_aspd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_balt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_clock.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_instr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_instr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_lamps.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_lamps.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\blackhawk\bh_wiper.h
# End Source File
# End Group
# Begin Group "hind cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_aspd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_balt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_clock.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_erpm.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_etmp.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_etrq.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_fuel.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_gmtr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_instr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_instr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_lamps.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_lamps.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_ralt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_rrpm.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_vsi.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\hind\hi_wiper.h
# End Source File
# End Group
# Begin Group "ka50 cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_aspd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_balt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_ckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_ckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_clock.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_erpm.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_etmp.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_etrq.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_fuel.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_gmtr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_instr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_instr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_lamps.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_lamps.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_ralt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_rrpm.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_vckpt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_vckpt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_vsi.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_wiper.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\ka50\hm_wiper.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\cockpits.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gunships\cockpits\cockpits.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\gunships\gunships.h
# End Source File
# End Group
# End Target
# End Project
