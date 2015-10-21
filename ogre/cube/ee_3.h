typedef int DDPIXELFORMAT;
#include "../../graphics/textsys.h"
#include "../../maths/vector.h"
#include "../../maths/matrix.h"
#include "../../graphics/colour.h"
#include "../3denv.h"
#include "../3dview.h"
#include "../objects.h"
typedef int object_3d_index_numbers;
typedef int object_3d_sub_object_index_numbers;
typedef int object_3d_camera_index_numbers;
typedef int object_3d_light_index_numbers;
#include "../3dobjdb.h"

#ifdef USE_TERRAIN

#include "terrtype.h"
#include "terrdata.h"
#include "terrdr.h"
#include "terrdrcl.h"

#endif
