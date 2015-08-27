#include "gbRect.h"
#include "D3DXGlobalFunction.h"
#include "GBAssert.h"

gbRect::gbRect()
	:D3DXPrimitive(new Vertex[5], 4, 5, nullptr, D3DPT_LINESTRIP)
{
	initBuf();
}

void gbRect::gbResetData()
{
	if(!gbNeedReset())
		return;
	Vertex* vertex = gbGetVertex();
	Vec2 t_size = gbGetSize();
	GBASSERT(t_size.x >= 0 && t_size.y >= 0);
	vertex[0].position = Vec3(m_rect.x, m_rect.y, 0.0f);
	vertex[1].position = Vec3(m_rect.x + t_size.x, m_rect.y, 0.0f);
	vertex[2].position = Vec3(m_rect.x + t_size.x, m_rect.y + t_size.y, 0.0f);
	vertex[3].position = Vec3(m_rect.x, m_rect.y + t_size.y, 0.0f);
	vertex[4].position = Vec3(m_rect.x, m_rect.y, 0.0f);
	for (size_t i = 0; i < 5; ++i)
		vertex[i].color = Color4f(1, 0, 0, 1);
	vertex[0].texcoord = Vec2(0, 1);
	vertex[1].texcoord = Vec2(1, 1);
	vertex[2].texcoord = Vec2(1, 0);
	vertex[3].texcoord = Vec2(0, 0);
	vertex[4].texcoord = Vec2(0, 1);

	gbSetReset(false);
}
