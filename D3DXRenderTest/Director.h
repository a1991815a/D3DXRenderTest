#ifndef __DIRECTOR__
#define __DIRECTOR__
#include "SingleInstance.h"
#include <vector>
#include "Scene.h"
#include "Application.h"
#include "LimitStateMachine.h"
#include "D3DXRenderEngine.h"

#define _director Director::getInstance()

class Director: public SingleInstance<Director>{
	DEFINE_PRIVATE_INSTANCE(Director);
	friend class Application;
private:
	Scene* m_scene;
	RenderEngine* render_engine;
	Application* m_app;
	void update();
public:
	bool init(HWND hwnd);

	void loop();

	void destroy();

	Vec2 getWindowSize() const;
	
	D3DXRenderEngine* getD3DXRenderEngine(){
		return (D3DXRenderEngine*)render_engine;
	}
public:
	void TransformScene(Scene* scene);
	Scene* getCurrentScene();
	void setRenderEngine(RenderEngine* render_endgine);
};
#endif