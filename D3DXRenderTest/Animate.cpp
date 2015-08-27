#include "Animate.h"

Animate* Animate::create()
{
	Animate* ret = nullptr;
	gbAlloc(ret);
	return ret;
}

Animate::Animate()
	:index(0), m_replay(true), m_reset(true)
{

}

void Animate::addSpriteFrame(SpriteFrame* frame)
{
	m_frameList.push_back(frame);
}

void Animate::setReplay(bool _replay)
{
	m_replay = _replay;
}

void Animate::setReset(bool _reset)
{
	m_reset = _reset;
}

void Animate::reset()
{
	index = 0;
}

void Animate::_update()
{
	if (index >= m_frameList.size())
		reset();
	Sprite* sprite = dynamic_cast<Sprite*>(getNode());
	sprite->m_frame = m_frameList.at(index++);
}
