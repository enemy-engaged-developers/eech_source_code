#include "stdafx.h"

#include "ogre_int.hpp"

#include "lws_exp.hpp"

typedef std::vector<SceneDatabase> AllScenes;

static AllScenes scenes;


// Adapter for scenes loading. Fills scenes.
// TODO: Add support of Special objects, LODs, Lights and (maybe) Cameras
class SceneComposer : public LwsExporter
{
public:
	SceneComposer(SceneDatabase& scene, SceneManager* sman)
		: scene(scene), mSceneMgr(sman)
	{
	}

	void Begin(void)
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
				return Quaternion(Radian(frame->heading), Vector3::UNIT_Y) * Quaternion(Radian(frame->pitch), Vector3::UNIT_X) * Quaternion(Radian(frame->roll), Vector3::UNIT_Z);
			}
			static Vector3 Position(const OBJECT_3D_SUB_OBJECT_KEYFRAME* frame)
			{
				return Vector3(frame->x, frame->y, frame->z);
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
				Animation* anim = mSceneMgr->createAnimation(KeyframeAnimationName(&scene, scene.elements.size() - 1), keyframes[number_of_keyframes - 1].index / 30.0f);
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
	}

	void LightAttrs(const REAL_COLOUR* colour)
	{
	}

private:
	SceneDatabase& scene;
	SceneManager* mSceneMgr;

	typedef std::map<int, unsigned> IndexToOffset;
	IndexToOffset ito;
	bool skip_object;
};

// Convert the scenes into internal database
void ogre_scenes_init(int number_of_scenes, const OBJECT_3D_SCENE_DATABASE_ENTRY* objects_3d_scene_database, SceneManager* sman)
{
	LwsExport lwsexport;

	scenes.resize(number_of_scenes + 1);

	for (int i = 1; i <= number_of_scenes; i++)
	{
		SceneComposer composer(scenes[i], sman);
		lwsexport.ExportScene(&composer, &objects_3d_scene_database[i], false);
	}
}

// Clear scenes information
// TODO: Clear keyframe animation as well
void ogre_scenes_clear(void)
{
	scenes.clear();
}

// Place the scene as a child of the supplied SceneNode
void ogre_scene_create(int scene_number, GameObjectScene& scene, SceneNode* root, SceneManager* mgr)
{
	SceneDatabase& sd = scenes[scene_number];
	scene.database = &sd;
	scene.nodes.clear();
	scene.nodes.reserve(sd.elements.size());
	for (SceneDatabaseElements::const_iterator itor(sd.elements.begin()); itor != sd.elements.end(); ++itor)
	{
		SceneNode* node = (itor->parent == SceneDatabaseElement::no_parent ? root : scene.nodes[itor->parent])->createChildSceneNode();
		node->setPosition(itor->position);
		node->setOrientation(itor->orientation);
		node->setScale(itor->scale);
		if (!itor->object.empty())
			node->attachObject(mgr->createEntity(itor->object));

		scene.nodes.push_back(node);
	}
}
