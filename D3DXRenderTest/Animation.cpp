#include "Animation.h"

Animation* Animation::create()
{
	Animation* ani = nullptr;
	gbAlloc(ani);
	return ani;
}

Animation::Animation()
	:m_frameList(),m_isReset(false),
	m_delay(0), m_isReplay(false)
{

}

Animation::~Animation()
{

}
