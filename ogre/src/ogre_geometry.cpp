#include "ogre_int.hpp"

Geometry::~Geometry()
{
	for (VBUFS::iterator vbufl(vbufs.begin()); vbufl != vbufs.end(); ++vbufl)
	{
		for (LIST_VBUF::iterator vbuf(vbufl->second.list.begin()); vbuf != vbufl->second.list.end(); ++vbuf)
		{
			Ogre::HardwareBufferManager::getSingleton().destroyVertexBufferBinding(vbuf->vbb);
			Ogre::HardwareBufferManager::getSingleton().destroyVertexDeclaration(vbuf->vd);
		}
	}
}

void Geometry::get_buf(const VertexDescription& s, size_t number_of_points, size_t number_of_indices, BUF& buf)
{
	assert(number_of_points <= VERTICES_HARD_LIMIT);


	// Vertex buffer

	VBUF_LIST& vbl = vbufs[(s.flags << 16) | s.vertex_size];

	if (vbl.list.empty() || vbl.list.back().offset + number_of_points > POINTS_PER_VERTEX_BUFFER)
	{
		flush_vbuf(vbl, s.vertex_size);

		// Create a new vertex buffer
		size_t elements = std::max(number_of_points, POINTS_PER_VERTEX_BUFFER);

		VBUF vbuf;
		vbuf.vbb = Ogre::HardwareBufferManager::getSingleton().createVertexBufferBinding();

		vbuf.index = vbuf.vbb->getNextIndex();

		vbuf.vd = Ogre::HardwareBufferManager::getSingleton().createVertexDeclaration();
		s.translate(vbuf.vd, vbuf.index);

		vbuf.offset = 0;

		vbl.list.push_back(vbuf);
		vbl.shadow.resize(elements * s.vertex_size);
	}

	buf.vbuf = vbl.list.back();
	buf.fdata = &vbl.shadow[buf.vbuf.offset * s.vertex_size];
	vbl.list.back().offset += number_of_points;


	// Index buffer

	if (ibufs.list.empty() || ibufs.list.back().offset + number_of_indices > POINTS_PER_INDEX_BUFFER)
	{
		flush_ibuf();

		// Create a new index buffer

		IBUF ibuf;
		size_t elements = std::max(number_of_indices, POINTS_PER_INDEX_BUFFER);
		ibuf.hib = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(INDEX_BUFFER_TYPE, elements, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
		ibuf.offset = 0;
		ibufs.list.push_back(ibuf);
		ibufs.shadow.resize(elements);
	}

	buf.ibuf = ibufs.list.back();
	buf.idata = &ibufs.shadow[buf.ibuf.offset];
	ibufs.list.back().offset += number_of_indices;
}

void Geometry::flush(void)
{
	for (VBUFS::iterator itor(vbufs.begin()); itor != vbufs.end(); ++itor)
		flush_vbuf(itor->second, itor->first & 0xFFFF);
	flush_ibuf();
}

void Geometry::statistics(const char* filename) const
{
	FILE* f = fopen(filename, "w");
	assert(f);

	size_t grand = 0;

	fprintf(f, "%u %u\n", POINTS_PER_VERTEX_BUFFER, POINTS_PER_INDEX_BUFFER);

	for (VBUFS::const_iterator itor(vbufs.begin()); itor != vbufs.end(); ++itor)
	{
		size_t size = itor->first & 0xFFFF;
		size_t total = 0;
		fprintf(f, "%u:", size); 
		for (LIST_VBUF::const_iterator it(itor->second.list.begin()); it != itor->second.list.end(); ++it)
		{
			total += it->offset;
			fprintf(f, " %u", it->offset);
		}
		fprintf(f, " [%u]\n", total);
		total *= size;
		fprintf(f, " (%u)\n", total);
		grand += total;
	}

	size_t size = 0;
	for (LIST_IBUF::const_iterator it(ibufs.list.begin()); it != ibufs.list.end(); ++it)
	{
		size += it->offset;
		fprintf(f, " %u", it->offset);
	}
	fprintf(f, " [%u]\n", size);
	size *= sizeof(IndexType);
	fprintf(f, " (%u)\n", size);
	grand += size;

	fprintf(f, "%u\n", grand);

	fclose(f);
}

void Geometry::flush_vbuf(VBUF_LIST& vbl, size_t vertex_size)
{
	if (vbl.shadow.empty())
		return;

	if (vbl.list.empty())
		return;

	VBUF& vbuf = vbl.list.back();
	assert(vbuf.hvb.isNull());

	vbuf.hvb = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(vertex_size * sizeof(Ogre::Real), vbuf.offset, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
	vbuf.vbb->setBinding(vbuf.index, vbuf.hvb);
	vbuf.hvb->writeData(0, vbuf.offset * vertex_size * sizeof(Ogre::Real), &vbl.shadow[0], true);
	vbl.shadow.clear();
}

void Geometry::flush_ibuf(void)
{
	if (ibufs.shadow.empty())
		return;

	if (ibufs.list.empty())
		return;

	IBUF& ibuf = ibufs.list.back();
	ibuf.hib->writeData(0, ibuf.offset * sizeof(IndexType), &ibufs.shadow[0], true);
	ibufs.shadow.clear();
}
