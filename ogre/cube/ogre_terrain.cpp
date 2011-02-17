#include "stdafx.h"

#include "ogre_int.hpp"

#ifdef USE_TERRAIN
#if defined(USE_TERRAIN_STATIC_GEOMETRY) || defined(USE_TERRAIN_PAGING)
#define USE_TERRAIN_CONVERT_ON_FLY
#endif

#ifndef USE_TERRAIN_CONVERT_ON_FLY
#ifdef USE_INDICES32
#define TERRAIN_POINTS_PER_VERTEX_BUFFER (1u << 20)
#define TERRAIN_POINTS_PER_INDEX_BUFFER (1u << 22)
#else
#define TERRAIN_POINTS_PER_VERTEX_BUFFER (1u << 16)
#define TERRAIN_POINTS_PER_INDEX_BUFFER (1u << 22)
#endif
#endif

#if !defined(USE_TERRAIN_PAGING) || (defined(USE_TERRAIN_TREES) && !defined(USE_TERRAIN_TREES_PAGING))
#define USE_TERRAIN_CACHE
#endif

#if defined(USE_TERRAIN_TREES) && !defined(USE_TERRAIN_TREES_PAGING)
#define USE_TERRAIN_TREES_OGRE
#endif

// Decompressed point of terrain
struct OriginalPoint
{
	float x, y, z;
#ifdef USE_TERRAIN_NORMALS
	float normal_x, normal_y, normal_z;
#endif
};
// All points of terrain's sector
typedef std::vector<OriginalPoint> OriginalPoints;

// Selects a subset of original sector's points for each Ogre::SubMesh.
// Performs old->new and reverse indices translation.
class Expander
{
public:
	Expander(float* fdata, size_t vertex_size, IndexType* idata, OriginalPoints& original_points, unsigned long* ref, size_t total_number_of_indices)
		: fdata(fdata), vertex_size(vertex_size), idata(idata), original_points(original_points), number_of_points(0), ref(ref), total_number_of_indices(total_number_of_indices)
	{
		std::fill(ref, ref + total_number_of_indices, NOVALUE);
	}
 
	IndexType get_number_of_points(void) const
	{
		return number_of_points;
	}

private:
	IndexType point_ref(unsigned short index)
	{
		unsigned long& value = ref[index];
		if (value != NOVALUE)
			return (IndexType)value;

		*(OriginalPoint*)fdata = original_points[index];
		fdata += vertex_size;

		value = number_of_points;
		return number_of_points++;
	}

public:

	template <typename PointRef>
	void indices_fan(PointRef* refs, unsigned number_of_points)
	{
		IndexType first = point_ref(refs++->point);
		IndexType next = point_ref(refs++->point);
		for (unsigned i = 2; i < number_of_points; i++)
		{
			*idata++ = first;
			*idata++ = next;
			*idata++ = next = point_ref(refs++->point);
		}
	}
	template <typename PointRef>
	void indices_strip(PointRef* refs, unsigned number_of_points)
	{
		IndexType one = point_ref(refs++->point);
		IndexType two = point_ref(refs++->point);
		for (unsigned i = 2; i < number_of_points; i++)
		{
			*idata++ = one;
			*idata++ = two;
			*idata++ = (i & 1 ? two : one) = point_ref(refs++->point);
		}
	}

	typedef std::vector<unsigned> UNREF;
	static const unsigned NOUNREF = ~0u;
	void make_unref(UNREF& unref)
	{
		std::fill(unref.begin(), unref.end(), NOUNREF);
		for (unsigned i = 0; i < total_number_of_indices; i++)
		{
			unsigned ref_index = ref[i];
			if (ref_index != NOVALUE)
			{
				assert(unref[ref_index] == NOUNREF);
				unref[ref[i]] = i;
			}
		}
	}

private:
	float* fdata;
	size_t vertex_size;
	IndexType* idata;
	const OriginalPoints& original_points;
	IndexType number_of_points;
	static const unsigned long NOVALUE = ~0ul;
	unsigned long* ref;
	unsigned total_number_of_indices;
};

// Converts EE terrain to Ogre::Meshes
class TerrainConverter
{
public:
	~TerrainConverter(void)
	{
		for (int z = 0; z < terrain_3d_map_height; z++)
			for (int x = 0; x < terrain_3d_map_width; x++)
				destroy_sector(x, z);
	}

	// Convert materials
	void convert_types(void)
	{
		unsigned material = MaterialHolder::get_index();
		for (terrain_types i = TERRAIN_TYPE_INVALID + 1; i != TERRAIN_TYPE_LAST; i++)
		{
			SurfDesc& sd = sda[i];
			{
				struct FuncCaps
				{
					void (*func)(int);
					SurfCaps caps;
				};
#ifdef USE_TERRAIN_TEXTURES
#define TTRUE true
#else
#define TTRUE false
#endif
#ifdef USE_TERRAIN_VERTEX_COLOURS
#define VTRUE true
#else
#define VTRUE false
#endif
#define MT_XZ 0, 2
#define MT_XY 0, 1
#define MT_ZY 2, 1
				static const FuncCaps funcs[] =
				{
					{ terrain_unclipped,                          { false, VTRUE, MT_XZ } },
					{ terrain_texture_x_unclipped,                { false, VTRUE, MT_ZY } },
					{ terrain_texture_z_unclipped,                { false, VTRUE, MT_XY } },
					{ terrain_colour_unclipped,                   { false, false, MT_XZ } },
					{ terrain_texture_x_colour_unclipped,         { false, false, MT_ZY } },
					{ terrain_texture_z_colour_unclipped,         { false, false, MT_XY } },
					{ terrain_twopass_unclipped,                  { TTRUE, VTRUE, MT_XZ } },
					{ terrain_twopass_texture_x_unclipped,        { TTRUE, VTRUE, MT_ZY } },
					{ terrain_twopass_texture_z_unclipped,        { TTRUE, VTRUE, MT_XY } },
					{ terrain_twopass_colour_unclipped,           { TTRUE, false, MT_XZ } },
					{ terrain_twopass_texture_x_colour_unclipped, { TTRUE, false, MT_ZY } },
					{ terrain_twopass_texture_z_colour_unclipped, { TTRUE, false, MT_XY } },
				};
#undef MT_XZ
#undef MT_XY
#undef MT_ZY
#undef TTRUE
#undef VTRUE

				sd.caps = NULL;
				void (*f)(int) = terrain_type_information[i].render_word_unclipped;
				if (!f)
					continue;

				for (int i = 0; i < sizeof(funcs) / sizeof(*funcs); i++)
				{
					if (funcs[i].func == f)
					{
						sd.caps = &funcs[i].caps;
						break;
					}
				}
				assert(sd.caps);
			}
#ifdef USE_TERRAIN_NORMALS
			static const bool normals = true;
#else
			static const bool normals = false;
#endif
			sd.vd = VertexDescription(normals, sd.caps->vertex_colour, false, true, sd.caps->texture2);

			// TODO: Improve materials support

			MaterialPtr mat = MaterialManager::getSingleton().create(MaterialName(MaterialHolder::get_index()), ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

			Pass* pass = mat->getTechnique(0)->getPass(0);
			//pass->setCullingMode(CULL_NONE);

			sd.colour = ColourValue(terrain_type_information[i].red / 255.0f, terrain_type_information[i].green / 255.0f, terrain_type_information[i].blue / 255.0f, terrain_type_information[i].transparent / 255.0f);
			TextureUnitState* tus = pass->createTextureUnitState();
#ifdef USE_TERRAIN_TEXTURES
			tus->setTextureName(TextureName((int)terrain_type_information[i].texture, false));
			tus->setTextureAddressingMode(TextureUnitState::TAM_WRAP, TextureUnitState::TAM_WRAP, TextureUnitState::TAM_CLAMP);
			if (sd.caps->texture2)
			{
				//pass->setSceneBlending(SBT_TRANSPARENT_ALPHA);
				pass->setSceneBlending(SBT_MODULATE);

				tus = pass->createTextureUnitState();
				//tus->setColourOperation(LBO_MODULATE);
				tus->setTextureName(TextureName((int)terrain_type_information[i].texture2, false));
				tus->setTextureAddressingMode(TextureUnitState::TAM_WRAP, TextureUnitState::TAM_WRAP, TextureUnitState::TAM_CLAMP);
			}
			else
#endif
			{
				if (sd.caps->vertex_colour)
				{
					pass->setVertexColourTracking(pass->getVertexColourTracking() | TVC_AMBIENT);
				}
				else
				{
#ifdef USE_TERRAIN_TEXTURES
					tus->setColourOperationEx(LBX_MODULATE, LBS_MANUAL, LBS_TEXTURE, sd.colour);
#else
					tus->setColourOperationEx(LBX_SOURCE1, LBS_MANUAL, LBS_CURRENT, sd.colour);
#endif
				}
			}

			sd.material = mat;
		}

		terrain_materials.reset(new MaterialHolder(material));
	}

	// Convert geometry
	void convert_sector(int x, int z, Geometry* terrain_geometry)
	{
		TERRAIN_3D_SECTOR& s = terrain_sectors[z][x];

		size_t total_number_of_indices = 0;
		for (int i = 0; i < s.number_of_polygons; i++)
		{
			total_number_of_indices += (s.polygons[i].number_of_points - 2) * 3;
		}

		assert(s.number_of_points);
		assert(s.number_of_polygons);
		assert(total_number_of_indices);

		std::vector<Ogre::Real> points;
		std::vector<unsigned long> ref(total_number_of_indices);
		std::vector<IndexType> indices(total_number_of_indices);

		OriginalPoints original_points(s.number_of_points);
		{
			// Unpack points and normals
#ifdef USE_TERRAIN_NORMALS
			const struct TERRAIN_3D_NORMAL_INDEX* normal_indices = s.normal_changes;
#endif
			for (int i = 0; i < s.number_of_points; i++)
			{
				OriginalPoint& p = original_points[i];
				p.x = s.points_xz[i].x * terrain_3d_xz_scale;
				p.y = s.points_y[i].y * terrain_3d_map_scaled_height_difference + terrain_3d_map_minimum_height;
				p.z = s.points_xz[i].z * terrain_3d_xz_scale;
#ifdef USE_TERRAIN_NORMALS
				if (s.points_y[i].normal_change)
					normal_indices++;
				const vec3d& n = terrain_3d_point_normals[normal_indices->index];
				p.normal_x = n.x;
				p.normal_y = n.y;
				p.normal_z = n.z;
#endif
			}
		}

		TerrainObject terrain_object(z, x);
		MeshPtr mesh = MeshManager::getSingleton().createManual(terrain_object, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

		const TERRAIN_3D_SURFACE* surface = s.surface_changes;

		std::auto_ptr<Expander> expander;

		IndexType offset = 0;
		IndexType number_of_indices = 0;
		for (int i = 0; i <= s.number_of_polygons; i++)
		{
			if (!i || i == s.number_of_polygons || s.polygons[i].surface_change)
			{
				if (i)
				{
					// Finished with the current surface

					IndexType number_of_points = expander->get_number_of_points();
					assert(number_of_points);
					SurfDesc& sd = sda[surface->surface_id];
					{
						// Put additional information into Vertices
						float* fdata = &points[0];
#ifdef USE_TERRAIN_TEXTURES
						float ts[3] = { terrain_type_information[surface->surface_id].xz_texture_scale, terrain_type_information[surface->surface_id].y_texture_scale, terrain_type_information[surface->surface_id].xz_texture_scale };
						float ts2[3] = { terrain_type_information[surface->surface_id].xz_texture_scale2, terrain_type_information[surface->surface_id].y_texture_scale2, terrain_type_information[surface->surface_id].xz_texture_scale2 };
						unsigned u = sd.caps->u;
						unsigned v = sd.caps->v;
						float texture_scale_u = ts[u];
						float texture_scale_v = ts[v];
						float texture_scale2_u = ts2[u];
						float texture_scale2_v = ts2[v];
						unsigned texture = sd.vd.texture1_offset;
						unsigned texture2 = sd.vd.texture2_offset;
#endif
#ifdef USE_TERRAIN_VERTEX_COLOURS
						unsigned vertex_colour = sd.vd.diffuse_offset;
						Expander::UNREF unref;
						if (vertex_colour)
						{
							unref.resize(s.number_of_points);
							expander->make_unref(unref);
						}
#endif
						for (int i = 0; i < number_of_points; i++)
						{
#ifdef USE_TERRAIN_VERTEX_COLOURS
							if (vertex_colour)
							{
								unsigned real_index = unref[i];
								assert(real_index != Expander::NOUNREF);
								TERRAIN_3D_COLOUR& c = s.point_colours[s.colour_indices[real_index].index];
								rgb_colour* pc = (rgb_colour*)&fdata[vertex_colour];
								pc->red = c.red;
								pc->green = c.green;
								pc->blue = c.blue;
								pc->alpha = 255;
							}
#endif
#ifdef USE_TERRAIN_TEXTURES
							fdata[texture + 0] = fdata[u] * texture_scale_u;
							fdata[texture + 1] = fdata[v] * texture_scale_v;
							if (texture2)
							{
								fdata[texture2 + 0] = fdata[u] * texture_scale2_u;
								fdata[texture2 + 1] = fdata[v] * texture_scale2_v;
							}
#endif
							fdata += sd.vd.vertex_size;
						}
					}


					// Create submesh

					Geometry::BUF buf;
					terrain_geometry->get_buf(sd.vd, number_of_points, number_of_indices, buf);
					std::copy(points.begin(), points.begin() + number_of_points * sd.vd.vertex_size, buf.fdata);
					std::copy(indices.begin(), indices.begin() + number_of_indices, buf.idata);

					SubMesh* sm = mesh->createSubMesh();
					sm->useSharedVertices = false;
					sm->operationType = RenderOperation::OT_TRIANGLE_LIST;
					sm->vertexData = OGRE_NEW VertexData(buf.vbuf.vd, buf.vbuf.vbb);
					sm->vertexData->vertexStart = buf.vbuf.offset;
					sm->vertexData->vertexCount = number_of_points;
					sm->indexData->indexBuffer = buf.ibuf.hib;
					sm->indexData->indexStart = buf.ibuf.offset;
					sm->indexData->indexCount = number_of_indices;

					sm->setMaterialName(sd.material->getName());

					number_of_indices = 0;

					if (i == s.number_of_polygons)
					{
						break;
					}
				}


				// Proceed with the next surface

				if (s.polygons[i].surface_change)
				{
					surface++;
				}

				SurfDesc& sd = sda[surface->surface_id];
				points.resize(s.number_of_points * sd.vd.vertex_size);
				expander.reset(new Expander(&points[0], sd.vd.vertex_size, &indices[0], original_points, &ref[0], total_number_of_indices));
			}


			// Expand geometry

			if (terrain_type_information[surface->surface_id].polygon_type == POLYGON_TYPE_FAN)
			{
				s.number_of_points < 257 ? expander->indices_fan(s.point_byte_references + offset, s.polygons[i].number_of_points) : expander->indices_fan(s.point_word_references + offset, s.polygons[i].number_of_points);
			}
			else
			{
				s.number_of_points < 257 ? expander->indices_strip(s.point_byte_references + offset, s.polygons[i].number_of_points) : expander->indices_strip(s.point_word_references + offset, s.polygons[i].number_of_points);
			}

			offset += s.polygons[i].number_of_points;
			number_of_indices += (s.polygons[i].number_of_points - 2) * 3;
		}

		static const float radius = TERRAIN_3D_SECTOR_SIDE_LENGTH / 2.0f;
		mesh->_setBounds(AxisAlignedBox(Vector3(-radius, terrain_3d_map_minimum_height, -radius), Vector3(radius, terrain_3d_map_maximum_height, radius)), false);
		mesh->_setBoundingSphereRadius(exp(log(terrain_3d_map_maximum_height * terrain_3d_map_maximum_height + 2.0f * radius * radius) / 2.0f));
		mesh->load();
	}

	void destroy_sector(int x, int z)
	{
		TerrainObject terrain_object(z, x);
		MeshManager::getSingleton().unload(terrain_object);
		MeshManager::getSingleton().remove(terrain_object);
	}

private:
	struct SurfCaps
	{
		bool texture2;
		bool vertex_colour;
		unsigned u;
		unsigned v;
	};

	struct SurfDesc
	{
		const SurfCaps* caps;
		VertexDescription vd;
		ColourValue colour;
		MaterialPtr material;
	};

	SurfDesc sda[TERRAIN_TYPE_LAST];

	MaterialHolderPtr terrain_materials;
};
typedef std::auto_ptr<TerrainConverter> TerrainConverterPtr;

static TerrainConverterPtr terrain_converter;


#ifdef USE_TERRAIN_PAGING
class TerrainLoader : public PageLoader
{
public:
	TerrainLoader(SceneManager* sman)
		: SceneMgr(sman)
	{
	}

	~TerrainLoader(void)
	{
		clear();
	}

	void loadPage(PageInfo& page)
	{
		clear();
		int x = page.xIndex, z = page.zIndex;
		if (x < 0 || x >= terrain_3d_map_width || z < 0 || z >= terrain_3d_map_height)
		{
			page.userData = 0;
			return;
		}

		SectorInfo* si = new SectorInfo(x, z);
		terrain_converter->convert_sector(x, z, &si->terrain_geometry);
		si->terrain_geometry.flush();
		si->ent = SceneMgr->createEntity(TerrainObject(z, x));
		addEntity(si->ent, page.centerPoint, Quaternion::IDENTITY);
		page.userData = si;
	}

	void unloadPage(PageInfo& page)
	{
		SectorInfo* si = static_cast<SectorInfo*>(page.userData);
		if (si)
			sis.push_back(si);
	}

private:
	struct SectorInfo
	{
		SectorInfo(int x, int z)
			: x(x), z(z), terrain_geometry(0, 0)
		{
		}

		int x, z;
		Geometry terrain_geometry;
		Entity* ent;
	};

	void clear(void)
	{
		while (!sis.empty())
		{
			SectorInfo* si = sis.front();
			sis.pop_front();
			SceneMgr->destroyEntity(si->ent);
			terrain_converter->destroy_sector(si->x, si->z);
			delete si;
		}
	}

	SceneManager* SceneMgr;
	std::list<SectorInfo*> sis;
};
#endif

#ifdef USE_TERRAIN_TREES
#ifdef USE_TERRAIN_TREES_PAGING
class TreesLoader : public PageLoader
{
public:
	TreesLoader(Entity* tree_ent)
		: tree_ent(tree_ent)
	{
	}

	void loadPage(PageInfo& page)
	{
		int x = page.xIndex, z = page.zIndex;
		if (x < 0 || x >= terrain_3d_map_width || z < 0 || z >= terrain_3d_map_height)
			return;

		for (int i = 0; i < terrain_tree_sectors[z][x].number_of_trees; i++)
		{
			const terrain_3d_tree_data& tree = terrain_tree_sectors[z][x].trees[i];
			Vector3 tree_position(tree.x * TERRAIN_3D_XZ_SCALE / 2, tree.y * terrain_3d_map_scaled_height_difference / 2 + terrain_3d_map_minimum_height, tree.z * TERRAIN_3D_XZ_SCALE / 2);
			float scale = get_terrain_3d_tree_scale((terrain_3d_tree_data*)&tree);
			addEntity(tree_ent, page.centerPoint + tree_position, Quaternion::IDENTITY, Vector3(scale, scale, scale));
		}
	}

private:
	Entity* tree_ent;
};
#endif
#endif

// Cache of terrain sector
// Contains currently vissible and recently invisible sectors
class TerrainCache
{
public:
	TerrainCache(Camera* camera, SceneManager* sman)
		:
#ifdef USE_TERRAIN_CACHE
		camera(camera),
		cur_x(-1000), cur_z(-1000),
#ifdef USE_TERRAIN_CACHE_SIZE
		lru_size(0),
#endif
#endif

#ifdef USE_TERRAIN_PAGING
		terrain(new PagedGeometry(camera, TERRAIN_3D_SECTOR_SIDE_LENGTH)), terrain_loader(new TerrainLoader(sman)),
#else
#ifndef USE_TERRAIN_STATIC_GEOMETRY
		terrain_node(sman->getRootSceneNode()->createChildSceneNode()),
#endif
#endif

#ifdef USE_TERRAIN_TREES
		tree_ent(sman->createEntity(TerrainTreeObject())),
#ifdef USE_TERRAIN_TREES_PAGING
		trees(new PagedGeometry(camera, TERRAIN_3D_SECTOR_SIDE_LENGTH)), trees_loader(new TreesLoader(tree_ent)),
#endif
#endif

		SceneMgr(sman)
	{
#ifdef USE_TERRAIN_PAGING
#ifdef USE_TERRAIN_VISIBILITY
		terrain->addDetailLevel<BatchPage>(USE_TERRAIN_VISIBILITY * TERRAIN_3D_SECTOR_SIDE_LENGTH);
#else
		terrain->addDetailLevel<BatchPage>(camera->getFarClipDistance());
#endif
		terrain->setPageLoader(terrain_loader.get());
#endif

#ifdef USE_TERRAIN_TREES
#ifdef USE_TERRAIN_TREES_PAGING
#ifdef USE_TERRAIN_TREES_VISIBILITY
		trees->addDetailLevel<BatchPage>(USE_TERRAIN_TREES_VISIBILITY * TERRAIN_3D_SECTOR_SIDE_LENGTH);
#else
#ifdef USE_TERRAIN_VISIBILITY
		trees->addDetailLevel<BatchPage>(USE_TERRAIN_VISIBILITY * TERRAIN_3D_SECTOR_SIDE_LENGTH);
#else
		trees->addDetailLevel<BatchPage>(camera->getFarClipDistance());
#endif
#endif
		trees->setPageLoader(trees_loader.get());
#endif
#endif
	}

	~TerrainCache()
	{
#ifdef USE_TERRAIN_CACHE
		while (!cache.empty())
			delete_sector(cache.begin());
#endif
#ifndef USE_TERRAIN_PAGING
#ifndef USE_TERRAIN_STATIC_GEOMETRY
		assert(!terrain_node->numChildren());
		terrain_node->getParent()->removeChild(terrain_node);
#endif
#endif
#ifdef USE_TERRAIN_TREES
		SceneMgr->destroyEntity(tree_ent);
#endif
	}

#ifdef USE_TERRAIN_CACHE
	// Construct sector as a node or static geometry.
	// Construct trees for sector if required.
	void convert_sector(int x, int z)
	{
		Sector sector;

#ifdef USE_TERRAIN_VISIBILITY
		sector.visible = true;
#ifdef USE_TERRAIN_CACHE_SIZE
		sector.lru_iterator = lru.end();
#endif
#endif

#ifndef USE_TERRAIN_PAGING
		Vector3 position((float)(x * TERRAIN_3D_SECTOR_SIDE_LENGTH + TERRAIN_3D_SECTOR_SIDE_LENGTH / 2), 0.0f, (float)(z * TERRAIN_3D_SECTOR_SIDE_LENGTH + TERRAIN_3D_SECTOR_SIDE_LENGTH / 2));
		{
#ifdef USE_TERRAIN_DRAW
#ifdef USE_TERRAIN_CONVERT_ON_FLY
			Geometry terrain_geometry(0, 0);
			terrain_converter->convert_sector(x, z, &terrain_geometry);
			terrain_geometry.flush();
#endif
			Entity* ent = SceneMgr->createEntity(TerrainObject(z, x));
#ifdef USE_TERRAIN_STATIC_GEOMETRY
			StaticGeometry* geom = SceneMgr->createStaticGeometry(TerrainStaticGeometry(z, x));
			geom->addEntity(ent, position);
			geom->build();
			SceneMgr->destroyEntity(ent);
			sector.sector = geom;
#ifdef USE_TERRAIN_CONVERT_ON_FLY
			terrain_converter->destroy_sector(x, z);
#endif
#else
			SceneNode* node = terrain_node->createChildSceneNode(position);
			node->attachObject(ent);
			sector.sector = node;
#endif
#endif
		}
#endif

#ifdef USE_TERRAIN_TREES_OGRE
		{
#ifdef USE_TERRAIN_TREES_INSTANCED
			InstancedGeometry* geom = SceneMgr->createInstancedGeometry(TerrainTree(z, x));
#else
			StaticGeometry* geom = SceneMgr->createStaticGeometry(TerrainTree(z, x));
#endif
			geom->setRegionDimensions(Vector3(2 * TERRAIN_3D_SECTOR_SIDE_LENGTH, 8192, 2 * TERRAIN_3D_SECTOR_SIDE_LENGTH));
			geom->setOrigin(position);
			for (int i = 0; i < terrain_tree_sectors[z][x].number_of_trees; i++)
			{
				const terrain_3d_tree_data& tree = terrain_tree_sectors[z][x].trees[i];
				Vector3 tree_position(tree.x * TERRAIN_3D_XZ_SCALE / 2, tree.y * terrain_3d_map_scaled_height_difference / 2 + terrain_3d_map_minimum_height, tree.z * TERRAIN_3D_XZ_SCALE / 2);
				float scale = get_terrain_3d_tree_scale((terrain_3d_tree_data*)&tree);
				geom->addEntity(tree_ent, position + tree_position, Quaternion::IDENTITY, Vector3(scale, scale, scale));
			}
			geom->build();

			sector.trees = geom;
		}
#endif

		cache.insert(Cache::value_type(Coord(z, x), sector));
	}
#endif

	// Make some sectors to be visible, some - to be invisible
	void update(void)
	{
#ifdef USE_TERRAIN_PAGING
		terrain->update();
#endif
#ifdef USE_TERRAIN_TREES
#ifdef USE_TERRAIN_TREES_PAGING
		trees->update();
#endif
#endif

#ifdef USE_TERRAIN_CACHE
#ifdef USE_TERRAIN_VISIBILITY
		const Vector3& pos = camera->getPosition();
		int x_sector = (int)floor(pos.x / TERRAIN_3D_SECTOR_SIDE_LENGTH);
		int z_sector = (int)floor(pos.z / TERRAIN_3D_SECTOR_SIDE_LENGTH);

		// Current sector is not changed, no sectors change visibility
		if (x_sector == cur_x && z_sector == cur_z)
			return;

		// Set some sectors to be invisible.
		// Remove old if lru is full.
		for (int z = std::max(0, cur_z - USE_TERRAIN_VISIBILITY); z <= std::min(terrain_3d_map_height - 1, cur_z + USE_TERRAIN_VISIBILITY); z++)
		{
			const bool z_visibility = z >= z_sector - USE_TERRAIN_VISIBILITY && z <= z_sector + USE_TERRAIN_VISIBILITY;
			for (int x = std::max(0, cur_x - USE_TERRAIN_VISIBILITY); x <= std::min(terrain_3d_map_width - 1, cur_x + USE_TERRAIN_VISIBILITY); x++)
			{
				const bool x_visibility = x >= x_sector - USE_TERRAIN_VISIBILITY && x <= x_sector + USE_TERRAIN_VISIBILITY;
				const bool visibility = z_visibility && x_visibility;

				if (visibility)
					continue;

				Cache::iterator itor = cache.find(Coord(z, x));
				if (itor == cache.end())
					continue;

				Sector& sector = itor->second;

				if (!sector.visible)
					continue;

				sector.visible = false;
#ifndef USE_TERRAIN_PAGING
#ifdef USE_TERRAIN_DRAW
				sector.sector->setVisible(false);
#endif
#endif
#ifdef USE_TERRAIN_TREES_OGRE
				sector.trees->setVisible(false);
#endif

#ifdef USE_TERRAIN_CACHE_SIZE
				if (lru_size >= USE_TERRAIN_CACHE_SIZE)
				{
					if (lru_size)
					{
						delete_sector(lru.front());
						lru.splice(lru.end(), lru, lru.begin());
						lru.back() = itor;
					}
					else
					{
						delete_sector(itor);
					}
				}
				else
				{
					lru.push_back(itor);
					lru_size++;
				}
				sector.lru_iterator = lru.end();
				--sector.lru_iterator;
#endif
			}
		}

		cur_x = x_sector;
		cur_z = z_sector;

		// Set some sectors to be visible.
		// Convert some sectors if required.
		for (int z = std::max(0, cur_z - USE_TERRAIN_VISIBILITY); z <= std::min(terrain_3d_map_height - 1, cur_z + USE_TERRAIN_VISIBILITY); z++)
		{
			for (int x = std::max(0, cur_x - USE_TERRAIN_VISIBILITY); x <= std::min(terrain_3d_map_width - 1, cur_x + USE_TERRAIN_VISIBILITY); x++)
			{
				Cache::iterator itor = cache.find(Coord(z, x));
				if (itor == cache.end())
				{
					convert_sector(x, z);
				}
				else
				{
					Sector& sector = itor->second;
					if (!sector.visible)
					{
						sector.visible = true;
#ifdef USE_TERRAIN_CACHE_SIZE
						lru.erase(sector.lru_iterator);
						lru_size--;
						sector.lru_iterator = lru.end();
#endif
#ifndef USE_TERRAIN_PAGING
#ifdef USE_TERRAIN_DRAW
						sector.sector->setVisible(true);
#endif
#endif
#ifdef USE_TERRAIN_TREES_OGRE
						sector.trees->setVisible(true);
#endif
					}
				}
			}
		}
#endif
#endif
	}

private:
#ifdef USE_TERRAIN_CACHE
	typedef std::pair<int, int> Coord;
	struct Sector;
	typedef std::map<Coord, Sector> Cache;
#ifdef USE_TERRAIN_VISIBILITY
#ifdef USE_TERRAIN_CACHE_SIZE
	typedef std::list<Cache::iterator> LRU;
#endif
#endif
	struct Sector
	{
#ifdef USE_TERRAIN_VISIBILITY
		bool visible;
#ifdef USE_TERRAIN_CACHE_SIZE
		LRU::iterator lru_iterator;
#endif
#endif

#ifndef USE_TERRAIN_PAGING
#ifdef USE_TERRAIN_DRAW
#ifdef USE_TERRAIN_STATIC_GEOMETRY
		StaticGeometry* sector;
#else
		SceneNode* sector;
#endif
#endif
#endif

#ifdef USE_TERRAIN_TREES_OGRE
#ifdef USE_TERRAIN_TREES_INSTANCED
		InstancedGeometry* trees;
#else
		StaticGeometry* trees;
#endif
#endif
	};

	// Destroy any geometry data linked with the sector
	void delete_sector(Cache::iterator itor)
	{
		Sector& sector = itor->second;

#ifndef USE_TERRAIN_PAGING
#ifdef USE_TERRAIN_DRAW
#ifdef USE_TERRAIN_STATIC_GEOMETRY
		SceneMgr->destroyStaticGeometry(sector.sector);
#else
		terrain_node->removeChild(sector.sector);
#endif
#endif
#endif

#ifdef USE_TERRAIN_TREES_OGRE
#ifdef USE_TERRAIN_TREES_INSTANCED
		SceneMgr->destroyInstancedGeometry(sector.trees);
#else
		SceneMgr->destroyStaticGeometry(sector.trees);
#endif
#endif

		cache.erase(itor);
	}
#endif


#ifdef USE_TERRAIN_CACHE
	Cache cache;
	Camera* camera;
	int cur_x, cur_z;
#ifdef USE_TERRAIN_CACHE_SIZE
	LRU lru;
	size_t lru_size;
#endif
#endif

#ifdef USE_TERRAIN_PAGING
	std::auto_ptr<PagedGeometry> terrain;
	std::auto_ptr<TerrainLoader> terrain_loader;
#else
#ifndef USE_TERRAIN_STATIC_GEOMETRY
	SceneNode* terrain_node;
#endif
#endif

#ifdef USE_TERRAIN_TREES
	Entity* tree_ent;
#ifdef USE_TERRAIN_TREES_PAGING
	std::auto_ptr<PagedGeometry> trees;
	std::auto_ptr<TreesLoader> trees_loader;
#endif
#endif

	SceneManager* SceneMgr;
};
typedef std::auto_ptr<TerrainCache> TerrainCachePtr;


// Geometry information for current terrain
#ifndef USE_TERRAIN_CONVERT_ON_FLY
static GeometryPtr terrain_geometry;
#endif

#ifdef USE_TERRAIN_TREES
static GeometryPtr tree_geometry;
static MaterialHolderPtr tree_materials;
#endif

static TerrainCachePtr terrain_cache;


#ifdef USE_TERRAIN_LIMIT_SIZE
static int old_terrain_3d_map_height, old_terrain_3d_map_width;
#endif

// Place terrain into the scene
void ogre_terrain_init(Camera* camera, SceneManager* mgr)
{
#ifdef USE_TERRAIN_LIMIT_SIZE
	old_terrain_3d_map_height = terrain_3d_map_height;
	old_terrain_3d_map_width = terrain_3d_map_width;
	terrain_3d_map_height = std::min(terrain_3d_map_height, USE_TERRAIN_LIMIT_SIZE);
	terrain_3d_map_width = std::min(terrain_3d_map_width, USE_TERRAIN_LIMIT_SIZE);
#endif

#ifndef USE_TERRAIN_CONVERT_ON_FLY
	assert(!terrain_geometry.get());
#endif
	assert(!terrain_converter.get());
	assert(!terrain_cache.get());

#ifdef USE_TERRAIN_VISIBILITY
	mgr->setFog(FOG_LINEAR, ColourValue(0.18f, 0.77f, 0.87f), 0, USE_TERRAIN_VISIBILITY * TERRAIN_3D_SECTOR_SIDE_LENGTH / 2, USE_TERRAIN_VISIBILITY * TERRAIN_3D_SECTOR_SIDE_LENGTH);
#endif

	terrain_converter.reset(new TerrainConverter);

	terrain_converter->convert_types();

#ifndef USE_TERRAIN_CONVERT_ON_FLY
	terrain_geometry.reset(new Geometry(TERRAIN_POINTS_PER_VERTEX_BUFFER, TERRAIN_POINTS_PER_INDEX_BUFFER));
	for (int z = 0; z < terrain_3d_map_height; z++)
		for (int x = 0; x < terrain_3d_map_width; x++)
			terrain_converter->convert_sector(x, z, terrain_geometry.get());
	terrain_geometry->flush();
	//terrain_geometry->statistics("TG_STAT.TXT");
#endif

	terrain_cache.reset(new TerrainCache(camera, mgr));

#if !defined(USE_TERRAIN_VISIBILITY) && defined(USE_TERRAIN_CACHE)
	for (int z = 0; z < terrain_3d_map_height; z++)
		for (int x = 0; x < terrain_3d_map_width; x++)
			terrain_cache->convert_sector(x, z);
#endif
}

// Clear terrain data
void ogre_terrain_clear(void)
{
	terrain_cache.reset(0);

	terrain_converter.reset(0);

#ifndef USE_TERRAIN_CONVERT_ON_FLY
	terrain_geometry.reset(0);
#endif

#ifdef USE_TERRAIN_LIMIT_SIZE
	terrain_3d_map_height = old_terrain_3d_map_height;
	terrain_3d_map_width = old_terrain_3d_map_width;
#endif
}

// Periodic update to reflect visibility changes
void ogre_terrain_update(void)
{
	terrain_cache->update();
}

#ifdef USE_TERRAIN_TREES
// Use specified object as a tree
void ogre_terrain_tree(const OBJECT_3D& o)
{
	assert(!tree_geometry.get() && !tree_materials.get());
	tree_geometry.reset(new Geometry(0, 0));
	unsigned material = MaterialHolder::get_index();
	ogre_objects_convert(o, MeshManager::getSingleton().createManual(TerrainTreeObject(), ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME), tree_geometry.get());
	tree_geometry->flush();
	tree_materials.reset(new MaterialHolder(material));
}

// Clear tree object
void ogre_terrain_tree_clear(void)
{
	TerrainTreeObject terrain_tree_object;
	MeshManager::getSingleton().unload(terrain_tree_object);
	MeshManager::getSingleton().remove(terrain_tree_object);

	tree_geometry.reset(0);
	tree_materials.reset(0);
}
#endif
#endif
