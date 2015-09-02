#ifndef __GBRECT__
#define __GBRECT__
#include "D3DXPrimitive.h"
#include "Rect.h"
#include "Vec.h"

class gbRect: public D3DXPrimitive{
private:
	Rect m_rect;
public:
	gbRect();

	Vec2 gbGetPosition() const{
		return Vec2(m_rect.x, m_rect.y);
	};
	void gbSetPosition(const Vec2& pos){
		m_rect.x = pos.x;
		m_rect.y = pos.y;
		gbSetReset(true);
	};
	void setPositionX(float x){
		m_rect.x = x;
		gbSetReset(true);
	};
	void setPositionY(float y){
		m_rect.y = y;
		gbSetReset(true);
	};

	Vec2 gbGetSize() const{
		return Vec2(m_rect.width, m_rect.height);
	};

	void gbSetSize(const Vec2& _Size){
		m_rect.width = _Size.x;
		m_rect.height = _Size.y;
		gbSetReset(true);
	};
	void gbSetSizeWidth(float _Width) {
		m_rect.width = _Width;
		gbSetReset(true);
	};
	void gbSetSizeHeight(float _Height) {
		m_rect.height = _Height;
		gbSetReset(true);
	};

	virtual void gbResetData() override;
};
#endif