# Microsoft Developer Studio Project File - Name="entity" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=entity - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "entity.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "entity.mak" CFG="entity - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "entity - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "entity - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "entity - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\entity"
# PROP Intermediate_Dir "Release\entity"
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

!ELSEIF  "$(CFG)" == "entity - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\entity"
# PROP Intermediate_Dir "Debug\entity"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /I "..\aphavoc\source" /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
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

# Name "entity - Win32 Release"
# Name "entity - Win32 Debug"
# Begin Group "entity"

# PROP Default_Filter ""
# Begin Group "en_misc"

# PROP Default_Filter ""
# Begin Group "en_anim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\en_misc\en_anim\en_anim.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\en_misc\en_anim\en_anim.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\en_misc\en_anim\key_anim.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\en_misc\en_anim\sub_anim.c
# End Source File
# End Group
# Begin Group "en_maths"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\en_misc\en_maths\en_cllsn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\en_misc\en_maths\en_cllsn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\en_misc\en_maths\en_maths.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\en_misc\en_misc.c
# End Source File
# End Group
# Begin Group "fixed"

# PROP Default_Filter ""
# Begin Group "cbuild"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cb_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\cbuild\cbuild.h
# End Source File
# End Group
# Begin Group "city"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\city.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\city\ct_vec3d.h
# End Source File
# End Group
# Begin Group "crater"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\cr_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\crater\crater.h
# End Source File
# End Group
# Begin Group "object"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\ob_vec3d.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\object\object.h
# End Source File
# End Group
# Begin Group "pylon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\py_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\pylon.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\pylon\pylon.h
# End Source File
# End Group
# Begin Group "scenic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\scenic.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\scenic\sn_vec3d.h
# End Source File
# End Group
# Begin Group "segment"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\segment.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\segment.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\segment\sg_updt.h
# End Source File
# End Group
# Begin Group "site"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\site.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\site\st_pack.h
# End Source File
# End Group
# Begin Group "siteupdt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\siteupdt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_anim.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_anim.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\siteupdt\su_updt.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fixed.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fixed.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_msgs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_objdb.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_objdb.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\fixed\fx_vec3d.h
# End Source File
# End Group
# Begin Group "system"

# PROP Default_Filter ""
# Begin Group "en_comms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_comms\en_comms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_comms\en_comms.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_comms\en_sessn.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_comms\en_sessn.h
# End Source File
# End Group
# Begin Group "en_debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_debug\en_dbarg.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_debug\en_dbdrw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_debug\en_dblst.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_debug\en_dbmsg.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_debug\en_debug.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_debug\en_stats.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_debug\en_valid.c
# End Source File
# End Group
# Begin Group "en_funcs"

# PROP Default_Filter ""
# Begin Group "en_list"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\fn_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\get_frst.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\get_pred.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\get_prnt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\get_succ.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\set_frst.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\set_pred.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\set_prnt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list\set_succ.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_att.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_att.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_char.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_char.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_creat.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_creat.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_draw.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_draw.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_dstry.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_dstry.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_float.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_float.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_funcs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_funcs.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_int.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_int.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_list.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_pack.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_pack.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_ptr.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_ptr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_snd.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_snd.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_str.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_str.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_updt.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_updt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_vec3d.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_funcs\en_vec3d.h
# End Source File
# End Group
# Begin Group "en_main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_main\en_dbase.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_main\en_heap.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_main\en_init.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_main\en_main.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_main\en_world.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_main\en_world.h
# End Source File
# End Group
# Begin Group "en_types"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_crew.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_day.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_force.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_force.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_forms.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_forms.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_group.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_group.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_land.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_plyr.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_route.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_sbtyp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_sbtyp.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_side.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_side.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_state.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_state.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_suply.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_suply.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_task.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_task.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_tgt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_thrt.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_types.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_types.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_view.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_view.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_wp.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_types\en_wp.h
# End Source File
# End Group
# Begin Group "en_attrs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_attrs\en_attrs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_attrs\en_attrs.h
# End Source File
# End Group
# Begin Group "en_msgs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_msgs\en_msgs.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\entity\system\en_msgs\en_msgs.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\entity\entity.h
# End Source File
# End Group
# End Target
# End Project
