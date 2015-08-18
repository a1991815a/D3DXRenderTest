#ifndef __TEXTURE2D__
#define __TEXTURE2D__
#include "D3DXHeader.h"
#include "Ref.h"
#include "RenderRef.h"

class Texture2D: public Ref, public RenderRef{
public:
	static Texture2D* create();
	static Texture2D* create(const std::string& file);
	static Texture2D* create(size_t width, size_t height);

public:
	Texture2D();
	Texture2D(IDirect3DTexture9* texture);
	~Texture2D();

	virtual void RenderThis() override;
	void renderToThis();

	float getWidth() const {
		return m_size.x;
	}
	float getHeight() const {
		return m_size.y;
	}
private:
	IDirect3DTexture9* m_d3dTexture;
	bool isTarget;
	Vec2 m_size;
};
#endif