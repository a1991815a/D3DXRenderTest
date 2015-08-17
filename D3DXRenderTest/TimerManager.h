#ifndef __TIMERMANAGER__
#define __TIMERMANAGER__
#include "SingleInstance.h"
#include "Timer.h"
#include "GameStep.h"
#include <unordered_set>

#define _timerManager TimerManager::getInstance()

class TimerManager: public SingleInstance<TimerManager>, public GameStep{
	DEFINE_PRIVATE_INSTANCE(TimerManager);
private:
	std::unordered_set<Timer*> m_timerList;				//计时器列表
	time_type m_startTime;								//计时管理器启动时间
	time_type m_preTime;								//上一次记录时间
	time_type m_curTime;								//当前时间
public:
	void push(Timer* _timer);
	void pop(Timer* _timer);

	virtual bool init() override;

	virtual void loop() override;

	virtual void destroy() override;


};
#endif