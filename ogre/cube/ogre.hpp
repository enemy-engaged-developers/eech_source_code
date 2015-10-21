void ogre_set(const char* resource_group, Ogre::SceneManager* scene_manager, Ogre::Camera* camera);

void ogre_textures_define(unsigned index, unsigned number_of_mipmaps, int mip, unsigned width, unsigned height, unsigned bpp, void* texture_image_data);
void ogre_textures_clear(void);

void ogre_objects_init(unsigned number_of_objects, const struct OBJECT_3D* objects);
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

void ogre_terrain_init();
void ogre_terrain_clear(void);
void ogre_terrain_update(void);
void ogre_terrain_tree(const struct OBJECT_3D* o);
void ogre_terrain_tree_clear(void);
