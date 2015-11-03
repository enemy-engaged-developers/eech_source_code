#include "BaseApplication.h"
#include <direct.h>

#pragma warning(disable:4305)

#include "ogreee.h"

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


#include <../COMMON/ARRAY.H>
#include <EET.CPP>
#include <NAMES.CPP>
#include <TEXTURES.CPP>
#include <OBJECTS.CPP>
#include <SCENES.CPP>
#include <TRANS.CPP>
#include <LWS_EXP.CPP>

#ifdef USE_TERRAIN
#include "ee.h"
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

// INCLUDES finish

EET eet;

unsigned OGREEE_CALL get_animation_size(unsigned index)
{
	return eet.GetAnimationSize(index);
}

unsigned OGREEE_CALL get_animation_texture(unsigned index, unsigned frame)
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
		OgreObjectsInit objects_init = { objects->GetNumberOfObjects(), &(*objects)[0], get_animation_size, get_animation_texture };
		ogre_objects_init(&objects_init);
#endif

#ifdef USE_TERRAIN_TREES
		ogre_terrain_tree(&(*objects)[0x2167]);
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

float cur_time;
std::auto_ptr<EE> ee;
#ifdef USE_OBJECTS_ONLY
const Scenes* scenes;
int objects[2];
OgreGameObjectScene ogos[2];
#endif
#ifdef USE_TERRAIN
int terrain;

float OGREEE_CALL get_terrain_3d_tree_scale_wrap ( terrain_3d_tree_data *tree )
{
	return get_terrain_3d_tree_scale(tree);
}
#endif

#ifdef USE_OBJECTS_ONLY
// Remove previously displayed objects and create new ones
void set_scene(int index, int change)
{
	objects[index] += change;
	if (objects[index] < 1)
		objects[index] += scenes->GetNumberOfScenes();
	if (objects[index] > scenes->GetNumberOfScenes())
		objects[index] -= scenes->GetNumberOfScenes();

	ogre_scene_destroy(&ogos[index]);
	ogre_scene_create(&ogos[index], objects[index]);
	vec3d v = { index ? -10 : 10, 0, 0 };
	ogre_node_set_position(ogos[index].root, &v);

	for (unsigned animation_index = 0, size; size = get_animation_size(animation_index); animation_index++)
		ogre_scene_animation(&ogos[index], animation_index, rand() % size);
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
	struct OgreTerrainInit terrain_init = { terrain_3d_sector_z_max, terrain_3d_sector_x_max, terrain_3d_map_scaled_height_difference, terrain_3d_map_minimum_height, terrain_3d_map_maximum_height, get_terrain_3d_tree_scale_wrap, terrain_type_information, terrain_sectors, terrain_tree_sectors };
	ogre_terrain_init(&terrain_init);
}
#endif

void OGREEE_CALL init(void)
{
	cur_time = 0.0f;

	ee.reset(new EE);
#ifdef USE_OBJECTS_ONLY
	scenes = ee->scenes.get();
#endif

#ifdef USE_OBJECTS_ONLY
	ogre_scenes_init(scenes->GetNumberOfScenes(), &scenes->GetScene(0));

	// Create a pair of objects

	objects[0] = objects[1] = 0x0001;

	ogre_scene_init(&ogos[0]);
	ogre_scene_init(&ogos[1]);

	set_scene(0, 0);
	set_scene(1, 0);
#endif

#ifdef USE_TERRAIN
	// Load and create terrain

	terrain = 1;
	set_terrain(0);
#endif
}

void OGREEE_CALL deinit(void)
{
#ifdef USE_OBJECTS_ONLY
	ogre_scene_destroy(&ogos[0]);
	ogre_scene_destroy(&ogos[1]);
#endif

#ifdef USE_TERRAIN
	ogre_terrain_clear();
	unload_3d_terrain();
#endif

#ifdef USE_OBJECTS_ONLY
	ogre_scenes_clear();
#endif

#ifdef USE_OBJECTS_ONLY
	scenes = 0;
#endif
	ee.reset(0);

#ifdef USE_TERRAIN
	deinitialise_file_system();
#endif
}

void OGREEE_CALL frame(float dtime)
{
	cur_time += dtime;
	if (cur_time > 10000.0f)
		cur_time = 0.0f;
#ifdef USE_OBJECTS_ONLY
	// Animate current objects if required
	for (int index = 0; index < 2; index++)
	{
		OgreGameObjectScene* g = &ogos[index];
		for (unsigned i = 0; i < g->number_of_nodes; i++)
		{
			float last = ogre_scene_subobject_keyframe_length(g, i);

			if (last == 0.0)
				continue;

			float last1 = last + 0.5f;
			float last3 = last1 + last;
			float pos = fmod(cur_time, last1 + last1);
			pos = pos >= last1 ? pos >= last3 ? 0.0f : (last3 - pos) : pos >= last ? last : pos;
			assert(pos >= 0.0f && pos <= last);

			ogre_scene_subobject_keyframe(g, i, pos);
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
			OgreSubObjectsSearch s;
			if (ogre_scene_find(g, so[o].subobject, &s))
			{
				for (unsigned j = 0; j != s.number_of_subobjects; j++)
				{
					OgreNode* n = g->nodes[s.subobjects[j]];
					matrix3x3 m33;
					ogre_node_get_orientation(n, m33);
					Ogre::Matrix3 m(m33), r;
					Ogre::Quaternion(Ogre::Radian(fmod(cur_time, 10.0f) * 0.01f), so[o].axis).ToRotationMatrix(r);
					m = m * r;
					memcpy(m33, m[0], sizeof(m33));
					ogre_node_set_orientation(n, m33);
				}
			}
		}
		{
			OgreSubObjectsSearch h;
			if (ogre_scene_find(g, 3, &h))
			{
				for (unsigned hi = 0; hi != h.number_of_subobjects; hi++)
				{
					OgreSubObjectsSearch p;
					if (ogre_scene_find2(g, 28, h.subobjects[hi], &p) && p.number_of_subobjects)
					{
						unsigned sp = p.subobjects[((unsigned)cur_time) % p.number_of_subobjects];
						for (unsigned pi = 0; pi != p.number_of_subobjects; pi++)
							ogre_node_set_visible(g->nodes[p.subobjects[pi]], false);
						ogre_node_set_visible(g->nodes[sp], true);
						OgreSubObjectsSearch w;
						if (ogre_scene_find2(g, 29, sp, &w))
						{
							double df = exp(((unsigned)cur_time) / p.number_of_subobjects / double(h.subobjects[hi]) + index);
							unsigned flags = reinterpret_cast<const unsigned&>(df);
							for (unsigned wi = 0; wi != w.number_of_subobjects; wi++)
								ogre_node_set_visible(g->nodes[w.subobjects[wi]], flags & (1 << wi));
						}
					}
				}
			}
		}
	}
#endif
#ifdef USE_TERRAIN
	// Mark terrain sectors as visible and invisible
	ogre_terrain_update();
#endif
}

#ifndef USE_OGRE_RUN
class TutorialApplication : public BaseApplication
{
protected:
	virtual void createFrameListener(void)
	{
		BaseApplication::createFrameListener();

		float speed = mCameraMan->getTopSpeed();
#ifdef USE_OBJECTS_ONLY
		speed /= 10.0f;
#else
		speed *= 10.0f;
#endif
		mCameraMan->setTopSpeed(speed);

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
		Ogre::ResourceGroupManager::getSingleton().createResourceGroup("EE");

		ogre_set("EE", mSceneMgr, mCamera);

		init ();

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
	virtual void destroyScene(void)
	{
		deinit();

		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("EE");

		BaseApplication::destroyScene();
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

		frame(evt.timeSinceLastFrame);

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

private:
#ifdef USE_OBJECTS_ONLY
	OgreBites::Label* obj_label;
#endif
#ifdef USE_TERRAIN
	OgreBites::Label* terr_label;
#endif
};
#endif

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
#ifdef _CRTDBG_MAP_ALLOC
_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
#ifdef USE_OGRE_RUN
	struct OgreRun run = { init, deinit, frame };
	ogre_run(&run);
#else
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
#endif
}

#ifdef __cplusplus
}
#endif
