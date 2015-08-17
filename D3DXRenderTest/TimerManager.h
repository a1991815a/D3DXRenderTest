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
	std::unordered_set<Timer*> m_timerList;				//��ʱ���б�
	time_type m_startTime;								//��ʱ����������ʱ��
	time_type m_preTime;								//��һ�μ�¼ʱ��
	time_type m_curTime;								//��ǰʱ��
public:
	void push(Timer* _timer);
	void pop(Timer* _timer);

	virtual bool init() override;

	virtual void loop() override;

	virtual void destroy() override;


};
#endif