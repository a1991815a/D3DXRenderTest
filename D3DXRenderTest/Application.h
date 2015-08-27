#ifndef __APPLICATION__
#define __APPLICATION__
#include "RenderEngine.h"
#include "GameStep.h"
#include <vector>
#include "Timer.h"
#include "Vec.h"
#include "UtilsHeader.h"

class Application{
public:
	Application()
	{}

	int run();

	bool init();

	void destroy();
	
	const Vec2& getWindowSize() const{
		return m_wndSize;
	}
	float getWindowWidth() const{
		return m_wndSize.x;
	}
	float getWindowHeight() const{
		return m_wndSize.y;
	}
	void setWindowSize(float width, float height){
		m_wndSize.x = width;
		m_wndSize.y = height;
	}
	const GString& getWindowName()const{
		return m_wndName;
	}
	void setWindowName(const GString& name){
		m_wndName = name;
	}
	void setResignSize(const GString& name, float width, float height, size_t frame){
		m_wndName = name;
		m_wndSize.x = width;
		m_wndSize.y = height;
		m_frame = frame;
	}
private:
	friend class AppdeleGate;

private:
	Timer m_globalTimer;
	size_t m_frame;
	float m_delay;
	Vec2 m_wndSize;
	GString m_wndName;
};
#endif