// Offsets (in both SceneDatabaseElements and SceneNodes) for objects with a specific sub_object_id
typedef std::vector<unsigned> SubObjects;
// All sub_object_id listed
typedef std::map<unsigned, SubObjects> AllSubObjects;
// All sub_object_id and parent listed
typedef std::map<std::pair<unsigned, unsigned>, SubObjects> ParentSubObjects;

// Object as a part of the scene (SceneDatabase)
struct SceneDatabaseElement
{
	SceneDatabaseElement()
	{
	}

	SceneDatabaseElement(const Ogre::String& object_)
		: parent(no_parent), object(object_), track(0)
	{
	}

	// Parent index (in SceneDatabaseElements and SceneNodes)
	unsigned parent;
	static const unsigned no_parent = ~0u;
	// Corresponding geometry object or empty
	Ogre::String object;
	// Linked animation
	Ogre::NodeAnimationTrack* track;
	// Initial position
	struct OgreGameObjectSceneElement initial;
};
typedef std::vector<SceneDatabaseElement> SceneDatabaseElements;

// Static scene
struct SceneDatabase
{
	SceneDatabaseElements elements;
	AllSubObjects sub_objects;
	ParentSubObjects parent_sub_objects;
	AnimationScene animation;
};


typedef std::pair<Ogre::SceneNode*, Ogre::Entity*> SceneNode;
typedef std::vector<SceneNode> SceneNodes;

typedef std::map<unsigned, unsigned> SceneAnimation;

// Dynamic scene - a representation of a game object
struct GameObjectScene
{
	GameObjectScene(const SceneDatabase& database)
		: database(database), root(0)
	{
	}
	~GameObjectScene()
	{
		assert(!root);
	}

	const SceneDatabase& database;

	size_t position;

	SceneAnimation animation;

	Ogre::SceneNode* root;
	SceneNodes nodes;
};

void ogre_scenes_update(void);
void ogre_scene_place(struct OgreGameObjectScene* scene);
