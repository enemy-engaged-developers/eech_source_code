#include "ogre_int.hpp"

#define NATIVE_TYPES
#define NO_LWSFILEEXPORTER
#define NO_LWSCAMERAEXPORT
#define MAX_NUMBER_OF_SUB_OBJECT_INDICES 512
static void error(...)
{
	abort();
}

struct Schem
{
	bool operator ==(const Schem&) const
	{
		return true;
	}
};

#include "lws_exp.cpp"

namespace
{
	typedef std::vector<SceneDatabase> AllScenes;

	AllScenes scenes;

	std::string animation_mesh;


	// Adapter for scenes loading. Fills scenes.
	// TODO: Add support of Special objects, LODs, Lights and (maybe) Cameras
	class SceneComposer : public LwsExporter
	{
	public:
		SceneComposer(SceneDatabase& scene)
			: scene(scene)
		{
		}

		void Begin(int)
		{
		}

		void End(void)
		{
		}

		void Object(int index, int number, int sub_object_index, int special = 0, const char* null_special = NULL)
		{
			if (special)
			{
				skip_object = true;
				return;
			}

			skip_object = false;

			unsigned offset = scene.elements.size();
			ito[index] = offset;
			scene.elements.push_back(SceneDatabaseElement(!number ? Ogre::String() : ObjectName(number)));
			if (sub_object_index > 0)
				scene.sub_objects[sub_object_index].push_back(offset);
			ogre_objects_add_animation(number, scene.animation, offset);
		}

		void Parent(int index)
		{
			if (skip_object)
				return;

			scene.elements.back().parent = ito[index];
		}

		void KeyFrames(const char* type, int visibility, int color, const Schem& schem, int number_of_keyframes, const OBJECT_3D_SUB_OBJECT_KEYFRAME* keyframes)
		{
			struct T
			{
				static Ogre::Quaternion Orientation(const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame)
				{
					return ogre_orientation(frame->heading, frame->pitch, frame->roll);
				}
				static Ogre::Vector3 Position(const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame)
				{
					return Ogre::Vector3(frame->x, frame->y, -frame->z);
				}
				static Ogre::Vector3 Scale(const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame)
				{
					return Ogre::Vector3(frame->scale_x, frame->scale_y, frame->scale_z);
				}
			};

			if (!strcmp(type, "Object"))
			{
				if (skip_object)
					return;

				SceneDatabaseElement& el = scene.elements.back();
				if (number_of_keyframes > 1)
				{
					Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().getByName(animation_mesh, ogre_resource_group);
					Ogre::Animation* anim = mesh->createAnimation(KeyframeAnimationName(ogre_index()), keyframes[number_of_keyframes - 1].index / 30.0f);
					Ogre::NodeAnimationTrack* track = anim->createNodeTrack(0);
					for (int i = 0; i < number_of_keyframes; i++)
					{
						const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame = &keyframes[i];
						Ogre::TransformKeyFrame* key = track->createNodeKeyFrame(keyframes[i].index / 30.0f);
						key->setTranslate(T::Position(frame));
						key->setRotation(T::Orientation(frame));
						key->setScale(T::Scale(frame));
					}
					el.track = track;
				}
				struct OgreGameObjectSceneElement& se = el.initial;
				se.relative_position.x = keyframes->x;
				se.relative_position.y = keyframes->y;
				se.relative_position.z = keyframes->z;
				se.relative_heading = keyframes->heading;
				se.relative_pitch = keyframes->pitch;
				se.relative_roll = keyframes->roll;
				se.relative_scale.x = keyframes->scale_x;
				se.relative_scale.y = keyframes->scale_y;
				se.relative_scale.z = keyframes->scale_z;
				se.animation = 0.0f;
				se.flags = 0;
				se.visible_object = true;
			}

			if (!strcmp(type, "Light"))
			{
			}
		}

		void Limits(const char* l, double min, double max)
		{
		}

		void LODs(int number_of_approximation_info, const OBJECT_3D_APPROXIMATION_INFO* approximation_info)
		{
		}

		void Collision(void)
		{
		}

		void Dissolve(int number_of_object_dissolve_keyframes, const OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME* object_dissolve_keyframes)
		{
		}

		void Ambient(void)
		{
		}

		void Light(int index)
		{
			skip_object = true;
		}

		void LightAttrs(const REAL_COLOUR* colour)
		{
		}

	private:
		SceneDatabase& scene;

		typedef std::map<int, unsigned> IndexToOffset;
		IndexToOffset ito;
		bool skip_object;
	};

	int search_convert(const SubObjects* so, struct OgreSubObjectsSearch* search)
	{
		if (so && !so->empty())
		{
			search->number_of_subobjects = so->size();
			search->subobjects = &(*so)[0];
			return true;
		}
		return false;
	}

	SceneDatabase empty_database;

	void place_node(Ogre::SceneNode* node, const SceneDatabaseElement& sde, const struct OgreGameObjectSceneElement& p)
	{
		if (!p.visible_object)
		{
			node->setVisible(false, true);
			return;
		}
		node->setVisible(true, false);
		if (sde.track)
		{
			node->resetToInitialState();
			sde.track->applyToNode(node, p.animation);
		}
		else
		{
			node->setPosition(ogre_position(p.relative_position));
			node->setOrientation(ogre_orientation(p.relative_heading, p.relative_pitch, p.relative_roll));
			node->setScale(ogre_scale(p.relative_scale));
		}
	}

	void destroy_node(Ogre::SceneNode* node)
	{
		assert(!node->numAttachedObjects());
		Ogre::SceneNode* parent = node->getParentSceneNode();
		if (parent)
			parent->removeChild(node);
		node->getCreator()->destroySceneNode(node);
	}

	void convert_scene(struct OgreGameObjectScene* scene, GameObjectScene& gos)
	{
		assert(!gos.root);
		gos.root = ogre_scene_manager->createSceneNode(GameSceneName(scene));
		gos.nodes.reserve(gos.database.elements.size());
		for (SceneDatabaseElements::const_iterator itor(gos.database.elements.begin()); itor != gos.database.elements.end(); ++itor)
		{
			Ogre::SceneNode* node = (itor->parent == SceneDatabaseElement::no_parent ? gos.root : gos.nodes[itor->parent].first)->createChildSceneNode();
			Ogre::Entity* ent = 0;
			if (!itor->object.empty())
			{
				ent = ogre_scene_manager->createEntity(itor->object);
				node->attachObject(ent);
			}
			gos.nodes.push_back(SceneNode(node, ent));
		}
	}

	void place_scene(struct OgreGameObjectScene* scene)
	{
		GameObjectScene& gos(*static_cast<GameObjectScene*>(scene->internal));
		gos.root->setPosition(ogre_position(scene->position));
		gos.root->setOrientation(ogre_orientation(scene->attitude));
		for (unsigned i = scene->number_of_elements; i--;)
			place_node(gos.nodes[i].first, gos.database.elements[i], scene->elements[i]);
		for (SceneAnimation::const_iterator itor(gos.animation.begin()); itor != gos.animation.end(); ++itor)
		{
			AnimationScene::const_iterator it = gos.database.animation.find(itor->first);
			assert(it != gos.database.animation.end());
			const SceneAnimationRefs& sars = it->second.refs;
			for (SceneAnimationRefs::const_iterator sar(sars.begin()); sar != sars.end(); ++sar)
			{
				Ogre::Entity* entity = gos.nodes[sar->subobject].second;
				assert(entity);
				Ogre::SubEntity* subentity = entity->getSubEntity(sar->submesh);
				assert(subentity);
				subentity->setMaterialName(MaterialAnimationName(sar->material_index, itor->second));
			}
		}
	}

	void destroy_scene(GameObjectScene& gos)
	{
		while (!gos.nodes.empty())
		{
			SceneNode& sn = gos.nodes.back();
			if (sn.second)
			{
				sn.first->detachObject(sn.second);
				ogre_scene_manager->destroyEntity(sn.second);
				destroy_node(sn.first);
			}
			gos.nodes.pop_back();
		}
		SceneNodes().swap(gos.nodes);
		if (gos.root)
		{
			destroy_node(gos.root);
			gos.root = 0;
		}
	}

	typedef std::deque<struct OgreGameObjectScene*> GameScenes;
	GameScenes game_scenes;
	typedef std::deque<size_t> FreeScenes;
	FreeScenes free_scenes;
}

// Convert the scenes into internal database
void OGREEE_CALL ogre_scenes_init(int number_of_scenes, const struct OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database)
{
	ogre_log(__FUNCTION__, "");

	LwsExport lwsexport;

	animation_mesh = ObjectName(-1);
	Ogre::MeshManager::getSingleton().createManual(animation_mesh, ogre_resource_group);

	scenes.resize(number_of_scenes + 1);

	for (int i = 1; i <= number_of_scenes; i++)
	{
		if (objects_3d_scene_database[i].succeeded)
		{
			SceneComposer composer(scenes[i]);
			lwsexport.ExportScene(&composer, &objects_3d_scene_database[i], false);
		}
	}
}

// Clear scenes information
void OGREEE_CALL ogre_scenes_clear(void)
{
	ogre_log(__FUNCTION__, "");

	assert(game_scenes.size() == free_scenes.size());
	FreeScenes().swap(free_scenes);
	GameScenes().swap(game_scenes);

	AllScenes().swap(scenes);
}

void ogre_scenes_update(void)
{
	unsigned total = 0;

	Ogre::Vector3 pos = ogre_camera->getPosition();

	for (GameScenes::iterator itor(game_scenes.begin()); itor != game_scenes.end(); ++itor)
	{
		if (!*itor)
			continue;
		struct OgreGameObjectScene* scene = *itor;
		GameObjectScene& gos = *static_cast<GameObjectScene*>(scene->internal);
		Ogre::Real d = (pos - ogre_position(scene->position)).squaredLength();
		if (d < SCENES_VISIBILITY_LOW * SCENES_VISIBILITY_LOW)
		{
			ogre_scene_place(scene);
			if (!gos.root->getParentSceneNode())
				ogre_scene_manager->getRootSceneNode()->addChild(gos.root);
			total++;
		}
		else
		{
			if (d < SCENES_VISIBILITY_HIGH * SCENES_VISIBILITY_HIGH)
			{
				if (gos.root)
				{
					Ogre::SceneNode* parent = gos.root->getParentSceneNode();
					if (parent)
						parent->removeChild(gos.root);
				}
			}
			else
				destroy_scene(gos);
		}
	}

	{
		static unsigned next;
		unsigned cur = GetTickCount();
		if (cur > next)
		{
			ogre_log(__FUNCTION__, "%u/%u", total, game_scenes.size() - free_scenes.size());
			next = cur + 1000;
		}
	}
}

void OGREEE_CALL ogre_scene_init(struct OgreGameObjectScene* scene)
{
	scene->internal = 0;
	memset(&scene->position, 0, sizeof(scene->position));
	memset(&scene->attitude, 0, sizeof(scene->attitude));
	scene->attitude[0][0] = 1.0f;
	scene->attitude[1][1] = 1.0f;
	scene->attitude[2][2] = 1.0f;
	scene->number_of_elements = 0;
	scene->elements = 0;
}

// Place the scene as a child of the supplied SceneNode
void OGREEE_CALL ogre_scene_create(struct OgreGameObjectScene* scene, unsigned scene_number)
{
	ogre_log(__FUNCTION__, "%p %04X total %u", scene, scene_number, game_scenes.size() - free_scenes.size());

	ogre_scene_init(scene);
	SceneDatabase& sd = scene_number < scenes.size() ? scenes[scene_number] : empty_database;
	std::auto_ptr<GameObjectScene> gos(new GameObjectScene(sd));
	scene->number_of_elements = sd.elements.size();
	scene->elements = scene->number_of_elements ? new struct OgreGameObjectSceneElement[scene->number_of_elements] : 0;
	for (unsigned i = 0; i < scene->number_of_elements; i++)
		scene->elements[i] = gos->database.elements[i].initial;

	if (!free_scenes.empty())
	{
		size_t position = free_scenes.back();
		free_scenes.pop_back();
		assert(!game_scenes[position]);
		gos->position = position;
		game_scenes[position] = scene;
	}
	else
	{
		gos->position = game_scenes.size();
		game_scenes.push_back(scene);
	}

	scene->internal = gos.release();
}

void OGREEE_CALL ogre_scene_destroy(struct OgreGameObjectScene* scene)
{
	ogre_log(__FUNCTION__, "%p total %u", scene, game_scenes.size() - free_scenes.size());

	if (scene->internal)
	{
		std::auto_ptr<GameObjectScene> gos(static_cast<GameObjectScene*>(scene->internal));
		game_scenes[gos->position] = 0;
		free_scenes.push_back(gos->position);
		destroy_scene(*gos);
	}
	if (scene->elements)
		delete [] scene->elements;
	ogre_scene_init(scene);
}

unsigned OGREEE_CALL ogre_scene_get_object(struct OgreGameObjectScene* scene, unsigned subobject)
{
	ogre_log(__FUNCTION__, "%p %u", scene, subobject);

	const SceneDatabase& database = static_cast<const GameObjectScene*>(scene->internal)->database;
	assert(subobject < database.elements.size());
	const Ogre::String& name = database.elements[subobject].object;
	//FIXME
	if (!name.empty())
		return strtol(name.c_str() + 7, 0, 16);
	return -1;
}

unsigned OGREEE_CALL ogre_scene_get_parent(struct OgreGameObjectScene* scene, unsigned subobject)
{
	//ogre_log(__FUNCTION__, "%p %u", scene, subobject);

	const SceneDatabase& database = static_cast<const GameObjectScene*>(scene->internal)->database;
	assert(subobject < database.elements.size());
	return database.elements[subobject].parent;
}

int OGREEE_CALL ogre_scene_find(struct OgreGameObjectScene* scene, unsigned sub_object_id, struct OgreSubObjectsSearch* search)
{
	//ogre_log(__FUNCTION__, "%p %u", scene, sub_object_id);

	const SceneDatabase& database = static_cast<GameObjectScene*>(scene->internal)->database;
	AllSubObjects::const_iterator i = database.sub_objects.find(sub_object_id);
	return search_convert(i != database.sub_objects.end() ? &i->second : 0, search);
}

int OGREEE_CALL ogre_scene_find2(struct OgreGameObjectScene* scene, unsigned sub_object_id, unsigned parent, struct OgreSubObjectsSearch* search)
{
	//ogre_log(__FUNCTION__, "%p %u", scene, sub_object_id);

	const SceneDatabase& database = static_cast<GameObjectScene*>(scene->internal)->database;
	ParentSubObjects::const_iterator i = database.parent_sub_objects.find(std::make_pair(sub_object_id, parent));
	if (i != database.parent_sub_objects.end())
		return search_convert(&i->second, search);
	SubObjects& pso = const_cast<ParentSubObjects&>(database.parent_sub_objects)[std::make_pair(sub_object_id, parent)];
	AllSubObjects::const_iterator j = database.sub_objects.find(sub_object_id);
	if (j != database.sub_objects.end())
	{
		const SubObjects& so = j->second;
		for (SubObjects::const_iterator k(so.begin()); k != so.end(); ++k)
			for (unsigned index = *k; index != SceneDatabaseElement::no_parent; index = database.elements[index].parent)
				if (index == parent)
				{
					pso.push_back(*k);
					break;
				}
	}
	return search_convert(&pso, search);
}

float OGREEE_CALL ogre_scene_subobject_keyframe_length(struct OgreGameObjectScene* scene, unsigned subobject)
{
	//ogre_log(__FUNCTION__, "%p %u", scene, subobject);

	GameObjectScene& gos = *static_cast<GameObjectScene*>(scene->internal);
	assert(subobject < gos.database.elements.size());
	Ogre::NodeAnimationTrack* track = gos.database.elements[subobject].track;
	float length = track ? track->getParent()->getLength() : 0.0f;
	return length;
}

void OGREEE_CALL ogre_scene_animation(struct OgreGameObjectScene* scene, unsigned animation, unsigned frame)
{
	//ogre_log(__FUNCTION__, "%p %u %u", scene, animation, frame);

	GameObjectScene& gos = *static_cast<GameObjectScene*>(scene->internal);
	AnimationScene::const_iterator it = gos.database.animation.find(animation);
	if (it == gos.database.animation.end())
		return;
	gos.animation[animation] = frame;
}

void OGREEE_CALL ogre_scene_animation_advance(struct OgreGameObjectScene* scene, unsigned animation)
{
	//ogre_log(__FUNCTION__, "%p %u", scene, animation);

	GameObjectScene& gos = *static_cast<GameObjectScene*>(scene->internal);
	AnimationScene::const_iterator it = gos.database.animation.find(animation);
	if (it == gos.database.animation.end())
		return;
	unsigned& frame = gos.animation[animation];
	if (++frame >= it->second.limit)
		frame = 0;
}

void ogre_scene_place(struct OgreGameObjectScene* scene)
{
	GameObjectScene& gos = *static_cast<GameObjectScene*>(scene->internal);
	if (!gos.root)
		convert_scene(scene, gos);
	place_scene(scene);
}
