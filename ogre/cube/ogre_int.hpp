#ifndef OGRE_INT_HPP
#define OGRE_INT_HPP

#include "options.hpp"

#include "ogre.hpp"

// Options for convertions

// Global geometry options
// Use per-vertex normals or not
#define USE_NORMALS
// Use any textures (and UV mapping) or not
#define USE_TEXTURES
// Use 32-bit or 16-bit indices
//#define USE_INDICES32

// Objects options
#ifdef USE_NORMALS
// Use per-vertex normals for objects or not
#define USE_OBJECTS_NORMALS
#endif
#ifdef USE_TEXTURES
// Use any textures (and UV mapping) for objects or not
#define USE_OBJECTS_TEXTURES
#endif

// Terrain options
#ifdef USE_TERRAIN
#ifdef USE_NORMALS
// Use per-vertex normals for terrain or not
// TODO: Produces strange results with colours
#define USE_TERRAIN_NORMALS
#endif
#ifdef USE_TEXTURES
// Use any textures (and UV mapping) for terrain or not
#define USE_TERRAIN_TEXTURES
#endif
// Use per-vertex terrain colours or per-surface ones (TODO: Looks like it's not used in the game)
//#define USE_TERRAIN_VERTEX_COLOURS
// Limit number of terrain sectors to draw
#define USE_TERRAIN_VISIBILITY 10

// Use PageGeometry for terrain drawing or internal Ogre methods
#define USE_TERRAIN_PAGING

#ifndef USE_TERRAIN_PAGING
// Draw terrain itself or not
#define USE_TERRAIN_DRAW

// Use Ogre::StaticGeometry for terrain or not
#define USE_TERRAIN_STATIC_GEOMETRY

#ifdef USE_TERRAIN_VISIBILITY
// Number of invisible entries in cache. Less than USE_TERRAIN_VISIBILITY * 4 is useless
#define USE_TERRAIN_CACHE_SIZE 100
#endif
#endif

#ifdef USE_TERRAIN_TREES
// Use PageGeometry for trees drawing or internal Ogre methods
#define USE_TERRAIN_TREES_PAGING
#ifdef USE_TERRAIN_TREES_PAGING
#define USE_TERRAIN_TREES_VISIBILITY 3
#else
// Use InstancedGeometry or StaticGeometry
// TODO: Seems to be a problem in Ogre with InstancedGeometry
//#define USE_TERRAIN_TREES_INSTANCED
#endif
#endif

#ifdef _DEBUG
// Decreases terrain processing time decreasing number of sectors in terrain
#define USE_TERRAIN_LIMIT_SIZE 20
#endif

#endif



// Helper for Ogre resource names creation
class fmt
{
public:
	explicit fmt(const char* format, ...)
	{
		va_list ap;
		va_start(ap, format);
		vsprintf(str, format, ap);
		va_end(ap);
	}
	operator Ogre::String(void) const
	{
		return str;
	}

private:
	char str[256];

	fmt(fmt&);
	void operator =(fmt&);
};

#define DEFINE_NAME(name,args,format,params) \
struct name : private fmt \
{ \
	explicit name(args) \
		: fmt(format, params) \
	{ \
	} \
	using fmt::operator Ogre::String; \
}

#define _ ,
DEFINE_NAME(MaterialName, unsigned index, "MATERIAL_%u", index);
DEFINE_NAME(MaterialAnimationName, unsigned index _ unsigned frame, "MATERIAL_%u_%u", index _ frame);
DEFINE_NAME(ObjectName, unsigned index, "OBJECT_%04X", index);
DEFINE_NAME(TextureName, unsigned index, "TEXTURE_%u", index);
// TODO: Invalid parameters for KeyframeAnimationName
DEFINE_NAME(KeyframeAnimationName, const void* scene _ unsigned number, "ANIMATION_%p_%u", scene _ number);
#ifdef USE_TERRAIN
DEFINE_NAME(TerrainObject, unsigned z _ unsigned x, "TERRAIN_%u_%u", z _ x);
DEFINE_NAME(TerrainStaticGeometry, unsigned z _ unsigned x, "TERRAIN_STATIC_%u_%u", z _ x);
DEFINE_NAME(TerrainTreeObject, void, "TERRAIN_TREE_OBJECT", 0);
DEFINE_NAME(TerrainTree, unsigned z _ unsigned x, "TERRAIN_TREE_%u_%u", z _ x);
#endif
#undef _

#undef DEFINE_NAME


using namespace Ogre;
using namespace Forests;

#include "ogre_geometry.hpp"

#include "ogre_objects.hpp"

#endif
