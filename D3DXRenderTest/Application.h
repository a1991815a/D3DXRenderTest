#ifndef __APPLICATION__
#define __APPLICATION__
#include "RenderEngine.h"
#include "GameStep.h"
#include <vector>

class Application: public GameStep{
private:
	std::vector<GameStep*> m_gameStepList;
public:
	Application():render_engine(nullptr) {}
	
	inline void run(){
		this->loop();
	}

	virtual bool init() override;

	virtual void loop() override;

	virtual void destroy() override;

	inline void setRenderEngine(RenderEngine* render_engine) { 
		this->render_engine = render_engine; 
	};

	inline RenderEngine* getRenderEngine(){ 
		return render_engine; 
	};

	inline const RenderEngine* getRenderEngine() const { 
		return render_engine; 
	};

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
};
#endif