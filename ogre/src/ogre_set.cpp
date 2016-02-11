#include "ogre_int.hpp"

namespace
{
	class TaskEnv : public Task
	{
	public:
		TaskEnv(const struct OgreEnvironment& env)
			: env(env)
		{
		}
		virtual TaskResult task(void)
		{
			ogre_camera->setPosition(ogre_position(&env.position.x));
			ogre_camera->setOrientation(ogre_orientation(env.attitude[0]));
			ogre_camera->setNearClipDistance(env.hither);
			ogre_camera->setFarClipDistance(env.yonder);
			ogre_scene_manager->setAmbientLight(ogre_colour(env.ambient));
			ogre_scene_manager->setFog(Ogre::FOG_LINEAR, ogre_colour(env.fog_colour), 0, env.fog_start, env.fog_end);
			ogre_camera->getViewport()->setBackgroundColour(ogre_colour(env.background_colour));

			return TR_TASK;
		}

	private:
		struct OgreEnvironment env;
	};
}

Ogre::SceneManager* ogre_scene_manager;
Ogre::Camera* ogre_camera;
Ogre::String ogre_resource_group;

void ogre_set(const char* resource_group, Ogre::SceneManager* scene_manager, Ogre::Camera* camera)
{
	assert(GetCurrentThreadId() == ogre_thread_id);
	ogre_log(__FUNCTION__, "");

	ogre_resource_group = resource_group;
	ogre_scene_manager = scene_manager;
	ogre_camera = camera;

	//FIXME
	ogre_scene_manager->setSkyDome(true, "Examples/CloudySky", 5, 8);
}

void OGREEE_CALL ogre_environment(const struct OgreEnvironment* env)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_tasks->enqueue(new TaskEnv(*env));
}

unsigned ogre_index(void)
{
	assert(GetCurrentThreadId() == ogre_thread_id);
	static unsigned index;

	return index++;
}

void ogre_log(const char* function, const char* format, ...)
{
	assert(GetCurrentThreadId() == ogre_thread_id);

	char buf[1024];
	va_list ap;
	va_start(ap, format);
	vsprintf(buf, format, ap);
	va_end(ap);
	Ogre::LogManager::getSingleton().logMessage(Ogre::String(function) + ": " + buf);
}

void ogre_log_(const char* function, const char* format, ...)
{
	assert(GetCurrentThreadId() == user_thread_id);

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
