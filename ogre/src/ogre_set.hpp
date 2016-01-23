extern Ogre::SceneManager* ogre_scene_manager;
extern Ogre::Camera* ogre_camera;
extern std::string ogre_resource_group;

unsigned ogre_index(void);
void ogre_log(const char* function, const char* format, ...);

inline Ogre::Vector3 ogre_position(const struct OgreVector3& v)
{
	return Ogre::Vector3(v.x, v.y, -v.z);
}

inline Ogre::Quaternion ogre_orientation(float heading, float pitch, float roll)
{
	heading *= -0.5f;
	pitch *= -0.5f;
	roll *= 0.5f;
	const float ch = cos(heading), sh = sin(heading);
	const float cp = cos(pitch), sp = sin(pitch);
	const float cr = cos(roll), sr = sin(roll);
	const float w = ch * cp, x = ch * sp, y = sh * cp, z = -sh * sp;
	return Ogre::Quaternion(w * cr - z * sr, x * cr + y * sr, y * cr - x * sr, w * sr + z * cr);
}

inline Ogre::Quaternion ogre_orientation(matrix3x3 m)
{
	return ogre_orientation(atan2(m[2][0], m[2][2]), asin(m[2][1]), atan2(-m[0][1], m[1][1]));
}

inline Ogre::Vector3 ogre_scale(const struct OgreVector3& v)
{
	return Ogre::Vector3(v.x, v.y, v.z);
}
