#ifndef __TEXTURE2D__
#define __TEXTURE2D__
#include "D3DXHeader.h"
#include "Ref.h"
#include "RenderObject.h"

class Texture2D: public Ref, public RenderObject{
public:
	static Texture2D* create();
	static Texture2D* create(const std::string& file);
	static Texture2D* create(size_t width, size_t height);
	static Texture2D* create(IDirect3DTexture9* texture, size_t width, size_t height);

	const Vec3* anchontPoint;								//Ãªµã
	const D3DXMATRIX* mMatrix;								//±ä»»¾ØÕó
public:
	Texture2D();
	Texture2D(IDirect3DTexture9* texture);
	~Texture2D();

	virtual void visit() override;
	void renderToThis(RenderObject* obj);

	inline float getWidth() const {
		return m_size.x;
	}
	inline float getHeight() const {
		return m_size.y;
	}
	inline void setMatrix(const D3DXMATRIX* matrix){
		mMatrix = matrix;
	};
	inline void setAnchontPoint(const Vec3* anchontPoint){
		this->anchontPoint = anchontPoint;
	}
private:
	IDirect3DTexture9* m_d3dTexture;
	bool isTarget;
	Vec2 m_size;
};
#endif