#include "ogre_int.hpp"

namespace
{
	struct Override
	{
		unsigned index;
		Ogre::TexturePtr texture;
	};
	typedef std::deque<Override> Overrides;

	Overrides overrides;
}

// Creates texture resource and uploads texture into Ogre
void OGREEE_CALL ogre_textures_define(unsigned index, unsigned number_of_mipmaps, int mip, unsigned width, unsigned height, unsigned bpp, void* texture_image_data)
{
	ogre_log(__FUNCTION__, "%u %i/%u", index, mip, number_of_mipmaps);

	TextureName texture_name(index);

	Ogre::TexturePtr tex;
	Ogre::PixelFormat format = bpp == 4 ? Ogre::PF_BYTE_BGRA : Ogre::PF_BYTE_BGR;
	if (mip <= 0)
		tex = Ogre::TextureManager::getSingleton().createManual(texture_name, ogre_resource_group, Ogre::TEX_TYPE_2D, width, height, number_of_mipmaps, format, Ogre::TU_STATIC_WRITE_ONLY);
	else
		tex = Ogre::TextureManager::getSingleton().getByName(texture_name, ogre_resource_group);

	if (mip >= 0)
		tex->getBuffer(0, mip)->blitFromMemory(Ogre::PixelBox(width, height, 1, format, texture_image_data));
}

// Unloads and removes all textures
void OGREEE_CALL ogre_textures_clear(void)
{
	ogre_log(__FUNCTION__, "");
}

void OGREEE_CALL ogre_textures_override(unsigned index, const char* file)
{
	ogre_log(__FUNCTION__, "%u %s", index, file);

	TextureName texture_name(index);
	Override o = { index, Ogre::TextureManager::getSingleton().getByName(texture_name, ogre_resource_group) };
	Ogre::TextureManager::getSingleton().remove(texture_name);
	Ogre::TextureManager::getSingleton().loadImage(texture_name, ogre_resource_group, Ogre::Image().load(file, ogre_resource_group));
}

void OGREEE_CALL ogre_textures_restore(void)
{
	ogre_log(__FUNCTION__, "");

	while (!overrides.empty())
	{
		Override& o = overrides.front();
		TextureName texture_name(o.index);
		if (o.texture.isNull())
			Ogre::TextureManager::getSingleton().remove(texture_name);
		else
			*Ogre::TextureManager::getSingleton().getByName(texture_name, ogre_resource_group) = *o.texture;
		overrides.pop_front();
	}
}
