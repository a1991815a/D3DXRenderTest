#include "Texture2D.h"
#include "MacroHeader.h"
#include "D3DXGlobalFunction.h"
#include "PathManager.h"

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
		D3DPOOL_MANAGED,
		&texture->m_d3dTexture
		);
	GBASSERT(texture->m_d3dTexture != nullptr);
	texture->m_size.left = 0;
	texture->m_size.top = 0;
	texture->m_size.right = width;
	texture->m_size.bottom = height;
	return texture;
}

Texture2D* Texture2D::create(const GString& file)
{
	Texture2D* texture = nullptr;
	gbAlloc(texture);
	D3DXIMAGE_INFO info = { 0 };

	for (size_t i = 0; i < _pathManager->size(); ++i)
	{
		GString t_path = _pathManager->getPath(file, i);
			
		D3DXCreateTextureFromFileExA(
			dxGetDevice(),
			t_path.c_str(),
			D3DX_FROM_FILE,
			D3DX_FROM_FILE,
			D3DX_DEFAULT,
			0,
			D3DFMT_A8B8G8R8,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0x00000000,
			&info,
			nullptr,
			&texture->m_d3dTexture
			);

		if(texture->m_d3dTexture)
			break;
	}
	if (texture->m_d3dTexture == nullptr)
	{
		GString out_text = file + "\n";
		OutputDebugStringA(out_text.c_str());
	}
	GBASSERT(texture->m_d3dTexture != nullptr);
	/*texture->m_size.left = 0;
	texture->m_size.top = 0;
	texture->m_size.right = info.Width;
	texture->m_size.bottom = info.Height;*/
	texture->m_size.left = 0;
	texture->m_size.top = 0;
	texture->m_size.right = info.Width;
	texture->m_size.bottom = info.Height;
	texture->m_name = file;
	return texture;
}

Texture2D* Texture2D::create(IDirect3DTexture9* texture, size_t width, size_t height)
{
	Texture2D* tex = nullptr;
	gbAlloc(tex);
	tex->m_d3dTexture = texture;

	tex->m_size.left = 0;
	tex->m_size.top = 0;
	tex->m_size.right = width;
	tex->m_size.bottom = height;
	return tex;
}

/*
Texture2D* Texture2D::create( const GString& file, const GString& plist )
{

}
*/

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

void Texture2D::visit()
{
	linkProgram();
	getProgram()->SetMatrix(D3D_VERTEX_SHADER, "mMatrix", mMatrix);
	getProgram()->SetBool(D3D_PIXEL_SHADER, "isSprite", true);
	dxGetSprite()->Draw(m_d3dTexture, &m_size, anchontPoint->getD3DXVector(), nullptr, 0xffffffff);
	dxGetSprite()->Flush();
}

void Texture2D::renderToThis(RenderObject* obj)
{
	GBASSERT(isTarget);
	auto device = dxGetDevice();
	IDirect3DSurface9* surface = nullptr;
	IDirect3DSurface9* tex_surface = nullptr;
	device->GetRenderTarget(0, &surface);
	m_d3dTexture->GetSurfaceLevel(0, &tex_surface);
	device->SetRenderTarget(0, tex_surface);
	device->BeginScene();
	dxGetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	obj->visit();
	dxGetSprite()->End();
	device->EndScene();
	device->SetRenderTarget(0, surface);
	SAFE_RELEASE_COM(surface);
	SAFE_RELEASE_COM(tex_surface);
}
