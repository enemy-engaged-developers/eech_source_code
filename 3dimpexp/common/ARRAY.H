#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

template <class T>
class Array
{
 private:

 unsigned allocated;
 unsigned used;
 T* array;


 public:

 Array(void) : allocated(0), used(0), array(NULL) {}
 Array(const Array& arr)
  : allocated(arr.allocated), used(arr.used), array(NULL)
 {
  if (arr.allocated)
   {
    array = new T[allocated];
    for (unsigned i = 0; i < used; i++)
     array[i] = arr.array[i];
   }
 }
 ~Array(void)
 {
  if (array)
   delete [] array;
 }

 void operator =(const Array& arr)
 {
  if (this == &arr)
   return;
  if (allocated < arr.used)
   {
    if (array)
     delete [] array;
    allocated = arr.allocated;
    used = arr.used;
    array = new T[allocated];
   }
  for (unsigned i = 0; i < arr.used; i++)
   array[i] = arr.array[i];
  for (unsigned i = arr.used; i < used; i++)
   array[i] = T();
  used = arr.used;
 }
 const T& operator [](unsigned index) const { return array[index]; }
 T& operator [](unsigned index)
 {
  if (index >= allocated)
   {
    allocated = 2 * index + 1;
    T* newarray = new T[allocated];
    if (array)
     {
      for (unsigned i = 0; i < used; i++)
       newarray[i] = array[i];
      delete [] array;
     }
    array = newarray;
   }
  if (index >= used)
   used = index + 1;
  return array[index];
 }
 unsigned operator !(void) const { return used; }
 T& Append(const T& t)
 {
  return operator[](used) = t;
 }
 T& Append(void)
 {
  return operator[](used);
 }
 T* Last(void)
 {
  return used ? array + (used - 1) : (T*)0;
 }
 const T* Last(void) const
 {
  return used ? array + (used - 1) : (const T*)0;
 }
};

#endif
