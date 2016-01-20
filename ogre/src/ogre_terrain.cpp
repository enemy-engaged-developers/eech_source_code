#include "ogre_int.hpp"

namespace
{
	struct OgreTerrainInit ogre_terrain;

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

	void get_vector(vec3d& v, float heading, float pitch)
	{
		float cp = cos(pitch);
		v.x = cp * sin(heading);
		v.y = sin(pitch);
		v.z = cp * cos(heading);
	}

	struct Normals : private Uncopyable
	{
		Normals()
		{
			int int_heading, int_pitch, count;
			float heading, pitch;

			count = 0;
			for (int_pitch = 0; int_pitch < 90; int_pitch += 9)
			{
				pitch = (int_pitch / 90.0f) *(M_PI / 2);
				for (int_heading = 0; int_heading < 360; int_heading += 15)
				{
					heading = (int_heading / 360.0f) * (M_PI * 2);
					get_vector(point_normals[count++], heading, pitch);
				}
			}

			get_vector(point_normals[count++], 0, M_PI / 2);

			int_pitch = -45;
			pitch = (int_pitch / 90.0f) * (M_PI / 2);
			for (int_heading = 0; int_heading < 360; int_heading += 30)
			{
				heading = (int_heading / 360.0f) * (M_PI * 2);
				get_vector(point_normals[count++], heading, pitch);
			}

			get_vector(point_normals[count], 0, -M_PI / 2);
		}

		vec3d point_normals[256];
	};

	Normals normals;

	// Selects a subset of original sector's points for each Ogre::SubMesh.
	// Performs old->new and reverse indices translation.
	class Expander : private Uncopyable
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

#ifdef USE_TERRAIN_VERTEX_COLOURS
		typedef std::vector<unsigned> INVREF;
		static const unsigned NOINVREF = ~0u;
		void make_invref(INVREF& invref)
		{
			std::fill(invref.begin(), invref.end(), NOINVREF);
			for (unsigned i = 0; i < total_number_of_indices; i++)
			{
				unsigned ref_index = ref[i];
				if (ref_index != NOVALUE)
				{
					assert(invref[ref_index] == NOINVREF);
					invref[ref[i]] = i;
				}
			}
		}
#endif

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
	class TerrainConverter : private Uncopyable
	{
	public:
		~TerrainConverter(void)
		{
			for (unsigned z = 0; z < ogre_terrain.sector_z_max; z++)
				for (unsigned x = 0; x < ogre_terrain.sector_x_max; x++)
					destroy_sector(x, z);
		}

		// Convert materials
		void convert_types(void)
		{
			unsigned material = ogre_index();
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
					void (*f)(int) = ogre_terrain.type_information[i].render_word_unclipped;
					if (!f)
						continue;

					for (size_t i = 0; i < sizeof(funcs) / sizeof(*funcs); i++)
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

				Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(MaterialName(ogre_index()), ogre_resource_group);
				mat->setCullingMode(Ogre::CULL_ANTICLOCKWISE);

				Ogre::Pass* pass = mat->getTechnique(0)->getPass(0);

				sd.colour = Ogre::ColourValue(ogre_terrain.type_information[i].red / 255.0f, ogre_terrain.type_information[i].green / 255.0f, ogre_terrain.type_information[i].blue / 255.0f, ogre_terrain.type_information[i].transparent / 255.0f);
				Ogre::TextureUnitState* tus = pass->createTextureUnitState();
#ifdef USE_TERRAIN_TEXTURES
				tus->setTextureName(TextureName(ogre_terrain.type_information[i].texture_index));
				tus->setTextureAddressingMode(Ogre::TextureUnitState::TAM_WRAP, Ogre::TextureUnitState::TAM_WRAP, Ogre::TextureUnitState::TAM_CLAMP);
				if (sd.caps->texture2)
				{
					//pass->setSceneBlending(SBT_TRANSPARENT_ALPHA);
					pass->setSceneBlending(Ogre::SBT_MODULATE);

					tus = pass->createTextureUnitState();
					//tus->setColourOperation(LBO_MODULATE);
					tus->setTextureName(TextureName(ogre_terrain.type_information[i].texture2_index));
					tus->setTextureAddressingMode(Ogre::TextureUnitState::TAM_WRAP, Ogre::TextureUnitState::TAM_WRAP, Ogre::TextureUnitState::TAM_CLAMP);
				}
				else
#endif
				{
					if (sd.caps->vertex_colour)
					{
						pass->setVertexColourTracking(pass->getVertexColourTracking() | Ogre::TVC_AMBIENT);
					}
					else
					{
#ifdef USE_TERRAIN_TEXTURES
						tus->setColourOperationEx(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, sd.colour);
#else
						tus->setColourOperationEx(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, sd.colour);
#endif
					}
				}

				sd.material = mat;
			}
		}

		// Convert geometry
		void convert_sector(unsigned x, unsigned z, Geometry* terrain_geometry)
		{
			//ogre_log(__FUNCTION__, "%u %u", x, z);

			TERRAIN_3D_SECTOR& s = ogre_terrain.sectors[z][x];

			size_t total_number_of_indices = 0;
			for (unsigned i = 0; i < s.number_of_polygons; i++)
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
				for (unsigned i = 0; i < s.number_of_points; i++)
				{
					OriginalPoint& p = original_points[i];
					p.x = s.points_xz[i].x * (float)TERRAIN_3D_XZ_SCALE;
					p.y = s.points_y[i].y * ogre_terrain.map_scaled_height_difference + ogre_terrain.map_minimum_height;
					p.z = s.points_xz[i].z * (float)TERRAIN_3D_XZ_SCALE;
#ifdef USE_TERRAIN_NORMALS
					if (s.points_y[i].normal_change)
						normal_indices++;
					const vec3d& n = normals.point_normals[normal_indices->index];
					p.normal_x = n.x;
					p.normal_y = n.y;
					p.normal_z = n.z;
					p.normal_z = -p.normal_z;
#endif
				}
			}

			TerrainObject terrain_object(z, x);
			Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(terrain_object, ogre_resource_group);

			const TERRAIN_3D_SURFACE* surface = s.surface_changes;

			std::auto_ptr<Expander> expander;

			IndexType offset = 0;
			IndexType number_of_indices = 0;
			for (unsigned i = 0; i <= s.number_of_polygons; i++)
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
							float ts[3] = { ogre_terrain.type_information[surface->surface_id].xz_texture_scale, ogre_terrain.type_information[surface->surface_id].y_texture_scale, ogre_terrain.type_information[surface->surface_id].xz_texture_scale };
							float ts2[3] = { ogre_terrain.type_information[surface->surface_id].xz_texture_scale2, ogre_terrain.type_information[surface->surface_id].y_texture_scale2, ogre_terrain.type_information[surface->surface_id].xz_texture_scale2 };
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
							Expander::INVREF invref;
							if (vertex_colour)
							{
								invref.resize(s.number_of_points);
								expander->make_invref(invref);
							}
#endif
							for (unsigned i = 0; i < number_of_points; i++)
							{
#ifdef USE_TERRAIN_VERTEX_COLOURS
								if (vertex_colour)
								{
									unsigned real_index = invref[i];
									assert(real_index != Expander::NOINVREF);
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
								fdata[2] = -fdata[2];
								fdata += sd.vd.vertex_size;
							}
						}


						// Create submesh

						Geometry::BUF buf;
						terrain_geometry->get_buf(sd.vd, number_of_points, number_of_indices, buf);
						std::copy(points.begin(), points.begin() + number_of_points * sd.vd.vertex_size, buf.fdata);
						std::copy(indices.begin(), indices.begin() + number_of_indices, buf.idata);

						Ogre::SubMesh* sm = mesh->createSubMesh();
						sm->useSharedVertices = false;
						sm->operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
						sm->vertexData = OGRE_NEW Ogre::VertexData(buf.vbuf.vd, buf.vbuf.vbb);
						sm->vertexData->vertexStart = buf.vbuf.offset;
						sm->vertexData->vertexCount = number_of_points;
						sm->indexData->indexBuffer = buf.ibuf.hib;
						sm->indexData->indexStart = buf.ibuf.offset;
						sm->indexData->indexCount = number_of_indices;

						sm->setMaterialName(sd.material->getName());

						number_of_indices = 0;

						if (i == s.number_of_polygons)
							break;
					}


					// Proceed with the next surface

					if (s.polygons[i].surface_change)
						surface++;

					SurfDesc& sd = sda[surface->surface_id];
					points.resize(s.number_of_points * sd.vd.vertex_size);
					expander.reset(new Expander(&points[0], sd.vd.vertex_size, &indices[0], original_points, &ref[0], total_number_of_indices));
				}


				// Expand geometry

				if (ogre_terrain.type_information[surface->surface_id].polygon_type == POLYGON_TYPE_FAN)
					s.number_of_points < 257 ? expander->indices_fan(s.point_byte_references + offset, s.polygons[i].number_of_points) : expander->indices_fan(s.point_word_references + offset, s.polygons[i].number_of_points);
				else
					s.number_of_points < 257 ? expander->indices_strip(s.point_byte_references + offset, s.polygons[i].number_of_points) : expander->indices_strip(s.point_word_references + offset, s.polygons[i].number_of_points);

				offset += s.polygons[i].number_of_points;
				number_of_indices += (s.polygons[i].number_of_points - 2) * 3;
			}

			static const float radius = TERRAIN_3D_SECTOR_SIDE_LENGTH / 2.0f;
			mesh->_setBounds(Ogre::AxisAlignedBox(Ogre::Vector3(-radius, ogre_terrain.map_minimum_height, -radius), Ogre::Vector3(radius, ogre_terrain.map_maximum_height, radius)), false);
			mesh->_setBoundingSphereRadius(exp(log(ogre_terrain.map_maximum_height * ogre_terrain.map_maximum_height + 2.0f * radius * radius) / 2.0f));
			mesh->load();
		}

		void destroy_sector(unsigned x, unsigned z)
		{
			//ogre_log(__FUNCTION__, "%u %u", x, z);

			TerrainObject terrain_object(z, x);
			Ogre::MeshManager::getSingleton().unload(terrain_object);
			Ogre::MeshManager::getSingleton().remove(terrain_object);
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
			Ogre::ColourValue colour;
			Ogre::MaterialPtr material;
		};

		SurfDesc sda[TERRAIN_TYPE_LAST];
	};
	typedef std::auto_ptr<TerrainConverter> TerrainConverterPtr;

	TerrainConverterPtr terrain_converter;


	typedef std::pair<unsigned, unsigned> Sector;

#ifdef USE_TERRAIN_OBJECTS
	class SectorObjects : private Uncopyable
	{
	public:
		SectorObjects()
		{
		}
		SectorObjects(const SectorObjects& so)
		{
			assert(so.objects.empty());
		}
		~SectorObjects()
		{
			for (Objects::iterator itor(objects.begin()); itor != objects.end(); ++itor)
				ogre_scene_destroy(*itor);
		}
		void append(struct OgreGameObjectScene* scene)
		{
			objects.push_back(scene);
		}
		void show()
		{
			Ogre::SceneNode* node = ogre_scene_manager->getRootSceneNode();
			for (Objects::iterator itor(objects.begin()); itor != objects.end(); ++itor)
				node->addChild(reinterpret_cast<Ogre::SceneNode*>((*itor)->root));
		}
		void hide()
		{
			Ogre::SceneNode* node = ogre_scene_manager->getRootSceneNode();
			for (Objects::iterator itor(objects.begin()); itor != objects.end(); ++itor)
				node->removeChild(reinterpret_cast<Ogre::SceneNode*>((*itor)->root));
		}

	private:
		typedef std::deque<OgreGameObjectScene*> Objects;
		Objects objects;
	};
	typedef std::map<Sector, SectorObjects> TerrainObjects;

	TerrainObjects terrain_objects;
#endif

#ifdef USE_TERRAIN_TREES
	GeometryPtr tree_geometry;
	Ogre::String tree_material;
	Ogre::InstanceManager* tree_manager;
#endif

	// Cache of terrain sector
	// Contains currently vissible and recently invisible sectors
	class TerrainCache : private Uncopyable
	{
	public:
		TerrainCache()
			:
#ifdef USE_TERRAIN_GROUP
				groups(0),
#else
				terrain_geometry(1 << 20, 1 << 21),
#endif
				terrain(0), cur_x(-1000), cur_z(-1000)
		{
#ifndef USE_TERRAIN_GROUP
			for (unsigned z = 0; z < ogre_terrain.sector_z_max; z++)
				for (unsigned x = 0; x < ogre_terrain.sector_x_max; x++)
					terrain_converter->convert_sector(x, z, &terrain_geometry);
			terrain_geometry.flush();
#endif
		}
		~TerrainCache()
		{
#ifdef USE_TERRAIN_GROUP
			terrain_clear();
			while (groups)
				destroy_group(groups);
#else
			terrain_clear();
			for (unsigned z = 0; z < ogre_terrain.sector_z_max; z++)
				for (unsigned x = 0; x < ogre_terrain.sector_x_max; x++)
					terrain_converter->destroy_sector(x, z);
#endif
		}
		void update(void)
		{
			const int v = USE_TERRAIN_VISIBILITY;

			Ogre::Vector3 pos = ogre_camera->getPosition();
			pos.z = -pos.z;
			int x_sector = (int)floor(pos.x / TERRAIN_3D_SECTOR_SIDE_LENGTH);
			int z_sector = (int)floor(pos.z / TERRAIN_3D_SECTOR_SIDE_LENGTH);

			// Current sector is not changed, no sectors change visibility
			if (x_sector == cur_x && z_sector == cur_z)
				return;

#ifdef USE_TERRAIN_TREES
			for (Trees::iterator itor(trees.begin()); itor != trees.end();)
				if (abs(cur_x - (int)itor->first.first) > v + 1 || abs(cur_z - (int)itor->first.second) > v)
					itor = trees.erase(itor);
				else
					++itor;
#endif

			cur_x = x_sector;
			cur_z = z_sector;

			terrain_clear();
#ifdef USE_TERRAIN_GROUP
			int g = (v - 1) / GROUP + 1;
			int xg = cur_x / GROUP, zg = cur_z / GROUP;
			for (Group** group = &groups; *group;)
				if (abs(xg - (int)(*group)->x) > g + 1 || abs(zg - (int)(*group)->z) > g + 1)
					destroy_group(*group);
				else
					group = &(*group)->next;
			for (int z = std::max(zg - g, 0); z <= std::min(zg + g, (int)ogre_terrain.sector_z_max / GROUP); z++)
				for (int x = std::max(xg - g, 0); x <= std::min(xg + g, (int)ogre_terrain.sector_x_max / GROUP); x++)
					convert_group(x, z);
#endif
			terrain = ogre_scene_manager->getRootSceneNode()->createChildSceneNode();
			for (int z = std::max(0, cur_z - v); z <= std::min((int)ogre_terrain.sector_z_max - 1, cur_z + v); z++)
				for (int x = std::max(0, cur_x - v); x <= std::min((int)ogre_terrain.sector_x_max - 1, cur_x + v); x++)
				{
#if 1
					Ogre::SceneNode* sector = terrain->createChildSceneNode();
					Ogre::Vector3 position((float)(x * TERRAIN_3D_SECTOR_SIDE_LENGTH + TERRAIN_3D_SECTOR_SIDE_LENGTH / 2), 0.0f, (float)(z * TERRAIN_3D_SECTOR_SIDE_LENGTH + TERRAIN_3D_SECTOR_SIDE_LENGTH / 2));
					position.z = -position.z;
					sector->setPosition(position);
					Ogre::Entity* entity = ogre_scene_manager->createEntity(TerrainObject(z, x));
					sector->attachObject(entity);
					SectorData sd = { sector, entity };
#ifdef USE_TERRAIN_OBJECTS
					TerrainObjects::iterator itor(terrain_objects.find(Sector(x, z)));
					if (itor != terrain_objects.end())
					{
						itor->second.show();
						sd.objects = &itor->second;
					}
#endif
					sectors_data.push_back(sd);
#endif
#ifdef USE_TERRAIN_TREES
					{
						TerrainTree terrain_tree(z, x);
						Trees::iterator itor(trees.find(Sector(x, z)));
						if (itor == trees.end())
						{
							Ogre::Vector3 position((float)(x * TERRAIN_3D_SECTOR_SIDE_LENGTH + TERRAIN_3D_SECTOR_SIDE_LENGTH / 2), 0.0f, (float)(z * TERRAIN_3D_SECTOR_SIDE_LENGTH + TERRAIN_3D_SECTOR_SIDE_LENGTH / 2));
							position.z = -position.z;
							SectorTrees& st = trees[Sector(x, z)];
							st.reserve(ogre_terrain.tree_sectors[z][x].number_of_trees);
							const terrain_3d_tree_data* tree = ogre_terrain.tree_sectors[z][x].trees;
							for (int i = 0; i < ogre_terrain.tree_sectors[z][x].number_of_trees; i++, tree++)
							{
								Ogre::InstancedEntity* ent = tree_manager->createInstancedEntity(tree_material);
								Ogre::Vector3 tree_position((float)(tree->x * (TERRAIN_3D_XZ_SCALE / 2)), tree->y * ogre_terrain.map_scaled_height_difference / 2 + ogre_terrain.map_minimum_height, (float)(tree->z * (TERRAIN_3D_XZ_SCALE / 2)));
								tree_position.z = -tree_position.z;
								float scale = ogre_terrain.get_tree_scale(const_cast<terrain_3d_tree_data*>(tree));
								ent->setPosition(position + tree_position);
								ent->setScale(Ogre::Vector3(scale, scale, scale));
								st.append(ent);
							}
						}
					}
#endif
				}
		}
	private:
#ifdef USE_TERRAIN_GROUP
		static const int GROUP = 20;
		struct Group : private Uncopyable
		{
			Group(unsigned x, unsigned z)
				: x(x), z(z), geometry(1 << 20, 1 << 20), next(0)
			{
			}

			const unsigned x, z;
			Geometry geometry;
			Group* next;
		};
		void convert_group(unsigned xg, unsigned zg)
		{
			ogre_log(__FUNCTION__, "%u %u", xg, zg);
			Group* group = new Group(xg, zg);
			group->next = groups;
			groups = group;

			Geometry* geometry = &group->geometry;
			for (unsigned z = zg * GROUP; z < std::min((zg + 1) * GROUP, ogre_terrain.sector_z_max); z++)
				for (unsigned x = xg * GROUP; x < std::min((xg + 1) * GROUP, ogre_terrain.sector_x_max); x++)
					terrain_converter->convert_sector(x, z, geometry);
			geometry->flush();
		}
		void destroy_group(Group*& group)
		{
			unsigned xg = group->x, zg = group->z;
			for (unsigned z = zg * GROUP; z < std::min((zg + 1) * GROUP, ogre_terrain.sector_z_max); z++)
				for (unsigned x = xg * GROUP; x < std::min((xg + 1) * GROUP, ogre_terrain.sector_x_max); x++)
					terrain_converter->destroy_sector(x, z);
			Group* g = group;
			group = group->next;
			delete g;
		}
		Group* groups;
#else
		Geometry terrain_geometry;
#endif
		void terrain_clear(void)
		{
			if (terrain)
			{
				while (!sectors_data.empty())
				{
					SectorsData::value_type& v = sectors_data.front();
					v.node->detachObject(v.entity);
					ogre_scene_manager->destroyEntity(v.entity);
#ifndef OGRE_TERRAIN_OBJECTS
					if (v.objects)
						v.objects->hide();
#endif
					sectors_data.pop_front();
				}
				terrain->removeAndDestroyAllChildren();
				terrain->getParentSceneNode()->removeChild(terrain);
				terrain->getCreator()->destroySceneNode(terrain);
			}
		}
		Ogre::SceneNode* terrain;
		struct SectorData
		{
			Ogre::SceneNode* node;
			Ogre::Entity* entity;
#ifdef USE_TERRAIN_OBJECTS
			SectorObjects* objects;
#endif
		};
		typedef std::deque<SectorData> SectorsData;
		SectorsData sectors_data;
#ifdef USE_TERRAIN_TREES
		class SectorTrees : private Uncopyable
		{
		public:
			SectorTrees()
			{
			}
			SectorTrees(const SectorTrees& st)
			{
				assert(st.trees.empty());
			}
			~SectorTrees()
			{
				for (Trees::iterator itor(trees.begin()); itor != trees.end(); ++itor)
					ogre_scene_manager->destroyInstancedEntity(*itor);
			}
			void reserve(size_t size)
			{
				trees.reserve(size);
			}
			void append(Ogre::InstancedEntity* tree)
			{
				trees.push_back(tree);
			}

		private:
			typedef std::vector<Ogre::InstancedEntity*> Trees;
			Trees trees;
		};
		typedef std::map<Sector, SectorTrees> Trees;
		Trees trees;
#endif
		int cur_x, cur_z;
	};
	typedef std::auto_ptr<TerrainCache> TerrainCachePtr;

	TerrainCachePtr terrain_cache;
}

// Place terrain into the scene
void OGREEE_CALL ogre_terrain_init(struct OgreTerrainInit* init)
{
	ogre_log(__FUNCTION__, "%u %u", init->sector_z_max, init->sector_x_max);

	ogre_terrain = *init;

#ifdef _DEBUG
	ogre_terrain.sector_x_max = std::min(ogre_terrain.sector_x_max, 10u);
	ogre_terrain.sector_z_max = std::min(ogre_terrain.sector_z_max, 10u);
#endif

	assert(!terrain_converter.get());
	assert(!terrain_cache.get());

#ifdef USE_TERRAIN_VISIBILITY
	//TODO: Wrong place
	ogre_camera->setNearClipDistance(1.0f);
	ogre_scene_manager->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.18f, 0.77f, 0.87f), 0, USE_TERRAIN_VISIBILITY * TERRAIN_3D_SECTOR_SIDE_LENGTH / 2, USE_TERRAIN_VISIBILITY * TERRAIN_3D_SECTOR_SIDE_LENGTH);
	ogre_scene_manager->setAmbientLight(Ogre::ColourValue(0.6f, 0.6f, 0.6f));
	ogre_scene_manager->setSkyDome(true, "Examples/CloudySky", 5, 8);
#endif

	terrain_converter.reset(new TerrainConverter);

	terrain_converter->convert_types();

	terrain_cache.reset(new TerrainCache);
}

// Clear terrain data
void OGREEE_CALL ogre_terrain_clear(void)
{
	ogre_log(__FUNCTION__, "");

#ifdef USE_TERRAIN_OBJECTS
	terrain_objects.clear();
#endif

	terrain_cache.reset(0);

	terrain_converter.reset(0);
}

// Periodic update to reflect visibility changes
void OGREEE_CALL ogre_terrain_update(void)
{
	//ogre_log(__FUNCTION__, "");

	terrain_cache->update();
}

// Use specified object as a tree
void OGREEE_CALL ogre_terrain_tree(const struct OBJECT_3D* o)
{
	ogre_log(__FUNCTION__, "");

#ifdef USE_TERRAIN_TREES
	assert(!tree_geometry.get());
	tree_geometry.reset(new Geometry(0));
	AnimationMesh am;
	TerrainTreeObject terrain_tree_object;
	Ogre::MeshPtr tree = Ogre::MeshManager::getSingleton().createManual(terrain_tree_object, ogre_resource_group);
	ogre_objects_convert(*o, tree, am, tree_geometry.get());
	tree_geometry->flush();
	tree_material = tree->getSubMesh(0)->getMaterialName();
	Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(tree_material, ogre_resource_group);
	Ogre::Pass* pass = mat->getTechnique(0)->getPass(0);
	pass->setVertexProgram("Ogre/Instancing/ShaderBased_vs");
	mat->load();
	tree_manager = ogre_scene_manager->createInstanceManager(TerrainTreeManager(), terrain_tree_object, ogre_resource_group, Ogre::InstanceManager::ShaderBased, 80, Ogre::IM_USEALL);
#endif
}

// Clear tree object
void OGREEE_CALL ogre_terrain_tree_clear(void)
{
	ogre_log(__FUNCTION__, "");

#ifdef USE_TERRAIN_TREES
	tree_material.clear();
	ogre_scene_manager->destroyInstanceManager(tree_manager);
	TerrainTreeObject terrain_tree_object;
	Ogre::MeshManager::getSingleton().unload(terrain_tree_object);
	Ogre::MeshManager::getSingleton().remove(terrain_tree_object);
	tree_geometry.reset(0);
#endif
}

void OGREEE_CALL ogre_terrain_user_scene(struct OgreGameObjectScene* scene)
{
	ogre_log(__FUNCTION__, "%p", scene);

#ifdef USE_TERRAIN_OBJECTS
	Ogre::SceneNode* node = reinterpret_cast<Ogre::SceneNode*>(scene->root);
	Ogre::Vector3 pos = node->getPosition();
	int x = (int)floor(pos.x / TERRAIN_3D_SECTOR_SIDE_LENGTH);
	int z = (int)floor(pos.z / TERRAIN_3D_SECTOR_SIDE_LENGTH);
	z = -z - 1;
	if (x < 0 || x >= (int)ogre_terrain.sector_x_max || z < 0 || z >= (int)ogre_terrain.sector_z_max)
		ogre_log(__FUNCTION__, "invalid sector for object %i %i", x, z);
	const SceneDatabase* database = static_cast<GameObjectScene*>(scene->internal)->database;
	if (database->elements.empty())
		ogre_log(__FUNCTION__, "empty scene");
	Ogre::SceneNode* parent = node->getParentSceneNode();
	if (parent)
		parent->removeChild(node);
	ogre_log(__FUNCTION__, "%s %i %i %f %f %f", database->elements.front().object.c_str(), x, z, pos.x, pos.y, pos.z);
	terrain_objects[Sector(x, z)].append(scene);
#endif
}
