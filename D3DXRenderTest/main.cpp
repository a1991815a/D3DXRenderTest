#include <windows.h>
#include "AppdeleGate.h"
#include "GameApplication.h"
#include "D3DXRenderEngine.h"
#include "Vec.h"
#include "D3DXVertex.h"
#include "gbLine.h"
#include "D3DXProgram.h"


gbLine* line = nullptr;
D3DXProgram program;

ID3DXConstantTable* vTable = nullptr;
ID3DXConstantTable* fTable = nullptr;

D3DXMATRIX mMatrix;

Vertex_pos pp[2] = {
	Vertex_pos(50, 50, 0.0f),
	Vertex_pos(120, 250, 0.0f)
};

int WINAPI WinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, 
	_In_ int nShowCmd)
{
	Application* application = new GameApplication();
	application->setRenderEngine(new D3DXRenderEngine());
	AppdeleGate::getInstance()->setCurrentApp(application);
	AppdeleGate::getInstance()->init();

	line = new gbLine();

	D3DXMatrixTranslation(&mMatrix, 50, 150, 0);

	return AppdeleGate::getInstance()->getCurrentApp()->run();
}



void GameDraw(IDirect3DDevice9* device, ID3DXSprite* sprite) {
	dxLinkProgram(nullptr);
	setTransformMatrix(nullptr);
	line->setData(pp, 0, 2);
	line->assemble();
	line->draw();
}