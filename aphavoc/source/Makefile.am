noinst_LIBRARIES = libsource.a
libsource_a_SOURCES = ai_extrn.c cdmusic.c cmndline.c deinit.c flight.c game.c gfxfiles.c global.c init.c install.c project.c test.c update.c

#SUBDIRS = ai app3d appsound comms entity events gameflow gunships misc ui_menu
SUBDIRS = ai app3d appsound entity events gunships misc

LDADD = ai/libai.a app3d/libapp3d.a appsound/libappsound.a comms/libcomms.a entity/libentity.a events/libevents.a gameflow/libgameflow.a gunships/libgunships.a misc/libmisc.a ui_menu/libui_menu.a
INCLUDES = -I$(top_srcdir)/modules -I..
