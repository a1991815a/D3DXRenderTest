#include "D3DXPrimitive.h"
#include "GBAssert.h"
#include "MacroHeader.h"
#include "AppdeleGate.h"

D3DXPrimitive::D3DXPrimitive()
	:m_vertex(nullptr), m_count(1), m_vCount(0), m_buf(nullptr), m_type()
{

}

D3DXPrimitive::D3DXPrimitive(
	Vertex* _Vertex, 
	size_t _Count, 
	size_t _vCount, 
	IDirect3DVertexBuffer9* _buf,
	D3DPRIMITIVETYPE type)
	:m_vertex(_Vertex), m_count(_Count), m_vCount(_vCount), m_buf(_buf), m_type(type)
{

}

D3DXPrimitive::~D3DXPrimitive()
{
	SAFE_RELEASE_COM(m_buf);
	SAFE_DELETE_ARRAY(m_vertex);
}

void D3DXPrimitive::assemble()
{
	void* data_ptr = nullptr;
	HRESULT result = m_buf->Lock(0, m_vertex->getSize() * m_vCount, (void**)&data_ptr, 0);
	GBASSERT(result == D3D_OK);
	memcpy_s(data_ptr, m_vertex->getSize() * m_vCount, m_vertex, m_vertex->getSize() * m_vCount);
	m_buf->Unlock();
}

void D3DXPrimitive::draw() const
{
	HRESULT result = D3D_OK;
	result = _renderEngine->getDevice()->SetVertexDeclaration(m_vertex->getVertexDecl());
	GBASSERT(result == D3D_OK);

	result = _renderEngine->getDevice()->SetStreamSource(0, m_buf, 0, m_vertex->getSize());
	GBASSERT(result == D3D_OK);
/*
着色器渲染不再需要直接指定FVF
*/
// 	result = _renderEngine->getDevice()->SetFVF(m_vertex->getFVF());
// 	GBASSERT(result == D3D_OK);
	result = _renderEngine->getDevice()->DrawPrimitive(m_type, 0, m_count);
	GBASSERT(result == D3D_OK);
}

void D3DXPrimitive::setData(Vertex* _vertex, size_t offset, size_t _count /*= 1 */)
{
	GBASSERT(m_vertex->getSize() == _vertex->getSize());
	memcpy_s(
		((char*)this->m_vertex) + m_vertex->getSize() * offset, m_vertex->getSize() * (m_vCount - offset),
		_vertex, _vertex->getSize() * _count
		);
}
