#include "stdafx.h"

// INCLUDES start

#include "options.hpp"

FILE* safe_fopen(const char* filename, const char* mode)
{
	FILE* file = fopen(filename, mode);
	assert(file);
	return file;
}

void error(const char* msg, ...)
{
	abort();
}

#define safe_fopen_rb(x) safe_fopen(x, "rb")


#define snprintf sprintf_s

#define PI (3.14159265359f)
#define PI2 (PI*2)
#define PI4 (PI*4)
#define PI_OVER_TWO (PI/2)
#define PI_OVER_FOUR (PI/4)


#include <../COMMON/ARRAY.H>
#include <EET.CPP>
#include <NAMES.CPP>
#include <TEXTURES.CPP>
#include <OBJECTS.CPP>
#include <SCENES.CPP>
#include <TRANS.CPP>
#include <LWS_EXP.CPP>

#include "ee_1.h"

#ifdef USE_TERRAIN
#include "ee_2.h"
#ifdef USE_TERRAIN_CURRENT
#include "terrtype.c"
#else
#define get_terrain_type_name get_terrain_type_name_
char* get_terrain_type_name(terrain_types type);
#include "terrtype_oldest.c"
#undef get_terrain_type_name
#endif
#include "terrdata.c"
#include "terrelev.c"
#include "terrobjs.c"
#include "terrsel.c"
#include "terrgeom.c"
#endif

#include "OGRE.HPP"

// INCLUDES finish

EET eet;

const char* get_texture_name(int index, bool animation)
{
	return eet.GetTexture(index, animation, (float)rand() / RAND_MAX);
}

int get_system_texture_index ( const char *name )
{
	for (unsigned i = 0; ; i++)
	{
		const char* texture = eet.GetTexture(i, false, 0.0f);
		if (!texture)
			break;
		if (!stricmp(name, texture))
			return i;
	}
	return -1;
}

// Adapter for textures loading
class TexturesExporter2 : public BaseTexturesExporter
{
	virtual void use_texture(int index, const char* name, int mip)
	{
		ogre_textures_define(index, number_of_mipmaps, mip, width, height, bpp, texture_image_data);
	}
};

// Loader and holder of EE textures, objects and scenes
struct EE
{
	EE(void)
	{
		{
			HKEY key;
			if (RegOpenKey(HKEY_LOCAL_MACHINE, "Software\\Razorworks\\Comanche Hokum", &key) == ERROR_SUCCESS)
			{
				char path[260] = "";
				DWORD size = sizeof(path);
				DWORD type = REG_SZ;
				RegQueryValueEx(key, "Installation Path", NULL, &type, (LPBYTE)path, &size);
				if (*path && size)
				{
					path[size] = '\0';
					strcat(path, "\\COHOKUM\\3DDATA");
					chdir(path);
				}
			}
			RegCloseKey(key);
		}

		{
			TexturesExporter2 exporter;
			exporter.export_textures(eet, false);
		}

		{
			AllNames all_names(eet);
		}

#ifdef USE_OBJECTS
		objects.reset(new Objects);
		scenes.reset(new Scenes(*objects));
#endif

#ifdef USE_OBJECTS_ONLY
		ogre_objects_init(objects->GetNumberOfObjects(), &(*objects)[0]);
#endif

#ifdef USE_TERRAIN_TREES
		ogre_terrain_tree((*objects)[0x2167]);
#endif
	}
	~EE()
	{
#ifdef USE_TERRAIN_TREES
		ogre_terrain_tree_clear();
#endif
#ifdef USE_OBJECTS_ONLY
		ogre_objects_clear();
#endif
		ogre_textures_clear();
	}

#ifdef USE_OBJECTS
	std::auto_ptr<Objects> objects;
	std::auto_ptr<Scenes> scenes;
#endif
};

// Declare a subclass of the ExampleFrameListener class
class MyListener : public ExampleFrameListener
{
public:
    MyListener(RenderWindow* win, Camera* cam, SceneManager* sman
#ifdef USE_OBJECTS_ONLY
	, const Scenes& scenes
#endif
	)
		: ExampleFrameListener(win, cam), mSceneMgr(sman),
#ifdef USE_OBJECTS_ONLY
		scenes(scenes),
#endif
			time(0.0f)
    {
#ifdef USE_OBJECTS_ONLY
		mMoveSpeed /= 10.0f;
#else
		mMoveSpeed *= 10.0f;
#endif

#ifdef USE_OBJECTS_ONLY
		// Create a pair of objects, 10 meters between their centers

		objects[0] = objects[1] = 0x0001;

		nodes[0] = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(-5.0f, 0, 0));
		nodes[1] = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(5.0f, 0, 0));

		ogre_scenes_init(scenes.GetNumberOfScenes(), &scenes.GetScene(0), mSceneMgr);

		set_scene(0, 0);
		set_scene(1, 0);
#endif

#ifdef USE_TERRAIN
		// Load and create terrain

		terrain = 1;
		set_terrain(0);
#endif

		mCamera->getViewport()->setBackgroundColour(ColourValue(0.3f, 0.3f, 0.3f));
		//mCamera->getViewport()->setBackgroundColour(ColourValue(1.0f, 1.0f, 1.0f));
    }

	~MyListener()
	{
#ifdef USE_TERRAIN
		ogre_terrain_clear();
		unload_3d_terrain();
#endif
#ifdef USE_OBJECTS_ONLY
		ogre_scenes_clear();
#endif
	}

    bool frameStarted(const FrameEvent& evt)
    {
		time += evt.timeSinceLastFrame;
		if (time > 10000.0f)
			time = 0.0f;
#ifdef USE_OBJECTS_ONLY
		// Animate current objects if required
		for (int index = 0; index < 2; index++)
		{
			for (unsigned i = 0; i < gos[index].database->elements.size(); i++)
			{
				const SceneDatabaseElement& el = gos[index].database->elements[i];

				if (!el.track)
					continue;

				float last = el.track->getParent()->getLength();
				float last1 = last + 0.5f;
				float last2 = last1 + last1;
				float last3 = last1 + last;
				float pos = fmod(time, last2);
				pos = pos >= last1 ? pos >= last3 ? 0.0f : (last3 - pos) : pos >= last ? last : pos;
				assert(pos >= 0.0f && pos <= last);

				SceneNode* node = gos[index].nodes[i];
				node->resetToInitialState();
				el.track->applyToNode(node, pos);
			}
		}
#endif
#ifdef USE_TERRAIN
		// Mark terrain sectors as visible and invisible
		ogre_terrain_update();
#endif
        return ExampleFrameListener::frameStarted(evt);
    }

    bool frameEnded(const FrameEvent& evt)
    {
		if (!ExampleFrameListener::frameEnded(evt))
		{
			return false;
		}
#ifdef USE_OBJECTS_ONLY
		// Display objects numbers
		{
			OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
			char buf[128];
			sprintf(buf, " Scns:%04X %04X", objects[0], objects[1]);
			guiBatches->setCaption(guiBatches->getCaption() + buf);
		}
#endif
#ifdef USE_TERRAIN
		// Display map number
		{
			OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
			char buf[128];
			sprintf(buf, " MAP:%i", terrain);
			guiBest->setCaption(guiBest->getCaption() + buf);
		}
#endif
        return true;
    }

	virtual bool processUnbufferedKeyInput(const FrameEvent& evt)
	{
		if (mTimeUntilNextToggle <= 0)
		{
			int sign = mKeyboard->isKeyDown(OIS::KC_LSHIFT) || mKeyboard->isKeyDown(OIS::KC_RSHIFT) ? -1 : 1;
#ifdef USE_OBJECTS_ONLY
			// Change the objects displayed
			if (mKeyboard->isKeyDown(OIS::KC_PERIOD))
				set_scene(0, 0x0001 * sign);
			if (mKeyboard->isKeyDown(OIS::KC_SLASH))
				set_scene(1, 0x0001 * sign);
			if (mKeyboard->isKeyDown(OIS::KC_SEMICOLON))
				set_scene(0, 0x0010 * sign);
			if (mKeyboard->isKeyDown(OIS::KC_APOSTROPHE))
				set_scene(1, 0x0010 * sign);
			if (mKeyboard->isKeyDown(OIS::KC_LBRACKET))
				set_scene(0, 0x0100 * sign);
			if (mKeyboard->isKeyDown(OIS::KC_RBRACKET))
				set_scene(1, 0x0100 * sign);
#endif
#ifdef USE_TERRAIN
			// Change the map displayed
			if (mKeyboard->isKeyDown(OIS::KC_M))
				set_terrain(sign);
#endif
		}

		return ExampleFrameListener::processUnbufferedKeyInput(evt);
	}

#ifdef USE_OBJECTS_ONLY
	// Remove previously displayed objects and create new ones
	void set_scene(int index, int change)
	{
		objects[index] += change;
		if (objects[index] < 1)
			objects[index] += scenes.GetNumberOfScenes();
		if (objects[index] > scenes.GetNumberOfScenes())
			objects[index] -= scenes.GetNumberOfScenes();

		nodes[index]->removeAllChildren();
		SceneNode* node = nodes[index]->createChildSceneNode();
		ogre_scene_create(objects[index], gos[index], node, mSceneMgr);
		mTimeUntilNextToggle = 0.3f;
	}
#endif

#ifdef USE_TERRAIN
	// Remove previously displayed terrain and create new one
	void set_terrain(int diff)
	{
		ogre_terrain_clear();
		unload_3d_terrain();

		terrain += diff;
		char path[1024];
		sprintf(path, "..\\..\\COMMON\\MAPS\\MAP%i\\TERRAIN", terrain);

		load_3d_terrain(path);
		ogre_terrain_init(mCamera, mSceneMgr);
	}
#endif

	SceneManager* mSceneMgr;
#ifdef USE_OBJECTS_ONLY
	const Scenes& scenes;
	SceneNode* nodes[2];
	int objects[2];
	GameObjectScene gos[2];
#endif
#ifdef USE_TERRAIN
	int terrain;
#endif
	float time;
};

// Declare a subclass of the ExampleApplication class
class SampleApp : public ExampleApplication
{
public:
   SampleApp()
   {
   }
   virtual ~SampleApp()
   {
   }

protected:
   // Define what is in the scene
   void createScene(void)
   {
#ifdef USE_OBJECTS_ONLY
		Light* light = mSceneMgr->createLight("light");
		light->setType(Light::LT_POINT);
		light->setDiffuseColour(ColourValue::White);
		light->setSpecularColour(ColourValue::White);
		light->setPosition(Vector3(0,4,0));
		light->setAttenuation(10.0f, 0.5f, 0.2f, 0.0f);

		mSceneMgr->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));
#else
		mSceneMgr->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f));
#endif
   }
    virtual void createCamera(void)
    {
	    ExampleApplication::createCamera();
#ifdef USE_TERRAIN
        mCamera->setPosition(Vector3(0, 2000, 0));
		mCamera->setDirection(Vector3(1, 0, 1));
#else
        mCamera->setPosition(Vector3(0, 0, 30));
#endif
        mCamera->setNearClipDistance(0.5f);
        mCamera->setFarClipDistance(20000.0f);
    }

   // Create new frame listener
   void createFrameListener(void)
   {
		ee.reset(new EE);
       mFrameListener = new MyListener(mWindow, mCamera, mSceneMgr
#ifdef USE_OBJECTS_ONLY
	   , *ee->scenes
#endif
	   );
       mRoot->addFrameListener(mFrameListener);
   }

	std::auto_ptr<EE> ee;
};

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    try {
    	// Instantiate our subclass
    	SampleApp myApp;

        // ExampleApplication provides a go method, which starts the rendering.
        myApp.go();
    }
    catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "Exception:\n";
        std::cerr << e.getFullDescription().c_str() << "\n";
#endif
        return 1;
    }

#ifdef USE_TERRAIN
deinitialise_file_system();
#endif

return 0;
}

#ifdef __cplusplus
}
#endif
