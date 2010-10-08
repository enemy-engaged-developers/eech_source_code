struct OBJECT_3D_SUB_OBJECT_KEYFRAME
{
 int index, linear;
 float x, y, z, heading, pitch, roll, scale_x, scale_y, scale_z;
 float tension, continuity, bias;
};

struct OBJECT_3D_SCENE_CAMERA
{
 int
  target_sub_object_id,
  heading_locked,
  pitch_locked,
  roll_locked,
  number_of_keyframes;
 struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;
};


class Cameras
{
 public:

 Cameras(void)
 {
 }

 ~Cameras(void)
 {
  for (unsigned i = 0; i != !objects_3d_camera_database; i++)
   delete [] objects_3d_camera_database[i].keyframes;
 }

 int GetNumberOfCameras(void) const
 {
  return !objects_3d_camera_database;
 }

 const OBJECT_3D_SCENE_CAMERA& GetCamera(int camera) const
 {
  return objects_3d_camera_database[camera];
 }

 void LoadAll(FILE* fp)
 {
  int total_number_of_cameras;

  fread(&total_number_of_cameras, sizeof(int), 1, fp);
  fseek(fp, sizeof(int), SEEK_CUR);
  for (int count = 0; count < total_number_of_cameras; count++)
   {
    OBJECT_3D_SCENE_CAMERA camera;
    struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;

    fread(&camera.number_of_keyframes, sizeof(int), 1, fp);
    fread(&camera.target_sub_object_id, sizeof(int), 1, fp);
    fread(&camera.heading_locked, sizeof(int), 1, fp);
    fread(&camera.pitch_locked, sizeof(int), 1, fp);
    fread(&camera.roll_locked, sizeof(int), 1, fp);

    keyframes = new OBJECT_3D_SUB_OBJECT_KEYFRAME [camera.number_of_keyframes];
    camera.keyframes = keyframes;

    for (int keyframe_count = 0; keyframe_count < camera.number_of_keyframes; keyframe_count++)
     {
      fread(&keyframes[keyframe_count].index, sizeof(int), 1, fp);
      fread(&keyframes[keyframe_count].linear, sizeof(int), 1, fp);

      fread(&keyframes[keyframe_count].x, sizeof(float), 1, fp);
      fread(&keyframes[keyframe_count].y, sizeof(float), 1, fp);
      fread(&keyframes[keyframe_count].z, sizeof(float), 1, fp);

      fread(&keyframes[keyframe_count].heading, sizeof(float), 1, fp);
      fread(&keyframes[keyframe_count].pitch, sizeof(float), 1, fp);
      fread(&keyframes[keyframe_count].roll, sizeof(float), 1, fp);

      fread(&keyframes[keyframe_count].scale_x, sizeof(float), 1, fp);
      fread(&keyframes[keyframe_count].scale_y, sizeof(float), 1, fp);
      fread(&keyframes[keyframe_count].scale_z, sizeof(float), 1, fp);

      fread(&keyframes[keyframe_count].tension, sizeof(float), 1, fp);
      fread(&keyframes[keyframe_count].continuity, sizeof(float), 1, fp);
      fread(&keyframes[keyframe_count].bias, sizeof(float), 1, fp);
     }
    objects_3d_camera_database.Append(camera);
   }
 }

 int Append(const OBJECT_3D_SCENE_CAMERA& camera)
 {
  objects_3d_camera_database.Append(camera);
  return !objects_3d_camera_database - 1;
 }

 private:

 Array<OBJECT_3D_SCENE_CAMERA> objects_3d_camera_database;
};
