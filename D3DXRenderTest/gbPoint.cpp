#include "gbPoint.h"
#include "D3DXGlobalFunction.h"

gbPoint::gbPoint()
	:D3DXPrimitive(new Vertex_Point[1], 1, 1, nullptr, D3DPT_POINTLIST)
{
	initBuf();
	setSolid(D3DFILL_POINT);
}

gbPoint::~gbPoint()
{

}

void gbPoint::resetData()
{
	if(!needReset())
		return;
	Vertex_Point* vertex = (Vertex_Point*)getVertex();
	vertex[0].psize = m_size;
	vertex[0].position = Vec3(m_position.x, m_position.y, 0.0f);
}

gbPointArray::gbPointArray(size_t _count)
	:D3DXPrimitive(new Vertex_Point[_count], _count, _count, nullptr, D3DPT_POINTLIST),
	m_position(new Vec2[_count]), m_size(new float[_count])
{
	initBuf();
	setSolid(D3DFILL_POINT);
}

gbPointArray::~gbPointArray()
{
	if(m_position)
		delete[] m_position;
	if(m_size)
		delete[] m_size;
}

void gbPointArray::resetData()
{
	if(!needReset())
		return;
	Vertex_Point* vertex = (Vertex_Point*)getVertex();
	for (size_t i = 0; i < getCount(); ++i)
	{
		vertex[i].position = Vec3(m_position[i].x, m_position[i].y, 0.0f);
		vertex[i].psize = m_size[i];
	}
	setReset(false);
}
