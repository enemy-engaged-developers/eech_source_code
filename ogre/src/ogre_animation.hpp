struct AnimationRef
{
	AnimationRef(unsigned submesh, unsigned material_index)
		: submesh(submesh), material_index(material_index)
	{
	}

	unsigned submesh;
	unsigned material_index;
};
typedef std::vector<AnimationRef> AnimationRefs;
struct AnimationInfo
{
	unsigned limit;
	AnimationRefs refs;
};
typedef std::map<unsigned, AnimationInfo> AnimationMesh;

struct SceneAnimationRef : public AnimationRef
{
	SceneAnimationRef(unsigned subobject, const AnimationRef& ar)
		: AnimationRef(ar), subobject(subobject)
	{
	}

	unsigned subobject;
};
typedef std::vector<SceneAnimationRef> SceneAnimationRefs;
struct SceneAnimationInfo
{
	unsigned limit;
	SceneAnimationRefs refs;
};
typedef std::map<unsigned, SceneAnimationInfo> AnimationScene;
