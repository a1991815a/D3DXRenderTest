#ifndef __ANIMATION__
#define __ANIMATION__
#include "Vector.h"
#include "SpriteFrame.h"
#include "Timer.h"
#include "Ref.h"

class Animation: public Ref{
	friend class Animate;
private:
	Vector<SpriteFrame*> m_frameList;
	bool m_isReset;
	bool m_isReplay;
	time_type m_delay;

public:
	static Animation* create();
	Animation();
	~Animation();
	inline bool isReplay() const{
		return m_isReplay;
	}
	inline void setReplay(bool flag){
		m_isReplay = flag;
	}

	inline const Vector<SpriteFrame*>& getFrameList() const{
		return m_frameList;
	}
	inline void setReset(bool reset){
		this->m_isReset = reset;
	};
	inline bool isReset() const{
		return m_isReset;
	}
	inline void setDelay(time_type delay){
		this->m_delay = delay;
	};

	inline time_type getDelay(){
		return m_delay;
	};
	void setVector(const Vector<SpriteFrame*>& vec){
		m_frameList = vec;
	}
	inline void init(
		const Vector<SpriteFrame*>& vec,
		time_type delay,
		bool is_replay,
		bool isReset
		)
	{
		setVector(vec);
		setDelay(delay);
		setReplay(is_replay);
		setReset(isReset);
	};
	inline size_t getFrameCount() const{
		return m_frameList.size();
	}
};
#endif