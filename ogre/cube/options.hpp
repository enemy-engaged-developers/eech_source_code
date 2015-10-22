#ifndef OPTIONS_HPP
#define OPTIONS_HPP

// Options, any combination is valid
// Whether display objects or not
#define USE_OBJECTS
// Whether display terrain or not
#define USE_TERRAIN
// Whether to use ogre_run or not
//#define USE_OGRE_RUN

// Use current terrdata.c, otherwise terrdata_oldest.c - the oldest one available
#define USE_TERRAIN_CURRENT

#ifdef USE_OBJECTS
#ifdef USE_TERRAIN
#define USE_TERRAIN_TREES
#else
#define USE_OBJECTS_ONLY
#endif
#endif

#include "../../graphics/textsys.h"
#include "../../maths/vector.h"
#include "../../maths/matrix.h"
#include "../../graphics/colour.h"
#include "../3denv.h"
#include "../3dview.h"
#include "../objects.h"
typedef int object_3d_index_numbers;
typedef int object_3d_sub_object_index_numbers;
typedef int object_3d_camera_index_numbers;
typedef int object_3d_light_index_numbers;
#include "../3dobjdb.h"

#ifdef USE_TERRAIN

#include "terrtype.h"
#include "terrdata.h"
#include "terrdr.h"
#include "terrdrcl.h"

#endif

#define NATIVE_TYPES
#define LOAD_NORMALS
#define LOAD_RADIUS
#define EET_NO_EXPORT
#define NO_LWSFILEEXPORTER
#define NO_LWSCAMERAEXPORT

#endif
