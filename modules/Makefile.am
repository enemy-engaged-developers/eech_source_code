###noinst_LIBRARIES = libmodules.a
###libmodules_a_SOURCES =

bin_PROGRAMS = apache_hammoc

##test
apache_hammoc_SOURCES = 
#system.h linuxsystem.h dummy.c
##INCLUDES = -I$(top_srcdir)/modules -I.. -I$(top_srcdir)/aphavoc/source
##test


SUBDIRS = maths system misc

# Order is everything. Undefined references might be that two or more libs.a
# are in wrong order

#apache_hammoc_
#LDADD/LIBADD
### LDFLAGS = @STATIC_LIB@
apache_hammoc_LDADD = \
	system/libsystem.la \
	maths/libmaths.la \
	misc/libmisc.la

##SUBDIRS = 2d 3d graphics maths misc multi sound system userint2

##LDADD = 2d/lib2d.a 3d/lib3d.a graphics/libgraphics.a maths/libmaths.a
##misc/libmisc.a multi/libmulti.a sound/libsound.a system/libsystem.a
##userint2/libuserint2.a
