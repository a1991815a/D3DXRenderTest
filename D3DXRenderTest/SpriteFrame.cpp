#include "SpriteFrame.h"
#include "TextureManager.h"
#include "MemoryPool\gbMemoryPool.h"
#include "MacroHeader.h"

#pragma warning(disable: 4244)

SpriteFrame* SpriteFrame::create( const GString& file_name )
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
	:m_rect(),m_texture(nullptr),
	pixelColor(nullptr),anchontPoint(nullptr), mMatrix(nullptr),
	m_pitch(0)
{

}

SpriteFrame::~SpriteFrame()
{
	SAFE_RELEASE(m_texture);
}

Color4f SpriteFrame::getColor(const Vec2& pos) const
{
	if(pos.x < 0 || pos.y < 0 || pos.x > getSize().x || pos.y > getSize().y)
		return Color4f(0, 0, 0, 0);
	POINT point = {(int)pos.x, (int)getSize().y - (int)pos.y};
	float r = 0, g = 0, b = 0, a = 0;
	unsigned char* ptr = pixelColor;
	ptr += point.y * m_pitch + point.x * 4;
	b = ptr[0];
	g = ptr[1];
	r = ptr[2];
	a = ptr[3];
	return Color4f(r / 255, g / 255, b / 255, a / 255);
}

void SpriteFrame::initColorRect()
{
	if(pixelColor != nullptr)
		return;
	IDirect3DTexture9* texture = m_texture->getTexture();

	D3DLOCKED_RECT info = {0};
	RECT color = {0, 0, (int)m_rect.width, (int)m_rect.height};
	
	texture->LockRect(0, &info, &color, 0);
	m_pitch = info.Pitch;
	pixelColor = new unsigned char[(int)m_rect.height * m_pitch];

	memmove_s(
		pixelColor, (int)m_rect.height * m_pitch,
		info.pBits, (int)m_rect.height * m_pitch
		);
	texture->UnlockRect(0);
}

void SpriteFrame::visit()
{
	linkProgram();
	RECT rect;
	rect.left = m_rect.x;
	rect.right = m_rect.x + m_rect.width;
	rect.top = m_rect.y;
	rect.bottom = m_rect.y + m_rect.height;
	dxGetProgram()->SetMatrix(D3D_VERTEX_SHADER, "mMatrix", dxGetIndentityMatrix());
	dxGetProgram()->SetBool(D3D_PIXEL_SHADER, "isSprite", true);

	dxGetSprite()->SetTransform(mMatrix);
	dxGetSprite()->Draw(m_texture->m_d3dTexture, &rect, anchontPoint->getD3DXVector(), nullptr, 0xffffffff);
	dxGetSprite()->Flush();
	
}


#pragma warning(default: 4244)