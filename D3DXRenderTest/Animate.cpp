#include "Animate.h"

void Animate::bindSpriteFrame( SpriteFrame** frame )
{
	m_useIndex.insert(
		std::unordered_map<SpriteFrame**, Timer_Frame>::value_type(frame, Timer_Frame()));
}

void Animate::update()
{
	auto itor = m_useIndex.begin();
	for (; itor != m_useIndex.end(); )
	{
		SpriteFrame** sf = itor->first;
		Timer_Frame& t_frame = itor->second;
		Timer& time = t_frame.m_timer;
		size_t& cur_frame = t_frame.cur_frame;

		if(time.getDelta() >= animation->getDelay()){
			if(++cur_frame >= animation->getFrameCount())
			{
				
				if(animation->isReplay())
					cur_frame = 0;
				else{
					if(animation->isReset())
					{
						cur_frame = 0;
						*sf = animation->m_frameList.at(cur_frame);
					}
					itor = m_useIndex.erase(itor);
					continue;
				}
			}
			*sf = animation->m_frameList.at(cur_frame);
			time.reset();
		}
		++itor;
	}
}
