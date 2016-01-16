#include "ogre_int.hpp"

#include "BaseApplication.h"

#define OGRE_TIMES

namespace
{
	struct OgreRun* run_info;

	class Application : public BaseApplication
	{
#ifdef OGRE_TIMES
	public:
		Application()
			: count(0), last(GetTickCount()), ogre(0), user(0)
		{
		}
#endif

	protected:
		virtual void createScene(void)
		{
			const char* resource_group_name = "EE";
			Ogre::ResourceGroupManager::getSingleton().createResourceGroup(resource_group_name);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(".", "FileSystem", resource_group_name, false, true);
			ogre_set(resource_group_name, mSceneMgr, mCamera);
			run_info->init();
		}
#ifdef OGRE_TIMES
		virtual void createFrameListener(void)
		{
			BaseApplication::createFrameListener();
			ogre_label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Ogre", "", 200);
			user_label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "User", "", 200);
		}
#endif
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

#ifdef OGRE_TIMES
			ULONG cur = GetTickCount();
			ogre += cur - last;
			last = cur;
#endif

			run_info->frame(evt.timeSinceLastFrame);

#ifdef OGRE_TIMES
			cur = GetTickCount();
			user += cur - last;
			last = cur;
			count++;
			if (ogre + user >= 1000)
			{
				char buf[64];
				sprintf(buf, "Ogre: %lu", ogre * 1000 / count);
				ogre_label->setCaption(buf);
				sprintf(buf, "User: %lu", user * 1000 / count);
				user_label->setCaption(buf);
				count = ogre = user = 0;
			}
#endif

			return true;
		}

#ifdef OGRE_TIMES
		ULONG count, last, ogre, user;
		OgreBites::Label* ogre_label;
		OgreBites::Label* user_label;
#endif
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
