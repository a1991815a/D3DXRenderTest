#include "SpriteFrame.h"
#include "TextureManager.h"
#include "MemoryPool\gbMemoryPool.h"
#include "MacroHeader.h"

#pragma warning(disable: 4244)

SpriteFrame* SpriteFrame::create( const std::string& file_name )
{
	Texture2D* tex = _textureManager->loadTextureFromFile(file_name);
	return SpriteFrame::create(tex);
}

SpriteFrame* SpriteFrame::create( Texture2D* tex )
{
	SpriteFrame* sf = nullptr;
	gbAlloc(sf);
	sf->m_texture = tex;
	sf->m_rect.x = sf->m_rect.y = 0;
	sf->m_rect.width = tex->getWidth();
	sf->m_rect.height = tex->getHeight();
	tex->retain();
	return sf;
}

SpriteFrame::SpriteFrame()
{

}

SpriteFrame::~SpriteFrame()
{
	SAFE_RELEASE(m_texture);
}

void SpriteFrame::visit()
{
	linkProgram();
	RECT rect;
	rect.left = m_rect.x;
	rect.right = m_rect.x + m_rect.width;
	rect.top = m_rect.y;
	rect.bottom = m_rect.y + m_rect.height;
	getProgram()->SetMatrix(D3D_VERTEX_SHADER, "mMatrix", dxGetIndentityMatrix());
	getProgram()->SetBool(D3D_PIXEL_SHADER, "isSprite", true);

	dxGetSprite()->SetTransform(mMatrix);
	dxGetSprite()->Draw(m_texture->m_d3dTexture, &rect, anchontPoint->getD3DXVector(), nullptr, 0xffffffff);
	dxGetSprite()->Flush();
}


#pragma warning(default: 4244)