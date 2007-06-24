# Microsoft Developer Studio Project File - Name="modules_3d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=modules_3d - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "modules_3d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "modules_3d.mak" CFG="modules_3d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modules_3d - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "modules_3d - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "modules_3d - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\modules_3d"
# PROP Intermediate_Dir "Release\modules_3d"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\modules" /I "..\aphavoc\source" /I "$(DX_SDK_PATH)\include" /D "_LIB" /D "NDEBUG" /D "WIN32" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x417 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "modules_3d - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\modules_3d"
# PROP Intermediate_Dir "Debug\modules_3d"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /I "..\modules" /I "..\aphavoc\source" /I "$(DX_SDK_PATH)\include" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
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

# Name "modules_3d - Win32 Release"
# Name "modules_3d - Win32 Debug"
# Begin Group "3D Source Files"

# PROP Default_Filter ""
# Begin Group "clouds"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\3d\clouds\3dclouds.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\modules\3d\clouds\3dtrump.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\3d\clouds\clouds.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\modules\3d\clouds\clouds.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\modules\3d\3danim.c

!IF  "$(CFG)" == "modules_3d - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "modules_3d - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dclip.c

!IF  "$(CFG)" == "modules_3d - Win32 Release"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "modules_3d - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dconfig.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dconstr.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3ddisp.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3denvget.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3denvset.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dexplos.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dfclip.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dhoriz.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dkeyfr.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dlight.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dline.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dmodels.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dmoon.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjbuf.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjdb.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjdrh.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjdrw.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjdrz.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobject.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjid.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjvb.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjvis.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3drain.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dscene.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dscon.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dshadow.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dsprite.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dstars.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dstrail.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dstrike.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dsubobj.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dsun.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dtemp.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dtrans.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dview.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dwface1.c
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dwface2.c
# End Source File
# End Group
# Begin Group "3D Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\modules\3d\3d_internal_proto.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3d_proto.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dconstr.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3denv.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dlight.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dline.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dmodels.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjbuf.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjdb.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobject.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjid.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjvb.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dobjvis.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dscon.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dstrail.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dstrike.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dtrans.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\3dwfaces.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\objects.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\readlw.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\3d\textanim.h
# End Source File
# Begin Source File

SOURCE=..\modules\3d\textname.h
# End Source File
# End Group
# End Target
# End Project
