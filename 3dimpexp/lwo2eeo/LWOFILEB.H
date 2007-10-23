#ifndef LWOFILEB_INCLUDED
#define LWOFILEB_INCLUDED


struct BlockAttribute : public BasicChunk
{
 enum Type
  {
   UNKNOWN,
   TEXTUREMAPPING,
   PROJECTIONMODE,
   MAJORAXIS,
   IMAGEMAP,
   IMAGEWRAPOPTIONS,
   IMAGEWRAPAMOUNTWIDTH,
   IMAGEWRAPAMOUNTHEIGHT,
   UVVERTEXMAP,
   ANTIALIASINGSTRENGTH,
   PIXELBLENDING,
   STICKYPROJECTION,
   TEXTUREAMPLITUDE,
   AXIS,
   BASICVALUE,
   ALGORITHMANDPARAMETERS,
   PARAMETERNAME,
   ITEMNAME,
   GRADIENTRANGESTART,
   GRADIENTRANGEEND,
   REPEATMODE,
   KEYVALUES,
   KEYPARAMETERS,
   SHADERALGORITHM
  };

 Type blockattributetype;

 BlockAttribute ( LWO::Tag tag_, Type blockattributetype_ )
  : BasicChunk ( tag_ ), blockattributetype ( blockattributetype_ )
 {
 }
};

struct BlockAttributeUnknown : public BlockAttribute
{
 unsigned ndata;
 unsigned char * data;

 BlockAttributeUnknown ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, UNKNOWN )
 {
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~BlockAttributeUnknown ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s unknown ndata %u\n", &tag, ndata );
  PrintData ( 2, ndata, data );
 }
};

#include"lwofilet.h"

struct TextureMapping : public BlockAttribute
{
 Array < TextureMappingAttribute * > attributes;

 TextureMapping ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, TEXTUREMAPPING )
 {
  LWO::Tag tag;

  lwo.SubChunk_Lower ();
  while ( tag = lwo.Read_SubChunk_Header ( NULL ) )
   {
    switch ( TAG_ ( &tag ) )
     {
      case TAG ( 'C', 'N', 'T', 'R' ) :
       attributes[!attributes] = new Position ( tag, lwo );
       break;
      case TAG ( 'S', 'I', 'Z', 'E' ) :
       attributes[!attributes] = new Size ( tag, lwo );
       break;
      case TAG ( 'R', 'O', 'T', 'A' ) :
       attributes[!attributes] = new Orientation ( tag, lwo );
       break;
      case TAG ( 'O', 'R', 'E', 'F' ) :
       attributes[!attributes] = new ReferenceObject ( tag, lwo );
       break;
      case TAG ( 'F', 'A', 'L', 'L' ) :
       attributes[!attributes] = new Falloff ( tag, lwo );
       break;
      case TAG ( 'C', 'S', 'Y', 'S' ) :
       attributes[!attributes] = new CoordinateSystem ( tag, lwo );
       break;
      default :
       attributes[!attributes] = new TextureMappingAttributeUnknown ( tag, lwo );
       break;
     }
   }
 }
 ~TextureMapping ( void )
 {
  unsigned i;

  for ( i = 0; i < !attributes; i++ )
   delete attributes[i];
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "  Subchunk %s nattributes %u\n", &tag, !attributes );
  for ( i = 0; i < !attributes; i++ )
   attributes[i]->Print ();
 }
};

struct ProjectionMode : public BlockAttribute
{
 unsigned short projection_mode;

 ProjectionMode ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, PROJECTIONMODE )
 {
  projection_mode = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s projection mode %u\n", &tag, projection_mode );
 }
};

struct MajorAxis : public BlockAttribute
{
 unsigned short texture_axis;

 MajorAxis ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, MAJORAXIS )
 {
  texture_axis = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s texture axis %u\n", &tag, texture_axis );
 }
};

struct ImageMap : public BlockAttribute
{
 unsigned long texture_image;

 ImageMap ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, IMAGEMAP )
 {
  texture_image = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s texture image %lu\n", &tag, texture_image );
 }
};

struct ImageWrapOptions : public BlockAttribute
{
 unsigned short width_wrap;
 unsigned short height_wrap;

 ImageWrapOptions ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, IMAGEWRAPOPTIONS )
 {
  width_wrap = lwo.Read_U2 ();
  height_wrap = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s width wrap %u height wrap %u\n",
           &tag, width_wrap, height_wrap );
 }
};

struct ImageWrapAmountWidth : public BlockAttribute
{
 float cycles;
 unsigned long envelope;

 ImageWrapAmountWidth ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, IMAGEWRAPAMOUNTWIDTH )
 {
  cycles = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s cycles %f envelope %lu\n", &tag, cycles, envelope );
 }
};

struct ImageWrapAmountHeight : public BlockAttribute
{
 float cycles;
 unsigned long envelope;

 ImageWrapAmountHeight ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, IMAGEWRAPAMOUNTHEIGHT )
 {
  cycles = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s cycles %f envelope %lu\n", &tag, cycles, envelope );
 }
};

struct UVVertexMap : public BlockAttribute
{
 FString txuv_map_name;

 UVVertexMap ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, UVVERTEXMAP )
 {
  txuv_map_name = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s txuv map name '%s'\n", &tag, &txuv_map_name );
 }
};

struct AntialiasingStrength : public BlockAttribute
{
 unsigned short flags;
 float antialiasing_strength;

 AntialiasingStrength ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, ANTIALIASINGSTRENGTH )
 {
  flags = lwo.Read_U2 ();
  antialiasing_strength = lwo.Read_Float ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s flags %u antialiasing strength %f\n",
           &tag, flags, antialiasing_strength );
 }
};

struct PixelBlending : public BlockAttribute
{
 unsigned short flags;

 PixelBlending ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, PIXELBLENDING )
 {
  flags = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s flags %u\n", &tag, flags );
 }
};

struct StickyProjection : public BlockAttribute
{
 unsigned short on_off;
 float time;

 StickyProjection ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, STICKYPROJECTION )
 {
  on_off = lwo.Read_U2 ();
  time = lwo.Read_Float ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s on off %u time %f\n", &tag, on_off, time );
 }
};

struct TextureAmplitude : public BlockAttribute
{
 float amplitude;
 unsigned long envelope;

 TextureAmplitude ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, TEXTUREAMPLITUDE )
 {
  amplitude = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s amplitude %f envelope %lu\n",
           &tag, amplitude, envelope );
 }
};

struct Axis : public BlockAttribute
{
 unsigned short axis;

 Axis ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, AXIS )
 {
  axis = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s axis %u\n", &tag, axis );
 }
};

struct BasicValue : public BlockAttribute
{
 int nvalues;
 union
 {
  float scalar;
  LWO::Vector vector;
 } value;

 BasicValue ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, BASICVALUE )
 {
  if ( lwo.SubChunk_Left () == 12 )
   {
    nvalues = 3;
    value.vector = lwo.Read_Vector ();
   }
  else
   {
    nvalues = 1;
    value.scalar = lwo.Read_Float ();
   }
 }
 void Print ( void )
 {
  if ( nvalues == 3 )
   printf ( "  Subchunk %s vector %f %f %f\n", &tag,
            value.vector.x, value.vector.y, value.vector.z );
  else
   printf ( "  Subchunk %s scalar %f\n", &tag, value.scalar );
 }
};

struct AlgorithmAndParameters : public BlockAttribute
{
 FString algorithm_name;
 unsigned ndata;
 unsigned char * data;

 AlgorithmAndParameters ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, ALGORITHMANDPARAMETERS )
 {
  algorithm_name = lwo.Read_String ();
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~AlgorithmAndParameters ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s algiruthm name '%s' ndata %u\n",
           &tag, &algorithm_name, ndata );
  PrintData ( 2, ndata, data );
 }
};

struct ParameterName : public BlockAttribute
{
 FString parameter;

 ParameterName ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, PARAMETERNAME )
 {
  parameter = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s parameter '%s'\n", &tag, &parameter );
 }
};

struct ItemName : public BlockAttribute
{
 FString item_name;

 ItemName ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, ITEMNAME )
 {
  item_name = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s item name %s\n", &tag, &item_name );
 }
};

struct GradientRangeStart : public BlockAttribute
{
 float input_range;

 GradientRangeStart ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, GRADIENTRANGESTART )
 {
  input_range = lwo.Read_Float ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s input range %f\n", &tag, input_range );
 }
};

struct GradientRangeEnd : public BlockAttribute
{
 float input_range;

 GradientRangeEnd ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, GRADIENTRANGEEND )
 {
  input_range = lwo.Read_Float ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s input range %f\n", &tag, input_range );
 }
};

struct RepeatMode : public BlockAttribute
{
 unsigned short repeat_mode;

 RepeatMode ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, REPEATMODE )
 {
  repeat_mode = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s repeat mode %u\n", &tag, repeat_mode );
 }
};

struct KeyValues : public BlockAttribute
{
 struct Key_values
 {
  float input;
  float output[4];
 };
 Array < Key_values > key_values;

 KeyValues ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, KEYVALUES )
 {
  unsigned i;

  while ( lwo.SubChunk_Left () > 0 )
   {
    unsigned nkey_values = !key_values;

    key_values[nkey_values].input = lwo.Read_Float ();
    for ( i = 0; i < 4; i++ )
     key_values[nkey_values].output[i] = lwo.Read_Float ();
   }
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "  Subchunk %s nkey values %u\n", &tag, !key_values );
  for ( i = 0; i < !key_values; i++ )
   printf ( "   %u: %f %f %f %f %f\n", i, key_values[i].input,
            key_values[i].output[0], key_values[i].output[1],
            key_values[i].output[2], key_values[i].output[3] );
 }
};

struct KeyParameters : public BlockAttribute
{
 Array < unsigned short > interpolation;

 KeyParameters ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, KEYPARAMETERS )
 {
  while ( lwo.SubChunk_Left () > 1 )
   interpolation[!interpolation] = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "  Subchunk %s ninterpolation %u\n", &tag, !interpolation );
  printf ( "  " );
  for ( i = 0; i < !interpolation; i++ )
   printf ( " %u", interpolation[i] );
  printf ( "\n" );
 }
};

struct ShaderAlgorithm : public BlockAttribute
{
 FString algorithm_name;
 unsigned ndata;
 unsigned char * data;

 ShaderAlgorithm ( LWO::Tag typetag, LWO & lwo )
  : BlockAttribute ( typetag, SHADERALGORITHM )
 {
  algorithm_name = lwo.Read_String ();
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 void Print ( void )
 {
  printf ( "  Subchunk %s algorithm name '%s' ndata %u\n",
           &tag, &algorithm_name, ndata );
  PrintData ( 2, ndata, data );
 }
};


#endif
