#include <stdio.h>

FILE* safe_fopen(const char* filename, const char* mode);

typedef int DDPIXELFORMAT;
#include "../../graphics/textsys.h"
#include "../../maths/vector.h"
typedef float matrix3x3[3][3];
struct VIEWPOINT
{

	union
	{

		vec3d
			position;

		struct
		{

			float
				x,
				y,
				z;
		};
	};

	union
	{

		matrix3x3
			attitude;

		struct
		{

			vec3d
				xv,
				yv,
				zv;
		};
	};
};
typedef struct VIEWPOINT viewpoint;

#include "../objects.h"
#include "../../graphics/colour.h"
typedef int object_3d_index_numbers;
typedef int object_3d_sub_object_index_numbers;
typedef int object_3d_camera_index_numbers;
typedef int object_3d_light_index_numbers;
#include "../3dobjdb.h"
void generate_object_3d_point_normal(object_3d_heading_pitch_normal *normal, vec3d *result);

#ifdef USE_TERRAIN

struct VERTEX
{

	//
	// 3D world coordinates ( q = 1/z )
	//

	float
		x,
		y,
		z,
		q;

	//
	// 2D screen coordinates
	//

	float
		i,
		j;

	//
	// Texture coordinates
	//

	float
		u,
		v,
		u2,
		v2;

	//
	// Linked list management ( next pointer )
	//

	struct VERTEX
		*next_vertex;

	unsigned char
		outcode,
		specular,
		fog;

	union
	{

		unsigned char
			userdata,
			userdata1,
			userdata2,
			normal_index;
	};

	//
	// The following union makes copying between a D3DCOLOR structure a simple memory move.
	//

	union
	{
	
		struct
		{
		
			unsigned char
				blue,
				green,
				red,
				alpha;
		};

		unsigned int
			colour;
	};

	union
	{
	
		struct
		{
		
			unsigned char
				blue2,
				green2,
				red2,
				alpha2;
		};

		unsigned int
			colour2;
	};

	//
	// Finally, 2 DWORDS to pad the structure to 64 bytes.
	//

	int
		padding_dword_1,
		padding_dword_2;
};

typedef	struct VERTEX vertex;

typedef	struct SCENE_SLOT_DRAWING_LIST scene_slot_drawing_list;

#include "terrtype.h"
#include "terrdata.h"
#include "terrelev.h"
#include "terrobjs.h"
#include "terrsel.h"
#include "terrgeom.h"
#include "terrmap.h"
#include "terrdr.h"
#include "terrdrcl.h"

extern int
        terrain_3d_map_width,
        terrain_3d_map_height;

extern vec3d
	terrain_3d_point_normals[256];

#endif
