#include "stdafx.h"

#include "ogre_int.hpp"

#ifdef USE_INDICES32
#define OBJECTS_POINTS_PER_VERTEX_BUFFER (1u << 20)
#define OBJECTS_POINTS_PER_INDEX_BUFFER (1u << 22)
#else
#define OBJECTS_POINTS_PER_VERTEX_BUFFER (1u << 16)
#define OBJECTS_POINTS_PER_INDEX_BUFFER (1u << 22)
#endif

static GeometryPtr objects_geometry;
static MaterialHolderPtr objects_materials;
static unsigned objects_number_of_objects;


// Surface comparer. The polygons of the equal surfaces go into the single Ogre::SubMesh.
static bool
compare_surfaces(const face_surface_description& left, const face_surface_description& right)
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

// Converts EE's OBJECT_3D into Ogre::Mesh
void ogre_objects_convert(const OBJECT_3D& o, MeshPtr mesh, Geometry* geometry)
{
	if (!o.number_of_points)
	{
		mesh->load();
		return;
	}

	std::vector<object_3d_point> points(o.number_of_points);
#ifdef USE_OBJECTS_NORMALS
	std::vector<vec3d> normals(o.number_of_point_normals);
#endif
	{
		// Calculate real point coordinates and normals

		const float
			xmax = std::max(fabs(o.bounding_box.xmin), fabs(o.bounding_box.xmax)) / 32767.0f,
			ymax = std::max(fabs(o.bounding_box.ymin), fabs(o.bounding_box.ymax)) / 32767.0f,
			zmax = std::max(fabs(o.bounding_box.zmin), fabs(o.bounding_box.zmax)) / 32767.0f;

		for (int j = 0; j < o.number_of_points; j++)
		{
			const object_short_3d_point& p = o.points[j];
			object_3d_point& p3 = points[j];
			p3.x = p.x * xmax;
			p3.y = p.y * ymax;
			p3.z = p.z * zmax;
		}

#ifdef USE_OBJECTS_NORMALS
		for (int j = 0; j < o.number_of_point_normals; j++)
			generate_object_3d_point_normal(&o.point_normals[j], &normals[j]);
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
		std::vector<float> fdata;
		std::vector<IndexType> idata;
	};
	typedef std::list<SurfacesInfo> Surfaces;
	Surfaces surfaces;

	// Merge equal surfaces into the single SurfaceInfo.
	// Convert and merge geometry.
	for (int j = 0; j < o.number_of_surfaces; j++)
	{
		// Find the existing SurfaceInfo or create new one.
		face_surface_description& s = o.surfaces[j];
		Surfaces::iterator itor(surfaces.begin());
		for (; itor != surfaces.end(); ++itor)
		{
			if (compare_surfaces(itor->surface, s))
				break;
		}
		SurfacesInfo& info = itor == surfaces.end() ? (surfaces.push_back(SurfacesInfo()), surfaces.back()) : *itor;

		info.surface = s;
		info.vd = VertexDescription(s);


		// Convert geometry using local caches

		const size_t number_of_points = s.number_of_points ? s.number_of_points : 256;
		size_t number_of_indices = 0;
		if (s.polygons)
		{
			for (size_t k = 0; k < s.number_of_faces; k++)
				number_of_indices += (cf[k].number_of_points - 2) * 3;
		}
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
				*f = 1.0f - *f;
				f += 2;
			}
			if (s.has_luminosity_texture)
			{
				*(object_3d_short_textured_point*)f = *cstp++;
				*f = 1.0f - *f;
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
		MaterialName material_name(MaterialHolder::get_index());
		MaterialPtr mat = MaterialManager::getSingleton().create(material_name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		// TODO: Materials don't use original surface information completely

		ColourValue colour(s.red / 255.0f, s.green / 255.0f, s.blue / 255.0f, s.alpha / 255.0f);

		Pass* pass = mat->getTechnique(0)->getPass(0);
		//pass->setCullingMode(CULL_NONE);

		if (s.detail)
			pass->setDepthBias(2.0f);

		TextureUnitState* tus = pass->createTextureUnitState();

		if (s.textured)
		{
			tus->setTextureName(TextureName(s.texture_index, s.texture_animation));
			tus->setTextureAddressingMode(s.texture_wrapped_u ? TextureUnitState::TAM_WRAP : TextureUnitState::TAM_CLAMP, s.texture_wrapped_v ? TextureUnitState::TAM_WRAP : TextureUnitState::TAM_CLAMP, TextureUnitState::TAM_CLAMP);

#if 1
			if (s.has_luminosity_texture)
			{
				Pass* pass = mat->getTechnique(0)->createPass();
				TextureUnitState* tus = pass->createTextureUnitState();

				tus->setTextureName(TextureName(s.luminosity_texture_index, s.luminosity_texture_animation));
				tus->setTextureAddressingMode(s.luminosity_texture_wrapped_u ? TextureUnitState::TAM_WRAP : TextureUnitState::TAM_CLAMP, s.luminosity_texture_wrapped_v ? TextureUnitState::TAM_WRAP : TextureUnitState::TAM_CLAMP, TextureUnitState::TAM_CLAMP);
				pass->setSceneBlending(SBT_MODULATE);
			}
#endif
		}
		else
		{
			tus->setColourOperationEx(LBX_SOURCE1, LBS_MANUAL, LBS_CURRENT, colour);
			if (s.additive || s.translucent)
				tus->setAlphaOperation(LBX_SOURCE1, LBS_MANUAL, LBS_CURRENT, colour.a);
		}

		if (/*s.textured && !s.texture_animation && get_textures_info(s.texture_index).contains_alpha ||*/ s.additive || s.translucent)
		{
			pass->setSceneBlending(SBT_TRANSPARENT_ALPHA);
			pass->setDepthWriteEnabled(false);
		}

		if (s.has_specularity)
			pass->setShininess(s.specularity / 255.0f);
		if (s.luminous)
			pass->setSelfIllumination(colour);


		// SubMesh

		SubMesh* sm = mesh->createSubMesh();
		sm->useSharedVertices = false;
		sm->operationType = s.polygons ? RenderOperation::OT_TRIANGLE_LIST : RenderOperation::OT_LINE_LIST;
		sm->vertexData = OGRE_NEW VertexData(buf.vbuf.vd, buf.vbuf.vbb);
		sm->vertexData->vertexStart = buf.vbuf.offset;
		sm->vertexData->vertexCount = info.fdata.size() / info.vd.vertex_size;
		sm->indexData->indexBuffer = buf.ibuf.hib;
		sm->indexData->indexStart = buf.ibuf.offset;
		sm->indexData->indexCount = info.idata.size();
		sm->setMaterialName(material_name);
	}

	mesh->_setBounds(AxisAlignedBox(Vector3(-o.radius, -o.radius, -o.radius), Vector3(o.radius, o.radius, o.radius)), false);
	mesh->_setBoundingSphereRadius(o.radius);
	mesh->load();
}


// Converts objects
void ogre_objects_init(unsigned number_of_objects, const OBJECT_3D* objects)
{
	assert(!objects_geometry.get() && !objects_materials.get());
	objects_geometry.reset(new Geometry(OBJECTS_POINTS_PER_VERTEX_BUFFER, OBJECTS_POINTS_PER_INDEX_BUFFER));

	objects_number_of_objects = number_of_objects;

	unsigned material = MaterialHolder::get_index();

	for (unsigned i = 0; i <= objects_number_of_objects; i++)
		ogre_objects_convert(objects[i], MeshManager::getSingleton().createManual(ObjectName(i), ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME), objects_geometry.get());
	objects_geometry->flush();

	objects_materials.reset(new MaterialHolder(material));

	//objects_geometry->statistics("OG_STAT.TXT");
}

// Clears objects information
void ogre_objects_clear(void)
{
	for (unsigned i = 0; i <= objects_number_of_objects; i++)
	{
			ObjectName object(i);
			MeshManager::getSingleton().unload(object);
			MeshManager::getSingleton().remove(object);
	}

	objects_geometry.reset(0);
	objects_materials.reset(0);
}
