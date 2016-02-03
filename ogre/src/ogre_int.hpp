#ifndef OGRE_INT_HPP
#define OGRE_INT_HPP

#include "ogreee.h"

// Options for convertions

// Global geometry options
// Use per-vertex normals or not
#define USE_NORMALS
// Use any textures (and UV mapping) or not
#define USE_TEXTURES
// Use 32-bit or 16-bit indices
//#define USE_INDICES32
#define USE_TERRAIN_TREES
#define USE_TERRAIN_OBJECTS
#define USE_TIME

// Objects options
#ifdef USE_NORMALS
// Use per-vertex normals for objects or not
#define USE_OBJECTS_NORMALS
#endif
#ifdef USE_TEXTURES
// Use any textures (and UV mapping) for objects or not
#define USE_OBJECTS_TEXTURES
#endif

#define USE_UI_CHARACTERS 0x530

// Scenes options
#define USE_SCENES_CACHE_FRAMES 10

// Terrain options
#ifdef USE_NORMALS
// Use per-vertex normals for terrain or not
// TODO: Produces strange results with colours
#define USE_TERRAIN_NORMALS
#endif
#ifdef USE_TEXTURES
// Use any textures (and UV mapping) for terrain or not
#define USE_TERRAIN_TEXTURES
#endif
#ifdef USE_TERRAIN_TEXTURES
//#define USE_TERRAIN_SINGLE_TEXTURE
#endif
// Use per-vertex terrain colours or per-surface ones (TODO: Looks like it's not used in the game)
//#define USE_TERRAIN_VERTEX_COLOURS
// Limit number of terrain sectors to draw
#define USE_TERRAIN_VISIBILITY 5
#define USE_TERRAIN_SECTOR_FRAMES 10
#define USE_TERRAIN_GROUP 5
#define USE_TERRAIN_GROUP_FRAMES 5


#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

#include "OgreSubMesh.h"
#include "OgreSubEntity.h"
#include "OgreMaterialManager.h"
#include "OgreTechnique.h"
#include "OgreMeshManager.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreEntity.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"
#include "OgreInstancedEntity.h"
#include "OgreOverlayManager.h"
#include "OgreOverlayContainer.h"
#include "OgreOverlayElementFactory.h"
#include "OgreFontManager.h"

#include <iterator>

#define OGRE_EE

#include "ee.h"

class Uncopyable
{
public:
	Uncopyable()
	{
	}

private:
	Uncopyable(const Uncopyable&);
	void operator =(const Uncopyable&);
};

// Helper for Ogre resource names creation
class fmt : private Uncopyable
{
public:
	explicit fmt(const char* format, ...)
	{
		char buf[256];
		va_list ap;
		va_start(ap, format);
		vsprintf(buf, format, ap);
		va_end(ap);
		str = buf;
	}
	operator const Ogre::String&(void) const
	{
		return str;
	}

private:
	Ogre::String str;
};

class Mutex : private Uncopyable
{
public:
	Mutex(void)
	{
		InitializeCriticalSection(&cs);
	}
	~Mutex(void)
	{
		DeleteCriticalSection(&cs);
	}
	void lock(void)
	{
		EnterCriticalSection(&cs);
	}
	void unlock(void)
	{
		LeaveCriticalSection(&cs);
	}

private:
	CRITICAL_SECTION cs;
};

class Guard : private Uncopyable
{
public:
	Guard(Mutex& m)
		: m(m)
	{
		m.lock();
	}
	~Guard(void)
	{
		m.unlock();
	}

private:
	Mutex& m;
};

class Semaphore : private Uncopyable
{
public:
	Semaphore(unsigned init, unsigned max)
		: sem(CreateSemaphore(0, init, max, 0))
	{
	}
	~Semaphore(void)
	{
		CloseHandle(sem);
	}
	void acquire(void)
	{
		WaitForSingleObject(sem, INFINITE);
	}
	void release(void)
	{
		ReleaseSemaphore(sem, 1, 0);
	}

private:
	HANDLE sem;
};

#include "ogre_set.hpp"
#include "ogre_tasks.hpp"
#include "ogre_geometry.hpp"
#include "ogre_animation.hpp"
#include "ogre_objects.hpp"
#include "ogre_scenes.hpp"
#include "ogre_terrain.hpp"
#include "ogre_ui.hpp"

#define DEFINE_NAME(name, args, format, params) \
struct name : private fmt \
{ \
	explicit name(args) \
		: fmt(format, params) \
	{ \
	} \
	using fmt::operator const Ogre::String&; \
}

#define _ ,
DEFINE_NAME(MaterialName, unsigned index, "MATERIAL_%u", index);
DEFINE_NAME(MaterialAnimationName, unsigned index _ unsigned frame, "MATERIAL_%u_%u", index _ frame);
DEFINE_NAME(ObjectName, unsigned index, "OBJECT_%04X", index);
DEFINE_NAME(TextureName, unsigned index, "TEXTURE_%u", index);
DEFINE_NAME(MaterialTextureName, unsigned index, "MATERIAL_TEXTURE_%u", index);
DEFINE_NAME(FontName, unsigned index, "FONT_%u", index);
DEFINE_NAME(KeyframeAnimationName, unsigned index, "ANIMATION_%u", index);
DEFINE_NAME(TerrainMaterialName, unsigned index, "TERRAIN_MATERIAL_%u", index);
DEFINE_NAME(TerrainObject, unsigned z _ unsigned x, "TERRAIN_%u_%u", z _ x);
DEFINE_NAME(TerrainTreeObject, void, "TERRAIN_TREE_OBJECT", 0);
DEFINE_NAME(TerrainTreeManager, void, "TERRAIN_TREE_MANAGER", 0);
DEFINE_NAME(TerrainTree, unsigned z _ unsigned x, "TERRAIN_TREE_%u_%u", z _ x);
DEFINE_NAME(UIElement, unsigned index, "UI_%u", index);
#undef _

#undef DEFINE_NAME

#endif
