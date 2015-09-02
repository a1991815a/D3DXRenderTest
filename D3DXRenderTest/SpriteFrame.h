#ifndef __SPRITEFRAME__
#define __SPRITEFRAME__
#include "Rect.h"
#include "Texture2D.h"
#include "RenderObject.h"
#include "Ref.h"

class SpriteFrame:public Ref, public RenderObject{
private:
	GString m_key;											//取帧键值
	Rect m_rect;											//绘图区域
	Texture2D* m_texture;									//纹理
	const Vec3* anchontPoint;								//锚点
	const Vec2* contentSize;								//纹理对应尺寸
	const Vec2* scale;										//缩放
	const D3DXMATRIX* mMatrix;								//变换矩阵
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

	void setKey(const GString& key);
	const GString& getKey() const{
		return m_key;
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

	void setContentSize(const Vec2* size){
		contentSize = size;
	}

	void initColorRect();

	virtual void visit();

};
#endif