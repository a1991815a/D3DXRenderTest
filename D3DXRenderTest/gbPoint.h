#ifndef __GBPOINT__
#define __GBPOINT__
#include "D3DXPrimitive.h"

class gbPoint : public D3DXPrimitive {
public:
	gbPoint();
	~gbPoint();

	float getPSize() const {
		return ((Vertex_Point*)(getVertex(0)))->psize;
	};
	void setPSize(float psize) {
		((Vertex_Point*)(getVertex(0)))->psize = psize;
	};
};

class gbPointArray : public D3DXPrimitive {
public:
	gbPointArray(size_t _count);
	~gbPointArray();
	float getPSize(size_t offset) const {
		return ((Vertex_Point*)(getVertex(offset)))->psize;
	};
	void setPSize(size_t offset, float psize) {
		((Vertex_Point*)(getVertex(offset)))->psize = psize;
	};
};
#endif