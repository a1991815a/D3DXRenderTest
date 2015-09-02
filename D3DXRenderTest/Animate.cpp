#include "Animate.h"
#include "SpriteFrameManager.h"

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

SpriteFrame* Animate::getFrame(size_t index)
{
	return m_frameList.at(index);
}

void Animate::addSpriteFrame(SpriteFrame* frame)
{
	m_frameList.push_back(frame);
}

void Animate::addSpriteFrameByName(const GString& name)
{
	m_frameList.push_back(
		SpriteFrameManager::getInstance()->getSpriteFrame(name)
		);
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

SpriteFrame* Animate::nextFrame()
{
	if (++index >= m_frameList.size())
		index = 0;
	return m_frameList.at(index);
}

SpriteFrame* Animate::preFrame()
{
	if (--index >= m_frameList.size())
		index = m_frameList.size() - 1;
	return m_frameList.at(index);
}

void Animate::_update()
{
	if (index >= m_frameList.size())
	{
		if(!m_replay)
		{
			setStop(true);
			if(m_reset)
				reset();
			return;
		}
		reset();
	}
	Sprite* sprite = dynamic_cast<Sprite*>(getNode());
	sprite->m_frame = m_frameList.at(index++);
}
