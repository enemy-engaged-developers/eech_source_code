noinst_LIBRARIES = libmobile.a
libmobile_a_SOURCES = mb_att.c mb_float.c mb_funcs.c mb_int.c mb_list.c mb_move.c mb_msgs.c mb_pack.c mb_tgt.c mb_vec3d.c mobile.c
SUBDIRS = aircraft cargo vehicle weapon
LDADD = aircraft/libaircraft.a cargo/libcargo.a vehicle/libvehicle.a weapon/libweapon.a
INCLUDES = -I$(top_srcdir)/modules -I../../.. -I../.. -I..
