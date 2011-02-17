// Offsets (in both SceneDatabaseElements and SceneNodes) for objects with a specific sub_object_id
typedef std::vector<unsigned> SubObjects;
// All sub_object_id listed
typedef std::map<unsigned, SubObjects> AllSubObjects;

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
	NodeAnimationTrack* track;
	// Initial position
	Quaternion orientation;
	Vector3 position;
	Vector3 scale;
};
typedef std::vector<SceneDatabaseElement> SceneDatabaseElements;

// Static scene
struct SceneDatabase
{
	SceneDatabaseElements elements;
	AllSubObjects sub_objects;
};


typedef std::vector<SceneNode*> SceneNodes;

// Dynamic scene - a representation of a game object
struct GameObjectScene
{
	const SceneDatabase* database;

	SceneNodes nodes;
};
