class LWO_Chunk
{
 private:

 LWO_Chunk(const LWO_Chunk&);
 LWO_Chunk& operator =(const LWO_Chunk&);

 protected:

 char tag[5];
 unsigned ndata;
 char* data;
 LWO_Chunk* head;
 LWO_Chunk** last;
 LWO_Chunk* next;
 unsigned long size;

 virtual void WriteSelf(ostream& out);
 void Write(ostream& out);

 public:

 LWO_Chunk(const char* _tag, unsigned long _ndata, const void* _data);
 virtual ~LWO_Chunk(void);

 virtual unsigned long Calculate(void);

 void AddSubChunk(LWO_Chunk*);
 void AddBasicData(unsigned long _ndata, const void* _data);
 void AddData(unsigned long _ndata, const void* _data);
 void AddIndex(unsigned long index);
};

class LWO_SubChunk : public LWO_Chunk
{
 protected:

 virtual void WriteSelf(ostream& out);

 public:

 LWO_SubChunk(const char* _tag, unsigned long _ndata, const void* _data);

 virtual unsigned long Calculate(void);
};

class LWO_File : public LWO_Chunk
{
 public :

 LWO_File(void);

 void WriteFile(const char* filename);
};


LWO_Chunk::LWO_Chunk(const char* _tag, unsigned long _ndata, const void* _data)
 : ndata(( _ndata + 1) & ~1), data(NULL), head(NULL), last(&head), next(NULL), size(0)
{
 sprintf(tag, "%-4.4s", _tag);
 if (ndata)
  {
   data = new char[ndata];
   memcpy(data, _data, ndata);
   if (_ndata & 1)
    data[_ndata] = '\0';
  }
}

LWO_Chunk::~LWO_Chunk(void)
{
 delete head;
 delete next;
 delete [] data;
}

unsigned long LWO_Chunk::Calculate(void)
{
 size = ndata;
 if (head != NULL)
  size += head->Calculate();
 return size + 4 + 4 + (next ? next->Calculate() : 0);
}

void LWO_Chunk::WriteSelf(ostream & out)
{
 out.write(tag, 4);
 unsigned char byte;
 byte = (unsigned char)(size >> 24);
 out.write((char*)&byte, 1);
 byte = (unsigned char)(size >> 16);
 out.write((char*)&byte, 1);
 byte = (unsigned char)(size >> 8);
 out.write((char*)&byte, 1);
 byte = (unsigned char)(size >> 0);
 out.write((char*)&byte, 1);
 if (ndata)
  out.write(data, ndata);
}

void LWO_Chunk::Write(ostream& out)
{
 WriteSelf(out);
 if (head)
  head->Write(out);
 if (next)
  next->Write(out);
}

void LWO_Chunk::AddSubChunk(LWO_Chunk* chunk)
{
 *last = chunk;
 last = &chunk->next;
}

void LWO_Chunk::AddBasicData(unsigned long _ndata, const void* _data)
{
 char* olddata;
 unsigned long oldndata;

 olddata = data;
 oldndata = ndata;
 ndata += (_ndata + 1) & ~1;
 data = new char[ndata];
 if (oldndata)
  memcpy(data, olddata, oldndata);
 memcpy(data + oldndata, _data, _ndata);
 if (_ndata & 1)
  data[ndata - 1] = '\0';
 delete [] olddata;
}

void LWO_Chunk::AddData(unsigned long _ndata, const void * _data)
{
 char* newdata;
 char* savenewdata;
 const char* _newdata;

 _newdata = ((const char*)_data) + _ndata - 1;
 savenewdata = newdata = new char[_ndata];
 while (_newdata >= _data)
  *newdata++ = *_newdata--;
 AddBasicData(_ndata, savenewdata);
 delete [] savenewdata;
}

void LWO_Chunk::AddIndex(unsigned long index)
{
 if (index < 0xFF00)
  AddData(2, &index);
 else
  {
   index |= 0xFF000000ul;
   AddData(4, &index);
  }
}


LWO_SubChunk::LWO_SubChunk(const char* _tag, unsigned long _ndata, const void* _data)
 : LWO_Chunk(_tag, _ndata, _data)
{
}

void LWO_SubChunk::WriteSelf(ostream& out)
{
 out.write(tag, 4);
 unsigned char byte;
 byte = (unsigned char)(size >> 8);
 out.write((char*)&byte, 1);
 byte = (unsigned char)(size >> 0);
 out.write((char*)&byte, 1);
 if (ndata)
  out.write(data, ndata);
}

unsigned long LWO_SubChunk::Calculate(void)
{
 size = ndata;
 if (head != NULL)
  size += head->Calculate();
 return size + 4 + 2 + (next ? next->Calculate () : 0);
}


LWO_File::LWO_File(void)
 : LWO_Chunk("FORM", 4, "LWO2")
{
}

void LWO_File::WriteFile(const char* filename)
{
 Calculate();

 ofstream out(filename, ios::out | ios::truncate | ios::binary);

 if (!out)
  return;

 Write(out);
}
