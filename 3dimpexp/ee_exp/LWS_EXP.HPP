class LwsExporter
{
 public:

 virtual ~LwsExporter(void)
 {
 }

 virtual void Begin(int max_keyframe_index) = 0;
 virtual void End(void) = 0;
 virtual void Object(int index, int number, int sub_object_index, int special = 0, const char* null_special = NULL) = 0;
 virtual void Parent(int index) = 0;
 virtual void KeyFrames(const char* type, int visibility, int color, const Schem& schem, int number_of_keyframes, const OBJECT_3D_SUB_OBJECT_KEYFRAME* keyframes) = 0;
 virtual void Limits(const char* l, double min, double max) = 0;
 virtual void LODs(int number_of_approximation_info, const OBJECT_3D_APPROXIMATION_INFO* approximation_info) = 0;
 virtual void Collision(void) = 0;
 virtual void Dissolve(int number_of_object_dissolve_keyframes, const OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME* object_dissolve_keyframes) = 0;
 virtual void Ambient(void) = 0;
 virtual void Light(int index) = 0;
 virtual void LightAttrs(const REAL_COLOUR* colour) = 0;
#ifndef NO_LWSCAMERAEXPORT
 virtual void Camera(int index, int name_index) = 0;
 virtual void CameraAttrs(int heading_locked, int pitch_locked, int roll_locked, int root, int target_sub_object_index) = 0;
#endif
};

class LwsExport
{
 private:

#ifndef NO_LWSCAMERAEXPORT
 const Cameras& cameras;
#endif

 LwsExporter* ex;
 int current;
 int* target_sub_object_index;


 public:

#ifndef NO_LWSCAMERAEXPORT
 LwsExport(const Cameras& cameras)
  : cameras(cameras)
 {
 }
#endif

 ~LwsExport(void)
 {
 }

 void ExportScene(LwsExporter* ex_, const OBJECT_3D_SCENE_DATABASE_ENTRY* scene, bool show_warnings);
#ifndef NO_LWSFILEEXPORTER
 void ExportScene(const AllNames& names, Translator& translator, const char* filename, const OBJECT_3D_SCENE_DATABASE_ENTRY& scene);
#endif
};
