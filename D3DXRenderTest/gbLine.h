#ifndef __GBLINE__
#define __GBLINE__
#include "D3DXPrimitive.h"

class gbLine: public D3DXPrimitive{
private:
	Vec2 m_Position;
	Vec2 m_toPosition;

public:
	gbLine();
	~gbLine();

	virtual void resetData();

	const Vec2& getPosition() const{
		return m_Position;
	};
	const Vec2& getToPosition() const{
		return m_toPosition;
	};

	void setPosition(const Vec2& pos){
		m_Position = pos;
		setReset(true);
	};

	void setPositionX(float x){
		m_Position.x = x;
		setReset(true);
	};

	void setPositionY(float y){
		m_Position.y = y;
		setReset(true);
	};

	void setToPosition(const Vec2& pos){
		m_toPosition = pos;
		setReset(true);
	};

	void setToPositionX(float x){
		m_toPosition.x = x;
		setReset(true);
	};

	void setToPositionY(float y){
		m_toPosition.y = y;
		setReset(true);
	};


};
#endif