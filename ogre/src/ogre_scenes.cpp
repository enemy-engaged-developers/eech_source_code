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
	typedef Ogre::vector<SceneDatabase>::type AllScenes;

	AllScenes scenes;

	Ogre::String animation_mesh;


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
						key->setTranslate(ogre_position(&frame->x));
						key->setRotation(ogre_orientation(frame->heading, frame->pitch, frame->roll));
						key->setScale(ogre_scale(&frame->scale_x));
					}
					el.track = track;
					el.track_length = track->getParent()->getLength();
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

		typedef Ogre::map<int, unsigned>::type IndexToOffset;
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

	class TaskScenesInit : public Task
	{
	public:
		TaskScenesInit(int number_of_scenes, const struct OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database, Semaphore& sem)
			: number_of_scenes(number_of_scenes), objects_3d_scene_database(objects_3d_scene_database), sem(sem)
		{
		}
		virtual TaskResult task(void)
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

			sem.release();
			return TR_TASK;
		}

	private:
		int number_of_scenes;
		const struct OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database;
		Semaphore& sem;
	};
}

namespace
{
	void place_node(Ogre::SceneNode* node, const SceneDatabaseElement& sde, const struct OgreGameObjectSceneElement& p)
	{
		assert(GetCurrentThreadId() == ogre_thread_id);

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
			node->setPosition(ogre_position(&p.relative_position.x));
			node->setOrientation(ogre_orientation(p.relative_heading, p.relative_pitch, p.relative_roll));
			node->setScale(ogre_scale(&p.relative_scale.x));
		}
	}

	void destroy_node(Ogre::SceneNode* node)
	{
		assert(GetCurrentThreadId() == ogre_thread_id);

		assert(!node->numAttachedObjects());
		Ogre::SceneNode* parent = node->getParentSceneNode();
		if (parent)
			parent->removeChild(node);
		node->getCreator()->destroySceneNode(node);
	}

	void convert_scene(DrawnScene& ds, const SceneDatabase& database)
	{
		assert(GetCurrentThreadId() == ogre_thread_id);

		assert(!ds.root);
		ds.root = ogre_scene_manager->createSceneNode();
		ds.nodes.reserve(database.elements.size());
		for (SceneDatabaseElements::const_iterator itor(database.elements.begin()); itor != database.elements.end(); ++itor)
		{
			Ogre::SceneNode* node = (itor->parent == SceneDatabaseElement::no_parent ? ds.root : ds.nodes[itor->parent].first)->createChildSceneNode();
			Ogre::Entity* ent = 0;
			if (!itor->object.empty())
			{
				ent = ogre_scene_manager->createEntity(itor->object);
				node->attachObject(ent);
			}
			ds.nodes.push_back(SceneNode(node, ent));
		}
	}

	template <typename Animation>
	void place_scene(DrawnScene& ds, const SceneDatabase& database, const struct OgreGameObjectSceneElement* elements, unsigned number_of_elements, const Animation& animation)
	{
		assert(GetCurrentThreadId() == ogre_thread_id);

		for (unsigned i = number_of_elements; i--;)
			place_node(ds.nodes[i].first, database.elements[i], elements[i]);
		for (typename Animation::const_iterator itor(animation.begin()); itor != animation.end(); ++itor)
		{
			AnimationScene::const_iterator it = database.animation.find(itor->first);
			assert(it != database.animation.end());
			const SceneAnimationRefs& sars = it->second.refs;
			for (SceneAnimationRefs::const_iterator sar(sars.begin()); sar != sars.end(); ++sar)
			{
				Ogre::Entity* entity = ds.nodes[sar->subobject].second;
				assert(entity);
				Ogre::SubEntity* subentity = entity->getSubEntity(sar->submesh);
				assert(subentity);
				subentity->setMaterialName(MaterialAnimationName(sar->material_index, itor->second));
			}
		}
	}

	void place_scene(DrawnScene& ds, const SceneDraw& sd)
	{
		assert(GetCurrentThreadId() == ogre_thread_id);

		assert(ds.root);
		ogre_scene_manager->getRootSceneNode()->addChild(ds.root);
		ds.root->setPosition(sd.position);
		ds.root->setOrientation(sd.orientation);
		ds.root->setScale(sd.scale);
		assert(!sd.elements.empty());
		place_scene(ds, *ds.database, &sd.elements[0], sd.elements.size(), sd.animation);
	}
}

DrawnScene::~DrawnScene(void)
{
	assert(GetCurrentThreadId() == ogre_thread_id);

	while (!nodes.empty())
	{
		SceneNode& sn = nodes.back();
		if (sn.second)
		{
			sn.first->detachObject(sn.second);
			ogre_scene_manager->destroyEntity(sn.second);
		}
		destroy_node(sn.first);
		nodes.pop_back();
	}
	if (root)
		destroy_node(root);
}

namespace
{
	struct DrawnSceneEx
	{
		DrawnScene ds;
		unsigned left;
	};
	typedef Ogre::list<DrawnSceneEx>::type DrawnScenes;
	DrawnScenes drawn_scenes;

	typedef Ogre::map<const SceneDatabase*, DrawnScenes>::type OldDrawnScenes;
	OldDrawnScenes old_drawn_scenes;

	class TaskScenesDraw : public Task
	{
	public:
		TaskScenesDraw(SceneDraws& sd)
		{
			this->sd.swap(sd);
		}
		virtual TaskResult task(void)
		{
			//ogre_log(__FUNCTION__, "%u %u", drawn_scenes.size(), sd.size());

			for (SceneDraws::iterator itor(sd.begin()); itor != sd.end(); ++itor)
			{
				OldDrawnScenes::iterator it(old_drawn_scenes.find(itor->database));
				if (it != old_drawn_scenes.end() && !it->second.empty())
					drawn_scenes.splice(drawn_scenes.begin(), it->second, it->second.begin());
				else
				{
					drawn_scenes.push_front(DrawnSceneEx());
					DrawnScene& ds = drawn_scenes.front().ds;
					ds.database = itor->database;
					convert_scene(ds, *itor->database);
				}
				place_scene(drawn_scenes.front().ds, *itor);
			}
			return TR_TASK;
		}

	private:
		SceneDraws sd;
	};
}

namespace
{
	SceneDraws scene_draws;

	class TaskScenesClear : public Task
	{
	public:
		TaskScenesClear(Semaphore& sem)
			: sem(sem)
		{
		}
		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			scene_draws.clear();

			drawn_scenes.clear();

			old_drawn_scenes.clear();

			AllScenes().swap(scenes);

			if (!animation_mesh.empty())
			{
				Ogre::MeshManager::getSingleton().unload(animation_mesh);
				Ogre::MeshManager::getSingleton().remove(animation_mesh);
				animation_mesh.clear();
			}

			sem.release();
			return TR_TASK;
		}

	private:
		int number_of_scenes;
		Semaphore& sem;
	};
}

// Convert the scenes into internal database
void OGREEE_CALL ogre_scenes_init(int number_of_scenes, const struct OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "");

	Semaphore sem;
	ogre_tasks->enqueue(new TaskScenesInit(number_of_scenes, objects_3d_scene_database, sem));
	sem.acquire();
}

// Clear scenes information
void OGREEE_CALL ogre_scenes_clear(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "");

	Semaphore sem;
	ogre_tasks->enqueue(new TaskScenesClear(sem));
	sem.acquire();
}

void ogre_scenes_frame(void)
{
	assert(GetCurrentThreadId() == ogre_thread_id);
	//ogre_log(__FUNCTION__, "%u", drawn_scenes.size());

	while (!drawn_scenes.empty())
	{
		DrawnScenes::iterator it(drawn_scenes.begin());
		it->ds.root->getParentSceneNode()->removeChild(it->ds.root);
		it->left = USE_SCENES_CACHE_FRAMES;
		DrawnScenes& ds = old_drawn_scenes[it->ds.database];
		ds.splice(ds.begin(), drawn_scenes, it);
	}

	for (OldDrawnScenes::iterator itor(old_drawn_scenes.begin()); itor != old_drawn_scenes.end();)
	{
		DrawnScenes& ds = itor->second;
		for (DrawnScenes::iterator it(ds.begin()); it != ds.end();)
			if (!it->left--)
				it = ds.erase(it);
			else
				++it;
		if (ds.empty())
			itor = old_drawn_scenes.erase(itor);
		else
			++itor;
	}
}

OGREEE_API void OGREEE_CALL ogre_scenes_commit(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "%u", scene_draws.size());

	ogre_tasks->enqueue(new TaskScenesDraw(scene_draws));
}

void OGREEE_CALL ogre_scene_init(struct OgreGameObjectScene* scene)
{
	assert(GetCurrentThreadId() == user_thread_id);
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
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_scene_init(scene);
	SceneDatabase& sd = scene_number < scenes.size() ? scenes[scene_number] : empty_database;
	std::auto_ptr<GameObjectScene> gos(new GameObjectScene(sd));
	scene->number_of_elements = sd.elements.size();
	scene->elements = scene->number_of_elements ? new struct OgreGameObjectSceneElement[scene->number_of_elements] : 0;
	for (unsigned i = 0; i < scene->number_of_elements; i++)
		scene->elements[i] = gos->database.elements[i].initial;
	scene->internal = gos.release();
}

void OGREEE_CALL ogre_scene_destroy(struct OgreGameObjectScene* scene)
{
	assert(GetCurrentThreadId() == user_thread_id);
	if (scene->internal)
		delete static_cast<GameObjectScene*>(scene->internal);
	if (scene->elements)
		delete [] scene->elements;
	ogre_scene_init(scene);
}

unsigned OGREEE_CALL ogre_scene_get_object(const struct OgreGameObjectScene* scene, unsigned subobject)
{
	assert(GetCurrentThreadId() == user_thread_id);
	const SceneDatabase& database = static_cast<const GameObjectScene*>(scene->internal)->database;
	assert(subobject < database.elements.size());
	const Ogre::String& name = database.elements[subobject].object;
	//FIXME
	if (!name.empty())
		return strtol(name.c_str() + 7, 0, 16);
	return -1;
}

unsigned OGREEE_CALL ogre_scene_get_parent(const struct OgreGameObjectScene* scene, unsigned subobject)
{
	assert(GetCurrentThreadId() == user_thread_id);
	const SceneDatabase& database = static_cast<const GameObjectScene*>(scene->internal)->database;
	assert(subobject < database.elements.size());
	return database.elements[subobject].parent;
}

int OGREEE_CALL ogre_scene_find(const struct OgreGameObjectScene* scene, unsigned sub_object_id, struct OgreSubObjectsSearch* search)
{
	assert(GetCurrentThreadId() == user_thread_id);
	const SceneDatabase& database = static_cast<const GameObjectScene*>(scene->internal)->database;
	AllSubObjects::const_iterator i = database.sub_objects.find(sub_object_id);
	return search_convert(i != database.sub_objects.end() ? &i->second : 0, search);
}

int OGREEE_CALL ogre_scene_find2(const struct OgreGameObjectScene* scene, unsigned sub_object_id, unsigned parent, struct OgreSubObjectsSearch* search)
{
	assert(GetCurrentThreadId() == user_thread_id);
	const SceneDatabase& database = static_cast<const GameObjectScene*>(scene->internal)->database;
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

float OGREEE_CALL ogre_scene_subobject_keyframe_length(const struct OgreGameObjectScene* scene, unsigned subobject)
{
	assert(GetCurrentThreadId() == user_thread_id);
	const GameObjectScene& gos = *static_cast<const GameObjectScene*>(scene->internal);
	assert(subobject < gos.database.elements.size());
	return gos.database.elements[subobject].track_length;
}

void OGREEE_CALL ogre_scene_animation(struct OgreGameObjectScene* scene, unsigned animation, unsigned frame)
{
	assert(GetCurrentThreadId() == user_thread_id);
	GameObjectScene& gos = *static_cast<GameObjectScene*>(scene->internal);
	AnimationScene::const_iterator it = gos.database.animation.find(animation);
	if (it == gos.database.animation.end())
		return;
	gos.animation[animation] = frame;
}

void OGREEE_CALL ogre_scene_animation_advance(struct OgreGameObjectScene* scene, unsigned animation)
{
	assert(GetCurrentThreadId() == user_thread_id);
	GameObjectScene& gos = *static_cast<GameObjectScene*>(scene->internal);
	AnimationScene::const_iterator it = gos.database.animation.find(animation);
	if (it == gos.database.animation.end())
		return;
	unsigned& frame = gos.animation[animation];
	if (++frame >= it->second.limit)
		frame = 0;
}

void ogre_scene_place(const struct OgreGameObjectScene* scene, DrawnScene& ds)
{
	assert(GetCurrentThreadId() == ogre_thread_id);
	GameObjectScene& gos = *static_cast<GameObjectScene*>(scene->internal);
	convert_scene(ds, gos.database);
	ds.root->setPosition(ogre_position(&scene->position.x));
	ds.root->setOrientation(ogre_orientation(scene->attitude[0]));
	place_scene(ds, gos.database, scene->elements, scene->number_of_elements, gos.animation);
}

void OGREEE_CALL ogre_scene_draw(const struct OgreGameObjectScene* scene, const float* scale)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "%p %u %u", scene, scene->number_of_elements, scene_draws.size());

	const GameObjectScene& gos = *static_cast<const GameObjectScene*>(scene->internal);
	if (gos.database.elements.empty())
		return;
	scene_draws.push_back(SceneDraw());
	SceneDraw& sd = scene_draws.back();
	sd.database = &gos.database;
	sd.animation.reserve(gos.animation.size());
	std::copy(gos.animation.begin(), gos.animation.end(), std::back_inserter(sd.animation));
	sd.position = ogre_position(&scene->position.x);
	sd.orientation = ogre_orientation(scene->attitude[0]);
	sd.scale = scale ? ogre_scale(scale) : Ogre::Vector3::UNIT_SCALE;
	sd.elements.assign(scene->elements, scene->elements + scene->number_of_elements);
}
