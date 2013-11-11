#include <algorithm>

class Convert
{
 private:

 static bool VmComp(const VertexMapping::Mapping& m1, const VertexMapping::Mapping& m2)
 {
  return m1.vert < m2.vert;
 }

 static bool DvmComp(const DiscontinuousVertexMapping::Mapping& m1, const DiscontinuousVertexMapping::Mapping& m2)
 {
  return m1.poly < m2.poly || m1.poly == m2.poly && m1.vert < m2.vert;
 }

 template <typename T, typename Comp>
 static void Sort(Array<T>& a, Comp comp)
 {
  if (!a)
   std::sort(&a[0], &a[0] + !a, comp);
 }
 template <typename T, typename Comp>
 static const T* Find(const Array<T>& a, const T& value, Comp comp)
 {
  int len = !a;
  if (!len)
   return NULL;
  int half;
  const T* first = &a[0];
  const T* middle;

  do
   {
    half = len >> 1;
    middle = first + half;
    if (comp(*middle, value))
     {
      first = middle + 1;
      len -= half + 1;
     }
    else
     len = half;
   }
  while (len > 0);
  return first == &a[0] + !a || comp(value, *first) ? NULL : first;
 }

void FindChunks(const LWOFile& lwofile)
{
 const Tags* t = NULL;

 /*
  * Find chunks
  */
 for (unsigned i = 0; i < !lwofile.chunks; i++)
  {
   const Chunk* chunk = lwofile.chunks[i];
   switch (chunk->chunktype)
    {
     case Chunk::LAYER:
      {
       const Layer* l = static_cast<const Layer*>(chunk);
       unsigned parent = ~0u;
       for (unsigned i = 0; i < !Layers; i++)
        {
         if (Layers[i].l->number == l->number)
          error("Dublicate number for layer");
         if (l->parent != 0xFFFF && l->parent == Layers[i].l->number)
          parent = i;
        }
       if (l->parent != 0xFFFF && parent == ~0u)
        error("Absent parent for layer");
       unsigned index = !Layers;
       Layers[index].l = l;
       Layers[index].parent = parent;
      }
      break;

     case Chunk::POINTS:
      {
       if (!!Layers)
        error("No layers stored to be applied with points");
       const Points* p = static_cast<const Points*>(chunk);
       unsigned index = !Point;
       Point[index].p = p;
       Point[index].layer = !Layers - 1;
      }
      break;

     case Chunk::VERTEXMAPPING:
      {
       const VertexMapping* vm = static_cast<const VertexMapping*>(chunk);

       if (TAG_(&vm->type) != TAG('T', 'X', 'U', 'V'))
        break;
       if (vm->dimention != 2)
        error("Invalid dimentions of VMAP TXUV");
       if (!!Point)
        error("No points stored to be applied with vertex mapping");
       Point.Last()->vm.Append(vm);
      }
      break;

     case Chunk::POLYGONLIST:
      {
       const PolygonList* pl = static_cast<const PolygonList*>(chunk);

       if (TAG_(&pl->type) != TAG('F', 'A', 'C', 'E'))
        break;
       if (!!Point)
        error("No points stored to be applied with polygon");
       Point.Last()->pl.Append().pl = pl;
      }
      break;

     case Chunk::TAGS:
      t = static_cast<const Tags*>(chunk);
      break;

     case Chunk::PTAGS:
      {
       const PTags* pt = static_cast<const PTags*>(chunk);

       if (!t)
        error("No tags stored to be applied with ptags");
       LPoint* point = Point.Last();
       if (!point)
        error("No points stored to be applied with ptags");
       LPoly* pl = point->pl.Last();
       if (!pl)
        error("No polygons stored to be applied with ptags");
       if (TAG_(&pt->type) == TAG('S', 'U', 'R', 'F'))
        {
         unsigned index = !pl->pt;
         pl->pt[index].t = t;
         pl->pt[index].pt = pt;
        }
       if (TAG_(&pt->type) == TAG('T', 'X', 'U', 'V'))
        {
         unsigned index = !pl->ptt;
         pl->ptt[index].t = t;
         pl->ptt[index].pt = pt;
        }
      }
      break;

     case Chunk::DISCONTINUOUSVERTEXMAPPING:
      {
       const DiscontinuousVertexMapping* dvm = static_cast<const DiscontinuousVertexMapping*>(chunk);

       if (TAG_(&dvm->type) != TAG('T', 'X', 'U', 'V'))
        break;
       if (dvm->dimention != 2)
        error("Invalid dimentions of VMAD TXUV");
       LPoint* point = Point.Last();
       if (!point)
        error("No points stored to be applied with discontinous vertex mapping");
       LPoly* pl = point->pl.Last();
       if (!pl)
        error("No polygons stored to be applied with discontinous vertex mapping");
       pl->dvm.Append(dvm);
      }
      break;

     case Chunk::ENVELOPE:
      break;

     case Chunk::IMAGE:
      break;

     case Chunk::SURFACE:
      rs.Append().s = static_cast<const Surface*>(chunk);
      break;

     case Chunk::BOUNDINGBOX:
      break;

     case Chunk::DESCRIPTIONLINE:
      break;

     case Chunk::COMMENTARYTEXT:
      break;

     case Chunk::THUMBNAILICONIMAGE:
      break;

     default:
      break;
    }
  }

 if (!!Layers)
  error("No layer");
 if (!!Point)
  error("No points");

 LWO::Vector scale = { 0.0, 0.0, 0.0 };
 Array<LWO::Vector> ps;
 for (unsigned i = 0; i < !Point; i++)
  {
   struct LPoint& lp = Point[i];
   LWO::Vector offset = { 0.0, 0.0, 0.0 };
   for (unsigned layer = lp.layer; layer != (unsigned)-1; layer = Layers[layer].parent)
    {
     offset.x += Layers[layer].l->pivot.x;
     offset.y += Layers[layer].l->pivot.y;
     offset.z += Layers[layer].l->pivot.z;
    }
   for (unsigned j = 0; j < !lp.p->points; j++)
    {
     unsigned index = !ps;
     LWO::Vector p =
      {
       lp.p->points[j].x + offset.x,
       lp.p->points[j].y + offset.y,
       lp.p->points[j].z + offset.z
      };
     BBI.x = min(BBI.x, p.x);
     BBI.y = min(BBI.y, p.y);
     BBI.z = min(BBI.z, p.z);
     BBA.x = max(BBA.x, p.x);
     BBA.y = max(BBA.y, p.y);
     BBA.z = max(BBA.z, p.z);
     scale.x = max(scale.x, static_cast<float>(fabs(p.x)));
     scale.y = max(scale.y, static_cast<float>(fabs(p.y)));
     scale.z = max(scale.z, static_cast<float>(fabs(p.z)));
     ps[index] = p;
     lp.rp[j] = index;
    }
  }
 Radius = sqrt(scale.x * scale.x + scale.y * scale.y + scale.z * scale.z);
 for (unsigned i = 0; i < !ps; i++)
  {
   Rpoints[i].x = (short)(ps[i].x * 32767.0f / scale.x);
   Rpoints[i].y = (short)(ps[i].y * 32767.0f / scale.y);
   Rpoints[i].z = (short)(ps[i].z * 32767.0f / scale.z);
   Rpoints[i].index = i;
  }
}

 protected:

 struct RSurface;
 friend struct RSurface;

 struct ESurface
 {
  RSurface* rs;
  Array<RPoly> polys;
  Array<RPolyPoint> points;
 };

#include "surface.cpp"

 Array<LLayer> Layers;
 Array<LPoint> Point;
 LWO::Vector BBI, BBA;
 Array<RPoint> Rpoints;
 Array<RSurface> rs;
 Array<ESurface> es;
 float Radius;

 public:

 Convert(const char* lwo, const char* log)
 {
  BBI.x = 0.0;
  BBI.y = 0.0;
  BBI.z = 0.0;
  BBA.x = 0.0;
  BBA.y = 0.0;
  BBA.z = 0.0;

  LWOFile lwofile(lwo);

  if (log)
   {
    fflush(stdout);
    int stdout_dup = dup(STDOUT_FILENO);
    if (stdout_dup >= 0)
     {
      int log_fd = open(log, O_WRONLY | O_TEXT | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IREAD | S_IWRITE);
      if (log_fd >= 0)
       {
        if (dup2(log_fd, STDOUT_FILENO) >= 0)
         {
          lwofile.Print();
          fflush(stdout);
          dup2(stdout_dup, STDOUT_FILENO);
         }
        close(log_fd);
       }
      close(stdout_dup);
     }
   }

  for (unsigned i = 0; i < !lwofile.chunks; i++)
   {
    Chunk* chunk = lwofile.chunks[i];
    switch (chunk->chunktype)
     {
      case Chunk::VERTEXMAPPING:
       {
        VertexMapping* vm = static_cast<VertexMapping*>(chunk);
        Sort(vm->mapping, VmComp);
        break;
       }
      case Chunk::DISCONTINUOUSVERTEXMAPPING:
       {
        DiscontinuousVertexMapping* dvm = static_cast<DiscontinuousVertexMapping*>(chunk);
        Sort(dvm->mapping, DvmComp);
        break;
       }
      default:
       break;
     }
   }

  FindChunks(lwofile);

  /*
   * Create surfaces
   */
  for (unsigned i = 0; i < !rs; i++)
   rs[i].Parse(lwofile, *this);
 }
};
