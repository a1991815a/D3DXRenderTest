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

	virtual void gbResetData();

	const Vec2& gbGetPosition() const{
		return m_Position;
	};
	const Vec2& gbGetToPosition() const{
		return m_toPosition;
	};

	void gbSetPosition(const Vec2& pos){
		m_Position = pos;
		gbSetReset(true);
	};

	void gbSetPositionX(float x){
		m_Position.x = x;
		gbSetReset(true);
	};

	void gbSetPositionY(float y){
		m_Position.y = y;
		gbSetReset(true);
	};

	void gbSetToPosition(const Vec2& pos){
		m_toPosition = pos;
		gbSetReset(true);
	};

	void gbSetToPositionX(float x){
		m_toPosition.x = x;
		gbSetReset(true);
	};

	void gbSetToPositionY(float y){
		m_toPosition.y = y;
		gbSetReset(true);
	};


};
#endif