#ifndef __DIRECTOR__
#define __DIRECTOR__
#include "SingleInstance.h"
#include <vector>
#include "Scene.h"
#include "Application.h"

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

public:
	void TransformScene(Scene* scene);
	Scene* getCurrentScene();
	void setRenderEngine(RenderEngine* render_endgine);
};
#endif