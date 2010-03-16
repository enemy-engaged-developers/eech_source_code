struct _D3DLIGHT7;
struct _D3DMATRIX;
struct _D3DVIEWPORT7;
struct _D3DVERTEXBUFFERDESC;
struct _D3DMATERIAL7;
struct IDirect3DVertexBuffer7;
typedef struct IDirect3DVertexBuffer7 *LPDIRECT3DVERTEXBUFFER7;
struct tagPALETTEENTRY;
struct IDirectDrawPalette;
typedef struct IDirectDrawPalette *LPDIRECTDRAWPALETTE;
struct _DDSURFACEDESC2;
struct IDirectDrawSurface7;
typedef struct IDirectDrawSurface7 *LPDIRECTDRAWSURFACE7;
struct tagRECT;
struct _DDBLTFX;
struct _DDPIXELFORMAT;
struct SCREEN;
typedef struct IDirectDraw7 *LPDIRECTDRAW7;


void f3d_set_light(unsigned index, struct _D3DLIGHT7 *light);
void f3d_light_enable(unsigned index, unsigned state);

void f3d_set_transform(unsigned type, struct _D3DMATRIX *matrix);

int f3d_set_viewport(struct _D3DVIEWPORT7 *viewport);

void f3d_vertex_create(struct _D3DVERTEXBUFFERDESC *desc, LPDIRECT3DVERTEXBUFFER7 *buffer);
void f3d_vertex_release(LPDIRECT3DVERTEXBUFFER7 *buffer);
int f3d_vertex_lock(LPDIRECT3DVERTEXBUFFER7 buffer, unsigned flags, void **ptr);
void f3d_vertex_lock_strict(LPDIRECT3DVERTEXBUFFER7 buffer, unsigned flags, void **ptr);
void f3d_vertex_unlock(LPDIRECT3DVERTEXBUFFER7 buffer);
void f3d_vertex_optimize(LPDIRECT3DVERTEXBUFFER7 buffer);

void f3d_draw_vb(unsigned type, LPDIRECT3DVERTEXBUFFER7 buffer, unsigned start,
	unsigned total, unsigned short *indices, unsigned count);
void f3d_draw(unsigned type, LPDIRECT3DVERTEXBUFFER7 buffer, unsigned start,
	unsigned total);

void f3d_zbuffer_clear(float value);

void f3d_render_state(unsigned state, unsigned data);
void f3d_set_texture_state(unsigned stage, unsigned state, unsigned data);
void f3d_set_texture(unsigned stage, struct SCREEN *texture);
void f3d_set_material(struct _D3DMATERIAL7 *material);

int f3d_scene_begin(void);
int f3d_scene_end(void);

void f3d_palette_create(struct tagPALETTEENTRY *palette, LPDIRECTDRAWPALETTE *texture_palette);
void f3d_palette_release(LPDIRECTDRAWPALETTE *texture_palette);

int f3d_surface_create(struct _DDSURFACEDESC2 *ddsd, LPDIRECTDRAWSURFACE7 *surface);
void f3d_surface_release(LPDIRECTDRAWSURFACE7 *texture_surface);
void f3d_surface_description(LPDIRECTDRAWSURFACE7 surface, struct _DDSURFACEDESC2* ddsd);
LPDIRECTDRAWSURFACE7 f3d_surface_front ( void );
LPDIRECTDRAWSURFACE7 f3d_surface_render ( void );
void f3d_surface_palette(LPDIRECTDRAWSURFACE7 surface, LPDIRECTDRAWPALETTE texture_palette);
void f3d_surface_blt(LPDIRECTDRAWSURFACE7 primary, struct tagRECT *rect1,
	LPDIRECTDRAWSURFACE7 secondary, struct tagRECT *rect2, unsigned flags,
	struct _DDBLTFX *fx);

void f3d_clear_zbuffer(void);
void f3d_clear_screen(void);
int f3d_set_3d_render_target ( struct SCREEN *this_screen );

int f3d_enumerate_formats(long (__stdcall *enumerate_texture_formats)(struct _DDPIXELFORMAT*, void*), void* context);

void f3d_evict_textures(void);

int f3d_texture_lock(struct SCREEN *texture, int mipmap_level);
int f3d_texture_unlock(struct SCREEN *texture);
void f3d_texture_create( struct SCREEN *texture, int width, int height, unsigned type, int number_of_mipmaps, int renderto );
int f3d_texture_release ( struct SCREEN *texture );
void f3d_texture_restore ( struct SCREEN *texture );

void f3d_memory(unsigned long *total, unsigned long *free);

unsigned f3d_pixel_size(void);

int f3d_test_video_resolution(int width, int height, int depth);

int f3d_enum_devices(struct IDirectDraw7* ddraw, long (__stdcall *enumerate_devices)(char* lpDeviceDescription, char* lpDeviceName, struct _D3DDeviceDesc7*, void*), void* arg);

void f3d_context_set(void);
void f3d_context_leave(void);
