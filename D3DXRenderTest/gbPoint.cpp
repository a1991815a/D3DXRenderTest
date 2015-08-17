#include "gbPoint.h"
#include "D3DXGlobalFunction.h"

gbPoint::gbPoint()
	:D3DXPrimitive(new Vertex_Point[1], 1, 1, nullptr, D3DPT_POINTLIST)
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

gbPoint::~gbPoint()
{

}

gbPointArray::gbPointArray(size_t _count)
	:D3DXPrimitive(new Vertex_Point[_count], _count, _count, nullptr, D3DPT_POINTLIST)
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

gbPointArray::~gbPointArray()
{

}
