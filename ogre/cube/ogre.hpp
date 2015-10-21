#ifndef OGRE_EE_H
#define OGRE_EE_H

#ifdef __cplusplus
extern "C"
{
#endif

struct OBJECT_3D;
struct OBJECT_3D_SCENE_DATABASE_ENTRY;
typedef float matrix3x3[3][3];

void ogre_set(const char* resource_group, void* scene_manager, void* camera);

void ogre_textures_define(unsigned index, unsigned number_of_mipmaps, int mip, unsigned width, unsigned height, unsigned bpp, void* texture_image_data);
void ogre_textures_clear(void);

struct OgreObjectsInit
{
	unsigned number_of_objects;
	const struct OBJECT_3D* objects;
	unsigned (*get_animation_size)(unsigned index);
	unsigned (*get_animation_texture)(unsigned index, unsigned frame);
};

void ogre_objects_init(struct OgreObjectsInit* init);
void ogre_objects_clear(void);

struct OgreNode;

void ogre_node_get_orientation(struct OgreNode* node, matrix3x3 orientation);
void ogre_node_set_orientation(struct OgreNode* node, matrix3x3 orientation);
void ogre_node_set_visible(struct OgreNode* node, int visible);

struct OgreGameObjectScene
{
	void* internal;
	unsigned number_of_nodes;
	struct OgreNode** nodes;
};

struct OgreSubObjectsSearch
{
	unsigned number_of_subobjects;
	const unsigned* subobjects;
};

void ogre_scenes_init(int number_of_scenes, const struct OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database);
void ogre_scenes_clear(void);
void ogre_scene_init(struct OgreGameObjectScene* scene);
void ogre_scene_create(int scene_number, struct OgreGameObjectScene* scene, Ogre::SceneNode* root);
void ogre_scene_destroy(struct OgreGameObjectScene* scene);
struct OgreSubObjectsSearch ogre_scene_find(struct OgreGameObjectScene* scene, unsigned sub_object_id);
struct OgreSubObjectsSearch ogre_scene_find2(struct OgreGameObjectScene* scene, unsigned sub_object_id, unsigned parent);
float ogre_scene_subobject_keyframe_length(struct OgreGameObjectScene* scene, unsigned subobject);
void ogre_scene_subobject_keyframe(struct OgreGameObjectScene* scene, unsigned subobject, float time);
void ogre_scene_animation(struct OgreGameObjectScene* scene, unsigned animation, unsigned frame);

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

void ogre_terrain_init(struct OgreTerrainInit* init);
void ogre_terrain_clear(void);
void ogre_terrain_update(void);
void ogre_terrain_tree(const struct OBJECT_3D* o);
void ogre_terrain_tree_clear(void);

#ifdef __cplusplus
}
#endif

#endif
