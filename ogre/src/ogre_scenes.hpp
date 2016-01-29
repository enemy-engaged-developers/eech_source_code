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
typedef std::vector<SceneDatabaseElement> SceneDatabaseElements;

// Static scene
struct SceneDatabase
{
	SceneDatabaseElements elements;
	AllSubObjects sub_objects;
	ParentSubObjects parent_sub_objects;
	AnimationScene animation;
};


// Dynamic scene - a representation of a game object
typedef std::map<unsigned, unsigned> SceneAnimation;
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
typedef std::vector<std::pair<unsigned, unsigned> > SceneDrawAnimation;
typedef std::vector<struct OgreGameObjectSceneElement> SceneDrawElements;

struct SceneDraw
{
	const SceneDatabase* database;
	SceneDrawAnimation animation;
	Ogre::Vector3 position;
	Ogre::Quaternion orientation;
	Ogre::Vector3 scale;
	SceneDrawElements elements;
};
typedef std::deque<SceneDraw> SceneDraws;


// Drawn scene information
typedef std::pair<Ogre::SceneNode*, Ogre::Entity*> SceneNode;
typedef std::vector<SceneNode> SceneNodes;

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
