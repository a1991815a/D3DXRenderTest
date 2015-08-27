#ifndef __SPRITEFRAME__
#define __SPRITEFRAME__
#include "Rect.h"
#include "Texture2D.h"
#include "RenderObject.h"
#include "Ref.h"

class SpriteFrame:public Ref, public RenderObject{
private:
	Rect m_rect;											//��ͼ����
	Texture2D* m_texture;									//����
	const Vec3* anchontPoint;								//ê��
	const D3DXMATRIX* mMatrix;								//�任����
	unsigned char* pixelColor;
	int m_pitch;
public:
	static SpriteFrame* create(Texture2D* tex);
	static SpriteFrame* create(const GString& file_name);
	static SpriteFrame* createFromSpriteFrameCache(const GString& name);
	
public:
	SpriteFrame();
	~SpriteFrame();

	inline const Rect& getRect() const{
		return m_rect;
	}

	Color4f getColor(const Vec2& pos) const;

	inline Vec2 getSize() const{
		return Vec2(m_rect.width, m_rect.height);
	}
	inline void setMatrix(const D3DXMATRIX* matrix){
		mMatrix = matrix;
	};
	inline void setAnchontPoint(const Vec3* anchontPoint){
		this->anchontPoint = anchontPoint;
	}

	Texture2D* getTexture() {
		return m_texture;
	};

	const Texture2D* getTexture() const {
		return m_texture;
	};

	void initColorRect();

	virtual void visit();

};
#endif