#include "ogre_int.hpp"

Ogre::SceneManager* ogre_scene_manager;
Ogre::Camera* ogre_camera;
std::string ogre_resource_group;

void ogre_set(const char* resource_group, void* scene_manager, void* camera)
{
	ogre_resource_group = resource_group;
	ogre_scene_manager = static_cast<Ogre::SceneManager*>(scene_manager);
	ogre_camera = static_cast<Ogre::Camera*>(camera);
}

unsigned ogre_index(void)
{
	static unsigned index;

	return index++;
}
