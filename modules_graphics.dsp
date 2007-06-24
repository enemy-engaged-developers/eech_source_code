# Microsoft Developer Studio Project File - Name="modules_graphics" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=modules_graphics - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "modules_graphics.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "modules_graphics.mak" CFG="modules_graphics - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "modules_graphics - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "modules_graphics - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "modules_graphics - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\modules_graphics"
# PROP Intermediate_Dir "Release\modules_graphics"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\modules\3d" /I "..\modules" /I "..\aphavoc\source" /I "$(DX_SDK_PATH)\include" /D "_LIB" /D "NDEBUG" /D "WIN32" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x417 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "modules_graphics - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\modules_graphics"
# PROP Intermediate_Dir "Debug\modules_graphics"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /Zi /Od /Ob1 /I "..\modules\3d" /I "..\modules" /I "..\aphavoc\source" /I "$(DX_SDK_PATH)\include" /D "_DEBUG" /D "DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /FD /GF /GZ /c
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

# Name "modules_graphics - Win32 Release"
# Name "modules_graphics - Win32 Debug"
# Begin Group "graphics Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\modules\graphics\block.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\circle.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\clip.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\colour.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\d3d.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\d3dfog.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\d3dpoly.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\d3dstate.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\d3dvert.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\dirdraw.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\dither.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\dresol.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\line.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\monofont.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\monosprt.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\mouseptr.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\opengl_state.c
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\pixel.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\pixeltxt.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\polyd3d.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\polyline.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\PSDread.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\psdwrite.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\render.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\rgb.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\rle.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\screens.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\textscrn.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\textsys.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\textuser.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\tga.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\tranbuf.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\vcache.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\viewport.c
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\zbuffer.c
# End Source File
# End Group
# Begin Group "graphics Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\modules\graphics\colour.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\d3dline.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\d3dstate.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\dirdraw.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\gfx_d3d.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\graphics_proto.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\mono3x6.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\mono5x7.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\mono5x9.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\mono6x10.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\mono6x7.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\mono7x12.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\mouseptr.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\polygon.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\polyscan.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\screens.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\scrnstr.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\textsys.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\tga.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\tranbuf.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\vertex.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\viewport.h
# End Source File
# Begin Source File

SOURCE=..\modules\graphics\zbuffer.h
# End Source File
# End Group
# End Target
# End Project
