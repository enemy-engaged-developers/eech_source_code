#include "ogre_int.hpp"

#include "BaseApplication.h"

namespace
{
	struct OgreRun* run_info;

	class Application : public BaseApplication
	{
	protected:
		virtual void createScene(void)
		{
			const char* resource_group_name = "EE";
			Ogre::ResourceGroupManager::getSingleton().createResourceGroup(resource_group_name);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(".", "FileSystem", resource_group_name, false, true);
			ogre_set(resource_group_name, mSceneMgr, mCamera);
			run_info->init();
		}
		virtual void destroyScene(void)
		{
			run_info->deinit();
			Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("EE");
			BaseApplication::destroyScene();
		}
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt)
		{
			if (!BaseApplication::frameRenderingQueued(evt))
				return false;

			run_info->frame(evt.timeSinceLastFrame);
			return true;
		}
	};
}

void OGREEE_CALL ogre_run(struct OgreRun* run)
{
	run_info = run;

	Application app;

	try
	{
		app.go();
	}
	catch (const Ogre::Exception& e)
	{
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
}
