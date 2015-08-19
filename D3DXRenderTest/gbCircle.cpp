#include "gbCircle.h"
#include <math.h>

gbCircle::gbCircle()
	:D3DXPrimitive(new Vertex[361], 359, 361, nullptr, D3DPT_TRIANGLEFAN),
	m_position(), m_radian(0)
{
	initBuf();
}

gbCircle::~gbCircle()
{

}

void gbCircle::resetData()
{
	if(!needReset())
		return;
	Vertex* vertex = getVertex();

	vertex[0].position = Vec3(m_position.x, m_position.y, 0);

	//1
	for (size_t i = 0; i <= 45; ++i)
		vertex[i + 1].position = Vec3(
		cos((float)i/180.0f * D3DX_PI) * m_radian, 
		sin((float)i/180.0f *D3DX_PI) * m_radian, 
		0) ;
	//2
	for (size_t i = 45; i <= 90; ++i)
		vertex[i + 1].position = Vec3(
		vertex[i + 1 - 45].position.y,
		vertex[i + 1 - 45].position.x,
		0);
	//3
	for (size_t i = 90; i <= 135; ++i)
		vertex[i + 1].position = Vec3(
		-vertex[i + 1 - 45].position.x,
		vertex[i + 1 - 45].position.y,
		0);
	//4
	for (size_t i = 135; i <= 180; ++i)
		vertex[i + 1].position = Vec3(
		-vertex[i + 1 - 45].position.y,
		-vertex[i + 1 - 45].position.x,
		0);
	//5
	for (size_t i = 180; i <= 225; ++i)
		vertex[i + 1].position = Vec3(
		vertex[i + 1 - 45].position.x,
		-vertex[i + 1 - 45].position.y,
		0);
	//6
	for (size_t i = 225; i <= 270; ++i)
		vertex[i + 1].position = Vec3(
		vertex[i + 1 - 45].position.y,
		vertex[i + 1 - 45].position.x,
		0);
	//7
	for (size_t i = 270; i <= 315; ++i)
		vertex[i + 1].position = Vec3(
		-vertex[i + 1 - 45].position.x,
		vertex[i + 1 - 45].position.y,
		0);
	//8
	for (size_t i = 315; i <= 360; ++i)
		vertex[i + 1].position = Vec3(
		-vertex[i + 1 - 45].position.y,
		-vertex[i + 1 - 45].position.x,
		0);
	/*	vertex[361].position = vertex[1].position;*/
	vertex[0].color = Color4f(1, 0, 0, 1);
	for (size_t i = 0; i <= 360; ++i){
		vertex[i + 1].position.x += m_position.x;
		vertex[i + 1].position.y += m_position.y;
		vertex[i + 1].color = Color4f(1, 0, 0, 1);
	}

	setReset(false);
}
