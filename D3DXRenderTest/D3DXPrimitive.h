#ifndef __D3DXPRIMITIVE__
#define __D3DXPRIMITIVE__
#include "D3DXHeader.h"
#include "D3DXVertex.h"

class D3DXPrimitive{
private:
	Vertex* m_vertex;
	size_t m_count;
	size_t m_vCount;
	IDirect3DVertexBuffer9* m_buf;
	D3DPRIMITIVETYPE m_type;
public:
	D3DXPrimitive();
	D3DXPrimitive(
		Vertex* _Vertex, 
		size_t _Count, 
		size_t _vCount, 
		IDirect3DVertexBuffer9* _buf,
		D3DPRIMITIVETYPE type);
	~D3DXPrimitive();
	void assemble();
	void draw() const;

	//设置顶点数据
	void setData(Vertex* _vertex, size_t offset, size_t _count = 1 );

	/*
		getter, setter
	*/
	inline const Vertex* getVertex() const { return m_vertex; }

/*	inline void setVertex(Vertex* val) { m_vertex = val; }
	不需要在外部初始化该属性
*/
	inline const size_t getCount() const { return m_count; }

/*	inline void setCount(size_t val) { m_count = val; }
	不需要在外部初始化该属性
*/
	inline const size_t getVCount() const { return m_vCount; }

/*	inline void setVCount(size_t val) { m_vCount = val; }
	不需要在外部初始化该属性
*/
	inline const IDirect3DVertexBuffer9* getBuf() const { return m_buf; }
	
	inline const D3DPRIMITIVETYPE getType() const { return m_type; }

/*	inline void setType(D3DPRIMITIVETYPE val) { m_type = val; }
	不需要在外部初始化该属性
*/

protected:
	inline void setBuf(IDirect3DVertexBuffer9* val) { m_buf = val; }
};
#endif