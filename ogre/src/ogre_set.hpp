extern Ogre::SceneManager* ogre_scene_manager;
extern Ogre::Camera* ogre_camera;
extern std::string ogre_resource_group;

unsigned ogre_index(void);
void ogre_matrix_mirror(Ogre::Matrix3& m);
void ogre_log(const char* function, const char* format, ...);

inline Ogre::Quaternion ogre_orientation(float heading, float pitch, float roll)
{
	heading *= -0.5f;
	pitch *= -0.5f;
	roll *= 0.5f;
	const float ch = cos(heading), sh = sin(heading);
	const float cp = cos(pitch), sp = sin(pitch);
	const float cr = cos(roll), sr = sin(roll);
	const float w = ch * cp, x = ch * sp, y = sh * cp, z = sh * sp;
	return Ogre::Quaternion(w * cr - z * sr, x * cr + y * sr, y * cr + x * sr, w * sr + z * cr);
}
