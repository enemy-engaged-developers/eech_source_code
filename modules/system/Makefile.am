noinst_LTLIBRARIES = libsystem.la

##Files that didn't need changes are
libsystem_la_SOURCES = \
	memblock.h event.h keyevent.h joyevent.h fpu.h safemem.h \
	memblock.c event.c keyevent.c joyevent.c fpu.c safemem.c \
	memcmp.h cpuclock.h trackir.h ev_stack.h ev_alpha.h ascii.h \
	memcmp.c cpuclock.c trackir.c ev_stack.c ev_alpha.c ascii.c
##
##The files sysinput.h and sysinput.c are not even needed in Linux.
##
##All other files that ned severe changes are located in the unix directory.

SUBDIRS = external unix
#libsystem_a_LIBADD = 
LDFLAGS = @STATIC_LIB@
libsystem_la_LIBADD = unix/libunix.la external/libexternal.la
INCLUDES = -I$(top_srcdir)/modules -I.. -I$(top_srcdir)/aphavoc/source -I-
