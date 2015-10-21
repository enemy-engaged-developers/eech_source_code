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

unsigned get_animation_size(unsigned index)
{
	return eet.GetAnimationSize(index);
}

unsigned get_animation_texture(unsigned index, unsigned frame)
{
	return eet.GetAnimationTexture(index, frame);
}

int get_system_texture_index ( const char *name )
{
	for (unsigned i = 0; ; i++)
	{
		const char* texture = eet.GetTexture(i);
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

class TutorialApplication : public BaseApplication
{
public:
	TutorialApplication(void)
		: time(0.0f)
	{
	}
	virtual ~TutorialApplication(void)
	{
#ifdef USE_TERRAIN
		ogre_terrain_clear();
		unload_3d_terrain();
#endif

#ifdef USE_OBJECTS_ONLY
		ogre_scenes_clear();
#endif
#ifdef USE_TERRAIN
		deinitialise_file_system();
#endif
	}

protected:
	virtual void createFrameListener(void)
	{
		BaseApplication::createFrameListener();

		ee.reset(new EE);
#ifdef USE_OBJECTS_ONLY
		scenes = ee->scenes.get();
#endif

		float speed = mCameraMan->getTopSpeed();
#ifdef USE_OBJECTS_ONLY
		speed /= 10.0f;
#else
		speed *= 10.0f;
#endif
		mCameraMan->setTopSpeed(speed);

#ifdef USE_OBJECTS_ONLY
		// Create a pair of objects, 10 meters between their centers

		objects[0] = objects[1] = 0x0001;

		nodes[0] = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(10.0f, 0, 0));
		nodes[1] = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(-10.0f, 0, 0));

		ogre_scenes_init(scenes->GetNumberOfScenes(), &scenes->GetScene(0), mSceneMgr);

		set_scene(0, 0);
		set_scene(1, 0);
#endif

#ifdef USE_TERRAIN
		// Load and create terrain

		terrain = 1;
		set_terrain(0);
#endif
		mCamera->getViewport()->setBackgroundColour(Ogre::ColourValue(0.18f, 0.77f, 0.87f));
#ifdef USE_OBJECTS_ONLY
		obj_label = mTrayMgr->createLabel(OgreBites::TL_TOP, "Objects", "", 200);
#endif
#ifdef USE_TERRAIN
		terr_label = mTrayMgr->createLabel(OgreBites::TL_TOP, "Map", "", 100);
#endif
	}
	virtual void createScene(void)
	{
#ifdef USE_OBJECTS_ONLY
		Ogre::Light* light = mSceneMgr->createLight("light");
		light->setType(Ogre::Light::LT_POINT);
		light->setDiffuseColour(Ogre::ColourValue::White);
		light->setSpecularColour(Ogre::ColourValue::White);
		light->setPosition(Ogre::Vector3(0,4,0));
		light->setAttenuation(10.0f, 0.5f, 0.2f, 0.0f);

		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.6f, 0.6f, 0.6f));
#else
		mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

		mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
#endif
	}
	virtual void createCamera(void)
	{
		BaseApplication::createCamera();
#ifdef USE_TERRAIN
		mCamera->setPosition(Ogre::Vector3(0, 2000, 0));
		mCamera->setDirection(Ogre::Vector3(1, 0, -1));
#else
		mCamera->setPosition(Ogre::Vector3(0, 0, -30));
		mCamera->setDirection(Ogre::Vector3(0, 0, 1));
#endif
		mCamera->setNearClipDistance(0.5f);
		mCamera->setFarClipDistance(20000.0f);
	}
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt)
	{
		if (!BaseApplication::frameRenderingQueued(evt))
			return false;

		time += evt.timeSinceLastFrame;
		if (time > 10000.0f)
			time = 0.0f;
#ifdef USE_OBJECTS_ONLY
		// Animate current objects if required
		for (int index = 0; index < 2; index++)
		{
			GameObjectScene& g = gos[index];
			for (unsigned i = 0; i < g.database->elements.size(); i++)
			{
				const SceneDatabaseElement& el = g.database->elements[i];

				if (!el.track)
					continue;

				float last = el.track->getParent()->getLength();
				float last1 = last + 0.5f;
				float last2 = last1 + last1;
				float last3 = last1 + last;
				float pos = fmod(time, last2);
				pos = pos >= last1 ? pos >= last3 ? 0.0f : (last3 - pos) : pos >= last ? last : pos;
				assert(pos >= 0.0f && pos <= last);

				Ogre::SceneNode* node = g.nodes[i];
				node->resetToInitialState();
				el.track->applyToNode(node, pos);
			}

			struct RI
			{
				unsigned subobject;
				const Ogre::Vector3& axis;
			};
			const RI so[] =
			{
				{ 19, Ogre::Vector3::UNIT_X },
				{ 20, Ogre::Vector3::UNIT_X },
				{ 24, Ogre::Vector3::UNIT_Y }
			};
			for (unsigned o = 0; o < ARRAYSIZE(so); o++)
			{
				const SubObjects& s = ogre_scene_find(g, so[o].subobject);
				for (SubObjects::const_iterator j = s.begin(); j != s.end(); ++j)
					g.nodes[*j]->setOrientation(g.nodes[*j]->getOrientation() * Ogre::Quaternion(Ogre::Radian(fmod(time, 10.0f) * 0.01f), so[o].axis));
			}
			{
				const SubObjects& h = ogre_scene_find(g, 3);
				for (SubObjects::const_iterator hi = h.begin(); hi != h.end(); ++hi)
				{
					const SubObjects& p = ogre_scene_find2(g, 28, *hi);
					if (!p.empty())
					{
						unsigned sp = p[((unsigned)time) % p.size()];
						for (SubObjects::const_iterator pi = p.begin(); pi != p.end(); ++pi)
							g.nodes[*pi]->setVisible(false, true);
						g.nodes[sp]->setVisible(true, true);
						const SubObjects& w = ogre_scene_find2(g, 29, sp);
						double df = exp(((unsigned)time) / p.size() / double(*hi));
						unsigned flags = reinterpret_cast<const unsigned&>(df);
						for (size_t wi = 0; wi != w.size(); wi++)
							g.nodes[w[wi]]->setVisible(flags & (1 << wi) ? true : false, true);
					}
				}
			}
		}
#endif
#ifdef USE_TERRAIN
		// Mark terrain sectors as visible and invisible
		ogre_terrain_update();
#endif

#ifdef USE_OBJECTS_ONLY
		// Display objects numbers
		{
			char buf[128];
			sprintf(buf, "Scns: %04X %04X", objects[0], objects[1]);
			obj_label->setCaption(buf);
		}
#endif
#ifdef USE_TERRAIN
		// Display map number
		{
			char buf[128];
			sprintf(buf, "MAP: %i", terrain);
			terr_label->setCaption(buf);
		}
#endif
		return true;
	}
	virtual bool keyPressed(const OIS::KeyEvent &evt)
	{
		BaseApplication::keyPressed(evt);

		{
			int sign = mKeyboard->isKeyDown(OIS::KC_LSHIFT) || mKeyboard->isKeyDown(OIS::KC_RSHIFT) ? -1 : 1;
#ifdef USE_OBJECTS_ONLY
			// Change the objects displayed
			if (evt.key == OIS::KC_PERIOD)
				set_scene(0, 0x0001 * sign);
			if (evt.key == OIS::KC_SLASH)
				set_scene(1, 0x0001 * sign);
			if (evt.key == OIS::KC_SEMICOLON)
				set_scene(0, 0x0010 * sign);
			if (evt.key == OIS::KC_APOSTROPHE)
				set_scene(1, 0x0010 * sign);
			if (evt.key == OIS::KC_LBRACKET)
				set_scene(0, 0x0100 * sign);
			if (evt.key == OIS::KC_RBRACKET)
				set_scene(1, 0x0100 * sign);
#endif
#ifdef USE_TERRAIN
			// Change the map displayed
			if (evt.key == OIS::KC_M)
				set_terrain(sign);
#endif
		}

		return true;
	}

#ifdef USE_OBJECTS_ONLY
	// Remove previously displayed objects and create new ones
	void set_scene(int index, int change)
	{
		objects[index] += change;
		if (objects[index] < 1)
			objects[index] += scenes->GetNumberOfScenes();
		if (objects[index] > scenes->GetNumberOfScenes())
			objects[index] -= scenes->GetNumberOfScenes();

		nodes[index]->removeAllChildren();
		Ogre::SceneNode* node = nodes[index]->createChildSceneNode();
		ogre_scene_create(objects[index], gos[index], node, mSceneMgr);

		for (unsigned animation_index = 0, size; size = get_animation_size(animation_index); animation_index++)
			ogre_scene_animation(gos[index], animation_index, rand() % size);
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
private:
	std::auto_ptr<EE> ee;
#ifdef USE_OBJECTS_ONLY
	const Scenes* scenes;
	Ogre::SceneNode* nodes[2];
	int objects[2];
	GameObjectScene gos[2];
#endif
#ifdef USE_TERRAIN
	int terrain;
#endif
	float time;
#ifdef USE_OBJECTS_ONLY
	OgreBites::Label* obj_label;
#endif
#ifdef USE_TERRAIN
	OgreBites::Label* terr_label;
#endif
};

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }
}

#ifdef __cplusplus
}
#endif
