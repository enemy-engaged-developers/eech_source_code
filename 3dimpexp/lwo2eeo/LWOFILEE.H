#ifndef LWOFILEE_INCLUDED
#define LWOFILEE_INCLUDED


struct EnvelopeAttribute : public BasicChunk
{
 enum EnvelopeAttributeType
 {
  UNKNOWN,
  ENVELOPETYPE,
  PREBEHAVIOR,
  POSTBEHAVIOR,
  KEYFRAMETIMEANDVALUE,
  INTERVALINTERPOLATION,
  PLUGINCHANNELMODIFIERS,
  CHANNELNAME
 };

 EnvelopeAttributeType envelopeattributetype;

 EnvelopeAttribute ( LWO::Tag tag_, EnvelopeAttributeType envelopeattributetype_ )
  : BasicChunk ( tag_ ), envelopeattributetype ( envelopeattributetype_ )
 {
 }
};

struct EnvelopeUnknown : public EnvelopeAttribute
{
 unsigned ndata;
 unsigned char * data;

 EnvelopeUnknown ( LWO::Tag typetag, LWO & lwo )
  : EnvelopeAttribute ( typetag, UNKNOWN )
 {
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~EnvelopeUnknown ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( " Subchunk %s unknown ndata %u\n", &tag, ndata );
  PrintData ( 1, ndata, data );
 }
};

struct EnvelopeType : public EnvelopeAttribute
{
 unsigned char user_format;
 unsigned char type;

 EnvelopeType ( LWO::Tag typetag, LWO & lwo )
  : EnvelopeAttribute ( typetag, ENVELOPETYPE )
 {
  user_format = lwo.Read_U1 ();
  type = lwo.Read_U1 ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s user format %u type %u\n", &tag, user_format, type );
 }
};

struct PreBehavior : public EnvelopeAttribute
{
 unsigned short type;

 PreBehavior ( LWO::Tag typetag, LWO & lwo )
  : EnvelopeAttribute ( typetag, PREBEHAVIOR )
 {
  type = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s type %u\n", &tag, type );
 }
};

struct PostBehavior : public EnvelopeAttribute
{
 unsigned short type;

 PostBehavior ( LWO::Tag typetag, LWO & lwo )
  : EnvelopeAttribute ( typetag, POSTBEHAVIOR )
 {
  type = lwo.Read_U2 ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s type %u\n", &tag, type );
 }
};

struct KeyFrameTimeAndValue : public EnvelopeAttribute
{
 float time;
 float value;

 KeyFrameTimeAndValue ( LWO::Tag typetag, LWO & lwo )
  : EnvelopeAttribute ( typetag, KEYFRAMETIMEANDVALUE )
 {
  time = lwo.Read_Float ();
  value = lwo.Read_Float ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s time %f value %f\n", &tag, time, value );
 }
};

struct IntervalInterpolation : public EnvelopeAttribute
{
 LWO::Tag type;
 Array < float > parameters;

 IntervalInterpolation ( LWO::Tag typetag, LWO & lwo )
  : EnvelopeAttribute ( typetag, INTERVALINTERPOLATION )
 {
  type = lwo.Read_Tag ();
  while ( lwo.SubChunk_Left () > 3 )
   parameters[!parameters] = lwo.Read_Float ();
 }
 void Print ( void )
 {
  unsigned i;

  printf ( " Subchunk %s type %s parameters %u\n", &tag, &type, !parameters );
  for ( i = 0; i < !parameters; i++ )
   printf ( " %f", parameters[i] );
  printf ( "\n" );
 }
};

struct PlugInChannelModifiers : public EnvelopeAttribute
{
 FString server_name;
 unsigned short flags;
 unsigned ndata;
 unsigned char * data;

 PlugInChannelModifiers ( LWO::Tag typetag, LWO & lwo )
  : EnvelopeAttribute ( typetag, PLUGINCHANNELMODIFIERS )
 {
  server_name = lwo.Read_String ();
  flags = lwo.Read_U2 ();
  ndata = ( unsigned ) lwo.SubChunk_Left ();
  data = new unsigned char [ ndata ];
  lwo.Read_Data ( data, ndata );
 }
 ~PlugInChannelModifiers ( void )
 {
  delete [] data;
 }
 void Print ( void )
 {
  printf ( " Subchunk %s server name '%s' flags %04x ndata %u\n",
           &tag, &server_name, flags, ndata );
  PrintData ( 1, ndata, data );
 }
};

struct ChannelName : public EnvelopeAttribute
{
 FString channel_name;

 ChannelName ( LWO::Tag typetag, LWO & lwo )
  : EnvelopeAttribute ( typetag, CHANNELNAME )
 {
  channel_name = lwo.Read_String ();
 }
 void Print ( void )
 {
  printf ( " Subchunk %s channel name '%s'\n", &tag, &channel_name );
 }
};


#endif
