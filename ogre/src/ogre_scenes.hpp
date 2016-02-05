// Offsets (in both SceneDatabaseElements and SceneNodes) for objects with a specific sub_object_id
typedef Ogre::vector<unsigned>::type SubObjects;
// All sub_object_id listed
typedef Ogre::map<unsigned, SubObjects>::type AllSubObjects;
// All sub_object_id and parent listed
typedef Ogre::map<std::pair<unsigned, unsigned>, SubObjects>::type ParentSubObjects;

// Object as a part of the scene (SceneDatabase)
struct SceneDatabaseElement
{
	SceneDatabaseElement()
	{
	}

	SceneDatabaseElement(const Ogre::String& object)
		: parent(no_parent), object(object), track(0), track_length(0.0f)
	{
	}

	// Parent index (in SceneDatabaseElements and SceneNodes)
	unsigned parent;
	static const unsigned no_parent = ~0u;
	// Corresponding geometry object or empty
	Ogre::String object;
	// Linked animation
	Ogre::NodeAnimationTrack* track;
	float track_length;
	// Initial position
	struct OgreGameObjectSceneElement initial;
};
typedef Ogre::vector<SceneDatabaseElement>::type SceneDatabaseElements;

// Static scene
struct SceneDatabase
{
	SceneDatabaseElements elements;
	AllSubObjects sub_objects;
	ParentSubObjects parent_sub_objects;
	AnimationScene animation;
};


// Dynamic scene - a representation of a game object
typedef Ogre::map<unsigned, unsigned>::type SceneAnimation;
struct GameObjectScene
{
	GameObjectScene(const SceneDatabase& database)
		: database(database)
	{
	}

	const SceneDatabase& database;
	SceneAnimation animation;
};

// Scene draw information
typedef Ogre::vector<std::pair<unsigned, unsigned> >::type SceneDrawAnimation;
typedef Ogre::vector<struct OgreGameObjectSceneElement>::type SceneDrawElements;

struct SceneDraw
{
	const SceneDatabase* database;
	SceneDrawAnimation animation;
	Ogre::Vector3 position;
	Ogre::Quaternion orientation;
	Ogre::Vector3 scale;
	SceneDrawElements elements;
};
typedef Ogre::deque<SceneDraw>::type SceneDraws;


// Drawn scene information
typedef std::pair<Ogre::SceneNode*, Ogre::Entity*> SceneNode;
typedef Ogre::vector<SceneNode>::type SceneNodes;

struct DrawnScene
{
	DrawnScene(void)
		: root(0), database(0)
	{
	}
	~DrawnScene();

	Ogre::SceneNode* root;
	SceneNodes nodes;
	const SceneDatabase* database;
};

void ogre_scenes_frame(void);
void ogre_scene_place(const struct OgreGameObjectScene* scene, DrawnScene& ds);
