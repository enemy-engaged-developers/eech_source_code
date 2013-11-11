#ifndef LWOFILE_H_INCLUDED
#define LWOFILE_H_INCLUDED
#include <stdio.h>
#include "lwo.h"

struct BasicChunk
{
 LWO::Tag tag;

 BasicChunk ( LWO::Tag tag_ )
  : tag ( tag_ )
 {
 }
 virtual ~BasicChunk ( void )
 {
 }
 virtual void Print ( void ) = 0;

 protected :

 static void PrintData ( unsigned offset, unsigned ndata,
                         unsigned char * data )
 {
  unsigned i;

  for ( i = 0; i < offset; i++ )
   printf ( " " );
  for ( i = 0; i < ndata; i++ )
   printf ( " %02X", data[i] );
  printf ( "\n" );
 }
};

struct Chunk : public BasicChunk
{
 enum ChunkType
  {
   UNKNOWN,
   LAYER,
   POINTS,
   VERTEXMAPPING,
   POLYGONLIST,
   TAGS,
   PTAGS,
   DISCONTINUOUSVERTEXMAPPING,
   ENVELOPE,
   IMAGE,
   SURFACE,
   BOUNDINGBOX,
   DESCRIPTIONLINE,
   COMMENTARYTEXT,
   THUMBNAILICONIMAGE
  };

 ChunkType chunktype;

 Chunk ( LWO::Tag tag_, ChunkType chunktype_ )
  : BasicChunk ( tag_ ), chunktype ( chunktype_ )
 {
 }
};

struct Unknown : public Chunk
{
 unsigned ndata;
 unsigned char * data;

 Unknown ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, UNKNOWN )
 {
  ndata = ( unsigned ) lwo.Chunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~Unknown ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( "Chunk %s unknown ndata %u\n", &tag, ndata );
  PrintData ( 0, ndata, data );
 }
};

struct Layer : public Chunk
{
 unsigned short number;
 unsigned short flags;
 LWO::Vector pivot;
 FString name;
 unsigned short parent;

 Layer ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, LAYER )
 {
  number = lwo.Read_U2 ();
  flags = lwo.Read_U2 ();
  pivot = lwo.Read_Vector ();
  name = lwo.Read_String ();
  if ( lwo.Chunk_Left () > 0 )
   parent = lwo.Read_U2 ();
  else
   parent = 0xFFFF;
 }
 void Print ( void )
 {
  printf ( "Chunk %s number %u flags %u pivot %f %f %f name '%s' parent %u\n",
           &tag, number, flags, pivot.x, pivot.y, pivot.z, &name, parent );
 }
};

struct Points : public Chunk
{
 Array < LWO::Vector > points;

 Points ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, POINTS )
 {
  while ( lwo.Chunk_Left () > 11 )
   points[!points] = lwo.Read_Vector ();
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "Chunk %s npoints %u\n", &tag, !points );
  for ( i = 0; i < !points; i++ )
   printf ( " %u: %f %f %f\n", i, points[i].x, points[i].y, points[i].z );
 }
};

struct VertexMapping : public Chunk
{
 LWO::Tag type;
 unsigned short dimention;
 FString name;
 struct Mapping
 {
  unsigned long vert;
  Array < float > value;
 };
 Array < Mapping > mapping;

 VertexMapping ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, VERTEXMAPPING )
 {
  unsigned i;

  type = lwo.Read_Tag ();
  dimention = lwo.Read_U2 ();
  name = lwo.Read_String ();
  while ( lwo.Chunk_Left () > 0 )
   {
    unsigned nmapping = !mapping;

    mapping[nmapping].vert = lwo.Read_Index ();
    if ( dimention )
     {
      for ( i = 0; i < dimention; i++ )
       mapping[nmapping].value[i] = lwo.Read_Float ();
     }
   }
 }
 void Print ( void )
 {
  unsigned i;
  unsigned short j;

  printf ( "Chunk %s type %s dimention %u name '%s' nmapping %u\n",
           &tag, &type, dimention, &name, !mapping );
  for ( i = 0; i < !mapping; i++ )
   {
    printf ( " %u: %lu", i, mapping[i].vert );
    for ( j = 0; j < dimention; j++ )
     printf ( " %f", mapping[i].value[j] );
    printf ( "\n" );
   }
 }
};

struct PolygonList : public Chunk
{
 LWO::Tag type;
 struct List
 {
  unsigned short numvertflags;
  Array < unsigned long > vert;
 };
 Array < List > list;

 PolygonList ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, POLYGONLIST )
 {
  unsigned size;
  unsigned i;

  type = lwo.Read_Tag ();
  while ( lwo.Chunk_Left () > 0 )
   {
    unsigned npolygons = !list;

    list[npolygons].numvertflags = lwo.Read_U2 ();
    size = list[npolygons].numvertflags & 0x03FFu;
    for ( i = 0; i < size; i++ )
     list[npolygons].vert[i] = lwo.Read_Index ();
   }
 }
 void Print ( void )
 {
  unsigned i, j;

  printf ( "Chunk %s type %s npolygons %u\n", &tag, &type, !list );
  for ( i = 0; i < !list; i++ )
   {
    printf ( " %i (%u): ", i, list[i].numvertflags & 0x03FFu );
    for ( j = 0; j < list[i].numvertflags & 0x03FFu; j++ )
     printf ( " %lu", list[i].vert[j] );
    printf ( "\n" );
   }
 }
};

struct Tags : public Chunk
{
 Array < FString > tags;

 Tags ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, TAGS )
 {
  while ( lwo.Chunk_Left () > 0 )
   tags[!tags] = lwo.Read_String ();
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "Chunk %s ntags %u\n", &tag, !tags );
  for ( i = 0; i < !tags; i++ )
   printf ( " %u: %s\n", i, &tags[i] );
 }
};

struct PTags : public Chunk
{
 LWO::Tag type;
 struct Ptags
 {
  unsigned long poly;
  unsigned short tag;
 };
 Array < Ptags > ptags;

 PTags ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, PTAGS )
 {
  type = lwo.Read_Tag ();
  while ( lwo.Chunk_Left () > 0 )
   {
    unsigned nptags = !ptags;

    ptags[nptags].poly = lwo.Read_Index ();
    ptags[nptags].tag = lwo.Read_U2 ();
   }
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "Chunk %s type %s nptags %u\n", &tag, &type, !ptags );
  for ( i = 0; i < !ptags; i++ )
   printf ( " %u: %lu %u\n", i, ptags[i].poly, ptags[i].tag );
 }
};

struct DiscontinuousVertexMapping : public Chunk
{
 LWO::Tag type;
 unsigned short dimention;
 FString name;
 struct Mapping
 {
  unsigned long vert;
  unsigned long poly;
  Array < float > value;
 };
 Array < Mapping > mapping;

 DiscontinuousVertexMapping ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, DISCONTINUOUSVERTEXMAPPING )
 {
  unsigned i;

  type = lwo.Read_Tag ();
  dimention = lwo.Read_U2 ();
  name = lwo.Read_String ();
  while ( lwo.Chunk_Left () > 0 )
   {
    unsigned nmapping = !mapping;

    mapping[nmapping].vert = lwo.Read_Index ();
    mapping[nmapping].poly = lwo.Read_Index ();
    if ( dimention )
     {
      for ( i = 0; i < dimention; i++ )
       mapping[nmapping].value[i] = lwo.Read_Float ();
     }
   }
 }
 void Print ( void )
 {
  unsigned i;
  unsigned short j;

  printf ( "Chunk %s type %s dimention %u name '%s' nmapping %u\n",
           &tag, &type, dimention, &name, !mapping );
  for ( i = 0; i < !mapping; i++ )
   {
    printf ( " %u: %lu %lu", i, mapping[i].vert, mapping[i].poly );
    for ( j = 0; j < dimention; j++ )
     printf ( " %f", mapping[i].value[j] );
    printf ( "\n" );
   }
 }
};

#include"lwofilee.h"

struct Envelope : public Chunk
{
 unsigned long index;
 Array < EnvelopeAttribute * > attributes;

 Envelope ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, ENVELOPE )
 {
  LWO::Tag tag;

  index = lwo.Read_Index ();
  while ( tag = lwo.Read_SubChunk_Header ( NULL ) )
   {
    switch ( TAG_ ( &tag ) )
     {
      case TAG ( 'T', 'Y', 'P', 'E' ) :
       attributes[!attributes] = new EnvelopeType ( tag, lwo );
       break;
      case TAG ( 'P', 'R', 'E', ' ' ) :
       attributes[!attributes] = new PreBehavior ( tag, lwo );
       break;
      case TAG ( 'P', 'O', 'S', 'T' ) :
       attributes[!attributes] = new PostBehavior ( tag, lwo );
       break;
      case TAG ( 'K', 'E', 'Y', ' ' ) :
       attributes[!attributes] = new KeyFrameTimeAndValue ( tag, lwo );
       break;
      case TAG ( 'S', 'P', 'A', 'N' ) :
       attributes[!attributes] = new IntervalInterpolation ( tag, lwo );
       break;
      case TAG ( 'C', 'H', 'A', 'N' ) :
       attributes[!attributes] = new PlugInChannelModifiers ( tag, lwo );
       break;
      case TAG ( 'N', 'A', 'M', 'E' ) :
       attributes[!attributes] = new ChannelName ( tag, lwo );
       break;
      default :
       attributes[!attributes] = new EnvelopeUnknown ( tag, lwo );
       break;
     }
   }
 }
 ~Envelope ( void )
 {
  unsigned i;

  for ( i = 0; i < !attributes; i++ )
   delete attributes[i];
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "Chunk %s index %lu nattributes %u\n", &tag, index, !attributes );
  for ( i = 0; i < !attributes; i++ )
   attributes[i]->Print ();
 }
};

#include"lwofilei.h"

struct Image : public Chunk
{
 unsigned long index;
 Array < ImageAttribute * > attributes;

 Image ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, IMAGE )
 {
  LWO::Tag tag;

  index = lwo.Read_U4 ();
  while ( tag = lwo.Read_SubChunk_Header ( NULL ) )
   {
    switch ( TAG_ ( &tag ) )
     {
      case TAG ( 'S', 'T', 'I', 'L' ) :
       attributes[!attributes] = new StillImage ( tag, lwo );
       break;
      case TAG ( 'I', 'S', 'E', 'Q' ) :
       attributes[!attributes] = new ImageSequence ( tag, lwo );
       break;
      case TAG ( 'A', 'N', 'I', 'M' ) :
       attributes[!attributes] = new PlugInAnimation ( tag, lwo );
       break;
      case TAG ( 'X', 'R', 'E', 'F' ) :
       attributes[!attributes] = new ReferenceClone ( tag, lwo );
       break;
      case TAG ( 'S', 'T', 'C', 'C' ) :
       attributes[!attributes] = new ColorCyclingStill ( tag, lwo );
       break;
      case TAG ( 'T', 'I', 'M', 'E' ) :
       attributes[!attributes] = new Time ( tag, lwo );
       break;
      case TAG ( 'C', 'O', 'N', 'T' ) :
       attributes[!attributes] = new Contrast ( tag, lwo );
       break;
      case TAG ( 'B', 'R', 'I', 'T' ) :
       attributes[!attributes] = new Brightness ( tag, lwo );
       break;
      case TAG ( 'S', 'A', 'T', 'R' ) :
       attributes[!attributes] = new Saturation ( tag, lwo );
       break;
      case TAG ( 'H', 'U', 'E', ' ' ) :
       attributes[!attributes] = new Hue ( tag, lwo );
       break;
      case TAG ( 'G', 'A', 'M', 'M' ) :
       attributes[!attributes] = new GammaCorrection ( tag, lwo );
       break;
      case TAG ( 'N', 'E', 'G', 'A' ) :
       attributes[!attributes] = new ImageNegative ( tag, lwo );
       break;
      case TAG ( 'I', 'F', 'L', 'T' ) :
       attributes[!attributes] = new PlugInImageFilters ( tag, lwo );
       break;
      case TAG ( 'P', 'F', 'L', 'T' ) :
       attributes[!attributes] = new PlugInPixelFilters ( tag, lwo );
       break;
      default :
       attributes[!attributes] = new ImageUnknown ( tag, lwo );
       break;
     }
   }
 }
 ~Image ( void )
 {
  unsigned i;

  for ( i = 0; i < !attributes; i++ )
   delete attributes[i];
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "Chunk %s index %lu nattributes %u\n", &tag, index, !attributes );
  for ( i = 0; i < !attributes; i++ )
   attributes[i]->Print ();
 }
};

#include"lwofiles.h"

struct Surface : public Chunk
{
 FString name;
 FString source;
 Array < SurfaceAttribute * > attributes;

 Surface ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, SURFACE )
 {
  LWO::Tag tag;

  name = lwo.Read_String ();
  source = lwo.Read_String ();
  while ( tag = lwo.Read_SubChunk_Header ( NULL ) )
   {
    switch ( TAG_ ( &tag ) )
     {
      case TAG ( 'C', 'O', 'L', 'R' ) :
       attributes[!attributes] = new BaseColor ( tag, lwo );
       break;
      case TAG ( 'D', 'I', 'F', 'F' ) :
       attributes[!attributes] = new Diffuse ( tag, lwo );
       break;
      case TAG ( 'L', 'U', 'M', 'I' ) :
       attributes[!attributes] = new Luminosity ( tag, lwo );
       break;
      case TAG ( 'S', 'P', 'E', 'C' ) :
       attributes[!attributes] = new Specular ( tag, lwo );
       break;
      case TAG ( 'R', 'E', 'F', 'L' ) :
       attributes[!attributes] = new Reflection ( tag, lwo );
       break;
      case TAG ( 'T', 'R', 'A', 'N' ) :
       attributes[!attributes] = new Transparency ( tag, lwo );
       break;
      case TAG ( 'T', 'R', 'N', 'L' ) :
       attributes[!attributes] = new Translucency ( tag, lwo );
       break;
      case TAG ( 'G', 'L', 'O', 'S' ) :
       attributes[!attributes] = new SpecularGlossiness ( tag, lwo );
       break;
      case TAG ( 'S', 'H', 'R', 'P' ) :
       attributes[!attributes] = new DiffuseSharpness ( tag, lwo );
       break;
      case TAG ( 'B', 'U', 'M', 'P' ) :
       attributes[!attributes] = new BumpIntensity ( tag, lwo );
       break;
      case TAG ( 'S', 'I', 'D', 'E' ) :
       attributes[!attributes] = new PolygonSideness ( tag, lwo );
       break;
      case TAG ( 'S', 'M', 'A', 'N' ) :
       attributes[!attributes] = new MaxSmoothingAngle ( tag, lwo );
       break;
      case TAG ( 'R', 'F', 'O', 'P' ) :
       attributes[!attributes] = new ReflectionOptions ( tag, lwo );
       break;
      case TAG ( 'R', 'I', 'M', 'G' ) :
       attributes[!attributes] = new ReflectionMapImage ( tag, lwo );
       break;
      case TAG ( 'R', 'S', 'A', 'N' ) :
       attributes[!attributes] = new ReflectionMapImageSeamAngle ( tag, lwo );
       break;
      case TAG ( 'R', 'B', 'R', 'L' ) :
       attributes[!attributes] = new ReflectionBlurring ( tag, lwo );
       break;
      case TAG ( 'R', 'I', 'N', 'D' ) :
       attributes[!attributes] = new RefractiveIndex ( tag, lwo );
       break;
      case TAG ( 'T', 'R', 'O', 'P' ) :
       attributes[!attributes] = new TransparencyOptions ( tag, lwo );
       break;
      case TAG ( 'T', 'I', 'M', 'G' ) :
       attributes[!attributes] = new RefractionMapImage ( tag, lwo );
       break;
      case TAG ( 'T', 'B', 'L', 'R' ) :
       attributes[!attributes] = new RefractionBlurring ( tag, lwo );
       break;
      case TAG ( 'C', 'L', 'R', 'H' ) :
       attributes[!attributes] = new ColorHighlights ( tag, lwo );
       break;
      case TAG ( 'C', 'L', 'R', 'F' ) :
       attributes[!attributes] = new ColorFilter ( tag, lwo );
       break;
      case TAG ( 'A', 'D', 'T', 'R' ) :
       attributes[!attributes] = new AdditiveTransparency ( tag, lwo );
       break;
      case TAG ( 'G', 'L', 'O', 'W' ) :
       attributes[!attributes] = new GlowEffect ( tag, lwo );
       break;
      case TAG ( 'L', 'I', 'N', 'E' ) :
       attributes[!attributes] = new RenderOutlines ( tag, lwo );
       break;
      case TAG ( 'A', 'L', 'P', 'H' ) :
       attributes[!attributes] = new AlphaMode ( tag, lwo );
       break;
      case TAG ( 'V', 'C', 'O', 'L' ) :
       attributes[!attributes] = new VertexColorMap ( tag, lwo );
       break;
      case TAG ( 'B', 'L', 'O', 'K' ) :
       attributes[!attributes] = new Block ( tag, lwo );
       break;
      case TAG ( 'C', 'M', 'N', 'T' ) :
       attributes[!attributes] = new Comment ( tag, lwo );
       break;
      case TAG ( 'V', 'E', 'R', 'S' ) :
       attributes[!attributes] = new CompatibilityVersion ( tag, lwo );
       break;
      default :
       attributes[!attributes] = new SurfaceUnknown ( tag, lwo );
       break;
     }
   }
 }
 ~Surface ( void )
 {
  unsigned i;

  for ( i = 0; i < !attributes; i++ )
   delete attributes[i];
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "Chunk %s name '%s' source '%s' nattributes %u\n",
           &tag, &name, &source, !attributes );
  for ( i = 0; i < !attributes; i++ )
   attributes[i]->Print ();
 }
};

struct BoundingBox : public Chunk
{
 LWO::Vector min;
 LWO::Vector max;

 BoundingBox ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, BOUNDINGBOX )
 {
  min = lwo.Read_Vector ();
  max = lwo.Read_Vector ();
 }
 void Print ( void )
 {
  printf ( "Chunk %s min %f %f %f max %f %f %f\n",
           &tag, min.x, min.y, min.z, max.x, max.y, max.z );
 }
};

struct DescriptionLine : public Chunk
{
 FString description_line;

 DescriptionLine ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, DESCRIPTIONLINE )
 {
  description_line = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( "Chunk %s description line '%s'\n", &tag, &description_line );
 }
};

struct CommentaryText : public Chunk
{
 FString commentary_text;

 CommentaryText ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, COMMENTARYTEXT )
 {
  commentary_text = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( "Chunk %s commentary text '%s'\n", &tag, &commentary_text );
 }
};

struct ThumbnailIconImage : public Chunk
{
 unsigned short encoding;
 unsigned short width;
 unsigned ndata;
 unsigned char * data;

 ThumbnailIconImage ( LWO::Tag typetag, LWO & lwo )
  : Chunk ( typetag, THUMBNAILICONIMAGE )
 {
  encoding = lwo.Read_U2 ();
  width = lwo.Read_U2 ();
  ndata = ( unsigned ) lwo.Chunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~ThumbnailIconImage ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( "Chunk %s encoding %u width %u ndata %u\n",
           &tag, encoding, width, ndata );
  PrintData ( 0, ndata, data );
 }
};

struct LWOFile
{
 Array < Chunk * > chunks;

 LWOFile ( const char * filename )
 {
  LWO lwo;
  LWO::Tag tag;

  lwo.Open ( filename, NULL );
  while ( tag = lwo.Read_Chunk_Header ( NULL ) )
   {
    switch ( TAG_ ( &tag ) )
     {
      case TAG ( 'L', 'A', 'Y', 'R' ) :
       chunks[!chunks] = new Layer ( tag, lwo );
       break;
      case TAG ( 'P', 'N', 'T', 'S' ) :
       chunks[!chunks] = new Points ( tag, lwo );
       break;
      case TAG ( 'V', 'M', 'A', 'P' ) :
       chunks[!chunks] = new VertexMapping ( tag, lwo );
       break;
      case TAG ( 'P', 'O', 'L', 'S' ) :
       chunks[!chunks] = new PolygonList ( tag, lwo );
       break;
      case TAG ( 'T', 'A', 'G', 'S' ) :
       chunks[!chunks] = new Tags ( tag, lwo );
       break;
      case TAG ( 'P', 'T', 'A', 'G' ) :
       chunks[!chunks] = new PTags ( tag, lwo );
       break;
      case TAG ( 'V', 'M', 'A', 'D' ) :
       chunks[!chunks] = new DiscontinuousVertexMapping ( tag, lwo );
       break;
      case TAG ( 'E', 'N', 'V', 'L' ) :
       chunks[!chunks] = new Envelope ( tag, lwo );
       break;
      case TAG ( 'C', 'L', 'I', 'P' ) :
       chunks[!chunks] = new Image ( tag, lwo );
       break;
      case TAG ( 'S', 'U', 'R', 'F' ) :
       chunks[!chunks] = new Surface ( tag, lwo );
       break;
      case TAG ( 'B', 'B', 'O', 'X' ) :
       chunks[!chunks] = new BoundingBox ( tag, lwo );
       break;
      case TAG ( 'D', 'E', 'S', 'C' ) :
       chunks[!chunks] = new DescriptionLine ( tag, lwo );
       break;
      case TAG ( 'T', 'E', 'X', 'T' ) :
       chunks[!chunks] = new CommentaryText ( tag, lwo );
       break;
      case TAG ( 'I', 'C', 'O', 'N' ) :
       chunks[!chunks] = new ThumbnailIconImage ( tag, lwo );
       break;
      default:
       chunks[!chunks] = new Unknown ( tag, lwo );
       break;
     }
   }
  lwo.Close ();
 }
 ~LWOFile ( void )
 {
  unsigned i;

  for ( i = 0; i < !chunks; i++ )
   delete chunks[i];
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "LWO2 File nchunks %u\n", !chunks );
  for ( i = 0; i < !chunks; i++ )
   chunks[i]->Print ();
 }
};

#endif
