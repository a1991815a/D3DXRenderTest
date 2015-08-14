#ifndef __APPDELEGATE__
#define __APPDELEGATE__
#include "Application.h"

#define _appdeleGate AppdeleGate::getInstance()
#define _curAppcalition _appdeleGate->getCurrentApp()
#define _renderEngine _curAppcalition->getRenderEngine()

class AppdeleGate{
private:
	Application* m_app;
public:
	AppdeleGate();
	~AppdeleGate();
	void init();

	inline void setCurrentApp(Application* app){m_app = app;};
	inline Application* getCurrentApp() { return m_app; };

public:
	static AppdeleGate* getInstance();
	static void destroyInstance();
private:
	static AppdeleGate* m_instance;
};
#endif