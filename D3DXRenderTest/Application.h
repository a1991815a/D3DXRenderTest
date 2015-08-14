#ifndef __APPLICATION__
#define __APPLICATION__
#include "RenderEngine.h"

class Application{
public:
	Application():render_engine(nullptr) {}

	virtual void init() = 0;			//初始化
	virtual int run() = 0;				//运行
	virtual void destroy() = 0;			//销毁

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
	//初始化
	void _init() {
		this->init();
		render_engine->init();
	};					

	//销毁
	void _destroy() { 
		render_engine->destroy();
		this->destroy();
	};			

private:
	RenderEngine* render_engine;
};
#endif