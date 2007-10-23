#ifndef LWOFILEI_INCLUDED
#define LWOFILEI_INCLUDED


struct ImageAttribute : public BasicChunk
{
 enum ImageAttributeType
 {
  UNKNOWN,
  STILLIMAGE,
  IMAGESEQUENCE,
  PLUGINANIMATION,
  REFERENCECLONE,
  COLORCYCLINGSTILL,
  TIME,
  CONTRAST,
  BRIGHTNESS,
  SATURATION,
  HUE,
  GAMMACORRECTION,
  NEGATIVE,
  PLUGINIMAGEFILTERS,
  PLUGINPIXELFILTERS
 };

 ImageAttributeType imageattributetype;

 ImageAttribute ( LWO::Tag tag_, ImageAttributeType imageattributetype_ )
  : BasicChunk ( tag_ ), imageattributetype ( imageattributetype_ )
 {
 }
};

struct ImageUnknown : public ImageAttribute
{
 unsigned ndata;
 unsigned char * data;

 ImageUnknown ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, UNKNOWN )
 {
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~ImageUnknown ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( " Subchunk %s unknown ndata %u\n", &tag, ndata );
  PrintData ( 1, ndata, data );
 }
};

struct StillImage : public ImageAttribute
{
 FString name;

 StillImage ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, STILLIMAGE )
 {
  name = lwo.Read_FileName ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s name %s\n", &tag, &name );
 }
};

struct ImageSequence : public ImageAttribute
{
 unsigned char num_digits;
 unsigned char flags;
 signed short offset;
 unsigned short reserved;
 signed short start;
 signed short end;
 FString prefix;
 FString suffix;

 ImageSequence ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, IMAGESEQUENCE )
 {
  num_digits = lwo.Read_U1 ();
  flags = lwo.Read_U1 ();
  offset = lwo.Read_S2 ();
  reserved = lwo.Read_U2 ();
  start = lwo.Read_S2 ();
  end = lwo.Read_S2 ();
  prefix = lwo.Read_FileName ();
  suffix = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s num digits %u flags %02X offset %i reserved %u" \
           "start %i end %i prefix '%s' suffix '%s'", &tag, num_digits,
           flags, offset, reserved, start, end, &prefix, &suffix );
 }
};

struct PlugInAnimation : public ImageAttribute
{
 FString filename;
 FString servername;
 unsigned short flags;
 unsigned ndata;
 unsigned char * data;

 PlugInAnimation ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, PLUGINANIMATION )
 {
  filename = lwo.Read_FileName ();
  servername = lwo.Read_String ();
  flags = lwo.Read_U2 ();
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~PlugInAnimation ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( " Subchunk %s filename '%s' servername '%s' flags %02X " \
           "ndata %u\n", &tag, &filename, &servername, flags, ndata );
  PrintData ( 1, ndata, data );
 }
};

struct ReferenceClone : public ImageAttribute
{
 unsigned long index;
 FString string;

 ReferenceClone ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, REFERENCECLONE )
 {
  index = lwo.Read_U4 ();
  string = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s index %lu string '%s'\n", &tag, index, &string );
 }
};

struct ColorCyclingStill : public ImageAttribute
{
 unsigned short lo;
 unsigned short hi;
 FString name;

 ColorCyclingStill ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, COLORCYCLINGSTILL )
 {
  lo = lwo.Read_S2 ();
  hi = lwo.Read_S2 ();
  name = lwo.Read_FileName ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s lo %u hi %u name '%s'\n", &tag, lo, hi, &name );
 }
};

struct Time : public ImageAttribute
{
 float start_time;
 float duration;
 float frame_rate;

 Time ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, TIME )
 {
  start_time = lwo.Read_Float ();
  duration = lwo.Read_Float ();
  frame_rate = lwo.Read_Float ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s start time %f duration %f frame rate %f\n",
           &tag, start_time, duration, frame_rate );
 }
};

struct Contrast : public ImageAttribute
{
 float contrast_delta;
 unsigned long envelope;

 Contrast ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, CONTRAST )
 {
  contrast_delta = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s contrast delta %f envelope %lu\n",
           &tag, contrast_delta, envelope );
 }
};

struct Brightness : public ImageAttribute
{
 float brightness_delta;
 unsigned long envelope;

 Brightness ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, BRIGHTNESS )
 {
  brightness_delta = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s brightness delta %f envelope %lu\n",
           &tag, brightness_delta, envelope );
 }
};

struct Saturation : public ImageAttribute
{
 float saturation_delta;
 unsigned long envelope;

 Saturation ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, SATURATION )
 {
  saturation_delta = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s saturation delta %f envelope %lu\n",
           &tag, saturation_delta, envelope );
 }
};

struct Hue : public ImageAttribute
{
 float hue_rotation;
 unsigned long envelope;

 Hue ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, HUE )
 {
  hue_rotation = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s hue rotation %f envelope %lu\n",
           &tag, hue_rotation, envelope );
 }
};

struct GammaCorrection : public ImageAttribute
{
 float gamma;
 unsigned long envelope;

 GammaCorrection ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, GAMMACORRECTION )
 {
  gamma = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s gamma %f envelope %lu\n",
           &tag, gamma, envelope );
 }
};

struct ImageNegative : public ImageAttribute
{
 unsigned short enable;

 ImageNegative ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, NEGATIVE )
 {
  enable = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s enable %u\n", &tag, enable );
 }
};

struct PlugInImageFilters : public ImageAttribute
{
 FString server_name;
 unsigned short flags;
 unsigned ndata;
 unsigned char * data;

 PlugInImageFilters ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, PLUGINIMAGEFILTERS )
 {
  server_name = lwo.Read_String ();
  flags = lwo.Read_U2 ();
  ndata = lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~PlugInImageFilters ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( " Subchunk %s server name %s flags %02X ndata %u\n",
           &tag, &server_name, flags, ndata );
  PrintData ( 1, ndata, data );
 }
};

struct PlugInPixelFilters : public ImageAttribute
{
 FString server_name;
 unsigned short flags;
 unsigned ndata;
 unsigned char * data;

 PlugInPixelFilters ( LWO::Tag typetag, LWO & lwo )
  : ImageAttribute ( typetag, PLUGINPIXELFILTERS )
 {
  server_name = lwo.Read_String ();
  flags = lwo.Read_U2 ();
  ndata = lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~PlugInPixelFilters ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( " Subchunk %s server name %s flags %02X ndata %u\n",
           &tag, &server_name, flags, ndata );
  PrintData ( 1, ndata, data );
 }
};


#endif
