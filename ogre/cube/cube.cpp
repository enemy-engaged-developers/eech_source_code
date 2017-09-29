#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <io.h>

#include <algorithm>
#include <memory>
#include <vector>
#include <deque>
#include <map>
#include <string>

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

#define bound(VALUE,LOWER,UPPER) ( ( VALUE ) < ( LOWER ) ? ( LOWER ) : ( ( VALUE ) > ( UPPER ) ? ( UPPER ) : ( VALUE ) ) )
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

namespace
{
EET eet;

#ifdef USE_TERRAIN_NEW_TEXTURES
typedef std::map<std::string, unsigned> NewTextures;
NewTextures new_textures;
#endif
}

int add_new_texture(const char* texture_name, const char* source)
{
#if defined(USE_TERRAIN) && defined(USE_TERRAIN_NEW_TEXTURES)
	int found = get_system_texture_index ( texture_name );
	if (found != -1)
		return found;
	unsigned index = eet.GetTextures() + new_textures.size();
	new_textures[texture_name] = index;
	return index;
#else
	return -1;
#endif
}

int get_system_texture_index ( const char *name )
{
	unsigned size = eet.GetTextures();
#ifdef USE_TERRAIN_NEW_TEXTURES
	NewTextures::iterator itor(new_textures.find(name));
	if (itor != new_textures.end())
	{
		return itor->second;
	}
#endif
	for (unsigned i = 0; i < size; i++)
	{
		if (!stricmp(name, eet.GetTexture(i)))
			return i;
	}
	return -1;
}

namespace
{
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

#if defined(USE_OBJECTS_ONLY) || defined(USE_PARTICLES)
		unsigned number_of_animations = eet.GetAnimations();
		std::vector<unsigned> data;
		for (unsigned i = 0; i < number_of_animations; i++)
		{
			unsigned size = eet.GetAnimationSize(i);
			data.push_back(size);
			for (unsigned j = 0; j < size; j++)
			{
				data.push_back(eet.GetAnimationTexture(i, j));
			}
		}
		ogre_textures_animation(number_of_animations, &data[0]);
		data.clear();
#endif

#ifdef USE_OBJECTS_ONLY
		ogre_objects_init(objects->GetNumberOfObjects(), &(*objects)[0]);
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

	for (unsigned animation_index = 0; animation_index < eet.GetAnimations(); animation_index++)
		ogre_scene_animation(&ogos[index], animation_index, rand() % eet.GetAnimationSize(animation_index));
}
#endif

#ifdef USE_TERRAIN
const char* terrain_name(int terrain)
{
	const char* maps[] =
	{
		NULL,
		"Thailand",
		"Cuba",
		"Georgia",
		"Taiwan",
		"Lebanon",
		"Yemen",
		"Alaska",
		"Aleut",
		"Kuwait",
		"Lybia",
		"Grand Canyon",
		"Mars",
		"Alexander Archipelago",
		"Skagway",
		"Saudi Arabia Red Sea",
		"Kenai Peninsula",
		"Afognak",
		"Puerto Rico",
		"Jordan Dead Sea",
		"Lake Powell",
	};
	if (terrain > 0 && terrain <= 20)
		return maps[terrain];
	switch (terrain)
	{
	case 31:
		return "Grand";
		break;
	case 32:
		return "Europe";
		break;
	case 35:
		return "Norway";
		break;
	};
	return "Unknown";
}

// Remove previously displayed terrain and create new one
void set_terrain(int diff)
{
	ogre_terrain_clear();
	unload_3d_terrain();
	ogre_textures_clear(FALSE);

	terrain += diff;
	char path[1024];
	sprintf(path, "..\\..\\COMMON\\MAPS\\MAP%i\\TERRAIN", terrain);

	initialize_terrain_textures();
	load_3d_terrain(path);
#ifdef USE_TERRAIN_NEW_TEXTURES
	initialize_terrain_texture_scales(path);
	const char* name = terrain_name(terrain);
	const char* paths[] =
	{
		"..\\GRAPHICS\\TEXTURES\\GENERAL",
		"..\\GRAPHICS\\TEXTURES\\CAMO",
		"..\\GRAPHICS\\TEXTURES\\TERRAIN\\WATER",
	};
	const char* ext[] = { "BMP", "TGA" };

	typedef std::map<unsigned, std::string> Override;
	Override override;
	for (NewTextures::const_iterator itor(new_textures.begin()); itor != new_textures.end(); ++itor)
	{
		for (unsigned i = 0; i < ARRAY_LENGTH(paths); i++)
			for (unsigned j = 0; j < ARRAY_LENGTH(ext); j++)
			{
				char name[1024];
				sprintf(name, "%s\\%s.%s", paths[i], itor->first.c_str(), ext[j]);
				if (file_exist(name))
					override[itor->second] = name;
			}
		if (override[itor->second].empty())
			error("Failed to find texture file for '%s'", itor->first.c_str());
	}
	char textures_path[1024];
	sprintf(textures_path, "..\\GRAPHICS\\TEXTURES\\TERRAIN\\%s", name);
	for (unsigned j = 0; j < ARRAY_LENGTH(ext); j++)
	{
		char name[1024];
		sprintf(name, "%s\\*.%s", textures_path, ext[j]);
		int rc;
		long handle;
		struct _finddata_t fd;
		for (rc = handle = _findfirst(name, &fd); rc != -1; rc = _findnext(handle, &fd))
			if (!(fd.attrib & _A_SUBDIR))
			{
				strcpy(name, fd.name);
				*strrchr(name, '.') = '\0';
				strupr(name);
				int index = get_system_texture_index(name);
				if (index >= 0)
				{
					sprintf(name, "%s\\%s", textures_path, fd.name);
					override[index] = name;
				}
			}
		_findclose(handle);
	}
	for (Override::const_iterator itor(override.begin()); itor != override.end(); ++itor)
		ogre_textures_override(itor->first, itor->second.c_str());
#endif
	ogre_textures_commit(TRUE);
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

#ifdef USE_TERRAIN
#define POSITION { 0, 2000, 0 }
float F = sqrt(0.5f);
#define ORIENTATION { F, 0, -F, 0, 1, 0, F, 0, F }
#else
#define POSITION { 0, 0, 30 }
#define ORIENTATION { -1, 0, 0, 0, 1, 0, 0, 0, -1 }
#endif
float ared = 0.6f, agreen = 0.6f, ablue = 0.6f;
struct OgreEnvironment env = { POSITION, ORIENTATION, PI / 4.0f, 1.0f, 10000.0f, 0xFF999999, 5000.0f, 10000.0f, 0xFF2EC4DE, 0xFF2EC4DE };

void set_env(void)
{
	ared = bound(ared, 0.0f, 1.0f);
	agreen = bound(agreen, 0.0f, 1.0f);
	ablue = bound(ablue, 0.0f, 1.0f);
	env.ambient = 0xFF000000 | (((unsigned)(255 * ared)) << 0) | (((unsigned)(255 * agreen)) << 8) | (((unsigned)(255 * ablue)) << 16);
	ogre_environment(&env);
}

void OGREEE_CALL init(void)
{
	set_env();

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

#ifdef USE_PARTICLES
	ogre_particles_init();
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

#ifdef USE_PARTICLES
	ogre_particles_clear();
#endif
}

#ifdef USE_PARTICLES
struct Particle
{
	OgreParticle particle;
	float current;
	float duration;
	float repeat;
	float start_radius;
	float stop_radius;
	float start_alpha;
	float end_alpha;
	float roll_speed;
};
#define PARTICLES 20
Particle particles[PARTICLES];
#endif

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
		sprintf(buf, "R:%.1f G:%.1f B:%.1f ", ared, agreen, ablue);
#ifdef USE_OBJECTS_ONLY
		sprintf(buf + strlen(buf), "Scns: %04X %04X", objects[0], objects[1]);
#endif
#ifdef USE_TERRAIN
		sprintf(buf + strlen(buf), "MAP: %s (%i)", terrain_name(terrain), terrain);
#endif
		ogre_info(buf);
	}

#ifdef USE_PARTICLES
	for (unsigned i = 0; i < PARTICLES; i++)
	{
		Particle& p = particles[i];
		p.current += dtime;
		if (p.current >= p.duration)
		{
			p.current = 0;
			p.duration = rand() * 10.0f / RAND_MAX + 2.0f;
			p.repeat = (float)(rand() % 5 + 1);
			p.start_radius = rand() * 20.0f / RAND_MAX + 1.0f;
			p.stop_radius = rand() * 20.0f / RAND_MAX + 1.0f;
			p.start_alpha = rand() * 1.0f / RAND_MAX;
			p.end_alpha = rand() * 1.0f / RAND_MAX;
			p.roll_speed = rand() * 20.0f / RAND_MAX - 10.0f;
			p.particle.position = env.position;
			p.particle.position.x += rand() * 200.0f / RAND_MAX - 100.0f;
			p.particle.position.y += rand() * 200.0f / RAND_MAX - 100.0f;
			p.particle.position.z += rand() * 200.0f / RAND_MAX - 100.0f;
			p.particle.texture_animation = rand() % eet.GetAnimations();
			p.particle.additive = rand() & 1;
		}
		const float factor = fmod(p.current * p.repeat / p.duration, 1.0f);
		p.particle.frame = (unsigned)(eet.GetAnimationSize(p.particle.texture_animation) * factor);
		p.particle.colour = ((unsigned)(255u * (p.start_alpha + (p.end_alpha - p.start_alpha) * factor)) << 24) | 0xFFFFFFu;
		p.particle.roll = p.roll_speed * factor;
		p.particle.radius = p.start_radius + (p.stop_radius - p.start_radius) * factor;
		ogre_particles_draw(&p.particle, 0, 0);
	}
	ogre_particles_commit();
#endif
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
	case DIK_U:
		ared += sign * 0.05f;
		agreen += sign * 0.05f;
		ablue += sign * 0.05f;
		set_env();
		break;
	case DIK_I:
		ared += sign * 0.05f;
		set_env();
		break;
	case DIK_O:
		agreen += sign * 0.05f;
		set_env();
		break;
	case DIK_P:
		ablue += sign * 0.05f;
		set_env();
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
			struct OgreVector3 p = { rand() * 1024.0f * terrain_3d_sector_x_max / RAND_MAX, 2000, rand() * 1024.0f * terrain_3d_sector_z_max / RAND_MAX };
			env.position = p;
			ogre_environment(&env);
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
