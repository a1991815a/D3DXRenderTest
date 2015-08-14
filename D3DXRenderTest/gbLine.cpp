#include "gbLine.h"
#include "AppdeleGate.h"

gbLine::gbLine()
	:D3DXPrimitive(new Vertex_pos[2], 1, 2, nullptr, D3DPT_LINELIST)
{
	IDirect3DDevice9* device = _renderEngine->getDevice();
	IDirect3DVertexBuffer9* buf = nullptr;
	device->CreateVertexBuffer(
		getVertex()->getSize() * getVCount(),
		0,
		getVertex()->getFVF(),
		D3DPOOL_DEFAULT,
		&buf,
		nullptr
		);
	setBuf(buf);
}

gbLine::~gbLine()
{

}
