#ifndef __GBPOINT__
#define __GBPOINT__
#include "D3DXPrimitive.h"
#include "GBAssert.h"

class gbPoint : public D3DXPrimitive {
private:
	Vec2 m_position;
	float m_size;
public:
	gbPoint();
	~gbPoint();

	const Vec2& gbGetPosition() const{
		return m_position;
	}
	void gbSetPosition(const Vec2& pos){
		m_position = pos;
		gbSetReset(true);
	}
	void setPositionX(float x){
		m_position.x = x;
		gbSetReset(true);
	}
	void setPositionY(float y){
		m_position.y = y;
		gbSetReset(true);
	}

	float getPSize() const {
		return m_size;
	};
	void setPSize(float psize) {
		m_size = psize;
		gbSetReset(true);
	};

	virtual void gbResetData() override;

};

class gbPointArray : public D3DXPrimitive {
private:
	Vec2* m_position;
	float* m_size;

public:
	gbPointArray() {};
	gbPointArray(size_t _count);
	~gbPointArray();

	const Vec2& gbGetPosition(size_t index) const{
		GBASSERT(index < gbGetCount());
		return m_position[index];
	}
	void gbSetPosition(size_t index, const Vec2& pos){
		GBASSERT(index < gbGetCount());
		m_position[index] = pos;
		gbSetReset(true);
	}

	void setPositionX(size_t index, float x){
		GBASSERT(index < gbGetCount());
		m_position[index].x = x;
		gbSetReset(true);
	};
	void setPositionY(size_t index, float y){
		GBASSERT(index < gbGetCount());
		m_position[index].y = y;
		gbSetReset(true);
	};

	float getPSize(size_t index) const {
		GBASSERT(index < gbGetCount());
		return m_size[index];
	};
	void setPSize(size_t index, float psize) {
		GBASSERT(index < gbGetCount());
		m_size[index] = psize;
		gbSetReset(true);
	};

	virtual void gbResetData() override;

};
#endif