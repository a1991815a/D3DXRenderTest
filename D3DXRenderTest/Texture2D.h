#ifndef __TEXTURE2D__
#define __TEXTURE2D__
#include "D3DXHeader.h"
#include "Ref.h"
#include "RenderObject.h"
#include "UtilsHeader.h"
#include "Vec.h"

class Texture2D: public Ref, public RenderObject{
	friend class SpriteFrame;
public:
	static Texture2D* create();
	static Texture2D* create(const GString& file);
	static Texture2D* create(size_t width, size_t height);
	static Texture2D* create(IDirect3DTexture9* texture, size_t width, size_t height);
//	static Texture2D* create(const GString& file, const GString& plist);
	const Vec3* anchontPoint;								//Ãªµã
	const D3DXMATRIX* mMatrix;								//±ä»»¾ØÕó
	GString m_name;
public:
	Texture2D();
	Texture2D(IDirect3DTexture9* texture);
	~Texture2D();

	virtual void visit() override;
	void renderToThis(RenderObject* obj);

	void setName(const GString& name){
		this->m_name = name;
	}
	const GString& getName() const{
		return m_name;
	};
	inline float getWidth() const {
		return (float)(m_size.right - m_size.left);
	}
	inline float getHeight() const {
		return (float)(m_size.bottom - m_size.top);
	}
	inline void setMatrix(const D3DXMATRIX* matrix){
		mMatrix = matrix;
	};
	inline void setAnchontPoint(const Vec3* anchontPoint){
		this->anchontPoint = anchontPoint;
	}

	IDirect3DTexture9* getTexture() {
		return m_d3dTexture;
	};
	const IDirect3DTexture9* getTexture() const {
		return m_d3dTexture;
	}

	Color4f getPixel(real x, real y) const;

private:
	IDirect3DTexture9* m_d3dTexture;
	bool isTarget;
	RECT m_size;
};
#endif