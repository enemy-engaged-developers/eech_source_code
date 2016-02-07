#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>

#include <algorithm>
#include <memory>
#include <vector>
#include <deque>

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#ifdef _MSC_VER
#define strupr _strupr
#define stricmp _stricmp
#define chdir _chdir
#define snprintf sprintf_s
#endif


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
typedef std::vector<unsigned char> Text;
std::deque<Text> texts;
class TexturesExporter2 : public BaseTexturesExporter
{
	virtual void use_texture(int index, const char* name, int mip)
	{
		const void* ptr = texture_image_data;
		if (mip <= 0)
		{
			if (bpp == 3)
			{
				texts.push_back(Text());
				texts.back().assign(texture_image_data, texture_image_data + width * height * bpp);
				ptr = &texts.back()[0];
			}
			else
			{
				for (unsigned size = width * height * bpp, off = 3; size; size -= 4, off += 4)
					texture_image_data[off] = ~texture_image_data[off];
			}
		}
		ogre_textures_define(index, number_of_mipmaps, mip, width, height, bpp, ptr);
	}
};

// Loader and holder of EE textures, objects and scenes
struct EE
{
	EE(void)
	{
		chdir("3ddata");

		{
			TexturesExporter2 exporter;
			exporter.export_textures(eet, false);
			ogre_textures_commit(false);
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
	}
	~EE()
	{
#ifdef USE_OBJECTS_ONLY
		ogre_objects_clear();
#endif
		ogre_textures_clear(TRUE);
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

float OGREEE_CALL get_terrain_3d_tree_scale_wrap ( const terrain_3d_tree_data *tree )
{
	return get_terrain_3d_tree_scale(const_cast<terrain_3d_tree_data*>(tree));
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
	struct OgreVector3& p = ogos[index].position;
	p.x = index ? -10.0f : 10.0f;
	p.y = 0;
	p.z = 0;

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
#ifdef USE_TERRAIN_TREES
	const struct OBJECT_3D* tree = &(*ee->objects)[ee->scenes->GetScene(0x0A58).index];
#else
	const struct OBJECT_3D* tree = 0;
#endif
	struct OgreTerrainInit terrain_init = { terrain_3d_sector_z_max, terrain_3d_sector_x_max, terrain_3d_map_scaled_height_difference, terrain_3d_map_minimum_height, terrain_3d_map_maximum_height, tree, get_terrain_3d_tree_scale_wrap, terrain_type_information, terrain_sectors, terrain_tree_sectors };
	ogre_terrain_init(&terrain_init);
}
#endif

#ifdef USE_UI
unsigned ui1, ui2;
#endif

void OGREEE_CALL init(void)
{
	{
#ifdef USE_TERRAIN
		float p[3] = { 0, 2000, 0 };
		float f = sqrt(0.5f);
		matrix3x3 o = { f, 0, -f, 0, 1, 0, f, 0, f };
#else
		float p[3] = { 0, 0, 30 };
		matrix3x3 o = { -1, 0, 0, 0, 1, 0, 0, 0, -1 };
#endif
		ogre_set_viewpoint(p, o);
	}

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

#ifdef USE_UI
	ui1 = ogre_texture_load("..\\graphics\\ui\\cohokum\\Combat.psd");
	ui2 = ogre_texture_load("..\\graphics\\ui\\cohokum\\Map\\ExitBTN.psd");
	ogre_ui_font(1, "times", 20);
	ogre_ui_font(2, "arial", 40);
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

#ifdef USE_UI
	ogre_texture_clear(ui1);
	ogre_texture_clear(ui2);
	ogre_ui_fonts_clear();
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
		for (unsigned i = 0; i < g->number_of_elements; i++)
		{
			float last = ogre_scene_subobject_keyframe_length(g, i);

			if (last == 0.0)
				continue;

			float last1 = last + 0.5f;
			float last3 = last1 + last;
			float pos = fmod(cur_time, last1 + last1);
			pos = pos >= last1 ? pos >= last3 ? 0.0f : (last3 - pos) : pos >= last ? last : pos;
			assert(pos >= 0.0f && pos <= last);

			g->elements[i].animation = pos;
		}

		struct RI
		{
			unsigned subobject;
			float OgreGameObjectSceneElement::* axis;
		};
		const RI so[] =
		{
			{ 19, &OgreGameObjectSceneElement::relative_pitch },
			{ 20, &OgreGameObjectSceneElement::relative_pitch },
			{ 24, &OgreGameObjectSceneElement::relative_heading }
		};
		for (unsigned o = 0; o < ARRAYSIZE(so); o++)
		{
			OgreSubObjectsSearch s;
			if (ogre_scene_find(g, so[o].subobject, &s))
			{
				for (unsigned j = 0; j != s.number_of_subobjects; j++)
				{
					struct OgreGameObjectSceneElement& n = g->elements[s.subobjects[j]];
					float& a = n.*so[o].axis;
					a = fmod(a + fmod(cur_time, 10.0f) * 0.01f, PI2);
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
							g->elements[p.subobjects[pi]].visible_object = false;
						g->elements[sp].visible_object = true;
						OgreSubObjectsSearch w;
						if (ogre_scene_find2(g, 29, sp, &w))
						{
							double df = exp(((unsigned)cur_time) / p.number_of_subobjects / double(h.subobjects[hi]) + index);
							unsigned flags = reinterpret_cast<const unsigned&>(df);
							for (unsigned wi = 0; wi != w.number_of_subobjects; wi++)
								g->elements[w.subobjects[wi]].visible_object = flags & (1 << wi) ? true : false;
						}
					}
				}
			}
		}

		ogre_scene_draw(g, 0);
	}
	ogre_scenes_commit();
#endif
#ifdef USE_TERRAIN
	ogre_terrain_draw();
#endif

#ifdef USE_UI
	ogre_ui_draw(ui1, 100, 200, 300, 400);
	ogre_ui_draw(ui2, 200, 300, 400, 500);
	ogre_ui_draw(ui2, 450, 200, 605, 260);
	ogre_ui_draw(ui2, 450, 300, 605, 361);
	ogre_ui_text(1, 600, 300, "ABC\xD0\x81" "abc", 0xFFFF0000);
	ogre_ui_text(2, 600, 330, "ABC\xD0\x81" "abc", 0xFF00FF00);
	ogre_ui_text(2, 600, 350, "ABC\xD0\x81" "abc", 0xFF0000FF);
#endif

	{
		char buf[128];
#ifdef USE_OBJECTS_ONLY
		sprintf(buf, "Scns: %04X %04X", objects[0], objects[1]);
#endif
#ifdef USE_TERRAIN
		sprintf(buf, "MAP: %i", terrain);
#endif
		ogre_info(buf);
	}
}

volatile int quit;
volatile unsigned key_pressed;
void OGREEE_CALL key_func(unsigned key)
{
	key_pressed = key;
}
void key_func(void)
{
	static int sign = 1;
	switch (key_pressed)
	{
	case DIK_ESCAPE:
		quit = 1;
		break;
	case DIK_LSHIFT:
		sign = -1;
		break;
	case DIK_LSHIFT | 0x100:
		sign = 1;
		break;
#ifdef USE_OBJECTS_ONLY
	case DIK_PERIOD:
		set_scene(0, 0x0001 * sign);
		break;
	case DIK_SLASH:
		set_scene(1, 0x0001 * sign);
		break;
	case DIK_SEMICOLON:
		set_scene(0, 0x0010 * sign);
		break;
	case DIK_APOSTROPHE:
		set_scene(1, 0x0010 * sign);
		break;
	case DIK_LBRACKET:
		set_scene(0, 0x0100 * sign);
		break;
	case DIK_RBRACKET:
		set_scene(1, 0x0100 * sign);
		break;
#endif
#ifdef USE_TERRAIN
	case DIK_M:
		set_terrain(sign);
		break;
	case DIK_J:
		{
			float p[3] = { rand() * 1024.0f * terrain_3d_sector_x_max / RAND_MAX, 2000, rand() * 1024.0f * terrain_3d_sector_z_max / RAND_MAX };
			float f = sqrt(0.5f);
			matrix3x3 o = { f, 0, -f, 0, 1, 0, f, 0, f };
			ogre_set_viewpoint(p, o);
		}
		break;
#endif
	default:
		return;
	}
	key_pressed = 0;
}
unsigned long OGREEE_CALL thread(void*)
{
	init();
	float last = GetTickCount() / 1000.0f;
	while (!quit)
	{
		float cur = GetTickCount() / 1000.0f;
		key_func();
		frame(cur - last);
		ogre_frame();
		last = cur;
	}
	deinit();
	ogre_quit();
	return 0;
}

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
				strcat(path, "\\COHOKUM");
				chdir(path);
			}
		}
		RegCloseKey(key);
	}
	struct OgreRun run = { thread, 0, key_func, 0 };
	ogre_run(&run);
	return 0;
}

#ifdef __cplusplus
}
#endif

#if 0
		mCamera->getViewport()->setBackgroundColour(Ogre::ColourValue(0.18f, 0.77f, 0.87f));
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
#endif
