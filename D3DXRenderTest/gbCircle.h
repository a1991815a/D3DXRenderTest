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
	const Vec2& gbGetPosition() const{
		return m_position;
	};
	void gbSetPosition(const Vec2& pos){
		m_position.x = pos.x;
		m_position.y = pos.y;
		gbSetReset(true);
	};
	void gbSetPositionX(float x){
		m_position.x = x;
		gbSetReset(true);
	};
	void gbSetPositionY(float y){
		m_position.y = y;
		gbSetReset(true);
	};

	float gbGetRadian() const{
		return m_radian;
	}
	void gbSetRadian(float r){
		m_radian = r;
		gbSetReset(true);
	}

	virtual void gbResetData() override;

};
#endif