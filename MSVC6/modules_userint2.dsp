# Microsoft Developer Studio Project File - Name="modules_userint2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=modules_userint2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "modules_userint2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "modules_userint2.mak" CFG="modules_userint2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modules_userint2 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "modules_userint2 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "modules_userint2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\modules_userint2"
# PROP Intermediate_Dir "Release\modules_userint2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "_LIB" /D "NDEBUG" /D "WIN32" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x417 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "modules_userint2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "modules_userint2___Win32_Debug"
# PROP BASE Intermediate_Dir "modules_userint2___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\modules_userint2"
# PROP Intermediate_Dir "Debug\modules_userint2"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "_DEBUG" /D "DEBUG" /D "DEBUG_ASSERT" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
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

# Name "modules_userint2 - Win32 Release"
# Name "modules_userint2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "ui_draw"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiarea.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiarea.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uibutton.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uibutton.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiclip.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiclip.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uicolour.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uicolour.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uifont.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uifont.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uigraph.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uigraph.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uihilght.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uihilght.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiorigin.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiorigin.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiscreen.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiscreen.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiwindow.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_draw\uiwindow.h
# End Source File
# End Group
# Begin Group "ui_obj"

# PROP Default_Filter ""
# Begin Group "area"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_col.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_col.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_fns.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_fns.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_graph.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_graph.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_links.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_links.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_notif.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_notif.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_org.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_org.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_pos.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_pos.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_proto.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_ptr.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_ptr.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_size.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_size.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_slid.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_slid.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_txt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_txt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_updt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\ar_updt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\area.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\area\area.h
# End Source File
# End Group
# Begin Group "slider"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_updt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\ms_updt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\mslider.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\mslider.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\sl_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\sl_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\sl_slid.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\sl_slid.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\slider.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\slider.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vs_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vs_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vs_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vs_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vs_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vs_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vs_updt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vs_updt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vslider.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\slider\vslider.h
# End Source File
# End Group
# Begin Group "button"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\button\bu_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\button\bu_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\button\bu_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\button\bu_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\button\bu_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\button\bu_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\button\button.h
# End Source File
# End Group
# Begin Group "close"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\close\cl_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\close\cl_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\close\cl_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\close\cl_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\close\cl_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\close\cl_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\close\close.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\close\close.h
# End Source File
# End Group
# Begin Group "input"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_updt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\in_updt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\input.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\input\input.h
# End Source File
# End Group
# Begin Group "list"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_size.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_size.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_updt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\li_updt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\list.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\list\list.h
# End Source File
# End Group
# Begin Group "menu"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\me_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\me_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\me_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\me_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\me_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\me_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\me_updt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\me_updt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\menu.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\menu\menu.h
# End Source File
# End Group
# Begin Group "number"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_fns.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_fns.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_txt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\nu_txt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\number.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\number\number.h
# End Source File
# End Group
# Begin Group "radio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\ra_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\ra_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\ra_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\ra_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\ra_fns.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\ra_fns.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\ra_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\ra_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\radio.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\radio\radio.h
# End Source File
# End Group
# Begin Group "screen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\sc_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\sc_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\sc_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\sc_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\sc_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\sc_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\sc_updt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\sc_updt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\screen.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\screen\screen.h
# End Source File
# End Group
# Begin Group "text"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\text.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_col.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_col.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_fns.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_fns.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_txt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\text\tx_txt.h
# End Source File
# End Group
# Begin Group "toggle"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\toggle\to_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\toggle\to_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\toggle\to_fns.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\toggle\to_fns.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\toggle\to_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\toggle\to_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\toggle\toggle.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\toggle\toggle.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\ui_obj.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_obj\ui_obj.h
# End Source File
# End Group
# Begin Group "ui_sys"

# PROP Default_Filter ""
# Begin Group "ui_funcs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_color.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_color.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_creat.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_creat.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_draw.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_draw.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_flags.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_flags.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_fns.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_fns.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_funcs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_funcs.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_graph.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_graph.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_links.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_links.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_notif.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_notif.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_org.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_org.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_pos.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_pos.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_ptr.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_ptr.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_size.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_size.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_slid.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_slid.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_txt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_txt.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_updt.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_funcs\ui_updt.h
# End Source File
# End Group
# Begin Group "ui_attrs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_attrs\ui_attrs.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_attrs\ui_attrs.h
# End Source File
# End Group
# Begin Group "ui_types"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_types\ui_types.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_types\ui_types.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_sys.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_sys\ui_sys.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\modules\userint2\ui_man.c
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_man.h
# End Source File
# Begin Source File

SOURCE=..\modules\userint2\ui_paint.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
