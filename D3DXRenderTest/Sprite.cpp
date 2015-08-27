#include "Sprite.h"
#include "SpriteFrameManager.h"

Sprite::Sprite()
	:m_frame(nullptr)
{

}

Sprite::~Sprite()
{

}

void Sprite::visit()
{
	m_frame->setProgram(getProgram());
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
	setContentSize(frame->getSize());
	frame->retain();
}

void Sprite::bindAnimate()
{
	throw std::runtime_error("");
}

Sprite* Sprite::createBySpriteFrame( const GString& key )
{
	Sprite* ret = Sprite::create();
	ret->setFrame(SpriteFrameManager::getInstance()->getSpriteFrame(key));
	return ret;
}
