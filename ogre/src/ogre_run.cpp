#include "ogre_int.hpp"

#include "BaseApplication.h"

unsigned long ogre_thread_id, user_thread_id;

namespace
{
	const struct OgreRun* run_info;
	HANDLE thread;
	Semaphore frames(2, 5);
	Ogre::String user_info;

	class Application : public BaseApplication
	{
	public:
		Application(void)
			: user_label(0)
#ifdef USE_TIME
				, count(0), last(GetTickCount()), ogre(0), wait(0), work(0)
#endif
		{
			ogre_tasks = &tq;
		}

	protected:
		virtual void setupResources(void)
		{
			Ogre::ConfigFile cf;
			cf.load(mResourcesCfg);
			Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
			Ogre::String sec, type, arch;
			while (seci.hasMoreElements())
			{
				sec = seci.peekNextKey();
				Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
				Ogre::ConfigFile::SettingsMultiMap::iterator i;
				for (i = settings->begin(); i != settings->end(); i++)
				{
					type = i->first;
					arch = i->second;
					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
				}
			}
			const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList("General");
			arch = genLocs.front()->archive->getName();
			type = "FileSystem";
			sec = "Popular";
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/Cg", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL_Cg", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/GLSLES", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/GLSL", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/GLSL150", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/HLSL", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/Cg", type, sec);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/RTShaderLib/HLSL_Cg", type, sec);
		}
		virtual void createScene(void)
		{
			const char* resource_group_name = "EE";
			Ogre::ResourceGroupManager::getSingleton().createResourceGroup(resource_group_name);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(".", "FileSystem", resource_group_name, false, true);
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation("C:\\WINDOWS\\Fonts", "FileSystem", resource_group_name, false, true);
			ogre_set(resource_group_name, mSceneMgr, mCamera);

			Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
			overlay = om.create("OgreUIOverlay");
			ogre_ui = static_cast<Ogre::OverlayContainer*>(om.createOverlayElement("Panel", "OgreUI"));
			overlay->add2D(ogre_ui);
			overlay->show();

			ogre_thread_id = GetCurrentThreadId();
			if (run_info->resolution)
			{
				unsigned int width, height, colourDepth;
				int left, top;
				mWindow->getMetrics(width, height, colourDepth, left, top);
				run_info->resolution(width, height);
			}
			thread = CreateThread(0, 0, run_info->thread_func, run_info->thread_param, 0, &user_thread_id);
		}
#ifdef USE_TIME
		virtual void createFrameListener(void)
		{
			BaseApplication::createFrameListener();
			ogre_label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Ogre", "", 200);
			wait_label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Wait", "", 200);
			work_label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Work", "", 200);
		}
#endif
		virtual void destroyScene(void)
		{
			Ogre::OverlayManager& om = Ogre::OverlayManager::getSingleton();
			Ogre::OverlayManager::getSingleton().destroyOverlayElement(ogre_ui);
			Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("EE");
			BaseApplication::destroyScene();
		}
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt)
		{
			//ogre_log(__FUNCTION__, "");

			if (!BaseApplication::frameRenderingQueued(evt))
				return false;

			if (!user_label && !user_info.empty())
				user_label = mTrayMgr->createLabel(OgreBites::TL_TOP, "User", "", 200);
			if (user_label)
				user_label->setCaption(user_info);

#ifdef USE_TIME
			unsigned cur = GetTickCount();
			ogre += cur - last;
			last = cur;
			unsigned tqwait;
			ogre_terrain_frame(false);
			ogre_scenes_frame();
			ogre_ui_frame();
			TaskResult tr = tq.run(tqwait);
			ogre_terrain_frame(true);
			overlay->setZOrder(10);
			cur = GetTickCount();
			work += cur - last - tqwait;
			wait += tqwait;
			last = cur;
			count++;
			if (ogre + wait + work >= 1000)
			{
				char buf[64];
				sprintf(buf, "Ogre: %lu", ogre * 1000 / count);
				ogre_label->setCaption(buf);
				sprintf(buf, "Wait: %lu", wait * 1000 / count);
				wait_label->setCaption(buf);
				sprintf(buf, "Work: %lu", work * 1000 / count);
				work_label->setCaption(buf);
				count = ogre = wait = work = 0;
			}
#else
			TaskResult tr = tq.run();
#endif
			frames.release();
			return tr != TR_APP;
		}
		virtual bool keyPressed(const OIS::KeyEvent& arg)
		{
			BaseApplication::keyPressed(arg);
			mShutDown = false;
			if (run_info->key_func)
				run_info->key_func(arg.key);
			return true;
		}
		virtual bool keyReleased(const OIS::KeyEvent& arg)
		{
			BaseApplication::keyReleased(arg);
			if (run_info->key_func)
				run_info->key_func(arg.key | 0x100);
			return true;
		}
		virtual bool mouseMoved(const OIS::MouseEvent& arg)
		{
			BaseApplication::mouseMoved(arg);
			if (run_info->mouse_func)
				run_info->mouse_func(0, arg.state.X.rel, arg.state.Y.rel, arg.state.Z.rel);
			return true;
		}
		virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
		{
			BaseApplication::mousePressed(arg, id);
			if (run_info->mouse_func)
				run_info->mouse_func(1 << (2 * id), 0, 0, 0);
			return true;
		}
		virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
		{
			BaseApplication::mouseReleased(arg, id);
			if (run_info->mouse_func)
				run_info->mouse_func(2 << (2 * id), 0, 0, 0);
			return true;
		}

		TaskQueue tq;
		Ogre::Overlay* overlay;
		OgreBites::Label* user_label;
#ifdef USE_TIME
		unsigned count, last, ogre, wait, work;
		OgreBites::Label* ogre_label;
		OgreBites::Label* wait_label;
		OgreBites::Label* work_label;
#endif
	};

	class TaskInfo : public Task
	{
	public:
		TaskInfo(const char* info)
			: info(info ? info : "")
		{
		}
		virtual TaskResult task(void)
		{
			user_info = info;
			return TR_TASK;
		}
	private:
		Ogre::String info;
	};

	struct TaskFrame : public Task
	{
		virtual TaskResult task(void)
		{
			return TR_FRAME;
		}
	};

	struct TaskQuit : public Task
	{
		virtual TaskResult task(void)
		{
			return TR_APP;
		}
	};
}

void OGREEE_CALL ogre_run(const struct OgreRun* run)
{
	ogre_log_(__FUNCTION__, "");

	run_info = run;

	Application app;

	try
	{
		app.go();
		WaitForSingleObject(thread, INFINITE);
	}
	catch (const Ogre::Exception& e)
	{
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
}

OGREEE_API void OGREEE_CALL ogre_info(const char* info)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	ogre_tasks->enqueue(new TaskInfo(info));
}

OGREEE_API void OGREEE_CALL ogre_frame(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	ogre_ui_commit();
	frames.acquire();
	ogre_tasks->enqueue(new TaskFrame);
}

OGREEE_API void OGREEE_CALL ogre_quit(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "");

	ogre_tasks->enqueue(new TaskQuit);
}
