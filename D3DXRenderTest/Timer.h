#ifndef __TIMER__
#define __TIMER__

typedef unsigned long long time_type;

class Timer{
	friend class TimerManager;
private:
	time_type m_time;
public:
	Timer();
	~Timer();
	inline void reset(){
		m_time = 0;
	};

	inline time_type getDelta() const{
		return m_time;
	};
};
#endif