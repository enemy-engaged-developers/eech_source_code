typedef Ogre::vector<unsigned>::type TextureAnimation;

struct AnimationRef
{
	AnimationRef(unsigned submesh, unsigned material_index)
		: submesh(submesh), material_index(material_index)
	{
	}

	unsigned submesh;
	unsigned material_index;
};
typedef Ogre::vector<AnimationRef>::type AnimationRefs;
struct AnimationInfo
{
	unsigned limit;
	AnimationRefs refs;
};
typedef Ogre::map<unsigned, AnimationInfo>::type AnimationMesh;

struct SceneAnimationRef : public AnimationRef
{
	SceneAnimationRef(unsigned subobject, const AnimationRef& ar)
		: AnimationRef(ar), subobject(subobject)
	{
	}

	unsigned subobject;
};
typedef Ogre::vector<SceneAnimationRef>::type SceneAnimationRefs;
struct SceneAnimationInfo
{
	unsigned limit;
	SceneAnimationRefs refs;
};
typedef Ogre::map<unsigned, SceneAnimationInfo>::type AnimationScene;
