#include "ogre_int.hpp"

namespace
{
	class TaskCamera : public Task
	{
	public:
		TaskCamera(const Ogre::Vector3& position, const Ogre::Quaternion& orientation)
			: position(position), orientation(orientation)
		{
		}
		virtual TaskResult task(void)
		{
			ogre_camera->setPosition(position);
			ogre_camera->setOrientation(orientation);
			return TR_TASK;
		}

	private:
		Ogre::Vector3 position;
		Ogre::Quaternion orientation;
	};
}

Ogre::SceneManager* ogre_scene_manager;
Ogre::Camera* ogre_camera;
std::string ogre_resource_group;

void ogre_set(const char* resource_group, Ogre::SceneManager* scene_manager, Ogre::Camera* camera)
{
	ogre_log(__FUNCTION__, "");

	ogre_resource_group = resource_group;
	ogre_scene_manager = scene_manager;
	ogre_camera = camera;

	//FIXME
	ogre_camera->getViewport()->setBackgroundColour(Ogre::ColourValue(0.18f, 0.77f, 0.87f));
	ogre_camera->setNearClipDistance(0.5f);
	ogre_camera->setFarClipDistance(10000.0f);
	ogre_scene_manager->setAmbientLight(Ogre::ColourValue(0.6f, 0.6f, 0.6f));
}

void OGREEE_CALL ogre_set_viewpoint(const float* position, const float orientation[][3])
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_tasks->enqueue(new TaskCamera(ogre_position(position), ogre_orientation(orientation[0])));
}

unsigned ogre_index(void)
{
	assert(GetCurrentThreadId() == ogre_thread_id);
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

void ogre_log_(const char* function, const char* format, ...)
{
	static FILE* fd;
	char buf[1024];
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	if (!fd)
	{
		fd = fopen("Ogre_.log", "w");
		if (fd)
			setbuf(fd, 0);
	}
	if (fd)
		fprintf(fd, "%s: %s\n", function, buf);
}
