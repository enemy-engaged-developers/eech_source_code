noinst_LIBRARIES = libvehicle.a
libvehicle_a_SOURCES = vehicle.c vh_anim.c vh_dbase.c vh_float.c vh_funcs.c vh_int.c vh_list.c vh_msgs.c vh_pack.c vh_ptr.c vh_str.c vh_tgt.c vh_vec3d.c vh_wpn.c
SUBDIRS = anti_air person ship routed
LDADD = anti_air/libanti_air.a person/libperson.a ship/libship.a routed/librouted.a
INCLUDES = -I$(top_srcdir)/modules -I../../../.. -I../../.. -I../.. -I..
