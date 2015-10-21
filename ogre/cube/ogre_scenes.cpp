#include "stdafx.h"

#include "ogre_int.hpp"

#include "lws_exp.hpp"

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
			scene.elements.push_back(SceneDatabaseElement(!number ? String() : ObjectName(number)));
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

		void KeyFrames(const char* type, int visibility, int color, int number_of_keyframes, const OBJECT_3D_SUB_OBJECT_KEYFRAME* keyframes)
		{
			struct T
			{
				static Quaternion Orientation(const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame)
				{
					//return Quaternion(Radian(frame->heading), Vector3::UNIT_Y) * Quaternion(Radian(frame->pitch), Vector3::UNIT_X) * Quaternion(Radian(frame->roll), Vector3::UNIT_Z);
					Matrix3 m; m.FromEulerAnglesYXZ(Radian(-frame->heading), Radian(-frame->pitch), Radian(frame->roll)); return m;
				}
				static Vector3 Position(const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame)
				{
					return Vector3(frame->x, frame->y, -frame->z);
				}
				static Vector3 Scale(const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame)
				{
					return Vector3(frame->scale_x, frame->scale_y, frame->scale_z);
				}
			};

			if (!strcmp(type, "Object"))
			{
				if (skip_object)
					return;

				SceneDatabaseElement& el = scene.elements.back();
				if (number_of_keyframes > 1)
				{
					MeshPtr mesh = MeshManager::getSingleton().getByName(animation_mesh, ogre_resource_group);
					Animation* anim = mesh->createAnimation(KeyframeAnimationName(ogre_index()), keyframes[number_of_keyframes - 1].index / 30.0f);
					NodeAnimationTrack* track = anim->createNodeTrack(0);
					for (int i = 0; i < number_of_keyframes; i++)
					{
						const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame = &keyframes[i];
						TransformKeyFrame* key = track->createNodeKeyFrame(keyframes[i].index / 30.0f);
						key->setTranslate(T::Position(frame));
						key->setRotation(T::Orientation(frame));
						key->setScale(T::Scale(frame));
					}
					el.track = track;
				}
				el.position = T::Position(keyframes);
				el.orientation = T::Orientation(keyframes);
				el.scale = T::Scale(keyframes);
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

	struct OgreSubObjectsSearch search_convert(const SubObjects* so)
	{
		struct OgreSubObjectsSearch osos = { 0, 0 };
		if (so && !so->empty())
		{
			osos.number_of_subobjects = so->size();
			osos.subobjects = &(*so)[0];
		}
		return osos;
	}
}

// Convert the scenes into internal database
void ogre_scenes_init(int number_of_scenes, const struct OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database)
{
	LwsExport lwsexport;

	animation_mesh = ObjectName(-1);
	MeshManager::getSingleton().createManual(animation_mesh, ogre_resource_group);

	scenes.resize(number_of_scenes + 1);

	for (int i = 1; i <= number_of_scenes; i++)
	{
		SceneComposer composer(scenes[i]);
		lwsexport.ExportScene(&composer, &objects_3d_scene_database[i], false);
	}
}

// Clear scenes information
void ogre_scenes_clear(void)
{
	scenes.clear();
}

void ogre_scene_init(struct OgreGameObjectScene* scene)
{
	scene->internal = 0;
	scene->number_of_nodes = 0;
	scene->nodes = 0;
}

// Place the scene as a child of the supplied SceneNode
void ogre_scene_create(int scene_number, struct OgreGameObjectScene* scene, SceneNode* root)
{
	std::auto_ptr<GameObjectScene> gos(new GameObjectScene);
	SceneDatabase& sd = scenes[scene_number];
	gos->database = &sd;
	gos->nodes.clear();
	gos->nodes.reserve(sd.elements.size());
	for (SceneDatabaseElements::const_iterator itor(sd.elements.begin()); itor != sd.elements.end(); ++itor)
	{
		SceneNode* node = (itor->parent == SceneDatabaseElement::no_parent ? root : gos->nodes[itor->parent])->createChildSceneNode();
		node->setPosition(itor->position);
		node->setOrientation(itor->orientation);
		node->setScale(itor->scale);
		if (!itor->object.empty())
			node->attachObject(ogre_scene_manager->createEntity(itor->object));

		gos->nodes.push_back(node);
	}
	scene->number_of_nodes = gos->nodes.size();
	scene->nodes = !gos->nodes.empty() ? reinterpret_cast<struct OgreNode**>(&gos->nodes[0]) : 0;
	scene->internal = gos.release();
}

void ogre_scene_destroy(struct OgreGameObjectScene* scene)
{
	delete static_cast<GameObjectScene*>(scene->internal);
	ogre_scene_init(scene);
}

struct OgreSubObjectsSearch ogre_scene_find(struct OgreGameObjectScene* scene, unsigned sub_object_id)
{
	const SceneDatabase* database = static_cast<GameObjectScene*>(scene->internal)->database;
	AllSubObjects::const_iterator i = database->sub_objects.find(sub_object_id);
	return search_convert(i != database->sub_objects.end() ? &i->second : 0);
}

struct OgreSubObjectsSearch ogre_scene_find2(struct OgreGameObjectScene* scene, unsigned sub_object_id, unsigned parent)
{
	const SceneDatabase* database = static_cast<GameObjectScene*>(scene->internal)->database;
	ParentSubObjects::const_iterator i = database->parent_sub_objects.find(std::make_pair(sub_object_id, parent));
	if (i != database->parent_sub_objects.end())
		return search_convert(&i->second);
	SubObjects& pso = const_cast<ParentSubObjects&>(database->parent_sub_objects)[std::make_pair(sub_object_id, parent)];
	AllSubObjects::const_iterator j = database->sub_objects.find(sub_object_id);
	if (j != database->sub_objects.end())
	{
		const SubObjects& so = j->second;
		for (SubObjects::const_iterator k(so.begin()); k != so.end(); ++k)
			for (unsigned index = *k; index != SceneDatabaseElement::no_parent; index = database->elements[index].parent)
				if (index == parent)
				{
					pso.push_back(*k);
					break;
				}
	}
	return search_convert(&pso);
}

float ogre_scene_subobject_keyframe_length(struct OgreGameObjectScene* scene, unsigned subobject)
{
	GameObjectScene* gos = static_cast<GameObjectScene*>(scene->internal);
	Ogre::NodeAnimationTrack* track = gos->database->elements[subobject].track;
	return track ? track->getParent()->getLength() : 0.0f;
}

void ogre_scene_subobject_keyframe(struct OgreGameObjectScene* scene, unsigned subobject, float time)
{
	GameObjectScene* gos = static_cast<GameObjectScene*>(scene->internal);
	Ogre::NodeAnimationTrack* track = gos->database->elements[subobject].track;
	assert(track);
	Ogre::SceneNode* sn = gos->nodes[subobject];
	sn->resetToInitialState();
	track->applyToNode(sn, time);
}

void ogre_scene_animation(struct OgreGameObjectScene* scene, unsigned animation, unsigned frame)
{
	GameObjectScene* gos = static_cast<GameObjectScene*>(scene->internal);
	AnimationScene::const_iterator itor = gos->database->animation.find(animation);
	if (itor == gos->database->animation.end())
		return;
	const SceneAnimationRefs& sars = itor->second;
	for (SceneAnimationRefs::const_iterator sar(sars.begin()); sar != sars.end(); ++sar)
	{
		Entity* entity = dynamic_cast<Entity*>(gos->nodes[sar->subobject]->getAttachedObject(0));
		assert(entity);
		SubEntity* subentity = entity->getSubEntity(sar->submesh);
		assert(subentity);
		subentity->setMaterialName(MaterialAnimationName(sar->material_index, frame));
	}
}
