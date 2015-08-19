#include "Sprite.h"

Sprite::Sprite()
	:m_texture(nullptr)
{

}

Sprite::~Sprite()
{

}

void Sprite::visit()
{
	linkProgram();
	m_texture->setAnchontPoint(&getAnchontPoint());
	m_texture->setMatrix(getTransformMatrix());
	m_texture->visit();
}

bool Sprite::init()
{
	return true;
}

void Sprite::setFrame(Texture2D* texture)
{
	m_texture = texture;
}

void Sprite::bindAnimate()
{
	throw std::runtime_error("");
}
