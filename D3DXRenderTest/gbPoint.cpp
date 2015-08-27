#include "gbPoint.h"
#include "D3DXGlobalFunction.h"

gbPoint::gbPoint()
	:D3DXPrimitive(new Vertex_Point[1], 1, 1, nullptr, D3DPT_POINTLIST)
{
	initBuf();
	gbSetSolid(D3DFILL_POINT);
}

gbPoint::~gbPoint()
{

}

void gbPoint::gbResetData()
{
	if(!gbNeedReset())
		return;
	Vertex_Point* vertex = (Vertex_Point*)gbGetVertex();
	vertex[0].psize = m_size;
	vertex[0].position = Vec3(m_position.x, m_position.y, 0.0f);
	vertex[0].color = Color4f(1, 0, 0, 1);
}

gbPointArray::gbPointArray(size_t _count)
	:D3DXPrimitive(new Vertex_Point[_count], _count, _count, nullptr, D3DPT_POINTLIST),
	m_position(new Vec2[_count]), m_size(new float[_count])
{
	initBuf();
	gbSetSolid(D3DFILL_POINT);
}

gbPointArray::~gbPointArray()
{
	if(m_position)
		delete[] m_position;
	if(m_size)
		delete[] m_size;
}

void gbPointArray::gbResetData()
{
	if(!gbNeedReset())
		return;
	Vertex_Point* vertex = (Vertex_Point*)gbGetVertex();
	for (size_t i = 0; i < gbGetCount(); ++i)
	{
		vertex[i].position = Vec3(m_position[i].x, m_position[i].y, 0.0f);
		vertex[i].psize = m_size[i];
		vertex[i].color = Color4f(1, 0, 0, 1);
	}
	gbSetReset(false);
}
