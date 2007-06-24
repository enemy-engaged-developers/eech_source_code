# Microsoft Developer Studio Project File - Name="cohokum_msvc6" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=cohokum_msvc6 - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "cohokum_msvc6.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "cohokum_msvc6.mak" CFG="cohokum_msvc6 - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "cohokum_msvc6 - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "cohokum_msvc6 - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cohokum_msvc6 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\cohokum_msvc6"
# PROP Intermediate_Dir "Release\cohokum_msvc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Zi /O2 /Ob2 /I "..\aphavoc\source" /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "_WINDOWS" /D "NDEBUG" /D "WIN32" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x417 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib winmm.lib dxguid.lib dinput.lib dsound.lib ddraw.lib amstrmid.lib /nologo /subsystem:windows /map /debug /machine:I386 /libpath:"D:\DX7SDK\lib" /fixed:no
# SUBTRACT LINK32 /verbose /pdb:none

!ELSEIF  "$(CFG)" == "cohokum_msvc6 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "cohokum_msvc6___Win32_Debug"
# PROP BASE Intermediate_Dir "cohokum_msvc6___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\cohokum_msvc6"
# PROP Intermediate_Dir "Debug\cohokum_msvc6"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Zi /Od /Ob1 /I "..\aphavoc\source" /I "..\modules" /I "$(DX_SDK_PATH)\include" /D "WIN32" /D "_DEBUG" /D "DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GF /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x417 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib advapi32.lib ole32.lib uuid.lib winmm.lib dxguid.lib dinput.lib dsound.lib ddraw.lib amstrmid.lib /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /libpath:"D:\DX7SDK\lib"
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "cohokum_msvc6 - Win32 Release"
# Name "cohokum_msvc6 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "AI"

# PROP Default_Filter ""
# Begin Group "ai_misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ai\ai_misc\ai_dbase.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\ai_misc\ai_dbase.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\ai_misc\ai_misc.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\ai_misc\ai_misc.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\ai_misc\ai_route.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "faction"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ai\faction\briefing.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\faction\faction.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\faction\faction.h

!IF  "$(CFG)" == "cohokum_msvc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cohokum_msvc6"

!ELSEIF  "$(CFG)" == "cohokum_msvc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cohokum_msvc6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\faction\popread.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\faction\routegen.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\faction\routegen.h

!IF  "$(CFG)" == "cohokum_msvc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cohokum_msvc6"

!ELSEIF  "$(CFG)" == "cohokum_msvc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cohokum_msvc6"

!ENDIF 

# End Source File
# End Group
# Begin Group "highlevl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ai\highlevl\highlevl.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\highlevl\highlevl.h

!IF  "$(CFG)" == "cohokum_msvc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cohokum_msvc6"

!ELSEIF  "$(CFG)" == "cohokum_msvc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cohokum_msvc6"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\highlevl\imaps.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\highlevl\order.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\highlevl\reaction.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\highlevl\setup.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\highlevl\suitable.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ai\parser\parsgen.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\parser\parsgen.h

!IF  "$(CFG)" == "cohokum_msvc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cohokum_msvc6"

!ELSEIF  "$(CFG)" == "cohokum_msvc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cohokum_msvc6"

!ENDIF 

# End Source File
# End Group
# Begin Group "taskgen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\ai\taskgen\assign.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\taskgen\croute.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\taskgen\engage.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\taskgen\taskgen.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\taskgen\taskgen.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\ai\ai.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\ai\ai.h

!IF  "$(CFG)" == "cohokum_msvc6 - Win32 Release"

# PROP Intermediate_Dir "Release\cohokum_msvc6"

!ELSEIF  "$(CFG)" == "cohokum_msvc6 - Win32 Debug"

# PROP Intermediate_Dir "Debug\cohokum_msvc6"

!ENDIF 

# End Source File
# End Group
# Begin Group "App3D"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\app3d\3d_draw.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\app3d\3d_init.c
# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\app3d\3d_main.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\app3d\app3d.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\app3d\app3d.h
# End Source File
# End Group
# Begin Group "appsound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\appsound\snd_data.c
# ADD CPP /Zd
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\appsound\snd_data.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\appsound\snd_init.h
# End Source File
# End Group
# Begin Group "comms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\comms\comm_man.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\comms\comms.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\comms\comms.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\comms\commsserver.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\comms\commsserver.h
# End Source File
# End Group
# Begin Group "events"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\events\ev_debug.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\events\ev_fns.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\events\events.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\events\userdef.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "misc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\misc\airspeed.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\gameexit.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\gameexit.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\language.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\message.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\message.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\miscell.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\miscell.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\msg_in.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\msg_out.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\scrnshot.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\tags.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\tags.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\terr_db.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\timeaccl.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\misc\tod.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "gameflow"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\aphavoc\source\gameflow\gameflow.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gameflow\gameflow.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\aphavoc\source\ai_extrn.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\aphavoc.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\AppResources.rc
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\cmndline.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\cmndline.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\eechini.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\flight.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gfxfiles.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gfxfiles.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\global.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\global.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\gwutcfg.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\init.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\project.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\project.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\servlog.c
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\test.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\update.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\update.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\version.h
# End Source File
# Begin Source File

SOURCE=..\aphavoc\source\wutcfg.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\setup\cohokum\eech.ico
# End Source File
# End Group
# End Target
# End Project
