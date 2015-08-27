#ifndef __TIMER__
#define __TIMER__

typedef unsigned long time_type;

class Timer{
	friend class TimerManager;
private:
	time_type m_time;
	bool m_pause;
public:
	Timer();
	~Timer();
	inline void reset(){
		m_time = 0;
	};

	inline time_type getDelta() const{
		return m_time;
	};

	void setPause(bool pause);
	bool getPause() const;
};
#endif