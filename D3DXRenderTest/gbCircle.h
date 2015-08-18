#ifndef __GBCIRCLE__
#define __GBCIRCLE__
#include "D3DXPrimitive.h"

class gbCircle: public D3DXPrimitive{
private:
	Vec2 m_position;
	float m_radian;
public:
	gbCircle();
	~gbCircle();
	const Vec2& getPosition() const{
		return m_position;
	};
	void setPosition(const Vec2& pos){
		m_position.x = pos.x;
		m_position.y = pos.y;
		setReset(true);
	};
	void setPositionX(float x){
		m_position.x = x;
		setReset(true);
	};
	void setPositionY(float y){
		m_position.y = y;
		setReset(true);
	};

	float getRadian() const{
		return m_radian;
	}
	void setRadian(float r){
		m_radian = r;
		setReset(true);
	}

	virtual void resetData() override;

};
#endif