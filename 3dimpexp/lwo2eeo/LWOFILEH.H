#ifndef LWOFILEH_INCLUDED
#define LWOFILEH_INCLUDED


struct BlockHeaderAttribute : public BasicChunk
{
 enum BlockHeaderAttributeType
  {
   UNKNOWN,
   CHANNEL,
   ENABLE,
   OPAQUE,
   DISPLACEMENTAXIS,
   NEGATIVE
  };

 BlockHeaderAttributeType blockheaderattributetype;

 BlockHeaderAttribute ( LWO::Tag tag_, BlockHeaderAttributeType blockheaderattributetype_ )
  : BasicChunk ( tag_ ), blockheaderattributetype ( blockheaderattributetype_ )
 {
 }
};

struct BlockHeaderAttributeUnknown : public BlockHeaderAttribute
{
 unsigned ndata;
 unsigned char * data;

 BlockHeaderAttributeUnknown ( LWO::Tag typetag, LWO & lwo )
  : BlockHeaderAttribute ( typetag, UNKNOWN )
 {
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~BlockHeaderAttributeUnknown ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s unknown ndata %u\n", &tag, ndata );
  PrintData ( 3, ndata, data );
 }
};

struct Channel : public BlockHeaderAttribute
{
 LWO::Tag texture_channel;

 Channel ( LWO::Tag typetag, LWO & lwo )
  : BlockHeaderAttribute ( typetag, CHANNEL )
 {
  texture_channel = lwo.Read_Tag ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s texture channel %s\n", &tag, &texture_channel );
 }
};

struct Enable : public BlockHeaderAttribute
{
 unsigned short enable;

 Enable ( LWO::Tag typetag, LWO & lwo )
  : BlockHeaderAttribute ( typetag, ENABLE )
 {
  enable = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s enable %u\n", &tag, enable );
 }
};

struct Opaque : public BlockHeaderAttribute
{
 unsigned short type;
 float opacity;
 unsigned long envelope;

 Opaque ( LWO::Tag typetag, LWO & lwo )
  : BlockHeaderAttribute ( typetag, OPAQUE )
 {
  type = lwo.Read_U2 ();
  opacity = lwo.Read_Float ();
  envelope = lwo.Read_Index ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s type %u opacity %f envelope %lu\n",
           &tag, type, opacity, envelope );
 }
};

struct DisplacementAxis : public BlockHeaderAttribute
{
 unsigned short displacement_axis;

 DisplacementAxis ( LWO::Tag typetag, LWO & lwo )
  : BlockHeaderAttribute ( typetag, DISPLACEMENTAXIS )
 {
  displacement_axis = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s displacement axis %u\n",
           &tag, displacement_axis );
 }
};

struct Negative : public BlockHeaderAttribute
{
 unsigned short enable;

 Negative ( LWO::Tag typetag, LWO & lwo )
  : BlockHeaderAttribute ( typetag, NEGATIVE )
 {
  enable = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( "   Subchunk %s enable %u\n", &tag, enable );
 }
};

struct BlockHeader : public BasicChunk
{
 enum Type
  {
   UNKNOWN,
   IMAGEMAPTEXTURE,
   PROCEDURALTEXTURE,
   GRADIENTTEXTURE,
   SHADERPLUGIN
  };

 Type blockheadertype;

 FString ordinal;
 Array < BlockHeaderAttribute * > attributes;

 BlockHeader ( LWO::Tag tag_, Type blockheadertype_, LWO & lwo )
  : BasicChunk ( tag_ ), blockheadertype ( blockheadertype_ )
 {
  LWO::Tag tag;

  ordinal = lwo.Read_String ();
  lwo.SubChunk_Lower ();
  while ( tag = lwo.Read_SubChunk_Header ( NULL ) )
   {
    switch ( TAG_ ( &tag ) )
     {
      case TAG ( 'C', 'H', 'A', 'N' ) :
       attributes[!attributes] = new Channel ( tag, lwo );
       break;
      case TAG ( 'E', 'N', 'A', 'B' ) :
       attributes[!attributes] = new Enable ( tag, lwo );
       break;
      case TAG ( 'O', 'P', 'A', 'C' ) :
       attributes[!attributes] = new Opaque ( tag, lwo );
       break;
      case TAG ( 'A', 'X', 'I', 'S' ) :
       attributes[!attributes] = new DisplacementAxis ( tag, lwo );
       break;
      case TAG ( 'N', 'E', 'G', 'A' ) :
       attributes[!attributes] = new Negative ( tag, lwo );
       break;
      default :
       attributes[!attributes] = new BlockHeaderAttributeUnknown ( tag, lwo );
       break;
     }
    lwo.Skip_SubChunk ();
   }
 }
 ~BlockHeader ( void )
 {
  unsigned i;

  for ( i = 0; i < !attributes; i++ )
   delete attributes[i];
 }
 void Print ( void )
 {
  unsigned i;

  printf ( "  Subchunk %s header ordinal ", &tag );
  for ( i = 0; ordinal[i]; i++ )
   printf ( "%02X", ordinal[i] );
  printf ( " nattributes %u\n", !attributes );
  for ( i = 0; i < !attributes; i++ )
   attributes[i]->Print ();
 }
};


#endif
