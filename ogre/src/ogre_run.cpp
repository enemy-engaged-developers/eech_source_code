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
		Application(void)
			: count(0), last(GetTickCount()), ogre(0), user(0), ogreee(0)
		{
		}
#endif

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
			ogre_set(resource_group_name, mSceneMgr, mCamera);
			run_info->init();
		}
#ifdef OGRE_TIMES
		virtual void createFrameListener(void)
		{
			BaseApplication::createFrameListener();
			ogre_label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "Ogre", "", 200);
			user_label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "User", "", 200);
			ogreee_label = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "OgreEE", "", 200);
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
#endif

			ogre_update();

#ifdef OGRE_TIMES
			cur = GetTickCount();
			ogreee += cur - last;
			last = cur;
			count++;
			if (ogre + user + ogreee >= 1000)
			{
				char buf[64];
				sprintf(buf, "Ogre: %lu", ogre * 1000 / count);
				ogre_label->setCaption(buf);
				sprintf(buf, "User: %lu", user * 1000 / count);
				user_label->setCaption(buf);
				sprintf(buf, "OgreEE: %lu", ogreee * 1000 / count);
				ogreee_label->setCaption(buf);
				count = ogre = user = ogreee = 0;
			}
#endif

			return true;
		}

#ifdef OGRE_TIMES
		ULONG count, last, ogre, user, ogreee;
		OgreBites::Label* ogre_label;
		OgreBites::Label* user_label;
		OgreBites::Label* ogreee_label;
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

void OGREEE_CALL ogre_update(void)
{
	ogre_scenes_update();
	ogre_terrain_update();
}
