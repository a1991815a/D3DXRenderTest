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

	const Vec2& getPosition() const{
		return m_position;
	}
	void setPosition(const Vec2& pos){
		m_position = pos;
		setReset(true);
	}
	void setPositionX(float x){
		m_position.x = x;
		setReset(true);
	}
	void setPositionY(float y){
		m_position.y = y;
		setReset(true);
	}

	float getPSize() const {
		return m_size;
	};
	void setPSize(float psize) {
		m_size = psize;
		setReset(true);
	};

	virtual void resetData() override;

};

class gbPointArray : public D3DXPrimitive {
private:
	Vec2* m_position;
	float* m_size;

public:
	gbPointArray() {};
	gbPointArray(size_t _count);
	~gbPointArray();

	const Vec2& getPosition(size_t index) const{
		GBASSERT(index < getCount());
		return m_position[index];
	}
	void setPosition(size_t index, const Vec2& pos){
		GBASSERT(index < getCount());
		m_position[index] = pos;
		setReset(true);
	}

	void setPositionX(size_t index, float x){
		GBASSERT(index < getCount());
		m_position[index].x = x;
		setReset(true);
	};
	void setPositionY(size_t index, float y){
		GBASSERT(index < getCount());
		m_position[index].y = y;
		setReset(true);
	};

	float getPSize(size_t index) const {
		GBASSERT(index < getCount());
		return m_size[index];
	};
	void setPSize(size_t index, float psize) {
		GBASSERT(index < getCount());
		m_size[index] = psize;
		setReset(true);
	};

	virtual void resetData() override;

};
#endif