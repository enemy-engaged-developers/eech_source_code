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
typedef std::map<unsigned, AnimationRefs> AnimationMesh;

struct SceneAnimationRef : public AnimationRef
{
	SceneAnimationRef(unsigned subobject, const AnimationRef& ar)
		: AnimationRef(ar), subobject(subobject)
	{
	}

	unsigned subobject;
};
typedef std::vector<SceneAnimationRef> SceneAnimationRefs;
typedef std::map<unsigned, SceneAnimationRefs> AnimationScene;
