#include <windows.h>
#include "AppdeleGate.h"
#include "GameApplication.h"
#include "D3DXRenderEngine.h"
#include "Vec.h"
#include "D3DXVertex.h"
#include "gbLine.h"
#include "D3DXProgram.h"
#include "gbPoint.h"
#include "gbRect.h"
#include "TimerManager.h"
#include "MessageManager.h"
#include "KeyListener.h"


gbLine* line = nullptr;
gbPointArray* gb_pa = nullptr;
gbRect* gb_rect = nullptr;
D3DXProgram program;

ID3DXConstantTable* vTable = nullptr;
ID3DXConstantTable* fTable = nullptr;

D3DXMATRIX mMatrix;

Vertex pp[2] = {
	Vertex(50, 50, 0.0f),
	Vertex(120, 250, 0.0f)
};

Vertex_Point ppp[5] = {
	Vertex_Point(Vec3(100, 100, 0), Color4f(), Vec3(), 50.0f),
	Vertex_Point(Vec3(100, 200, 0), Color4f(), Vec3(), 50.0f),
	Vertex_Point(Vec3(100, 300, 0), Color4f(), Vec3(), 50.0f),
	Vertex_Point(Vec3(100, 400, 0), Color4f(), Vec3(), 50.0f),
	Vertex_Point(Vec3(100, 500, 0), Color4f(), Vec3(), 50.0f),
};

Vertex re[6] = {
	Vertex(50, 50, 0),
	Vertex(250, 50, 0),
	Vertex(250, 250, 0),
	Vertex(50, 250, 0),
	Vertex(50, 50, 0)
};

int WINAPI WinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, 
	_In_ int nShowCmd)
{
	Application* application = new GameApplication();
	application->pushInnerLoop(MessageManager::getInstance());
	application->pushExternLoop(TimerManager::getInstance());


	application->setRenderEngine(new D3DXRenderEngine());
	AppdeleGate::getInstance()->setCurrentApp(application);
	AppdeleGate::getInstance()->init();

	line = new gbLine();
	gb_pa = new gbPointArray(5);
	gb_rect = new gbRect();
	line->setData(pp, 0, 2);
	gb_pa->setData(ppp, 0, 5);
	gb_rect->setData(re, 0, 5);

	D3DXMatrixTranslation(&mMatrix, 50, 150, 0);
	
	KeyListener* listener = new KeyListener();
	listener->OnKeyDown = [](Event* e) {
		OutputDebugStringA("°´ÏÂ°´¼ü \n");
		return true;
	};
	_dispatchMessage->addEventListener(listener);



	AppdeleGate::getInstance()->getCurrentApp()->run();
	return 0;
}



void GameDraw(IDirect3DDevice9* device, ID3DXSprite* sprite) {
	dxLinkProgram(nullptr);
	setTransformMatrix(&mMatrix);
	
	line->assemble();
	line->draw();


	dxLinkProgram(nullptr);
	setTransformMatrix(nullptr);
	gb_rect->assemble();
	gb_rect->draw();

// 	dxLinkProgram(nullptr);
// 	setTransformMatrix(nullptr);
// 	gb_pa->assemble();
// 	gb_pa->draw();
// 	gb_pa->setPSize(1, gb_pa->getPSize(1) - 0.1f);
}