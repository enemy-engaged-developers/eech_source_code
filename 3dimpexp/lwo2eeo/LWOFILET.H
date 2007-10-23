#ifndef LWOFILET_INCLUDED
#define LWOFILET_INCLUDED


struct TextureMappingAttribute : public BasicChunk
{
 enum Type
  {
   UNKNOWN,
   POSITION,
   SIZE,
   ORIENTATION,
   REFERENCEOBJECT,
   FALLOFF,
   COORDINATESYSTEM
  };

 Type texturemappingattributetype;

 TextureMappingAttribute ( LWO::Tag tag_, Type texturemappingattributetype_ )
  : BasicChunk ( tag_ ), texturemappingattributetype ( texturemappingattributetype_ )
 {
 }
};

struct TextureMappingAttributeUnknown : public TextureMappingAttribute
{
 unsigned ndata;
 unsigned char * data;

 TextureMappingAttributeUnknown ( LWO::Tag typetag, LWO & lwo )
  : TextureMappingAttribute ( typetag, UNKNOWN )
 {
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~TextureMappingAttributeUnknown ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s unknown ndata %u\n", &tag, ndata );
  PrintData ( 3, ndata, data );
 }
};

struct Position : public TextureMappingAttribute
{
 LWO::Vector vector;
 unsigned long envelope;

 Position ( LWO::Tag typetag, LWO & lwo )
  : TextureMappingAttribute ( typetag, POSITION )
 {
  vector = lwo.Read_Vector ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s vector %f %f %f envelope %lu\n",
           &tag, vector.x, vector.y, vector.z, envelope );
 }
};

struct Size : public TextureMappingAttribute
{
 LWO::Vector vector;
 unsigned long envelope;

 Size ( LWO::Tag typetag, LWO & lwo )
  : TextureMappingAttribute ( typetag, SIZE )
 {
  vector = lwo.Read_Vector ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s vector %f %f %f envelope %lu\n",
           &tag, vector.x, vector.y, vector.z, envelope );
 }
};

struct Orientation : public TextureMappingAttribute
{
 LWO::Vector vector;
 unsigned long envelope;

 Orientation ( LWO::Tag typetag, LWO & lwo )
  : TextureMappingAttribute ( typetag, ORIENTATION )
 {
  vector = lwo.Read_Vector ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s vector %f %f %f envelope %lu\n",
           &tag, vector.x, vector.y, vector.z, envelope );
 }
};

struct ReferenceObject : public TextureMappingAttribute
{
 FString object_name;

 ReferenceObject ( LWO::Tag typetag, LWO & lwo )
  : TextureMappingAttribute ( typetag, REFERENCEOBJECT )
 {
  object_name = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s object name '%s'\n", &tag, &object_name );
 }
};

struct Falloff : public TextureMappingAttribute
{
 unsigned short type;
 LWO::Vector vector;
 unsigned long envelope;

 Falloff ( LWO::Tag typetag, LWO & lwo )
  : TextureMappingAttribute ( typetag, FALLOFF )
 {
  type = lwo.Read_U2 ();
  vector = lwo.Read_Vector ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s type %u vector %f %f %f envelope %lu\n",
           &tag, type, vector.x, vector.y, vector.z, envelope );
 }
};

struct CoordinateSystem : public TextureMappingAttribute
{
 unsigned short type;

 CoordinateSystem ( LWO::Tag typetag, LWO & lwo )
  : TextureMappingAttribute ( typetag, COORDINATESYSTEM )
 {
  type = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s type %u\n", &tag, type );
 }
};


#endif
