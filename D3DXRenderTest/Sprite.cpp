#include "Sprite.h"

Sprite::Sprite()
	:m_frame(nullptr)
{

}

Sprite::~Sprite()
{

}

void Sprite::visit()
{
	linkProgram();
	m_frame->setAnchontPoint(&getAnchontPoint());
	m_frame->setMatrix(getTransformMatrix());
	m_frame->visit();
}

bool Sprite::init()
{
	return true;
}

void Sprite::setFrame(SpriteFrame* frame)
{
	m_frame = frame;
	frame->retain();
}

void Sprite::bindAnimate()
{
	throw std::runtime_error("");
}
