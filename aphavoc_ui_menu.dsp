# Microsoft Developer Studio Project File - Name="aphavoc_ui_menu" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=aphavoc_ui_menu - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "aphavoc_ui_menu.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "aphavoc_ui_menu.mak" CFG="aphavoc_ui_menu - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "aphavoc_ui_menu - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "aphavoc_ui_menu - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\aphavoc_ui_menu"
# PROP Intermediate_Dir "Release\aphavoc_ui_menu"
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

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\aphavoc_ui_menu"
# PROP Intermediate_Dir "Debug\aphavoc_ui_menu"
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

# Name "aphavoc_ui_menu - Win32 Release"
# Name "aphavoc_ui_menu - Win32 Debug"
# Begin Group "ui_menu"

# PROP Default_Filter ""
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\main\main.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\main\main_fn.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\main\main_sc.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "multiop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\multiop\mult_fn.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\multiop\mult_sc.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\multiop\multiop.h
# End Source File
# End Group
# Begin Group "options"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\op_commn.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\op_ctrlr.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\op_dynam.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\op_grafx.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\op_insnd.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\op_real.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\op_snd.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\options.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\options\options.h
# End Source File
# End Group
# Begin Group "player"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\player\play_gn.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\player\play_md.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\player\play_sc.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\player\play_wp.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\player\player.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\player\player.h
# End Source File
# End Group
# Begin Group "session ui_menu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\session\mission.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\session\sess_sc.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\session\session.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\session\uisess_fn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\session\uisession.c
# End Source File
# End Group
# Begin Group "sessparm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\sessparm\sessparm.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\sessparm\sparm_sc.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "ingame"

# PROP Default_Filter ""
# Begin Group "campaign"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_base.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_base.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_brief.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_brief.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_chat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_chat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_dbf.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_dbf.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_fsmap.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_fsmap.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_group.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_group.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_hist.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_hist.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_info.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_info.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_log.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_log.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_map.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_map.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_menu.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_menu.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_mouse.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_mouse.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_save.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_save.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_selct.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_selct.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_sort.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_sort.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_stat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_stat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_wload.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\ca_wload.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\campaign.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\campaign\campaign.h
# End Source File
# End Group
# Begin Group "common ingame"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\common\common.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\common\common.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\common\infobar.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\common\map.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\common\map.h
# End Source File
# End Group
# Begin Group "fflight"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\fflight\ff_info.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\fflight\ff_map.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\fflight\ff_selct.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\fflight\fflight.c

!IF  "$(CFG)" == "aphavoc_ui_menu - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "aphavoc_ui_menu - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ingame\fflight\fflight.h
# End Source File
# End Group
# End Group
# Begin Group "credits"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\credits\credits.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\credits\credits.h
# End Source File
# End Group
# Begin Group "czone"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\czone\czone.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\czone\zone_sc.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\czone\zone_sc.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\menus.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ui_menu\ui_menu.h
# End Source File
# End Group
# End Target
# End Project
