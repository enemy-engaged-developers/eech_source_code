#include "stdafx.h"

#include "ogre_int.hpp"

// Creates texture resource and uploads texture into Ogre
void ogre_textures_define(int index, int number_of_mipmaps, int mip, int width, int height, int bpp, void* texture_image_data)
{
	TextureName texture_name(index, false);

	TexturePtr tex;
	PixelFormat format = bpp == 4 ? PF_BYTE_BGRA : PF_BYTE_BGR;
	if (mip <= 0)
		tex = TextureManager::getSingleton().createManual(texture_name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, width, height, number_of_mipmaps, format, TU_STATIC_WRITE_ONLY);
	else
		tex = TextureManager::getSingleton().getByName(texture_name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	if (mip >= 0)
	{
		tex->getBuffer(0, mip)->blitFromMemory(PixelBox(width, height, 1, format, texture_image_data));
	}
}

// Unloads and removes all textures
void ogre_textures_clear(void)
{
	for (unsigned i = 0; ; i++)
	{
		if (!get_texture_name(i, false))
			break;
		TextureName texture_name(i, false);
		TextureManager::getSingleton().unload(texture_name);
		TextureManager::getSingleton().remove(texture_name);
	}
}
