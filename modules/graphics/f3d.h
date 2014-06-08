struct _D3DLIGHT9;
struct _D3DMATRIX;
struct _D3DVIEWPORT9;
struct _D3DMATERIAL9;
struct IDirect3DVertexBuffer9;
typedef struct IDirect3DVertexBuffer9 *LPDIRECT3DVERTEXBUFFER9;
struct IDirect3DIndexBuffer9;
typedef struct IDirect3DIndexBuffer9 *LPDIRECT3DINDEXBUFFER9;
struct SCREEN;

enum TEXTURE_ROLE
{
	TEXTURE_ROLE_STATIC_RGBX,
	TEXTURE_ROLE_STATIC_RGBA,
	TEXTURE_ROLE_DYNAMIC_RGBX,
	TEXTURE_ROLE_DYNAMIC_RGBA,
	TEXTURE_ROLE_RENDER_TARGET,
};

void f3d_set_light(unsigned index, struct _D3DLIGHT9 *light);
void f3d_light_enable(unsigned index, unsigned state);

void f3d_set_transform(unsigned type, struct _D3DMATRIX *matrix);

int f3d_set_viewport(struct _D3DVIEWPORT9 *viewport);

void f3d_vertex_create(unsigned size, unsigned fvf, LPDIRECT3DVERTEXBUFFER9 *buffer);
void f3d_vertex_release(LPDIRECT3DVERTEXBUFFER9 *buffer);
void f3d_vertex_lock(LPDIRECT3DVERTEXBUFFER9 buffer, unsigned flags, void **ptr);
void f3d_vertex_unlock(LPDIRECT3DVERTEXBUFFER9 buffer);

void f3d_index_create(unsigned size, LPDIRECT3DINDEXBUFFER9 *ibuffer);
void f3d_index_release(LPDIRECT3DINDEXBUFFER9 *ibuffer);
void f3d_index_lock(LPDIRECT3DINDEXBUFFER9 ibuffer, unsigned flags, unsigned short **ptr);
void f3d_index_unlock(LPDIRECT3DINDEXBUFFER9 ibuffer);

void f3d_dip(unsigned type, LPDIRECT3DVERTEXBUFFER9 buffer, unsigned vstart, unsigned vtotal, LPDIRECT3DINDEXBUFFER9 ibuffer, unsigned istart, unsigned primitives, unsigned fvf, unsigned stride);
void f3d_dp(unsigned type, LPDIRECT3DVERTEXBUFFER9 buffer, unsigned vstart, unsigned primitivecount, unsigned fvf, unsigned stride);

void f3d_render_state(unsigned state, unsigned data);
void f3d_set_texture_state(unsigned stage, unsigned state, unsigned data);
void f3d_set_sampler_state(unsigned sampler, unsigned type, unsigned data);
void f3d_set_texture(unsigned stage, struct SCREEN *texture);
void f3d_set_material(struct _D3DMATERIAL9 *material);

int f3d_scene_begin(void);
int f3d_scene_end(void);

void f3d_clear_zbuffer(void);
void f3d_clear_screen(unsigned color);
int f3d_set_3d_render_target(struct SCREEN *this_screen);
void f3d_stop_3d_render_target(struct SCREEN *this_screen);

void f3d_texture_create(struct SCREEN *texture, int width, int height, int number_of_mipmaps, enum TEXTURE_ROLE role);
void f3d_texture_release(struct SCREEN *texture);
void f3d_texture_pre(struct SCREEN *texture);
void f3d_texture_post(struct SCREEN *texture);
int f3d_texture_lock(struct SCREEN *texture, int mipmap_level);
int f3d_texture_unlock(struct SCREEN *texture);
