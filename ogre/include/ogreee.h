#ifndef OGRE_EE_H
#define OGRE_EE_H

#ifdef OGREEE_EXPORTS
#define OGREEE_API __declspec(dllexport)
#else
#define OGREEE_API __declspec(dllimport)
#endif
#define OGREEE_CALL __stdcall

#ifdef __cplusplus
extern "C"
{
#endif

struct OBJECT_3D;
struct OBJECT_3D_SCENE_DATABASE_ENTRY;
typedef float matrix3x3[3][3];
struct VEC3D;

OGREEE_API void OGREEE_CALL ogre_set(const char* resource_group, void* scene_manager, void* camera);
OGREEE_API void OGREEE_CALL ogre_set_viewpoint(struct VEC3D* position, matrix3x3 orientation);

OGREEE_API void OGREEE_CALL ogre_textures_define(unsigned index, unsigned number_of_mipmaps, int mip, unsigned width, unsigned height, unsigned bpp, void* texture_image_data);
OGREEE_API void OGREEE_CALL ogre_textures_clear(void);
OGREEE_API void OGREEE_CALL ogre_textures_override(unsigned index, const char* file);
OGREEE_API void OGREEE_CALL ogre_textures_restore(void);

struct OgreObjectsInit
{
	unsigned number_of_objects;
	const struct OBJECT_3D* objects;
	unsigned (OGREEE_CALL *get_animation_size)(unsigned index);
	unsigned (OGREEE_CALL *get_animation_texture)(unsigned index, unsigned frame);
};

OGREEE_API void OGREEE_CALL ogre_objects_init(struct OgreObjectsInit* init);
OGREEE_API void OGREEE_CALL ogre_objects_clear(void);

struct OgreVector3
{
	float x, y, z;
};

struct OgreGameObjectSceneElement
{
	struct OgreVector3 relative_position;
	float relative_heading, relative_pitch, relative_roll;
	struct OgreVector3 relative_scale;
	float animation;
	union
	{
		unsigned flags;
		struct
		{
			unsigned visible_object:1;
		};
	};
};

struct OgreGameObjectScene
{
	void* internal;
	struct OgreVector3 position;
	matrix3x3 attitude;
	unsigned number_of_elements;
	struct OgreGameObjectSceneElement* elements;
};

struct OgreSubObjectsSearch
{
	unsigned number_of_subobjects;
	const unsigned* subobjects;
};

OGREEE_API void OGREEE_CALL ogre_scenes_init(int number_of_scenes, const struct OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database);
OGREEE_API void OGREEE_CALL ogre_scenes_clear(void);
OGREEE_API void OGREEE_CALL ogre_scene_init(struct OgreGameObjectScene* scene);
OGREEE_API void OGREEE_CALL ogre_scene_create(struct OgreGameObjectScene* scene, unsigned scene_number);
OGREEE_API void OGREEE_CALL ogre_scene_destroy(struct OgreGameObjectScene* scene);
OGREEE_API unsigned OGREEE_CALL ogre_scene_get_object(struct OgreGameObjectScene* scene, unsigned subobject);
OGREEE_API unsigned OGREEE_CALL ogre_scene_get_parent(struct OgreGameObjectScene* scene, unsigned subobject);
OGREEE_API int OGREEE_CALL ogre_scene_find(struct OgreGameObjectScene* scene, unsigned sub_object_id, struct OgreSubObjectsSearch* search);
OGREEE_API int OGREEE_CALL ogre_scene_find2(struct OgreGameObjectScene* scene, unsigned sub_object_id, unsigned parent, struct OgreSubObjectsSearch* search);
OGREEE_API float OGREEE_CALL ogre_scene_subobject_keyframe_length(struct OgreGameObjectScene* scene, unsigned subobject);
OGREEE_API void OGREEE_CALL ogre_scene_animation(struct OgreGameObjectScene* scene, unsigned animation, unsigned frame);
OGREEE_API void OGREEE_CALL ogre_scene_animation_advance(struct OgreGameObjectScene* scene, unsigned animation);

typedef void (*OgreTerrainFunction)(int);

#define terrain_unclipped ((OgreTerrainFunction)1)
#define terrain_texture_x_unclipped ((OgreTerrainFunction)2)
#define terrain_texture_z_unclipped ((OgreTerrainFunction)3)
#define terrain_colour_unclipped ((OgreTerrainFunction)4)
#define terrain_texture_x_colour_unclipped ((OgreTerrainFunction)5)
#define terrain_texture_z_colour_unclipped ((OgreTerrainFunction)6)
#define terrain_twopass_unclipped ((OgreTerrainFunction)7)
#define terrain_twopass_texture_x_unclipped ((OgreTerrainFunction)8)
#define terrain_twopass_texture_z_unclipped ((OgreTerrainFunction)9)
#define terrain_twopass_colour_unclipped ((OgreTerrainFunction)10)
#define terrain_twopass_texture_x_colour_unclipped ((OgreTerrainFunction)11)
#define terrain_twopass_texture_z_colour_unclipped ((OgreTerrainFunction)12)
#define terrain_clipped ((OgreTerrainFunction)13)
#define terrain_texture_x_clipped ((OgreTerrainFunction)14)
#define terrain_texture_z_clipped ((OgreTerrainFunction)15)
#define terrain_colour_clipped ((OgreTerrainFunction)16)
#define terrain_texture_x_colour_clipped ((OgreTerrainFunction)17)
#define terrain_texture_z_colour_clipped ((OgreTerrainFunction)18)
#define terrain_twopass_clipped ((OgreTerrainFunction)19)
#define terrain_twopass_texture_x_clipped ((OgreTerrainFunction)20)
#define terrain_twopass_texture_z_clipped ((OgreTerrainFunction)21)
#define terrain_twopass_colour_clipped ((OgreTerrainFunction)22)
#define terrain_twopass_texture_x_colour_clipped ((OgreTerrainFunction)23)
#define terrain_twopass_texture_z_colour_clipped ((OgreTerrainFunction)24)

struct OgreTerrainInit
{
	unsigned sector_z_max, sector_x_max;
	float map_scaled_height_difference, map_minimum_height, map_maximum_height;
	float (OGREEE_CALL *get_tree_scale)(struct TERRAIN_3D_TREE_DATA*);
	struct TERRAIN_TYPE_INFO* type_information;
	struct TERRAIN_3D_SECTOR** sectors;
	struct TERRAIN_3D_TREE_SECTOR** tree_sectors;
};

OGREEE_API void OGREEE_CALL ogre_terrain_init(struct OgreTerrainInit* init);
OGREEE_API void OGREEE_CALL ogre_terrain_clear(void);
OGREEE_API void OGREEE_CALL ogre_terrain_tree(const struct OBJECT_3D* o);
OGREEE_API void OGREEE_CALL ogre_terrain_tree_clear(void);
OGREEE_API void OGREEE_CALL ogre_terrain_user_scene(struct OgreGameObjectScene* scene);

struct OgreRun
{
	void (OGREEE_CALL *init)(void);
	void (OGREEE_CALL *deinit)(void);
	void (OGREEE_CALL *frame)(float dtime);
};

OGREEE_API void OGREEE_CALL ogre_run(struct OgreRun* run);
OGREEE_API void OGREEE_CALL ogre_update(void);

#ifdef __cplusplus
}
#endif

#endif