#include "ogre_int.hpp"

namespace
{
	Ogre::set<unsigned>::type textures;
	Ogre::deque<Ogre::String>::type materials;

	void register_material(unsigned texture_animation)
	{
		const TextureAnimation& ta = ogre_textures_animation(texture_animation);
		for (unsigned frame = 0; frame < ta.size(); frame++)
		{
			for (int additive = 0; additive <= 1; additive++)
			{
				MaterialParticlesName material_name(texture_animation, frame, additive);
				Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(material_name, ogre_resource_group);
				Ogre::Pass* pass = mat->getTechnique(0)->getPass(0);
				pass->setDepthBias(1.0f, 1.0f);
				pass->setSceneBlending(additive ? Ogre::SBT_ADD : Ogre::SBT_TRANSPARENT_ALPHA);
				pass->setDepthWriteEnabled(false);
				pass->setVertexColourTracking(pass->getVertexColourTracking() | Ogre::TVC_DIFFUSE);
				TextureName texture_name(ta[frame]);
				Ogre::TextureUnitState* tus = pass->createTextureUnitState(texture_name);
				tus->setColourOperationEx(Ogre::LBX_MODULATE, Ogre::LBS_TEXTURE, Ogre::LBS_DIFFUSE);
				tus->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_TEXTURE, Ogre::LBS_DIFFUSE);
				materials.push_back(material_name);
			}
		}
	}

	struct NodeBillboard
	{
		Ogre::SceneNode* node;
		Ogre::BillboardSet* bbs;
		unsigned left;
	};
	typedef Ogre::list<NodeBillboard>::type DrawnParticles;
	DrawnParticles drawn_particles, cached_particles;

	void clear_particle(NodeBillboard& nb)
	{
		nb.node->detachObject(nb.bbs);
		ogre_scene_manager->destroyBillboardSet(nb.bbs);
		nb.node->getParentSceneNode()->removeChild(nb.node);
		nb.node->getCreator()->destroySceneNode(nb.node);
	}
	void clear_particles(DrawnParticles& particles)
	{
		for (DrawnParticles::iterator itor(particles.begin()); itor != particles.end(); ++itor)
			clear_particle(*itor);
		particles.clear();
	}

	class TaskParticlesClear : public Task
	{
	public:
		virtual TaskResult task(void)
		{
			ogre_particles_frame();
			clear_particles(cached_particles);

			for (unsigned i = 0; i < materials.size(); i++)
			{
				const Ogre::String& material_name = materials[i];
				Ogre::MaterialManager::getSingleton().unload(material_name);
				Ogre::MaterialManager::getSingleton().remove(material_name);
			}
			materials.clear();

			return TR_TASK;
		}
	};
}

namespace
{
	typedef std::pair<OgreParticle, Ogre::vector<OgreVector3>::type> ParticleGroup;
	typedef Ogre::deque<ParticleGroup>::type Particles;
	Particles particles;

	class TaskParticlesCommit : public Task
	{
	public:
		explicit TaskParticlesCommit(Particles& particles)
		{
			this->particles.swap(particles);
		}
		void create_billboard(Ogre::BillboardSet* bbs, const OgreParticle& p, const OgreVector3& position)
		{
			Ogre::Billboard* bs = bbs->createBillboard(ogre_position(&position.x), ogre_colour(p.colour));
			bs->setRotation(Ogre::Radian(p.roll));
		}
		virtual TaskResult task(void)
		{
			for (unsigned i = 0; i < particles.size(); i++)
			{
				const ParticleGroup& pg = particles[i];
				const OgreParticle& p = pg.first;
				if (textures.insert(p.texture_animation).second)
				{
					register_material(p.texture_animation);
				}

				if (cached_particles.empty())
				{
					NodeBillboard nb;
					nb.node = ogre_scene_manager->createSceneNode();
					ogre_scene_manager->getRootSceneNode()->addChild(nb.node);
					nb.bbs = ogre_scene_manager->createBillboardSet(std::max(pg.second.size(), 1u));
					nb.node->attachObject(nb.bbs);
					nb.bbs->setRenderQueueGroup(Ogre::RENDER_QUEUE_7);
					nb.bbs->setBillboardRotationType(Ogre::BBR_VERTEX);
					drawn_particles.push_back(nb);
				}
				else
					drawn_particles.splice(drawn_particles.end(), cached_particles, cached_particles.begin());
				NodeBillboard& nb = drawn_particles.back();
				nb.node->setVisible(true);

				nb.bbs->setDefaultDimensions(p.radius, p.radius);
				MaterialParticlesName material_name(p.texture_animation, p.frame, p.additive);
				nb.bbs->setMaterialName(material_name);
				if (pg.second.empty())
					create_billboard(nb.bbs, p, p.position);
				else
					for (unsigned i = 0; i < pg.second.size(); i++)
						create_billboard(nb.bbs, p, pg.second[i]);
			}

			for (DrawnParticles::iterator it = cached_particles.begin(); it != cached_particles.end();)
			{
				if (--it->left)
				{
					++it;
				}
				else
				{
					clear_particle(*it);
					it = cached_particles.erase(it);
				}
			}

			return TR_TASK;
		}

	private:
		Particles particles;
	};
}

void OGREEE_CALL ogre_particles_init(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
}

void OGREEE_CALL ogre_particles_clear(void)
{
	assert(GetCurrentThreadId() == user_thread_id);

	ogre_tasks->enqueue(new TaskParticlesClear());
}

void OGREEE_CALL ogre_particles_draw(const struct OgreParticle* particle, unsigned number_of_positions, struct OgreVector3* positions)
{
	assert(GetCurrentThreadId() == user_thread_id);

	particles.push_back(ParticleGroup());
	ParticleGroup& pg = particles.back();
	pg.first = *particle;
	if (number_of_positions)
	{
		pg.second.assign(positions, positions + number_of_positions);
	}
}

void OGREEE_CALL ogre_particles_commit(void)
{
	assert(GetCurrentThreadId() == user_thread_id);

	ogre_tasks->enqueue(new TaskParticlesCommit(particles));
}

void ogre_particles_frame(void)
{
	assert(GetCurrentThreadId() == ogre_thread_id);

	for (DrawnParticles::iterator it(drawn_particles.begin()); it != drawn_particles.end(); ++it)
	{
		it->bbs->clear();
		it->node->setVisible(false);
		it->left = USE_PARTICLES_CACHE_FRAMES;
	}
	cached_particles.splice(cached_particles.end(), drawn_particles);
}
