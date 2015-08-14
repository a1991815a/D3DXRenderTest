#ifndef __RENDERENGINE__
#define __RENDERENGINE__
#include <d3d9.h>
#include <d3dx9.h>

class D3DXRenderEngine;

class RenderEngine{
private:
	void** m_context;					//上下文指针,
public:
	RenderEngine(void** context)
		: m_context(context)
	{};

	virtual ~RenderEngine(){};
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void destroy() = 0;

	D3DXRenderEngine* toD3DXRenderEngine(){
		return (D3DXRenderEngine*)this;
	}

	IDirect3DDevice9* getDevice(){
		return (IDirect3DDevice9*)*m_context;
	}
};
#endif