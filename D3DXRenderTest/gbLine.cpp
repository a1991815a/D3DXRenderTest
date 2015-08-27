#include "gbLine.h"
#include "AppdeleGate.h"
#include "D3DXGlobalFunction.h"

gbLine::gbLine()
	:D3DXPrimitive(new Vertex[2], 1, 2, nullptr, D3DPT_LINELIST)
{
	initBuf();
}

gbLine::~gbLine()
{

}

void gbLine::gbResetData()
{
	if(!gbNeedReset())
		return;
	Vertex* vertex = gbGetVertex();
	vertex[0].position = Vec3(m_Position.x, m_Position.y, 0.0f);
	vertex[0].color = Color4f(1, 0, 0, 1);
	vertex[1].position = Vec3(m_toPosition.x, m_toPosition.y, 0.0f);
	vertex[1].color = Color4f(1, 0, 0, 1);
	gbSetReset(false);
}
