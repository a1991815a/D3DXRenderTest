#ifndef __SPRITEFRAME__
#define __SPRITEFRAME__
#include "Rect.h"
#include "Texture2D.h"
#include "RenderObject.h"
#include "Ref.h"

class SpriteFrame:public Ref, public RenderObject{
private:
	Rect m_rect;											//»æÍ¼ÇøÓò
	Texture2D* m_texture;									//ÎÆÀí
	const Vec3* anchontPoint;								//Ãªµã
	const D3DXMATRIX* mMatrix;								//±ä»»¾ØÕó

public:
	static SpriteFrame* create(Texture2D* tex);
	static SpriteFrame* create(const std::string& file_name);
	static SpriteFrame* createFromSpriteFrameCache(const std::string& name);
public:
	SpriteFrame();
	~SpriteFrame();

	inline const Rect& getRect() const{
		return m_rect;
	}
	inline Vec2 getSize() const{
		return Vec2(m_rect.width, m_rect.height);
	}
	inline void setMatrix(const D3DXMATRIX* matrix){
		mMatrix = matrix;
	};
	inline void setAnchontPoint(const Vec3* anchontPoint){
		this->anchontPoint = anchontPoint;
	}

	virtual void visit();

};
#endif