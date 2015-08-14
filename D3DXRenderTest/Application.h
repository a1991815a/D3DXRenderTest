#ifndef __APPLICATION__
#define __APPLICATION__
#include "RenderEngine.h"

class Application{
public:
	Application():render_engine(nullptr) {}

	virtual void init() = 0;			//��ʼ��
	virtual int run() = 0;				//����
	virtual void destroy() = 0;			//����

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
	//��ʼ��
	void _init() {
		this->init();
		render_engine->init();
	};					

	//����
	void _destroy() { 
		render_engine->destroy();
		this->destroy();
	};			

private:
	RenderEngine* render_engine;
};
#endif