#ifndef __APPLICATION__
#define __APPLICATION__
#include "RenderEngine.h"
#include "GameStep.h"
#include <vector>
#include "Timer.h"

class Application : public GameStep {
private:
	std::vector<GameStep*> m_gameInnerLoop;
	std::vector<GameStep*> m_gameExternLoop;
public:
	Application()
		:render_engine(nullptr)
	{}

	inline void run() {
		this->loop();
	}

	virtual bool init() override;

	virtual void loop() override;

	virtual void destroy() override;

	inline void setRenderEngine(RenderEngine* render_engine) {
		this->render_engine = render_engine;
	};

	inline RenderEngine* getRenderEngine() {
		return render_engine;
	};

	inline const RenderEngine* getRenderEngine() const {
		return render_engine;
	};

	inline void pushInnerLoop(GameStep* step) {
		m_gameInnerLoop.push_back(step);
	};

	inline void pushExternLoop(GameStep* step) {
		m_gameExternLoop.push_back(step);
	};

	inline void popGameStep() {
		m_gameInnerLoop.pop_back();
	}

private:
	friend class AppdeleGate;
	//³õÊ¼»¯
	void _init() {
		this->init();
		render_engine->init();
	};					

	//Ïú»Ù
	void _destroy() { 
		render_engine->destroy();
		this->destroy();
	};			

private:
	RenderEngine* render_engine;
	Timer m_globalTimer;
	float m_frame;
};
#endif