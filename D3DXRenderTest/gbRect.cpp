#include "gbRect.h"
#include "D3DXGlobalFunction.h"
#include "GBAssert.h"

gbRect::gbRect()
	:D3DXPrimitive(new Vertex[5], 4, 5, nullptr, D3DPT_LINESTRIP)
{
	initBuf();
}

void gbRect::resetData()
{
	if(!needReset())
		return;
	Vertex* vertex = getVertex();
	Vec2 t_size = getSize();
	GBASSERT(t_size.x >= 0 && t_size.y >= 0);
	vertex[0].position = Vec3(m_rect.x, m_rect.y, 0.0f);
	vertex[1].position = Vec3(m_rect.x + t_size.x, m_rect.y, 0.0f);
	vertex[2].position = Vec3(m_rect.x + t_size.x, m_rect.y + t_size.y, 0.0f);
	vertex[3].position = Vec3(m_rect.x, m_rect.y + t_size.y, 0.0f);
	vertex[4].position = Vec3(m_rect.x, m_rect.y, 0.0f);
	setReset(false);
}
