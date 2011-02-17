#ifdef USE_INDICES32
#define INDEX_BUFFER_TYPE HardwareIndexBuffer::IT_32BIT
#define VERTICES_HARD_LIMIT (~0u)
typedef unsigned int IndexType;
#else
#define INDEX_BUFFER_TYPE HardwareIndexBuffer::IT_16BIT
#define VERTICES_HARD_LIMIT (1u << 16)
typedef unsigned short IndexType;
#endif

// Simple alternative for Ogre::VertexDeclaration
// Provides presence and offset of certain fields for each vertex in buffer
struct VertexDescription
{
	void init(bool normal_, bool diffuse_, bool specular_, bool texture1_, bool texture2_)
	{
		flags = 0;
		vertex_size = 3;
		normal_offset = diffuse_offset = specular_offset = texture1_offset = texture2_offset = 0;
#ifdef USE_NORMALS
		if (normal_)
		{
			normal = 1;
			normal_offset = vertex_size;
			vertex_size += 3;
		}
#endif
		if (diffuse_)
		{
			diffuse = 1;
			diffuse_offset = vertex_size;
			vertex_size += 1;
		}
		if (specular_)
		{
			specular = 1;
			specular_offset = vertex_size;
			vertex_size += 1;
		}
#ifdef USE_TEXTURES
		if (texture1_)
		{
			texture1 = 1;
			texture1_offset = vertex_size;
			vertex_size += 2;
		}
		if (texture2_)
		{
			texture2 = 1;
			texture2_offset = vertex_size;
			vertex_size += 2;
		}
#endif
	}

	VertexDescription(void)
	{
	}

	VertexDescription(const face_surface_description& s)
	{
		init(s.smoothed, false, false, s.textured, s.has_luminosity_texture);
	}

	VertexDescription(bool normal, bool diffuse, bool specular, bool texture1, bool texture2)
	{
		init(normal, diffuse, specular, texture1, texture2);
	}

	void translate(VertexDeclaration* vd, unsigned short index) const
	{
		size_t offset = 0;
		vd->addElement(index, offset, VET_FLOAT3, VES_POSITION);
		offset += VertexElement::getTypeSize(VET_FLOAT3);
		if (diffuse)
		{
			vd->addElement(index, offset, VET_COLOUR, VES_DIFFUSE);
			offset += VertexElement::getTypeSize(VET_COLOUR);
		}
		if (specular)
		{
			vd->addElement(index, offset, VET_COLOUR, VES_SPECULAR);
			offset += VertexElement::getTypeSize(VET_COLOUR);
		}
#ifdef USE_NORMALS
		if (normal)
		{
			vd->addElement(index, offset, VET_FLOAT3, VES_NORMAL);
			offset += VertexElement::getTypeSize(VET_FLOAT3);
		}
#endif
#ifdef USE_TEXTURES
		if (texture1)
		{
			vd->addElement(index, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
			offset += VertexElement::getTypeSize(VET_FLOAT2);
		}
		if (texture2)
		{
			vd->addElement(index, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES, texture1);
			offset += VertexElement::getTypeSize(VET_FLOAT2);
		}
#endif
		assert(offset == vertex_size * sizeof(Real));
	}

	size_t vertex_size;
	union
	{
		struct
		{
			unsigned normal:1, diffuse:1, specular:1, texture1:1, texture2:1;
		};
		unsigned flags;
	};
	unsigned normal_offset, diffuse_offset, specular_offset, texture1_offset, texture2_offset;
};

// Collector of VertexBuffers and corresponding IndexBuffers.
// Merges vertices of different submeshes with the same VertexDescriptors
// Merges indices of different submeshes
class Geometry
{
public:
	// Vertex buffer descriptor
	struct VBUF
	{
		VertexBufferBinding* vbb;
		HardwareVertexBufferSharedPtr hvb;
		unsigned short index;
		VertexDeclaration* vd;
		size_t offset;
	};

	// Index buffer descriptor
	struct IBUF
	{
		HardwareIndexBufferSharedPtr hib;
		size_t offset;
	};

	// Composition of vertex and index buffers
	struct BUF
	{
		VBUF vbuf;
		float* fdata;
		IBUF ibuf;
		IndexType* idata;
	};

	// Sets limits for buffers sizes. If limit is reached, an additional buffer is allocated
	Geometry(unsigned POINTS_PER_VERTEX_BUFFER, unsigned POINTS_PER_INDEX_BUFFER)
		: POINTS_PER_VERTEX_BUFFER(POINTS_PER_VERTEX_BUFFER), POINTS_PER_INDEX_BUFFER(POINTS_PER_INDEX_BUFFER)
	{
		assert(POINTS_PER_VERTEX_BUFFER <= VERTICES_HARD_LIMIT);
	}

	~Geometry();

	// Returns buffers (buffers caches) for the specified conditions
	void get_buf(const VertexDescription& s, size_t number_of_points, size_t number_of_indices, BUF& buf);

	// Flushes the caches of buffers
	void flush(void);

	void statistics(const char* filename) const;

private:
	const unsigned POINTS_PER_VERTEX_BUFFER;
	const unsigned POINTS_PER_INDEX_BUFFER;

	typedef std::list<VBUF> LIST_VBUF;
	struct VBUF_LIST
	{
		LIST_VBUF list;
		std::vector<float> shadow;
	};
	typedef std::map<size_t, VBUF_LIST> VBUFS;

	typedef std::list<IBUF> LIST_IBUF;
	struct IBUFS
	{
		LIST_IBUF list;
		std::vector<IndexType> shadow;
	};

	VBUFS vbufs;
	IBUFS ibufs;

	void flush_vbuf(VBUF_LIST& vbl, size_t vertex_size);
	void flush_ibuf(void);
};
typedef std::auto_ptr<Geometry> GeometryPtr;


class MaterialHolder
{
public:
	MaterialHolder(unsigned begin)
		: begin(begin), end(index)
	{
	}

	~MaterialHolder()
	{
		for (unsigned i = begin; i != end; i++)
		{
			MaterialName material_name(i);
			MaterialManager::getSingleton().unload(material_name);
			MaterialManager::getSingleton().remove(material_name);
		}
	}

	static unsigned get_index(void)
	{
		return index++;
	}

private:
	unsigned begin, end;
	static unsigned index;
};
typedef std::auto_ptr<MaterialHolder> MaterialHolderPtr;
