noinst_LIBRARIES = libavionics.a
libavionics_a_SOURCES = avionics.c
SUBDIRS = apache comanche common havoc hokum
LDADD = apache/libapache.a comanche/libcomanche.a common/libcommon.a havoc/libhavoc.a hokum/libhokum.a
INCLUDES = -I$(top_srcdir)/modules -I../../.. -I../.. -I..
