#ifndef OPTIONS_HPP
#define OPTIONS_HPP

// Options, any combination is valid
// Whether display objects or not
#define USE_OBJECTS
// Whether display terrain or not
#define USE_TERRAIN

// Use current terrdata.c, otherwise terrdata_oldest.c - the oldest one available
#define USE_TERRAIN_CURRENT

#ifdef USE_OBJECTS
#ifdef USE_TERRAIN
#define USE_TERRAIN_TREES
#else
#define USE_OBJECTS_ONLY
#endif
#endif

#include "ee_3.h"

// FIXME
unsigned get_animation_size(unsigned index);
unsigned get_animation_texture(unsigned index, unsigned frame);


#define NATIVE_TYPES
#define LOAD_NORMALS
#define LOAD_RADIUS
#define EET_NO_EXPORT
#define NO_LWSFILEEXPORTER
#define NO_LWSCAMERAEXPORT

#endif
