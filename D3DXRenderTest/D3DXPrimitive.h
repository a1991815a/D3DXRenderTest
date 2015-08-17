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
	
	inline D3DPRIMITIVETYPE getType() const { return m_type; }

/*	
	inline void setType(D3DPRIMITIVETYPE val) { m_type = val; }
	:不需要在外部初始化该属性
*/
	const Vec3 getPosition(size_t offset) const {
		return getVertex(offset)->position;
	};
	void setPosition(size_t offset, const Vec3& toPos) {
		getVertex(offset)->position = toPos;
	};
	inline void setColor(size_t offset, real r, real g, real b, real a) {
		Vertex* vertex = getVertex(offset);
		vertex->color.r = r;
		vertex->color.g = g;
		vertex->color.b = b;
		vertex->color.a = a;
	};
	inline void setColor(size_t offset, const Color4f& color) {
		getVertex(offset)->color = color;
	};
	inline const Color4f& getColor(size_t offset) const {
		return getVertex(offset)->color;
	};
	inline const Vec3& getNormal(size_t offset) const {
		return getVertex(offset)->normal;
	};
	inline void setNormal(size_t offset, const Vec3& normal) {
		getVertex(offset)->normal = normal;
	}


protected:
	inline void setBuf(IDirect3DVertexBuffer9* val) { m_buf = val; }
	inline const Vertex* getVertex(size_t offset) const {
		return m_vertex->getNextVertex(offset);
	};
	inline Vertex* getVertex(size_t offset) {
		return m_vertex->getNextVertex(offset);
	};
};
#endif