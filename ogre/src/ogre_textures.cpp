#include "ogre_int.hpp"

namespace
{
	typedef Ogre::vector<unsigned char>::type Data;
	Data data;
	struct Info
	{
		Ogre::String file;
		Ogre::PixelBox pb;
		Ogre::String override;

		void load(const Ogre::String& texture_name)
		{
			if (override.empty() && file.empty())
			{
				Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual(texture_name, ogre_resource_group, Ogre::TEX_TYPE_2D, pb.right, pb.bottom, 0, pb.format, Ogre::TU_STATIC_WRITE_ONLY);
				if (pb.data)
					tex->getBuffer(0, 0)->blitFromMemory(pb);
			}
			else
				Ogre::TextureManager::getSingleton().loadImage(texture_name, ogre_resource_group, Ogre::Image().load(override.empty() ? file : override, ogre_resource_group));
		}
	};
	typedef Ogre::map<unsigned, Info>::type Textures;

	Textures textures;

	typedef Ogre::deque<std::pair<unsigned, Ogre::String> >::type TexturesOverride;
	TexturesOverride textures_override;

	struct TaskTexturesInit : public Task
	{
	public:
		TaskTexturesInit(int clearable, Semaphore& sem)
			: clearable(clearable), sem(sem)
		{
		}
		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "");

			for (TexturesOverride::iterator itor(textures_override.begin()); itor != textures_override.end(); ++itor)
			{
				Info& info = textures[itor->first];
				(clearable ? info.override : info.file).swap(itor->second);
			}
			textures_override.clear();

			for (Textures::iterator itor(textures.begin()); itor != textures.end(); ++itor)
			{
				if (clearable && itor->second.override.empty())
				{
					assert(itor->second.pb.data || !itor->second.file.empty());
					continue;
				}

				assert(itor->second.pb.data || !itor->second.file.empty() || !itor->second.override.empty());
				TextureName texture_name(itor->first);
				Ogre::TextureManager::getSingleton().unload(texture_name);
				Ogre::TextureManager::getSingleton().remove(texture_name);

				itor->second.load(texture_name);
			}

			sem.release();
			return TR_TASK;
		}

	private:
		int clearable;
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
				if (!full && itor->second.override.empty())
					continue;

				TextureName texture_name(itor->first);
				Ogre::TextureManager::getSingleton().unload(texture_name);
				Ogre::TextureManager::getSingleton().remove(texture_name);

				if (!full && !itor->second.override.empty())
				{
					Ogre::String().swap(itor->second.override);
					itor->second.load(texture_name);
				}
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
}

namespace
{
	static unsigned texture_ui_index = 100000;

	class TaskTextureLoad : public Task
	{
	public:
		TaskTextureLoad(unsigned index, const char* filename)
			: index(index), filename(filename)
		{
		}

		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "%u %s", index, filename.c_str());

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

	class TaskTextureDefine : public Task
	{
	public:
		TaskTextureDefine(unsigned index, unsigned width, unsigned height, unsigned bpp, const void* data)
			: index(index), width(width), height(height), bpp(bpp), data(data)
		{
		}

		virtual TaskResult task(void)
		{
			ogre_log(__FUNCTION__, "%u %u %u %u", index, width, height, bpp);

			TextureName texture_name(index);
			Ogre::PixelBox pb(width, height, 1, bpp == 4 ? Ogre::PF_BYTE_BGRA : Ogre::PF_BYTE_BGR, const_cast<void*>(data));
			Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual(texture_name, ogre_resource_group, Ogre::TEX_TYPE_2D, pb.right, pb.bottom, 0, pb.format, Ogre::TU_STATIC_WRITE_ONLY);
			tex->getBuffer(0, 0)->blitFromMemory(pb);

			Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(MaterialTextureName(index), ogre_resource_group);
			Ogre::Pass* pass = mat->getTechnique(0)->getPass(0);
			pass->createTextureUnitState(texture_name);
			pass->setLightingEnabled(false);
			pass->setDepthCheckEnabled(false);
			if (bpp == 4)
				pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

			return TR_TASK;
		}

	private:
		unsigned index;
		unsigned width;
		unsigned height;
		unsigned bpp;
		const void* data;
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

void OGREEE_CALL ogre_textures_define(unsigned index, unsigned number_of_mipmaps, int mip, unsigned width, unsigned height, unsigned bpp, const void* texture_image_data)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "%u %u %i %u %u %u %p", index, number_of_mipmaps, mip, width, height, bpp, texture_image_data);

	if (mip > 0)
		return;

	if (bpp == 4)
	{
		if (data.empty())
			data.reserve(4733312);
		const char* image = static_cast<const char*>(texture_image_data);
		unsigned offset = data.size();
		unsigned size = 4 * width * height;
		data.insert(data.end(), image, image + size);
		for (unsigned off = offset + 3; size; size -= 4, off += 4)
			data[off] = ~data[off];
		texture_image_data = &data[offset];
	}
	Info& info = textures[index];
	info.pb = Ogre::PixelBox(width, height, 1, bpp == 4 ? Ogre::PF_BYTE_BGRA : Ogre::PF_BYTE_BGR, const_cast<void*>(texture_image_data));
}

void OGREEE_CALL ogre_textures_override(unsigned index, const char* file)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "%u %s", index, file);

	textures_override.push_back(std::make_pair(index, file));
}

void OGREEE_CALL ogre_textures_commit(int clearable)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "%i", clearable);

	Semaphore sem;
	ogre_tasks->enqueue(new TaskTexturesInit(clearable, sem));
	sem.acquire();
}

void OGREEE_CALL ogre_textures_clear(int full)
{
	assert(GetCurrentThreadId() == user_thread_id);
	ogre_log_(__FUNCTION__, "%i", full);

	Semaphore sem;
	ogre_tasks->enqueue(new TaskTexturesClear(full, sem));
	sem.acquire();
}

unsigned OGREEE_CALL ogre_texture_load(const char* filename)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	ogre_tasks->enqueue(new TaskTextureLoad(texture_ui_index, filename));
	return texture_ui_index++;
}

unsigned OGREEE_CALL ogre_texture_define(unsigned width, unsigned height, unsigned bpp, const void* data)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	ogre_tasks->enqueue(new TaskTextureDefine(texture_ui_index, width, height, bpp, data));
	return texture_ui_index++;
}

void OGREEE_CALL ogre_texture_clear(unsigned handle)
{
	assert(GetCurrentThreadId() == user_thread_id);
	//ogre_log_(__FUNCTION__, "");

	ogre_tasks->enqueue(new TaskTextureClear(handle));
}
