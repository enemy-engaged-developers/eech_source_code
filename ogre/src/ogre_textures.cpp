#include "ogre_int.hpp"

namespace
{
	struct Info
	{
		Ogre::String file;
		Ogre::PixelBox pb;
		std::vector<unsigned char> data;
	};
	typedef std::map<unsigned, Info> Textures;

	Textures textures;

	struct TaskTexturesInit : public Task
	{
	public:
		TaskTexturesInit(Semaphore& sem)
			: sem(sem)
		{
		}
		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			for (Textures::iterator itor(textures.begin()); itor != textures.end(); ++itor)
			{
				//ogre_log(__FUNCTION__, "%u %s %u", itor->first, itor->second.file.c_str(), itor->second.data.size());

				TextureName texture_name(itor->first);
				if (itor->second.file.empty())
				{
					const Ogre::PixelBox& pb = itor->second.pb;
					Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual(texture_name, ogre_resource_group, Ogre::TEX_TYPE_2D, pb.right, pb.bottom, 0, pb.format, Ogre::TU_STATIC_WRITE_ONLY);
					if (pb.data)
						tex->getBuffer(0, 0)->blitFromMemory(pb);
				}
				else
					Ogre::TextureManager::getSingleton().loadImage(texture_name, ogre_resource_group, Ogre::Image().load(itor->second.file, ogre_resource_group));
			}
			sem.release();
			return TR_TASK;
		}

	private:
		Semaphore& sem;
	};

	struct TaskTexturesClear : public Task
	{
	public:
		TaskTexturesClear(int full, Semaphore& sem)
			: full(full), sem(sem)
		{
		}
		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			for (Textures::iterator itor(textures.begin()); itor != textures.end(); ++itor)
			{
				Ogre::String().swap(itor->second.file);
				TextureName texture_name(itor->first);
				Ogre::TextureManager::getSingleton().unload(texture_name);
				Ogre::TextureManager::getSingleton().remove(texture_name);
			}

			if (full)
				textures.clear();

			sem.release();
			return TR_TASK;
		}

	private:
		int full;
		Semaphore& sem;
	};

	class TaskTextureLoad : public Task
	{
	public:
		TaskTextureLoad(unsigned index, const char* filename)
			: index(index), filename(filename)
		{
		}

		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			TextureName texture_name(index);
			Ogre::TextureManager::getSingleton().loadImage(texture_name, ogre_resource_group, Ogre::Image().load(filename, ogre_resource_group));

			Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(MaterialTextureName(index), ogre_resource_group);
			Ogre::Pass* pass = mat->getTechnique(0)->getPass(0);
			pass->createTextureUnitState(texture_name);
			pass->setLightingEnabled(false);
			pass->setDepthCheckEnabled(false);
			pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
			pass->getTextureUnitState(0)->setTextureFiltering(Ogre::TFO_BILINEAR);

			return TR_TASK;
		}

	private:
		unsigned index;
		Ogre::String filename;
	};

	class TaskTextureClear : public Task
	{
	public:
		TaskTextureClear(unsigned index)
			: index(index)
		{
		}

		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			MaterialTextureName material_texture_name(index);
			Ogre::MaterialManager::getSingleton().unload(material_texture_name);
			Ogre::MaterialManager::getSingleton().remove(material_texture_name);

			TextureName texture_name(index);
			Ogre::TextureManager::getSingleton().unload(texture_name);
			Ogre::TextureManager::getSingleton().remove(texture_name);

			return TR_TASK;
		}

	private:
		unsigned index;
	};
}

void OGREEE_CALL ogre_textures_define(unsigned index, unsigned number_of_mipmaps, int mip, unsigned width, unsigned height, unsigned bpp, void* texture_image_data)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	if (mip > 0)
		return;

	Info& info = textures[index];
	if (mip >= 0)
	{
		const unsigned char* data = static_cast<const unsigned char*>(texture_image_data);
		info.data.assign(data, data + bpp * width * height);
	}
	info.pb = Ogre::PixelBox(width, height, 1, bpp == 4 ? Ogre::PF_BYTE_BGRA : Ogre::PF_BYTE_BGR, info.data.empty() ? 0 : &info.data[0]);
}

void OGREEE_CALL ogre_textures_override(unsigned index, const char* file)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	Info& info = textures[index];
	info.data.clear();
	info.file = file;
}

void OGREEE_CALL ogre_textures_commit(void)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "");

	Semaphore sem(0, 1);
	ogre_tasks->enqueue(new TaskTexturesInit(sem));
	sem.acquire();
}

void OGREEE_CALL ogre_textures_clear(int full)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "");

	Semaphore sem(0, 1);
	ogre_tasks->enqueue(new TaskTexturesClear(full, sem));
	sem.acquire();
}

unsigned OGREEE_CALL ogre_texture_load(const char* filename)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	static unsigned index = 100000;

	ogre_tasks->enqueue(new TaskTextureLoad(index, filename));
	return index++;
}

void OGREEE_CALL ogre_texture_clear(unsigned handle)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	ogre_tasks->enqueue(new TaskTextureClear(handle));
}
