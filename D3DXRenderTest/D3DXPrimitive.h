#ifndef __D3DXPRIMITIVE__
#define __D3DXPRIMITIVE__
#include "D3DXHeader.h"
#include "D3DXVertex.h"
#include "Node.h"

class D3DXPrimitive: public Node{
private:
	Vertex* m_vertex;
	size_t m_count;
	size_t m_vCount;
	IDirect3DVertexBuffer9* m_buf;
	D3DPRIMITIVETYPE m_type;
	bool m_resetFlag;
	D3DFILLMODE m_fillMode;
	Vec2 m_anchontPoint;
public:
	D3DXPrimitive();
	D3DXPrimitive(
		Vertex* _Vertex, 
		size_t _Count, 
		size_t _vCount, 
		IDirect3DVertexBuffer9* _buf,
		D3DPRIMITIVETYPE type);
	~D3DXPrimitive();
	void gbAssemble();
	void gbDraw() const;

	//设置顶点数据
	void gbSetData(Vertex* _vertex, size_t offset, size_t _count = 1 );

	virtual void gbResetData() = 0;
	inline void gbSetReset(bool flag){
		m_resetFlag = flag;
	};													//设置重构标记
	inline bool gbNeedReset() const{
		return m_resetFlag;
	};

	inline void gbSetSolid(D3DFILLMODE solid){
		m_fillMode = solid;
	};

	inline D3DFILLMODE gbGetSolid() const{
		return m_fillMode;
	}

	void initBuf();
	/*
		getter, setter
	*/
	inline const Vertex* gbGetVertex() const { return m_vertex; }

/*	inline void setVertex(Vertex* val) { m_vertex = val; }
	不需要在外部初始化该属性
*/
	inline const size_t gbGetCount() const { return m_count; }

/*	inline void setCount(size_t val) { m_count = val; }
	不需要在外部初始化该属性
*/
	inline const size_t gbGetVCount() const { return m_vCount; }

/*	inline void setVCount(size_t val) { m_vCount = val; }
	不需要在外部初始化该属性
*/
	inline const IDirect3DVertexBuffer9* gbGetBuf() const { return m_buf; }
	
	inline D3DPRIMITIVETYPE gbGetType() const { return m_type; }

/*	
	inline void setType(D3DPRIMITIVETYPE val) { m_type = val; }
	:不需要在外部初始化该属性
*/
	const Vec3 gbGetPosition(size_t offset) const {
		return gbGetVertex(offset)->position;
	};
	void gbSetPosition(size_t offset, const Vec3& toPos) {
		gbGetVertex(offset)->position = toPos;
	};
	inline void gbSetColor(size_t offset, real r, real g, real b, real a) {
		Vertex* vertex = gbGetVertex(offset);
		vertex->color.r = r;
		vertex->color.g = g;
		vertex->color.b = b;
		vertex->color.a = a;
	};
	inline void gbSetColor(size_t offset, const Color4f& color) {
		gbGetVertex(offset)->color = color;
	};
	inline const Color4f& gbGetColor(size_t offset) const {
		return gbGetVertex(offset)->color;
	};
	inline const Vec3& gbGetNormal(size_t offset) const {
		return gbGetVertex(offset)->anchoPoint;
	};
	inline void gbSetNormal(size_t offset, const Vec3& normal) {
		gbGetVertex(offset)->anchoPoint = normal;
	}
	inline void gbSetAnchontPoint(const Vec2& point) {
		m_anchontPoint = point;
		gbSetReset(true);
	};
	inline void gbSetAnchontPoint(const Vec3& point) {
		m_anchontPoint.x = point.x;
		m_anchontPoint.y = point.y;
		gbSetReset(true);
	};

	inline const Vec2& gbGetAnchontPoint() const{
		return m_anchontPoint;
	}

protected:
	inline void gbSetBuf(IDirect3DVertexBuffer9* val) { m_buf = val; }
	inline const Vertex* gbGetVertex(size_t offset) const {
		return m_vertex->getNextVertex(offset);
	};
	inline Vertex* gbGetVertex(size_t offset) {
		return m_vertex->getNextVertex(offset);
	};
	inline Vertex* gbGetVertex(){
		return m_vertex;
	}

	virtual void visit() override;

};
#endif