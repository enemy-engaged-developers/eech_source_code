#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

.ERASE

.OPTIMIZE

.EXTENSIONS:

.EXTENSIONS: .exe .obj .c .asm

!   loaddll    hcl   c1xx
!   loaddll    hcl1   c1
!   loaddll    hcl2   hwdll
!   loaddll    wcc386   wccd386
#!   loaddll    wlink    wlink
!       loaddll    hcl3 mspdb50

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

# define EECH_ROOTDIR in your environment to specify location of the main EECH SRC directory (added by crh@outpost.co.nz)
# eg EECH_ROOTDIR=y:\Projects\EECH

projectname = project

rootdir = $(%EECH_ROOTDIR)

projectdir = $(rootdir)\aphavoc

modulesdir = $(rootdir)\modules

############################################################################
# All the version definitions have been moved to \aphavoc\source\version.h #
############################################################################

# !ifdef visualc
# application_name = Enemy_Engaged_RAH66_Comanche_Vs_KA52_Hokum
# !else
# application_name = Enemy Engaged RAH66 Comanche Vs KA52 Hokum
# !endif
#
# major_revision = 1
#
# data_revision = 6
#
# minor_revision = 0

#
# Build types:
#       A: Alpha
#       B: Beta
#       C: Commercial
#       D: Demo
#       E: Electronic Distribution (Commercial make minus CD protection)
#       X: Experimental patch (although same as Commercial build)
#
# build_type = W7

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

target : $(projectname).exe

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

c_object_files =

c_mobule_object_files =

asm_object_files =

asm_mobule_object_files =

lib_files =

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

!ifdef visualc

cc = cl

!else

!ifdef gcc

cc = gcc

!else

cc = wcc386

!endif

!endif

asm = wasm

cc_args =
asm_args =

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

!include $(projectdir)\$(projectname).imf

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

########################################
#
# COMPILATION OPTIONS
#
########################################

#
# APPLICATION NAME
#

# !ifdef visualc
#
# cc_args += /DAPP_NAME="""$(application_name)_v$(major_revision).$(data_revision).$(minor_revision)$(build_type)"""
#
# !else
#
# cc_args += /DAPP_NAME="$(application_name) v$(major_revision).$(data_revision).$(minor_revision)$(build_type)"
#
# !endif

#
# APPLICATION VERSION
#

# cc_args += /DMAJOR_VERSION=$(major_revision)

# cc_args += /DDATA_VERSION=$(data_revision)

# cc_args += /DMINOR_VERSION=$(minor_revision)

# !ifdef visualc
#
# cc_args += /DBUILD_TYPE="""$(build_type)"""
#
# !else
#
# cc_args += /DBUILD_TYPE="$(build_type)"
#
# !endif

#
# ENVIRONMENT VARIABLE NAME
#

# !ifdef visualc
#
# cc_args += /DENV_NAME="""COMANCHE_HOKUM"""
#
# !else
#
# cc_args += /DENV_NAME="COMANCHE_HOKUM"
#
# !endif

#
# NO ENTITY OPTION
#

!ifdef no_entity_symbols

!ifdef visualc

cc_args += /D "NO_ENTITY_SYMBOLS"

!else

!ifdef gcc

cc_ags += -D NO_ENTITY_SYMBOLS

!else

cc_args += /DNO_ENTITY_SYMBOLS

!endif

!endif

!endif

#
# STANDARD OPTIONS
#

!ifdef visualc

cc_args += /c
cc_args += /TC
cc_args += /nologo
cc_args += /YX
cc_args += /MTd
cc_args += /Yd
cc_args += /Zi
cc_args += /Zp8
cc_args += /W0

cc_args += /I"$(modulesdir)"
cc_args += /I"$(projectdir)\source"

cc_args += /D "WIN32"
cc_args += /D "_WINDOWS"

!else

!ifdef gcc

cc_args += -mwindows
cc_args += -c
cc_args += -I $(DXSDK)\include
cc_args += -I $(modulesdir)
cc_args += -I $(projectdir)\source
cc_args += -W 
#cc_args += -Wall
#cc_args += -x c++

!else

cc_args += /I=$(modulesdir)
cc_args += /I=$(projectdir)\source

!ifndef relaxed

#cc_args += /we

!endif


cc_args += /bm
cc_args += /bt=win95
cc_args += /ze
cc_args += /e10
cc_args += /ei
cc_args += /zp4

cc_args += /6r
cc_args += /zw
cc_args += /zq
cc_args += /fp6
cc_args += /fpi
cc_args += /dWIN32
#cc_args += /ri
cc_args += /wx
#cc_args += /zld
#cc_args += /ep
#cc_args += /ee

# runtime sample profiling
#cc_args += /et

cc_args += /fh

asm_args += /c
asm_args += /W3
asm_args += /nologo

!endif

!endif

#
# DEBUG OPTIONS
#

!ifdef debug

!ifndef optimise

!ifdef visualc

cc_args += /D "DEBUG"
cc_args += /Ge

!else

!ifdef gcc

cc_args += -g
cc_args += -D DEBUG

!else

cc_args += /d2
cc_args += /of+
cc_args += /hd
cc_args += /DDEBUG

!endif

!endif

!else

#
# VTUNE
#

!ifdef visualc

cc_args += /Ox
cc_args += /G6
cc_args += /D "DEBUG"

!else

!ifdef gcc

cc_args += -g
cc_args += -D DEBUG

!else

cc_args += /d2
cc_args += /hd
cc_args += /dVTUNE
cc_args += /dDEBUG

!endif

!endif

!endif

!endif

#
# OPTIMISATION OPTIONS
#

!ifdef optimise

!ifdef visualc

cc_args += /Ox
cc_args += /G6

!else

!ifdef gcc

cc_args += -O2

!else

cc_args += /oneatx /oh /ol+ /ob
# new optimizations:
cc_args += /ok /or

!endif

!endif

!endif

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

#
# RELEASE OPTIONS
#

!ifdef commercial

!ifdef visualc
cc_args += /d"COMMERCIAL"
!else
!ifdef gcc
cc_args += -D COMMERCIAL
!else
cc_args += /dCOMMERCIAL
!endif
!endif

!endif

!ifdef install_from_cdrom

!ifdef visualc
cc_args += /d"INSTALL_FROM_CDROM"
!else
!ifdef gcc
cc_args += -D INSTALL_FROM_CDROM
!else
cc_args += /dINSTALL_FROM_CDROM
!endif
!endif

!endif

!ifdef ogre
cc_args += /dOGRE_EE /I=$(rootdir)\ogre\include
!endif

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

########################################
#
# HOW TO COMPILE SOURCE FILES INTO OBJECT FILES
#
########################################

.asm.obj:
        * $(asm) $(asm_args) /fo=$^@ $[@

.c.obj: 
!ifdef visualc
        * $(cc) $[@ $(cc_args) /Fo$^@
!else
!ifdef gcc
        * $(cc) $(cc_args) -o $^@ $[@
!else
        * $(cc) $(cc_args) /Fo=$^@ $[@
!endif
!endif

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

########################################
#
# HOW TO MAKE LINKER RESPONSE FILE
#
########################################

$(projectname).lnk : makefile $(c_object_files) $(c_modules_object_files) linkclean
#        @ echo Creating Linker Response File ...
!ifdef visualc
        @ %create $^@
                @ %append $^@ /NOLOGO
                @ %append $^@ /SUBSYSTEM:WINDOWS
        @ %append $^@ /OUT:$^&.exe
!ifdef debug
                @ %append $^@ /DEBUG
                @ %append $^@ /DEBUGTYPE:CV
!endif
                @ %append $^@ /NODEFAULTLIB:LIBCMTD
                @ %append $^@ user32.lib
                @ %append $^@ ctl3d32s.lib
                @ %append $^@ winmm.lib
                @ %append $^@ ole32.lib
                @ %append $^@ GDI32.lib
                @ %append $^@ LIBC.lib
                @ %append $^@ LIBCMT.lib
                @ %append $^@ MSVCRT.lib
                @ %append $^@ MTXIH.lib
        @ for %i in ($(lib_files)) do @ %append $^@ %i
        @ for %i in ($(c_module_object_files)) do @ %append $^@ %i
        @ for %i in ($(c_object_files)) do @ %append $^@ %i
        @ for %i in ($(asm_module_object_files)) do @ %append $^@ %i

!else
        @ %create $^@
        @ %append $^@ OPTION VERBOSE
        @ %append $^@ SYSTEM Win95
        @ %append $^@ OPTION SYMF
        @ %append $^@ OPTION MAP
!ifdef debug
        @ %append $^@ DEBUG ALL
!endif
        @ %append $^@ NAME $^&
                @ %append $^@ OPTION INCREMENTAL=$(projectname).ilk
                @ %append $^@ OPTION VERSION=1.6
                @ %append $^@ OPTION STATICS
                @ %append $^@ OPTION RESOURCE=cohokum.res
#               @ %append $^@ OPTION ELIMINATE
        @ %append $^@ OPTION STACK=256000
        @ for %i in ($(lib_files)) do @ %append $^@ LIBRARY %i
        @ for %i in ($(c_module_object_files)) do @ %append $^@ FILE %i
        @ for %i in ($(c_object_files)) do @ %append $^@ FILE %i
        @ for %i in ($(asm_module_object_files)) do @ %append $^@ FILE %i
!endif

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

########################################
#
# HOW TO MAKE TARGET
#
########################################

!ifdef visualc

$(projectname).exe : $(c_object_files) $(c_module_object_files) $(projectname).lnk
                link @$(projectname).lnk

!else

$(projectname).exe : $(c_object_files) $(c_module_object_files) $(projectname).lnk
                wlink debug all library winmm library ws2_32 @$(projectname).lnk

!endif

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

########################################
#
# REMAKE ( remake .obj and files )
#
########################################

remake : .SYMBOLIC
        @ for %i in ( $(c_object_files)) do quietdel %i
        @ for %i in ( $(c_module_object_files)) do quietdel %i
        @ quietdel $(projectname).lnk

#################################################################################################################################
#################################################################################################################################
#################################################################################################################################

########################################
#
# linkclean ( delete working files used by linker )
#
########################################

linkclean : .SYMBOLIC
        @ del $(projectname).lnk
	@ del $(projectname).map
	@ del $(projectname).sym
	
#################################################################################################################################
#################################################################################################################################
#################################################################################################################################
