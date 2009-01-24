#ifndef LWOFILES_INCLUDED
#define LWOFILES_INCLUDED


struct SurfaceAttribute : public BasicChunk
{
 enum SurfaceAttributeType
 {
  UNKNOWN,
  BASECOLOR,
  DIFFUSE,
  LUMINOSITY,
  SPECULAR,
  REFLECTION,
  TRANSPARENCY,
  TRANSLUCENCY,
  SPECULARGLOSSINESS,
  DIFFUSESHARPNESS,
  BUMPINTENSITY,
  POLYGONSIDENESS,
  MAXSMOOTHINGANGLE,
  REFLECTIONOPTIONS,
  REFLECTIONMAPIMAGE,
  REFLECTIONMAPIMAGESEAMANGLE,
  REFLECTIONBLURRING,
  REFRACTIVEINDEX,
  TRANSPARENCYOPTIONS,
  REFRACTIONMAPIMAGE,
  REFRACTIONBLURRING,
  COLORHIGHLIGHTS,
  COLORFILTER,
  ADDITIVETRANSPARENCY,
  GLOWEFFECT,
  RENDEROUTLINES,
  ALPHAMODE,
  VERTEXCOLORMAP,
  BLOCK,
  COMMENT,
  COMPATIBILITYVERSION
 };

 SurfaceAttributeType surfaceattributetype;

 SurfaceAttribute ( LWO::Tag tag_, SurfaceAttributeType surfaceattributetype_ )
  : BasicChunk ( tag_ ), surfaceattributetype ( surfaceattributetype_ )
 {
 }
};

struct SurfaceUnknown : public SurfaceAttribute
{
 unsigned ndata;
 unsigned char * data;

 SurfaceUnknown ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, UNKNOWN )
 {
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~SurfaceUnknown ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( " Subchunk %s unknown ndata %u\n", &tag, ndata );
  PrintData ( 1, ndata, data );
 }
};

struct BaseColor : public SurfaceAttribute
{
 LWO::Color base_color;
 unsigned long envelope;

 BaseColor ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, BASECOLOR )
 {
  base_color = lwo.Read_Color ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s base Color %f %f %f envelope %lu\n",
           &tag, base_color.red, base_color.green, base_color.blue,
           envelope );
 }
};

struct Diffuse : public SurfaceAttribute
{
 float intensity;
 unsigned long envelope;

 Diffuse ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, DIFFUSE )
 {
  intensity = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s intensity %f envelope %lu\n",
           &tag, intensity, envelope );
 }
};

struct Luminosity : public SurfaceAttribute
{
 float intensity;
 unsigned long envelope;

 Luminosity ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, LUMINOSITY )
 {
  intensity = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s intensity %f envelope %lu\n",
           &tag, intensity, envelope );
 }
};

struct Specular : public SurfaceAttribute
{
 float intensity;
 unsigned long envelope;

 Specular ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, SPECULAR )
 {
  intensity = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s intensity %f envelope %lu\n",
           &tag, intensity, envelope );
 }
};

struct Reflection : public SurfaceAttribute
{
 float intensity;
 unsigned long envelope;

 Reflection ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, REFLECTION )
 {
  intensity = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s intensity %f envelope %lu\n",
           &tag, intensity, envelope );
 }
};

struct Transparency : public SurfaceAttribute
{
 float intensity;
 unsigned long envelope;

 Transparency ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, TRANSPARENCY )
 {
  intensity = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s intensity %f envelope %lu\n",
           &tag, intensity, envelope );
 }
};

struct Translucency : public SurfaceAttribute
{
 float intensity;
 unsigned long envelope;

 Translucency ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, TRANSLUCENCY )
 {
  intensity = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s intensity %f envelope %lu\n",
           &tag, intensity, envelope );
 }
};

struct SpecularGlossiness : public SurfaceAttribute
{
 float glossiness;
 unsigned long envelope;

 SpecularGlossiness ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, SPECULARGLOSSINESS )
 {
  glossiness = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s glossiness %f envelope %lu\n",
           &tag, glossiness, envelope );
 }
};

struct DiffuseSharpness : public SurfaceAttribute
{
 float sharpness;
 unsigned long envelope;

 DiffuseSharpness ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, DIFFUSESHARPNESS )
 {
  sharpness = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s sharpness %f envelope %lu\n",
           &tag, sharpness, envelope );
 }
};

struct BumpIntensity : public SurfaceAttribute
{
 float strength;
 unsigned long envelope;

 BumpIntensity ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, BUMPINTENSITY )
 {
  strength = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s strength %f envelope %lu\n",
           &tag, strength, envelope );
 }
};

struct PolygonSideness : public SurfaceAttribute
{
 unsigned short sideness;

 PolygonSideness ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, POLYGONSIDENESS )
 {
  sideness = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s sideness %u\n", &tag, sideness );
 }
};

struct MaxSmoothingAngle : public SurfaceAttribute
{
 float max_smoothing_angle;

 MaxSmoothingAngle ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, MAXSMOOTHINGANGLE )
 {
  max_smoothing_angle = lwo.Read_Float ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s max smoothing angle %f\n",
           &tag, max_smoothing_angle );
 }
};

struct ReflectionOptions : public SurfaceAttribute
{
 unsigned short reflection_options;

 ReflectionOptions ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, REFLECTIONOPTIONS )
 {
  reflection_options = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s reflection options %u\n", &tag, reflection_options );
 }
};

struct ReflectionMapImage : public SurfaceAttribute
{
 unsigned long image;

 ReflectionMapImage ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, REFLECTIONMAPIMAGE )
 {
  image = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s image %lu\n", &tag, image );
 }
};

struct ReflectionMapImageSeamAngle : public SurfaceAttribute
{
 float seam_angle;
 unsigned long envelope;

 ReflectionMapImageSeamAngle ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, REFLECTIONMAPIMAGESEAMANGLE )
 {
  seam_angle = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s seam angle %f envelope %lu\n",
           &tag, seam_angle, envelope );
 }
};

struct ReflectionBlurring : public SurfaceAttribute
{
 float blur_percentage;
 unsigned long envelope;

 ReflectionBlurring ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, REFLECTIONBLURRING )
 {
  blur_percentage = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s blur percentage %f envelope %lu\n",
           &tag, blur_percentage, envelope );
 }
};

struct RefractiveIndex : public SurfaceAttribute
{
 float refractive_index;
 unsigned long envelope;

 RefractiveIndex ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, REFRACTIVEINDEX )
 {
  refractive_index = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s refractive index %f envelope %lu\n",
           &tag, refractive_index, envelope );
 }
};

struct TransparencyOptions : public SurfaceAttribute
{
 unsigned short transparency_options;

 TransparencyOptions ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, TRANSPARENCYOPTIONS )
 {
  transparency_options = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s transparenct options %u\n",
           &tag, transparency_options );
 }
};

struct RefractionMapImage : public SurfaceAttribute
{
 unsigned long image;

 RefractionMapImage ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, REFRACTIONMAPIMAGE )
 {
  image = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s image %lu\n", &tag, image );
 }
};

struct RefractionBlurring : public SurfaceAttribute
{
 float blur_percentage;
 unsigned long envelope;

 RefractionBlurring ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, REFRACTIONBLURRING )
 {
  blur_percentage = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s blur percentage %f envelope %lu\n",
           &tag, blur_percentage, envelope );
 }
};

struct ColorHighlights : public SurfaceAttribute
{
 float color_highlights;
 unsigned long envelope;

 ColorHighlights ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, COLORHIGHLIGHTS )
 {
  color_highlights = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s color highlights %f envelope %lu\n",
           &tag, color_highlights, envelope );
 }
};

struct ColorFilter : public SurfaceAttribute
{
 float color_filter;
 unsigned long envelope;

 ColorFilter ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, COLORFILTER )
 {
  color_filter = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s color filter %f envelope %lu\n",
           &tag, color_filter, envelope );
 }
};

struct AdditiveTransparency : public SurfaceAttribute
{
 float additive;
 unsigned long envelope;

 AdditiveTransparency ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, ADDITIVETRANSPARENCY )
 {
  additive = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s additive %f envelope %lu\n",
           &tag, additive, envelope );
 }
};

struct GlowEffect : public SurfaceAttribute
{
 unsigned short type;
 float intensity;
 unsigned long intensity_envelope;
 float size;
 unsigned long size_envelope;

 GlowEffect ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, GLOWEFFECT )
 {
  type = lwo.Read_U2 ();
  intensity = lwo.Read_Float ();
  intensity_envelope = lwo.Read_Index ();
  size = lwo.Read_Float ();
  size_envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s type %u intensity %f intensity envelope %lu" \
           " size %f size envelope %lu\n", &tag, type, intensity,
           intensity_envelope, size, size_envelope );
 }
};

struct RenderOutlines : public SurfaceAttribute
{
 unsigned short flags;
 int size_present;
 float size;
 unsigned long size_envelope;
 int color_present;
 LWO::Color color;
 unsigned long color_envelope;

 RenderOutlines ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, RENDEROUTLINES )
 {
  flags = lwo.Read_U2 ();
  size_present = 0;
  color_present = 0;
  if ( lwo.SubChunk_Left () > 0 )
   {
    size_present = 1;
    size = lwo.Read_Float ();
    size_envelope = lwo.Read_Index ();
    if ( lwo.SubChunk_Left () > 0 )
     {
      color_present = 1;
      color = lwo.Read_Color ();
      color_envelope = lwo.Read_Index ();
     }
    }
 }
 void Print ( void )
 {
  if ( !size_present )
   printf ( " Subchunk %s flags %u\n", &tag, flags );
  else
   if ( !color_present )
    printf ( " Subchunk %s flags %u size %f size envelope %lu\n",
             &tag, flags, size, size_envelope );
   else
    printf ( " Subchunk %s flags %u size %f size envelope %lu" \
             " color %f %f %f color envelope %lu\n", &tag, flags, size,
             size_envelope, color.red, color.green, color.blue,
             color_envelope );
 }
};

struct AlphaMode : public SurfaceAttribute
{
 unsigned short mode;
 float value;

 AlphaMode ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, ALPHAMODE )
 {
  mode = lwo.Read_U2 ();
  value = lwo.Read_Float ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s mode %u value %f\n", &tag, mode, value );
 }
};

struct VertexColorMap : public SurfaceAttribute
{
 float intensity;
 unsigned long envelope;
 LWO::Tag vmap_type;
 FString name;

 VertexColorMap ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, VERTEXCOLORMAP )
 {
  intensity = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
  vmap_type = lwo.Read_Tag ();
  name = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s diffuse %f envelope %lu vmap type %s name '%s'\n",
           &tag, intensity, envelope, &vmap_type, &name );
 }
};

#include"lwofileh.h"
#include"lwofileb.h"

struct Block : public SurfaceAttribute
{
 BlockHeader * header;
 unsigned nattributes;
 Array < BlockAttribute * > attributes;

 Block ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, BLOCK )
 {
  LWO::Tag tag;

  lwo.SubChunk_Lower ();
  tag = lwo.Read_SubChunk_Header ( NULL );
  header = NULL;
  switch ( TAG_ ( &tag ) )
   {
    case TAG ( 'I', 'M', 'A', 'P' ) :
     header = new BlockHeader ( tag, BlockHeader::IMAGEMAPTEXTURE, lwo );
     break;
    case TAG ( 'P', 'R', 'O', 'C' ) :
     header = new BlockHeader ( tag, BlockHeader::PROCEDURALTEXTURE, lwo );
     break;
    case TAG ( 'G', 'R', 'A', 'D' ) :
     header = new BlockHeader ( tag, BlockHeader::GRADIENTTEXTURE, lwo );
     break;
    case TAG ( 'S', 'H', 'D', 'R' ) :
     header = new BlockHeader ( tag, BlockHeader::SHADERPLUGIN, lwo );
     break;
    default :
     header = new BlockHeader ( tag, BlockHeader::UNKNOWN, lwo );
     break;
   }
  if ( header == NULL )
   {
    lwo.SubChunk_Higher ();
    lwo.Skip_SubChunk ();
   }
  else
   while ( tag = lwo.Read_SubChunk_Header ( NULL ) )
    {
     switch ( header -> blockheadertype )
      {
       case BlockHeader::IMAGEMAPTEXTURE :
        switch ( TAG_ ( &tag ) )
         {
          case TAG ( 'T', 'M', 'A', 'P' ) :
           attributes[!attributes] = new TextureMapping ( tag, lwo );
           break;
          case TAG ( 'P', 'R', 'O', 'J' ) :
           attributes[!attributes] = new ProjectionMode ( tag, lwo );
           break;
          case TAG ( 'A', 'X', 'I', 'S' ) :
           attributes[!attributes] = new MajorAxis ( tag, lwo );
           break;
          case TAG ( 'I', 'M', 'A', 'G' ) :
           attributes[!attributes] = new ImageMap ( tag, lwo );
           break;
          case TAG ( 'W', 'R', 'A', 'P' ) :
           attributes[!attributes] = new ImageWrapOptions ( tag, lwo );
           break;
          case TAG ( 'W', 'R', 'P', 'W' ) :
           attributes[!attributes] = new ImageWrapAmountWidth ( tag, lwo );
           break;
          case TAG ( 'W', 'R', 'P', 'H' ) :
           attributes[!attributes] = new ImageWrapAmountHeight ( tag, lwo );
           break;
          case TAG ( 'V', 'M', 'A', 'P' ) :
           attributes[!attributes] = new UVVertexMap ( tag, lwo );
           break;
          case TAG ( 'A', 'A', 'S', 'T' ) :
           attributes[!attributes] = new AntialiasingStrength ( tag, lwo );
           break;
          case TAG ( 'P', 'I', 'X', 'B' ) :
           attributes[!attributes] = new PixelBlending ( tag, lwo );
           break;
          case TAG ( 'S', 'T', 'C', 'K' ) :
           attributes[!attributes] = new StickyProjection ( tag, lwo );
           break;
          case TAG ( 'T', 'A', 'M', 'P' ) :
           attributes[!attributes] = new TextureAmplitude ( tag, lwo );
           break;
          default :
           attributes[!attributes] = new BlockAttributeUnknown ( tag, lwo );
           break;
         }
        break;
       case BlockHeader::PROCEDURALTEXTURE :
        switch ( TAG_ ( &tag ) )
         {
          case TAG ( 'A', 'X', 'I', 'S' ) :
           attributes[!attributes] = new Axis ( tag, lwo );
           break;
          case TAG ( 'V', 'A', 'L', 'U' ) :
           attributes[!attributes] = new BasicValue ( tag, lwo );
           break;
          case TAG ( 'F', 'U', 'N', 'C' ) :
           attributes[!attributes] = new AlgorithmAndParameters ( tag, lwo );
           break;
          default :
           attributes[!attributes] = new BlockAttributeUnknown ( tag, lwo );
           break;
         }
        break;
       case BlockHeader::GRADIENTTEXTURE :
        switch ( TAG_ ( &tag ) )
         {
          case TAG ( 'P', 'N', 'A', 'M' ) :
           attributes[!attributes] = new ParameterName ( tag, lwo );
           break;
          case TAG ( 'I', 'N', 'A', 'M' ) :
           attributes[!attributes] = new ItemName ( tag, lwo );
           break;
          case TAG ( 'G', 'R', 'S', 'T' ) :
           attributes[!attributes] = new GradientRangeStart ( tag, lwo );
           break;
          case TAG ( 'G', 'R', 'E', 'N' ) :
           attributes[!attributes] = new GradientRangeEnd ( tag, lwo );
           break;
          case TAG ( 'G', 'R', 'P', 'T' ) :
           attributes[!attributes] = new RepeatMode ( tag, lwo );
           break;
          case TAG ( 'F', 'K', 'E', 'Y' ) :
           attributes[!attributes] = new KeyValues ( tag, lwo );
           break;
          case TAG ( 'I', 'K', 'E', 'Y' ) :
           attributes[!attributes] = new KeyParameters ( tag, lwo );
           break;
          default :
           attributes[!attributes] = new BlockAttributeUnknown ( tag, lwo );
           break;
         }
        break;
       case BlockHeader::SHADERPLUGIN :
        switch ( TAG_ ( &tag ) )
         {
          case TAG ( 'F', 'U', 'N', 'C' ) :
           attributes[!attributes] = new ShaderAlgorithm ( tag, lwo );
           break;
          default :
           attributes[!attributes] = new BlockAttributeUnknown ( tag, lwo );
           break;
         }
        break;
       default :
        attributes[!attributes] = new BlockAttributeUnknown ( tag, lwo );
        break;
      }
    }
 }
 ~Block ( void )
 {
  unsigned i;

  delete header;
  for ( i = 0; i < !attributes; i++ )
   delete attributes[i];
 }
 void Print ( void )
 {
  unsigned i;

  printf ( " Subchunk %s nattributes %u\n", &tag, !attributes );
  if ( header != NULL )
   header->Print ();
  for ( i = 0; i < !attributes; i++ )
   attributes[i]->Print ();
 }
};

struct Comment : public SurfaceAttribute
{
 FString comment;

 Comment ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, COMMENT )
 {
  comment = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s comment '%s'\n", &comment );
 }
};

struct CompatibilityVersion : public SurfaceAttribute
{
 unsigned long version;

 CompatibilityVersion ( LWO::Tag typetag, LWO & lwo )
  : SurfaceAttribute ( typetag, COMPATIBILITYVERSION )
 {
  version = lwo.Read_U4 ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s version %lu\n", &tag, version );
 }
};

#endif
