#ifndef __RENDERENGINE__
#define __RENDERENGINE__
#include <d3d9.h>
#include <d3dx9.h>
#include "GameStep.h"

class D3DXRenderEngine;

class RenderEngine: public GameStep{
private:
	void** m_context;					//上下文指针,
public:
	RenderEngine(void** context)
		: m_context(context)
	{};

	virtual ~RenderEngine(){};

	D3DXRenderEngine* toD3DXRenderEngine(){
		return (D3DXRenderEngine*)this;
	}

	IDirect3DDevice9* getDevice(){
		return (IDirect3DDevice9*)*m_context;
	}
};
#endif