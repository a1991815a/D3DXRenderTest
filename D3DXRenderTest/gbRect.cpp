#include "gbRect.h"
#include "D3DXGlobalFunction.h"

gbRect::gbRect()
	:D3DXPrimitive(new Vertex[5], 4, 5, nullptr, D3DPT_LINESTRIP)
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
