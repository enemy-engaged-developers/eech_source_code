#ifndef OGRE_EE_H
#define OGRE_EE_H

#ifdef OGREEE_EXPORTS
#define OGREEE_API __declspec(dllexport)
#else
#define OGREEE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

struct OBJECT_3D;
struct OBJECT_3D_SCENE_DATABASE_ENTRY;
typedef float matrix3x3[3][3];
struct VEC3D;

OGREEE_API void ogre_set(const char* resource_group, void* scene_manager, void* camera);

OGREEE_API void ogre_textures_define(unsigned index, unsigned number_of_mipmaps, int mip, unsigned width, unsigned height, unsigned bpp, void* texture_image_data);
OGREEE_API void ogre_textures_clear(void);

struct OgreObjectsInit
{
	unsigned number_of_objects;
	const struct OBJECT_3D* objects;
	unsigned (*get_animation_size)(unsigned index);
	unsigned (*get_animation_texture)(unsigned index, unsigned frame);
};

OGREEE_API void ogre_objects_init(struct OgreObjectsInit* init);
OGREEE_API void ogre_objects_clear(void);

struct OgreNode;

OGREEE_API void ogre_node_get_position(struct OgreNode* node, struct VEC3D* position);
OGREEE_API void ogre_node_set_position(struct OgreNode* node, struct VEC3D* position);
OGREEE_API void ogre_node_get_orientation(struct OgreNode* node, matrix3x3 orientation);
OGREEE_API void ogre_node_set_orientation(struct OgreNode* node, matrix3x3 orientation);
OGREEE_API void ogre_node_set_visible(struct OgreNode* node, int visible);

struct OgreGameObjectScene
{
	void* internal;
	struct OgreNode* root;
	unsigned number_of_nodes;
	struct OgreNode** nodes;
};

struct OgreSubObjectsSearch
{
	unsigned number_of_subobjects;
	const unsigned* subobjects;
};

OGREEE_API void ogre_scenes_init(int number_of_scenes, const struct OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database);
OGREEE_API void ogre_scenes_clear(void);
OGREEE_API void ogre_scene_init(struct OgreGameObjectScene* scene);
OGREEE_API void ogre_scene_create(int scene_number, struct OgreGameObjectScene* scene);
OGREEE_API void ogre_scene_destroy(struct OgreGameObjectScene* scene);
OGREEE_API struct OgreSubObjectsSearch ogre_scene_find(struct OgreGameObjectScene* scene, unsigned sub_object_id);
OGREEE_API struct OgreSubObjectsSearch ogre_scene_find2(struct OgreGameObjectScene* scene, unsigned sub_object_id, unsigned parent);
OGREEE_API float ogre_scene_subobject_keyframe_length(struct OgreGameObjectScene* scene, unsigned subobject);
OGREEE_API void ogre_scene_subobject_keyframe(struct OgreGameObjectScene* scene, unsigned subobject, float time);
OGREEE_API void ogre_scene_animation(struct OgreGameObjectScene* scene, unsigned animation, unsigned frame);

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
	unsigned map_height, map_width;
	float xz_scale, map_scaled_height_difference, map_minimum_height, map_maximum_height;
	float (*get_tree_scale)(struct TERRAIN_3D_TREE_DATA*);
	struct TERRAIN_TYPE_INFO* type_information;
	struct TERRAIN_3D_SECTOR** sectors;
	struct TERRAIN_3D_TREE_SECTOR** tree_sectors;
};

OGREEE_API void ogre_terrain_init(struct OgreTerrainInit* init);
OGREEE_API void ogre_terrain_clear(void);
OGREEE_API void ogre_terrain_update(void);
OGREEE_API void ogre_terrain_tree(const struct OBJECT_3D* o);
OGREEE_API void ogre_terrain_tree_clear(void);

struct OgreRun
{
	void (*init)(void);
	void (*deinit)(void);
	void (*frame)(float dtime);
};

OGREEE_API void ogre_run(struct OgreRun* run);

#ifdef __cplusplus
}
#endif

#endif
