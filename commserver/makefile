.ERASE

.OPTIMIZE

.EXTENSIONS:

.EXTENSIONS: .exe .obj .cpp

all : .SYMBOLIC

# BEGIN USER

targets = t1 t2 t3 t4

targ_t1 = EECHCommUDPServer.
targ_t2 = EECHCommSIOCClient.
targ_t3 = TestCommClient.
targ_t4 = TestCommServer.

objs_t1 = Values.obj SharedMemHelpers.obj dispatcher.obj UDP.obj CommServer.obj
objs_t2 = Values.obj SharedMemHelpers.obj TCP.obj CommClient.obj
objs_t3 = UDP.obj client.obj
objs_t4 = TCP.obj server.obj

$(targ_t1)exe : $(targ_t1)lnk

$(targ_t2)exe : $(targ_t2)lnk

$(targ_t3)exe : $(targ_t3)lnk

$(targ_t4)exe : $(targ_t4)lnk

$(targ_t1)lnk : $(objs_t1)

$(targ_t2)lnk : $(objs_t2)

$(targ_t3)lnk : $(objs_t3)

$(targ_t4)lnk : $(objs_t4)

# END USER


targets_all = $(targets:t=$$targ_t)
targ_all = $(targets_all:.=.exe)
objs_all = $(targets:t=$$objs_t)
lnks_all = $(targ_all:.exe=.lnk)

all : $(targ_all)


cc = wpp386

cc_args =

cc_args += /I=../aphavoc/source

cc_args += /bm
cc_args += /bt=win95
cc_args += /ze
cc_args += /e10
cc_args += /ei
cc_args += /zp4
#cc_args += /fh
cc_args += /6r
cc_args += /zw
cc_args += /zq
cc_args += /fp6
cc_args += /fpi
cc_args += /dWIN32
cc_args += /ri
cc_args += /w4
cc_args += /zld
cc_args += /xs

!ifdef debug

cc_args += /d3s

!else

cc_args += /oneatx /oh /ol+ /ob

!endif

.cpp.obj: 
	$(cc) $(cc_args) /Fo=$^@ $[@

$(lnks_all) :
	@ %create $^@
	@ %append $^@ OPTION VERBOSE
	@ %append $^@ SYSTEM Win95
	@ %append $^@ OPTION SYMF
	@ %append $^@ OPTION MAP
	@ %append $^@ RUNTIME CONSOLE
	@ %append $^@ NAME $^&
	@ %append $^@ OPTION INCREMENTAL=$^&.ilk
	@ %append $^@ OPTION VERSION=1.0
	@ %append $^@ OPTION STATICS
	@ %append $^@ OPTION RESOURCE=resources.res
	@ %append $^@ OPTION STACK=256000
	@ for %i in ($<) do @ %append $^@ FILE %i

$(targ_all) :
	wlink debug all library winmm library ws2_32 @$[@

clean : .SYMBOLIC
	@ del $(lnks_all) $(targ_all:.exe=.map) $(targ_all:.exe=.sym) 2>nul
	@ del $(objs_all) $(targ_all:.exe=.ilk) 2>nul

cleanall : .SYMBOLIC clean
	@ del $(targ_all) 2>nul

