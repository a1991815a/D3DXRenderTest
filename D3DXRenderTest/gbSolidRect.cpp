#include "gbSolidRect.h"
#include "GBAssert.h"

gbSolidRect::gbSolidRect()
	:D3DXPrimitive(new Vertex[6], 2, 6, nullptr, D3DPT_TRIANGLELIST)
{
	initBuf();
	setSolid(D3DFILL_SOLID);
}

gbSolidRect::~gbSolidRect()
{

}

void gbSolidRect::resetData()
{
	if(!needReset())
		return;
	Vertex* vertex = getVertex();
	Vec2 t_size = getSize();
	GBASSERT(t_size.x >= 0 && t_size.y >= 0);
	vertex[0].position = Vec3(m_rect.x, m_rect.y, 0.0f);
	vertex[1].position = Vec3(m_rect.x + t_size.x, m_rect.y, 0.0f);
	vertex[2].position = Vec3(m_rect.x + t_size.x, m_rect.y + t_size.y, 0.0f);
	vertex[3].position = Vec3(m_rect.x + t_size.x, m_rect.y + t_size.y, 0.0f);
	vertex[4].position = Vec3(m_rect.x, m_rect.y + t_size.y, 0.0f);
	vertex[5].position = Vec3(m_rect.x, m_rect.y, 0.0f);
	
	for (size_t i = 0; i < 6; ++i)
		vertex[i].color = Color4f(1, 0, 0, 1);

	setReset(false);
}
