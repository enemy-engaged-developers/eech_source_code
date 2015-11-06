extern Ogre::SceneManager* ogre_scene_manager;
extern Ogre::Camera* ogre_camera;
extern std::string ogre_resource_group;

unsigned ogre_index(void);
void ogre_matrix_mirror(Ogre::Matrix3& m);
void ogre_log(const char* function, const char* format, ...);
