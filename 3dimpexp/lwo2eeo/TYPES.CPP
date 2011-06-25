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

 int operator ==(const RPoint& rp)
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

struct RNormal
{
 double _heading, _pitch;
 unsigned char heading, pitch;
 unsigned index;

 int Set(const RPoint& p1, const RPoint& p2, const RPoint& p3)
 {
  struct
  {
   long x, y, z;
  } u, v, n;

  u.x = p2.x - p1.x;
  u.y = p2.y - p1.y;
  u.z = p2.z - p1.z;
  v.x = p3.x - p1.x;
  v.y = p3.y - p1.y;
  v.z = p3.z - p1.z;

  n.x = u.y * v.z - u.z * v.y;
  n.y = u.z * v.x - u.x * v.z;
  n.z = u.x * v.y - u.y * v.x;

  return Set(n.x, n.y, n.z);
 }

 int Set(long x, long y, long z)
 {
  if (!x && !y && !z)
   {
    _heading = 0;
    _pitch = 0;
    return -1;
   }

  if (!x && !z)
   {
    _heading = 0;
    _pitch = y > 0 ? M_PI / 2 : - M_PI / 2;
   }
  else
   if (!z)
    {
     _heading = x > 0 ? M_PI / 2 : - M_PI / 2;
     _pitch = atan2((double) y, fabs((double) x));
    }
   else
    if (!x)
     {
      _heading = z > 0 ? 0 : - M_PI;
      _pitch = atan2((double) y, fabs((double) z));
     }
    else
     {
      _pitch = atan2(y, sqrt((double)x * x + (double)z * z));
      _heading = atan2((double) x, (double) z);
     }

  {
   double xd, yd, zd;
   xd = sin(_heading) * cos(_pitch);
   yd = sin(_pitch);
   zd = cos(_heading) * cos(_pitch);
   double an = (x * xd + y * yd + z * zd) /
    sqrt((xd * xd + yd * yd + zd * zd) *
     ((double)x * x + (double)y * y + (double)z * z));
   if (an < cos(3 * M_PI / 180))
    error("Invalid normal vector");
  }

  double _pitch_ = _pitch;
  _pitch_ += M_PI / 2;
  _pitch_ *= 256 / M_PI;
  pitch = _pitch_ < 0 ? 0 : _pitch_ > 255 ? 255 : (int)(_pitch_ + 0.5);

  double _heading_ = _heading;
  _heading_ += M_PI;
  _heading_ *= 128 / M_PI;
  heading = _heading_ < 0 ? 0 : _heading_ > 255 ? 255 : (int)(_heading_ + 0.5);

  return 0;
 }
 int operator ==(const RNormal& n)
 {
  return heading == n.heading && pitch == n.pitch;
 }
};

struct RANormal
{
 double x, y, z;
 unsigned index;

 RANormal() : x(0.0), y(0.0), z(0.0), index(0) {}

 void operator +=(const RNormal& n)
 {
  x += sin(n._heading) * cos(n._pitch);
  y += sin(n._pitch);
  z += cos(n._heading) * cos(n._pitch);
 }

 int SetTo(RNormal& normal)
 {
  return normal.Set((long)(x * 10000), (long)(y * 10000), (long)(z * 10000));
 }
};

struct RPolyPoint
{
 RPoint p;
 RTPoint tp;
 RTPoint lp;
 unsigned index;
 RANormal normal;

 int operator ==(const RPolyPoint& rp)
 {
  return p == rp.p && tp == rp.tp && lp == rp.lp;
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
