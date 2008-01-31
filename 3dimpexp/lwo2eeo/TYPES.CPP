template <class T>
void AddPoint(Array<T>& array, T& p)
{
 unsigned i;

 for (i = 0; i < !array; i++)
  if (array[i] == p)
   break;

 if (i == !array)
  array[i] = p;

 p.index = i;
}


struct LLayer
{
  const Layer* l;
  int parent;
};

struct LPTags
{
 const Tags* t;
 const PTags* pt;
};

struct LPoly
{
 const PolygonList* pl;
 Array<LPTags> pt, ptt;
 Array<const DiscontinuousVertexMapping*> dvm;
};

struct LPoint
{
 const Points* p;
 Array<unsigned> rp;
 unsigned layer;
 Array<const VertexMapping*> vm;
 Array<LPoly> pl;
};


struct RPoint
{
 short x, y, z;
 unsigned index;

 int operator == (const RPoint& rp)
 {
  return x == rp.x && y == rp.y && z == rp.z;
 }
};

struct RTPoint
{
 float u, v;
 int set;

 RTPoint(void)
  : u(0.0f), v(0.0f), set(0)
 {
 }
 void Set(const float* values)
 {
  /*if (set)
   warning("Texture coordinates for point already set");*/
  u = values[0];
  v = 1.0f - values[1];
  set = 1;
 }
 int operator ==(const RTPoint& rp)
 {
  return u == rp.u && u == rp.u;
 }
};

struct RPolyPoint
{
 RPoint p;
 RTPoint tp;
 RTPoint lp;
 unsigned index;

 int operator == (const RPolyPoint& rp)
 {
  return p == rp.p && tp == rp.tp && lp == rp.lp;
 }
};

struct RNormal
{
 unsigned char heading, pitch;
 unsigned index;

 int Set(const RPoint& p1, const RPoint& p2, const RPoint& p3)
 {
  struct
  {
   long x, y, z;
  } u, v, n;
  double _heading, _pitch;

  u.x = p2.x - p1.x;
  u.y = p2.y - p1.y;
  u.z = p2.z - p1.z;
  v.x = p3.x - p1.x;
  v.y = p3.y - p1.y;
  v.z = p3.z - p1.z;

  n.x = u.y * v.z - u.z * v.y;
  n.y = u.z * v.x - u.x * v.z;
  n.z = u.x * v.y - u.y * v.x;

  if (!n.x && !n.y && !n.z)
   {
    /*printf("%i %i %i | %i %i %i | %i %i %i |\n%li %li %li | %li %li %li | %li %li %li\n",
             p1.x, p1.y, p1.z, p2.x, p2.y, p2.z, p3.x, p3.y, p3.z,
             u.x, u.y, u.z, v.x, v.y, v.z, n.x, n.y, n.z);*/
    return -1;
   }

  if (!n.x && !n.z)
   {
    _heading = 0;
    _pitch = n.y < 0 ? M_PI / 2 : - M_PI / 2;
   }
  else
   if (!n.z)
    {
     _heading = n.x > 0 ? M_PI / 2 : - M_PI / 2;
     _pitch = atan2(n.y, fabs(n.x));
    }
   else
    if (!n.x)
     {
      _pitch = atan2(n.y, fabs(n.z));
      _heading = n.z > 0 ? 0 : - M_PI;
     }
    else
     {
      _pitch = atan2(n.y, sqrt(( double) n.x * n.x +(double) n.z * n.z));
      _heading = atan2(n.x, n.z);
     }

  _pitch += M_PI / 2;
  _pitch *= 256 / M_PI;
  pitch = _pitch < 0 ? 0 : _pitch > 255 ? 255 :(int)(_pitch + 0.5);

  _heading += M_PI;
  _heading *= 128 / M_PI;
  heading = _heading < 0 ? 0 : _heading > 255 ? 255 :(int)(_heading + 0.5);

#if 0
  double d = sqrt(( double) n.x * n.x +(double) n.y * n.y +(double) n.z * n.z);
  struct
  {
   double x, y, z;
  } n1, n2;
  n2.x = n.x / d;
  n2.y = n.y / d;
  n2.z = n.z / d;

  _heading = heading / 256.0;
  _pitch = pitch / 256.0;

  _heading *= 2 * M_PI;
  _pitch *= M_PI;

  _heading -= M_PI;
  _pitch -= M_PI / 2;

  n1.x = cos(_pitch) * sin(_heading);
  n1.y = sin(_pitch);
  n1.z = cos(_pitch) * cos(_heading);
  if (fabs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z) < cos(M_PI / 128))
   error("Normal\n%f\n%f\n%f %f\n(%f %f %f)\n(%f %f %f)",
           fabs(n1.x * n2.x + n1.y * n2.y + n1.z * n2.z), cos(M_PI / 128),
           _pitch, _heading,
           n2.x, n2.y, n2.z, n1.x, n1.y, n1.z);
#endif

  return 0;
 }
 int operator == (const RNormal& n)
 {
  return heading == n.heading && pitch == n.pitch;
 }
};

struct RPoly
{
 const PolygonList* pl;
 Array<RPolyPoint> points;
 RNormal norm;
 unsigned index;

 RPoly(void) : index(0) {}
};
