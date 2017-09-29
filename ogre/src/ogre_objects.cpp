#include "ogre_int.hpp"

namespace
{
	GeometryPtr objects_geometry;
	typedef Ogre::vector<AnimationMesh>::type ObjectsAnim;
	ObjectsAnim objects_anim;
	unsigned material_first, material_last;

	class Normal : private Uncopyable
	{
	public:
		Normal(void)
		{
			for (int count = 0; count < 256; count++)
			{
				float heading, pitch;
				pitch = heading = (float)count;
				heading /= 256.0;
				pitch /= 256.0;
				heading *= 2 * M_PI;
				pitch *= M_PI;
				heading -= M_PI;
				pitch -= M_PI / 2;
				sin_heading[count] = sin(heading);
				cos_heading[count] = cos(heading);
				sin_pitch[count] = sin(pitch);
				cos_pitch[count] = cos(pitch);
			}
		}

		void normal(const object_3d_heading_pitch_normal& normal, vec3d& result)
		{
			float cp = cos_pitch[normal.pitch];
			result.x = cp * sin_heading[normal.heading];
			result.y = sin_pitch[normal.pitch];
			result.z = cp * cos_heading[normal.heading];
			result.z = -result.z;
		}
	private:
		float sin_heading[256], cos_heading[256], sin_pitch[256], cos_pitch[256];
	};

	Normal normal;

	// Surface comparer. The polygons of the equal surfaces go into the single Ogre::SubMesh.
	static bool compare_surfaces(const face_surface_description& left, const face_surface_description& right)
	{
#if 0
		return false;
#else

#define CMP(x) if ((left.x) != (right.x)) return false;
#define ANY(x) if ((left.x) || (right.x)) return false;

		ANY(texture_animation);
		ANY(luminosity_texture_animation);
		CMP(surface_flags & 0xFFFFFF);
#if 1
		CMP(texture_index);
		CMP(luminosity_texture_index);
#endif
		if (left.has_specularity)
			CMP(specularity);
#if 0
		CMP(reflectivity);
#endif
		if (!left.textured || left.luminous)
			CMP(colour);

#undef CMP
#undef ANY

		return true;
#endif
	}

	class TaskObjectsInit : public Task
	{
	public:
		TaskObjectsInit(unsigned number_of_objects, const struct OBJECT_3D* objects, Semaphore& sem)
			: number_of_objects(number_of_objects), objects(objects), sem(sem)
		{
		}
		virtual TaskResult task(void)
		{
			assert(!objects_geometry.get());
			objects_geometry.reset(new Geometry);

			material_first = ogre_index() + 1;

			objects_anim.resize(number_of_objects + 1);
			for (unsigned i = 0; i <= number_of_objects; i++)
				ogre_objects_convert(objects[i], Ogre::MeshManager::getSingleton().createManual(ObjectName(i), ogre_resource_group), objects_anim[i], objects_geometry.get());
			objects_geometry->flush();

			material_last = ogre_index() - 1;

			sem.release();
			return TR_TASK;
		}

	private:
		unsigned number_of_objects;
		const struct OBJECT_3D* objects;
		Semaphore& sem;
	};

	class TaskObjectsClear : public Task
	{
	public:
		TaskObjectsClear(Semaphore& sem)
			: sem(sem)
		{
		}
		virtual TaskResult task(void)
		{
			for (unsigned i = 0; i < objects_anim.size(); i++)
			{
				ObjectName object(i);
				Ogre::MeshManager::getSingleton().unload(object);
				Ogre::MeshManager::getSingleton().remove(object);
			}

			for (ObjectsAnim::iterator oa(objects_anim.begin()); oa != objects_anim.end(); ++oa)
				for (AnimationMesh::iterator am(oa->begin()); am != oa->end(); ++am)
					for (AnimationRefs::iterator ar(am->second.refs.begin()); ar != am->second.refs.end(); ++ar)
						for (unsigned frame = 0; frame < am->second.limit; frame++)
						{
							MaterialAnimationName material_animation_name(ar->material_index, frame);
							Ogre::MaterialManager::getSingleton().unload(material_animation_name);
							Ogre::MaterialManager::getSingleton().remove(material_animation_name);
						}
			objects_anim.clear();

			for (unsigned material_index = material_first ; material_index <= material_last; material_index++)
			{
				MaterialName material_name(material_index);
				Ogre::MaterialManager::getSingleton().unload(material_name);
				Ogre::MaterialManager::getSingleton().remove(material_name);
			}

			objects_geometry.reset(0);

			sem.release();
			return TR_TASK;
		}

	private:
		Semaphore& sem;
	};

	bool texture_contains_alpha(const Ogre::String& texture_name)
	{
		Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName(texture_name);
		return texture.get() && Ogre::PixelUtil::hasAlpha(texture->getFormat());
	}
}

// Converts EE's OBJECT_3D into Ogre::Mesh
void ogre_objects_convert(const OBJECT_3D& o, Ogre::MeshPtr mesh, AnimationMesh& animation, Geometry* geometry)
{
	assert(GetCurrentThreadId() == ogre_thread_id);

	if (!o.number_of_points)
	{
		mesh->load();
		return;
	}

	Ogre::vector<object_3d_point>::type points(o.number_of_points);
#ifdef USE_OBJECTS_NORMALS
	Ogre::vector<vec3d>::type normals(o.number_of_point_normals);
#endif
	{
		// Calculate real point coordinates and normals

		const float xmax = std::max(fabs(o.bounding_box.xmin), fabs(o.bounding_box.xmax)) / 32767.0f;
		const float ymax = std::max(fabs(o.bounding_box.ymin), fabs(o.bounding_box.ymax)) / 32767.0f;
		const float zmax = std::max(fabs(o.bounding_box.zmin), fabs(o.bounding_box.zmax)) / 32767.0f;

		for (int j = 0; j < o.number_of_points; j++)
		{
			const object_short_3d_point& p = o.points[j];
			object_3d_point& p3 = points[j];
			p3.x = p.x * xmax;
			p3.y = p.y * ymax;
			p3.z = p.z * zmax;
			p3.z = -p3.z;
		}

#ifdef USE_OBJECTS_NORMALS
		for (int j = 0; j < o.number_of_point_normals; j++)
			normal.normal(o.point_normals[j], normals[j]);
#endif
	}

	object_3d_point* cp = &points[0];
	object_3d_face* cf = o.faces;
#ifdef USE_OBJECTS_NORMALS
	vec3d* cpn = o.number_of_point_normals ? &normals[0] : NULL;
#endif
	point_3d_short_reference* cppl = o.object_faces_point_plain_list;
	object_3d_short_textured_point* cstp = o.surface_texture_points;
	point_3d_plain_reference* csp = o.surface_points;
#ifdef USE_OBJECTS_NORMALS
	point_3d_plain_reference* cspn = o.surface_point_normals;
#endif

	// Aggregator of the equal surfaces
	struct SurfacesInfo
	{
		face_surface_description surface;
		VertexDescription vd;
		Ogre::vector<float>::type fdata;
		Ogre::vector<IndexType>::type idata;
	};
	typedef Ogre::list<SurfacesInfo>::type Surfaces;
	Surfaces surfaces;

	// Merge equal surfaces into the single SurfaceInfo.
	// Convert and merge geometry.
	for (int j = 0; j < o.number_of_surfaces; j++)
	{
		// Find the existing SurfaceInfo or create new one.
		face_surface_description& s = o.surfaces[j];
		Surfaces::iterator itor(surfaces.begin());
		for (; itor != surfaces.end(); ++itor)
			if (compare_surfaces(itor->surface, s))
				break;
		SurfacesInfo& info = itor == surfaces.end() ? (surfaces.push_back(SurfacesInfo()), surfaces.back()) : *itor;

		info.surface = s;
		info.vd = VertexDescription(s);


		// Convert geometry using local caches

		const size_t number_of_points = s.number_of_points ? s.number_of_points : 256;
		size_t number_of_indices = 0;
		if (s.polygons)
			for (size_t k = 0; k < s.number_of_faces; k++)
				number_of_indices += (cf[k].number_of_points - 2) * 3;
		else
			number_of_indices = s.number_of_faces * 2;

		const size_t old_fsize = info.fdata.size();
		const size_t old_index = old_fsize / info.vd.vertex_size;
		const size_t old_isize = info.idata.size();

		info.fdata.resize(old_fsize + number_of_points * info.vd.vertex_size);
		info.idata.resize(old_isize + number_of_indices);

		float* f = &info.fdata[old_fsize];
		IndexType* i = &info.idata[old_isize];

		for (size_t k = 0; k < number_of_points; k++)
		{
			*(object_3d_point*)f = cp[csp++->point];
			f += 3;
#ifdef USE_OBJECTS_NORMALS
			if (s.smoothed)
			{
				*(vec3d*)f = cpn[cspn++->point];
				f += 3;
			}
#endif
#ifdef USE_OBJECTS_TEXTURES
			if (s.textured)
			{
				*(object_3d_short_textured_point*)f = *cstp++;
				f += 2;
			}
			if (s.has_luminosity_texture)
			{
				*(object_3d_short_textured_point*)f = *cstp++;
				f += 2;
			}
#endif
		}

		for (int k = 0; k < s.number_of_faces; k++)
		{
			if (s.polygons)
			{
				IndexType first = cppl++->point + old_index;
				IndexType next = cppl++->point + old_index;
				for (int l = 2; l < cf->number_of_points; l++)
				{
					*i++ = first;
					*i++ = next;
					next = cppl++->point + old_index;
					*i++ = next;
				}
				cf++;
			}
			else
			{
				*i++ = cppl++->point + old_index;
				*i++ = cppl++->point + old_index;
			}
		}
	}

	// For each SurfaceInfo and its cached geometry - create Ogre::SubMesh
	for (Surfaces::const_iterator itor(surfaces.begin()); itor != surfaces.end(); ++itor)
	{
		const SurfacesInfo& info = *itor;
		const face_surface_description& s = info.surface;

		// Geometry
		Geometry::BUF buf;
		geometry->get_buf(info.vd, info.fdata.size() / info.vd.vertex_size, info.idata.size(), buf);
		std::copy(info.fdata.begin(), info.fdata.end(), buf.fdata);
		std::copy(info.idata.begin(), info.idata.end(), buf.idata);

		// Material
		unsigned material_index = ogre_index();
		MaterialName material_name(material_index);
		Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(material_name, ogre_resource_group);
		mat->setCullingMode(Ogre::CULL_ANTICLOCKWISE);

		// TODO: Materials don't use original surface information completely

		Ogre::ColourValue colour(s.red / 255.0f, s.green / 255.0f, s.blue / 255.0f, s.alpha / 255.0f);

		Ogre::Pass* pass = mat->getTechnique(0)->getPass(0);

		if (s.detail)
			pass->setDepthBias(2.0f, 1.0f);

		Ogre::TextureUnitState* tus = pass->createTextureUnitState();

		if (s.textured)
		{
			if (!s.texture_animation)
				tus->setTextureName(TextureName(s.texture_index));
			tus->setTextureAddressingMode(s.texture_wrapped_u ? Ogre::TextureUnitState::TAM_WRAP : Ogre::TextureUnitState::TAM_CLAMP, s.texture_wrapped_v ? Ogre::TextureUnitState::TAM_WRAP : Ogre::TextureUnitState::TAM_CLAMP, Ogre::TextureUnitState::TAM_CLAMP);

#if 1
			if (s.has_luminosity_texture)
			{
				Ogre::TextureUnitState* tus = pass->createTextureUnitState(Ogre::String(), 1);

				if (!s.luminosity_texture_animation)
					tus->setTextureName(TextureName(s.luminosity_texture_index));
				tus->setTextureAddressingMode(s.luminosity_texture_wrapped_u ? Ogre::TextureUnitState::TAM_WRAP : Ogre::TextureUnitState::TAM_CLAMP, s.luminosity_texture_wrapped_v ? Ogre::TextureUnitState::TAM_WRAP : Ogre::TextureUnitState::TAM_CLAMP, Ogre::TextureUnitState::TAM_CLAMP);
				tus->setColourOperation(Ogre::LBO_MODULATE);
			}
#endif
		}
		else
		{
			tus->setColourOperationEx(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, colour);
			if (s.additive || s.translucent)
				tus->setAlphaOperation(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, colour.a);
		}

		if (s.textured && !s.texture_animation && texture_contains_alpha(TextureName(s.texture_index)) || s.additive || s.translucent)
		{
			pass->setSceneBlending(s.additive ? Ogre::SBT_ADD : Ogre::SBT_TRANSPARENT_ALPHA);
			pass->setDepthWriteEnabled(false);
		}

		if (s.has_specularity)
			pass->setShininess(s.specularity / 255.0f);
		if (s.luminous)
			pass->setSelfIllumination(colour);


		// SubMesh

		Ogre::SubMesh* sm = mesh->createSubMesh();
		sm->useSharedVertices = false;
		sm->operationType = s.polygons ? Ogre::RenderOperation::OT_TRIANGLE_LIST : Ogre::RenderOperation::OT_LINE_LIST;
		sm->vertexData = OGRE_NEW Ogre::VertexData(buf.vbuf.vd, buf.vbuf.vbb);
		sm->vertexData->vertexStart = buf.vbuf.offset;
		sm->vertexData->vertexCount = info.fdata.size() / info.vd.vertex_size;
		sm->indexData->indexBuffer = buf.ibuf.hib;
		sm->indexData->indexStart = buf.ibuf.offset;
		sm->indexData->indexCount = info.idata.size();
		sm->setMaterialName(material_name);

		do
		{
			if (!s.textured)
				break;

			assert(!s.texture_animation || !s.luminosity_texture_animation);
			unsigned animation_index;
			unsigned tus_index;
			if (s.texture_animation)
			{
				animation_index = s.texture_index;
				tus_index = 0;
			}
			else
			{
				if (s.luminosity_texture_animation)
				{
					animation_index = s.luminosity_texture_index;
					tus_index = 1;
				}
				else
					break;
			}
			unsigned smi = mesh->getNumSubMeshes() - 1;
			AnimationInfo& ai = animation[animation_index];
			const TextureAnimation& texture_animation = ogre_textures_animation(animation_index);
			ai.limit = texture_animation.size();
			ai.refs.push_back(AnimationRef(smi, material_index));
			unsigned size = ai.limit;
			for (unsigned frame = 0; frame < size; frame++)
			{
				MaterialAnimationName material_animation_name(material_index, frame);
				Ogre::MaterialPtr mata = mat->clone(material_animation_name);
				TextureName texture_name(texture_animation[frame]);
				Ogre::Pass* pass = mata->getTechnique(0)->getPass(0);
				pass->getTextureUnitState(tus_index)->setTextureName(texture_name);
				if (texture_contains_alpha(texture_name))
				{
					pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
					pass->setDepthWriteEnabled(false);
				}
			}
			sm->setMaterialName(MaterialAnimationName(material_index, 0));
		}
		while (false);
	}

	mesh->_setBounds(Ogre::AxisAlignedBox(Ogre::Vector3(-o.radius, -o.radius, -o.radius), Ogre::Vector3(o.radius, o.radius, o.radius)), false);
	mesh->_setBoundingSphereRadius(o.radius);
	mesh->load();
}

void ogre_objects_add_animation(unsigned object, AnimationScene& as, unsigned subobject)
{
	assert(GetCurrentThreadId() == ogre_thread_id);

	assert(object < objects_anim.size());
	const AnimationMesh& am = objects_anim[object];
	for (AnimationMesh::const_iterator i(am.begin()); i != am.end(); ++i)
	{
		SceneAnimationInfo& sar = as[i->first];
		sar.limit = i->second.limit;
		for (AnimationRefs::const_iterator j(i->second.refs.begin()); j != i->second.refs.end(); j++)
			sar.refs.push_back(SceneAnimationRef(subobject, *j));
	}
}

// Converts objects
void OGREEE_CALL ogre_objects_init(unsigned number_of_objects, const struct OBJECT_3D* objects)
{
	assert(GetCurrentThreadId() == user_thread_id);

	Semaphore sem;
	ogre_tasks->enqueue(new TaskObjectsInit(number_of_objects, objects, sem));
	sem.acquire();
}

// Clears objects information
void OGREEE_CALL ogre_objects_clear(void)
{
	assert(GetCurrentThreadId() == user_thread_id);

	Semaphore sem;
	ogre_tasks->enqueue(new TaskObjectsClear(sem));
	sem.acquire();
}
