#include "gbLine.h"
#include "AppdeleGate.h"
#include "D3DXGlobalFunction.h"

gbLine::gbLine()
	:D3DXPrimitive(new Vertex[2], 1, 2, nullptr, D3DPT_LINELIST)
{
	IDirect3DVertexBuffer9* buf = nullptr;
	dxGetDevice()->CreateVertexBuffer(
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
