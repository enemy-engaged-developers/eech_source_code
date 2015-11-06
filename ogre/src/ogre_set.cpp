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
	Ogre::Vector3 v(position->x, position->y, position->z);
	v.z = -v.z;
	ogre_camera->setPosition(v);
	Ogre::Matrix3 m(orientation);
	ogre_matrix_mirror(m);
	ogre_camera->setOrientation(m);
}

unsigned ogre_index(void)
{
	static unsigned index;

	return index++;
}

void ogre_matrix_mirror(Ogre::Matrix3& m)
{
	m[0][2] = -m[0][2];
	m[1][2] = -m[1][2];
	m[2][0] = -m[2][0];
	m[2][1] = -m[2][1];
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
