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
	bool m_resetFlag;
	D3DFILLMODE m_fillMode;
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

	//���ö�������
	void setData(Vertex* _vertex, size_t offset, size_t _count = 1 );

	virtual void resetData() = 0;
	inline void setReset(bool flag){
		m_resetFlag = flag;
	};													//�����ع����
	inline bool needReset() const{
		return m_resetFlag;
	};

	inline void setSolid(D3DFILLMODE solid){
		m_fillMode = solid;
	};

	inline D3DFILLMODE getSolid() const{
		return m_fillMode;
	}

	void initBuf();
	/*
		getter, setter
	*/
	inline const Vertex* getVertex() const { return m_vertex; }

/*	inline void setVertex(Vertex* val) { m_vertex = val; }
	����Ҫ���ⲿ��ʼ��������
*/
	inline const size_t getCount() const { return m_count; }

/*	inline void setCount(size_t val) { m_count = val; }
	����Ҫ���ⲿ��ʼ��������
*/
	inline const size_t getVCount() const { return m_vCount; }

/*	inline void setVCount(size_t val) { m_vCount = val; }
	����Ҫ���ⲿ��ʼ��������
*/
	inline const IDirect3DVertexBuffer9* getBuf() const { return m_buf; }
	
	inline D3DPRIMITIVETYPE getType() const { return m_type; }

/*	
	inline void setType(D3DPRIMITIVETYPE val) { m_type = val; }
	:����Ҫ���ⲿ��ʼ��������
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
	inline Vertex* getVertex(){
		return m_vertex;
	}
};
#endif