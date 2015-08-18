#ifndef __GBSOLIDRECT__
#define __GBSOLIDRECT__
#include "D3DXPrimitive.h"
#include "Rect.h"

class gbSolidRect: public D3DXPrimitive{
private:
	Rect m_rect;
public:
	gbSolidRect();
	~gbSolidRect();

	Vec2 getPosition() const{
		return Vec2(m_rect.x, m_rect.y);
	};
	void setPosition(const Vec2& pos){
		m_rect.x = pos.x;
		m_rect.y = pos.y;
		setReset(true);
	};
	void setPositionX(float x){
		m_rect.x = x;
		setReset(true);
	};
	void setPositionY(float y){
		m_rect.y = y;
		setReset(true);
	};

	Vec2 getSize() const{
		return Vec2(m_rect.width, m_rect.height);
	};

	void setSize(const Vec2& _Size){
		m_rect.width = _Size.x;
		m_rect.height = _Size.y;
		setReset(true);
	};
	void setSizeWidth(float _Width){
		m_rect.width = _Width;
		setReset(true);
	};
	void setSizeHeight(float _Height){
		m_rect.height = _Height;
		setReset(true);
	};

	virtual void resetData() override;
};
#endif