#include "ogre_int.hpp"

// Creates texture resource and uploads texture into Ogre
void ogre_textures_define(unsigned index, unsigned number_of_mipmaps, int mip, unsigned width, unsigned height, unsigned bpp, void* texture_image_data)
{
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
void ogre_textures_clear(void)
{
}
