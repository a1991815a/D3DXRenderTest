#include "Texture2D.h"
#include "MacroHeader.h"

Texture2D* Texture2D::create()
{
	Texture2D* texture = nullptr;
	gbAlloc(texture);
	return texture;
}

Texture2D* Texture2D::create(size_t width, size_t height)
{
	Texture2D* texture = nullptr;
	gbAlloc(texture);
	texture->isTarget = true;
	D3DXCreateTexture(
		dxGetDevice(),
		width,
		height,
		0,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8B8G8R8,
		D3DPOOL_DEFAULT,
		&texture->m_d3dTexture
		);
	GBASSERT(texture->m_d3dTexture != nullptr);

	texture->m_size.x = (real)width;
	texture->m_size.y = (real)height;
	return texture;
}

Texture2D* Texture2D::create(const std::string& file)
{
	Texture2D* texture = nullptr;
	gbAlloc(texture);
	D3DXIMAGE_INFO info = { 0 };
	D3DXCreateTextureFromFileExA(
		dxGetDevice(),
		file.c_str(),
		D3DX_FROM_FILE,
		D3DX_FROM_FILE,
		D3DX_DEFAULT,
		0,
		D3DFMT_FROM_FILE,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x00000000,
		&info,
		nullptr,
		&texture->m_d3dTexture
		);
	GBASSERT(texture->m_d3dTexture != nullptr);
	texture->m_size.x = (real)info.Width;
	texture->m_size.y = (real)info.Height;
	return texture;
}

Texture2D::Texture2D()
	:m_d3dTexture(nullptr), isTarget(false)
{

}

Texture2D::Texture2D(IDirect3DTexture9* texture)
	: m_d3dTexture(texture), isTarget(false)
{	
}

Texture2D::~Texture2D()
{
	SAFE_RELEASE_COM(m_d3dTexture);
}

void Texture2D::RenderThis()
{
	

}

void Texture2D::renderToThis()
{
	GBASSERT(isTarget);
}
