noinst_LTLIBRARIES = libgraphics.la

GRAPHICS_D3D = d3d.c d3dfog.c d3dpoly.c d3dstate.c d3dvert.c

GRAPHICS_SOFT = block.c circle.c clip.c colour.c \
	dassess.c dirdraw.c dither.c dresol.c \
	fillasm.asm gfxzoom.c heckfill.c lbm.c line.c mipmap.c monofont.c monosprt.c \
	mouseptr.c palette.c pixel.c pixeltxt.c polyd3d.c polyline.c psdread.c \
	psdwrite.c render.c rgb.c rle.c screens.c shadfill.c tempbuf.c textscrn.c \
	textsys.c textures.c textuser.c tga.c tranbuf.c vcache.c viewport.c \
	zbufasm.asm zbuffer.c

libgraphics_la_SOURCES = \
	render.c \
	screens.c

SUBDIRS = external SDL
LDFLAGS = @STATIC_LIB@
libgraphics_la_LIBADD = external/libexternal.la SDL/libSDL.la
INCLUDES = -I$(top_srcdir)/modules -I..
