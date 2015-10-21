#include "stdafx.h"

#include "ogre_int.hpp"

Ogre::SceneManager* ogre_scene_manager;
Ogre::Camera* ogre_camera;
std::string ogre_resource_group;

void ogre_set(const char* resource_group, Ogre::SceneManager* scene_manager, Ogre::Camera* camera)
{
	ogre_resource_group = resource_group;
	ogre_scene_manager = scene_manager;
	ogre_camera = camera;
}

unsigned ogre_index(void)
{
	static unsigned index;

	return index++;
}
