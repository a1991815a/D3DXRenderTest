#ifndef __TEXTURE2D__
#define __TEXTURE2D__
#include "D3DXHeader.h"
#include "Ref.h"
#include "RenderObject.h"
#include <string>

class Texture2D: public Ref, public RenderObject{
	friend class SpriteFrame;
public:
	static Texture2D* create();
	static Texture2D* create(const std::string& file);
	static Texture2D* create(size_t width, size_t height);
	static Texture2D* create(IDirect3DTexture9* texture, size_t width, size_t height);
//	static Texture2D* create(const std::string& file, const std::string& plist);
	const Vec3* anchontPoint;								//Ãªµã
	const D3DXMATRIX* mMatrix;								//±ä»»¾ØÕó
	std::string m_name;
public:
	Texture2D();
	Texture2D(IDirect3DTexture9* texture);
	~Texture2D();

	virtual void visit() override;
	void renderToThis(RenderObject* obj);

	void setName(const std::string& name){
		this->m_name = name;
	}
	const std::string& getName() const{
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
private:
	IDirect3DTexture9* m_d3dTexture;
	bool isTarget;
	RECT m_size;
};
#endif