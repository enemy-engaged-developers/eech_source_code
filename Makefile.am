bin_PROGRAMS = eech
eech_SOURCES = dummy.c
SUBDIRS = aphavoc modules
LDADD = aphavoc/libaphavoc.a modules/libmodules.a

mrproper : maintainer-clean
	rm -f core
	rm -f DEADJOE
	rm -f *~
	rm -f Makefile.in
	rm -f modules/DEADJOE
	rm -f modules/*~
	rm -f modules/Makefile.in
	rm -f modules/core
	rm -f modules/system/DEADJOE
	rm -f modules/system/*~
	rm -f modules/system/Makefile.in
	rm -f modules/system/unix/DEADJOE
	rm -f modules/system/unix/*~
	rm -f modules/system/unix/Makefile.in
	rm -f modules/system/unix/config.log
	rm -f config.guess config.h config.h.in config.log config.status config.sub
	rm -f mkinstalldirs
	rm -f aclocal.m4
	rm -f missing
	rm -f ltmain.sh
	rm -f install-sh
	rm -f stamp-h*
	rm -f configure
	rm -f libtool
	rm -f ltconfig
	rm -rf autom4te.cache
	rm -f stamp.h.in