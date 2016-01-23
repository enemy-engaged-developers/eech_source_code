#include "ogre_int.hpp"

Ogre::SceneManager* ogre_scene_manager;
Ogre::Camera* ogre_camera;
std::string ogre_resource_group;

void OGREEE_CALL ogre_set(const char* resource_group, void* scene_manager, void* camera)
{
	ogre_log(__FUNCTION__, "");

	ogre_resource_group = resource_group;
	ogre_scene_manager = static_cast<Ogre::SceneManager*>(scene_manager);
	ogre_camera = static_cast<Ogre::Camera*>(camera);
}

void OGREEE_CALL ogre_set_viewpoint(struct VEC3D* position, matrix3x3 orientation)
{
	ogre_camera->setPosition(ogre_position(*reinterpret_cast<struct OgreVector3*>(position)));
	ogre_camera->setOrientation(ogre_orientation(orientation));
}

unsigned ogre_index(void)
{
	static unsigned index;

	return index++;
}

void ogre_log(const char* function, const char* format, ...)
{
	char buf[1024];
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	Ogre::LogManager::getSingleton().logMessage(Ogre::String(function) + ": " + buf);
}
