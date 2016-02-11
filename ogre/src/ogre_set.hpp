extern Ogre::SceneManager* ogre_scene_manager;
extern Ogre::Camera* ogre_camera;
extern Ogre::String ogre_resource_group;

extern unsigned long ogre_thread_id, user_thread_id;

void ogre_set(const char* resource_group, Ogre::SceneManager* scene_manager, Ogre::Camera* camera);
unsigned ogre_index(void);
void ogre_log(const char* function, const char* format, ...);
void ogre_log_(const char* function, const char* format, ...);

inline Ogre::ColourValue ogre_colour(unsigned colour)
{
	return Ogre::ColourValue(((colour >> 16) & 0xFF) / 255.0f, ((colour >> 8) & 0xFF) / 255.0f, ((colour >> 0) & 0xFF) / 255.0f, ((colour >> 24) & 0xFF) / 255.0f);
}

inline Ogre::Vector3 ogre_position(const float* f)
{
	return Ogre::Vector3(f[0], f[1], -f[2]);
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

inline Ogre::Quaternion ogre_orientation(const float* m)
{
	return ogre_orientation(atan2(m[6], m[8]), -asin(m[7]), atan2(-m[1], m[4]));
}

inline Ogre::Vector3 ogre_scale(const float* f)
{
	return Ogre::Vector3(f);
}
