void ogre_textures_define(unsigned index, int number_of_mipmaps, int mip, int width, int height, int bpp, void* texture_image_data);
void ogre_textures_clear(void);

void ogre_objects_init(unsigned number_of_objects, const OBJECT_3D* objects);
void ogre_objects_clear(void);

#include "ogre_animation.hpp"
#include "ogre_scenes.hpp"

void ogre_scenes_init(int number_of_scenes, const OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database, Ogre::SceneManager* sman);
void ogre_scenes_clear(void);
void ogre_scene_create(int scene_number, GameObjectScene& scene, Ogre::SceneNode* root, Ogre::SceneManager* mgr);
const SubObjects& ogre_scene_find(GameObjectScene& scene, unsigned sub_object_id);
const SubObjects& ogre_scene_find2(GameObjectScene& scene, unsigned sub_object_id, unsigned parent);
void ogre_scene_animation(GameObjectScene& scene, unsigned animation, unsigned frame);

void ogre_terrain_init(Ogre::Camera* camera, Ogre::SceneManager* mgr);
void ogre_terrain_clear(void);
void ogre_terrain_update(void);
void ogre_terrain_tree(const OBJECT_3D& o);
void ogre_terrain_tree_clear(void);
