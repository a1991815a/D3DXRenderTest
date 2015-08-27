#include <windows.h>
#include "AppdeleGate.h"
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
#include "gbSolidRect.h"
#include "gbCircle.h"
#include "AppdeleGate.h"
#include "MemoryPool/gbMemoryPool.h"
#include "MemoryPoolManager.h"
#include "Ref.h"
#include "Director.h"
#include "Scene.h"
#include "Sprite.h"
#include "PathManager.h"
#include "SpriteFrame.h"

gbLine* line = nullptr;
gbPointArray* gb_pa = nullptr;
gbSolidRect* gb_rect = nullptr;
gbCircle* circle = nullptr;
D3DXProgram program;

ID3DXConstantTable* vTable = nullptr;
ID3DXConstantTable* fTable = nullptr;

float xx = 0; 
float yy = 0;

D3DXMATRIX mMatrix;

IDirect3DTexture9* texture = nullptr;

D3DXHANDLE texHandler = nullptr;
D3DXCONSTANT_DESC desc;

Sprite* sprite = nullptr;
Sprite* sprite_2 = nullptr;

int WINAPI WinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, 
	_In_ int nShowCmd)
{
	MemoryChunkPoolInit;
	_pathManager->init();
	Application* application = new Application();
	_director->setRenderEngine(new D3DXRenderEngine());
	AppdeleGate::getInstance()->setCurrentApp(application);
	AppdeleGate::getInstance()->init();

	


	return AppdeleGate::getInstance()->getCurrentApp()->run();
}



// void GameDraw(IDirect3DDevice9* device, ID3DXSprite* sprite) {
// 
// 	dxLinkProgram(nullptr);
// //	setTransformMatrix(&mMatrix);
// 	line->assemble();
// 	line->draw();
// 
// 
// 	dxLinkProgram(nullptr);
// 	setTransformMatrix(nullptr);
// 	gb_rect->assemble();
// 	gb_rect->draw();
// 
// 	dxLinkProgram(nullptr);
// 	setTransformMatrix(nullptr);
// 	gb_pa->assemble();
// 	gb_pa->draw();
// 
// 	dxLinkProgram(nullptr);
// //	setTransformMatrix(&mMatrix);
// 	circle->assemble();
// 	circle->draw();
// 	
// 	dxLinkProgram(nullptr);
// 	dxGetProgram()->SetBool(D3D_PIXEL_SHADER, "isSprite", true);
// 	RECT rect = {0, 0, 48, 48 };
// 	sprite->Draw(texture, &rect, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(xx, yy, 0), 0xFFFFFFFF);
// }

bool GameInit(HWND hWnd) {
	return _director->init(hWnd);
}