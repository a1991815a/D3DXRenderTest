#include "Sprite.h"
#include "SpriteFrameManager.h"
#include "MacroHeader.h"

Sprite::Sprite()
	:m_frame(nullptr)
{

}

Sprite::~Sprite()
{
	SAFE_RELEASE(m_frame);
}

void Sprite::visit()
{
	m_frame->setProgram(getProgram());
	m_frame->setAnchontPoint(&getAnchontPoint());
	m_frame->setContentSize(&getContentSize());
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

void Sprite::setFrameByName(const GString& name)
{
	setFrame(
		SpriteFrameManager::getInstance()->getSpriteFrame(name)
		);
}

void Sprite::bindAnimate()
{
	throw std::runtime_error("");
}

Value Sprite::serialization()
{
	Value val = Node::serialization();
	ValueMap& vm = val.asVMap();
	vm["frame"] = m_frame->getTexture()->getName();
	vm["type"] = "sprite";
	return val;
}

Sprite* Sprite::createBySpriteFrame(const GString& key)
{
	Sprite* ret = Sprite::create();
	ret->setFrame(SpriteFrameManager::getInstance()->getSpriteFrame(key));
	return ret;
}

Sprite* Sprite::createByKey(const char* key_1, ...)
{
	Sprite* ret = Sprite::create();
	va_list ap;
	va_start(ap, key_1);
	SpriteFrame* sf = SpriteFrameManager::getInstance()->getFrameByVMap(ap, key_1);
	ret->setFrame(sf);
	va_end(ap);
	OutputDebugStringA(sf->getKey().c_str());
	return ret;
}
