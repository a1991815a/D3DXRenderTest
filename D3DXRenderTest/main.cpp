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
#include "gbSolidRect.h"
#include "gbCircle.h"
#include "AppdeleGate.h"
#include "MemoryPool/gbMemoryPool.h"
#include "MemoryPoolManager.h"
#include "Ref.h"
#include "Director.h"

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

int WINAPI WinMain(
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, 
	_In_ int nShowCmd)
{
	MemoryChunkPoolInit;
	Application* application = new GameApplication();
	application->pushInnerLoop(MessageManager::getInstance());
	application->pushInnerLoop(Director::getInstance());
	application->pushInnerLoop(MemoryPoolManager::getInstance());
	application->pushExternLoop(TimerManager::getInstance());

	application->setRenderEngine(new D3DXRenderEngine());
	AppdeleGate::getInstance()->setCurrentApp(application);
	AppdeleGate::getInstance()->init();

	gbAlloc(line);
	
//	new(a)();
	/*line = new gbLine();*/
/*	gb_pa = new gbPointArray(5);*/
	Ref* r = nullptr;
	gbAlloc(r);
	r->autorelease();
	gbConstruct(gb_pa, gbPointArray, 5);

	gbAlloc(gb_rect);
	line->setPositionX(50);
	line->setPositionY(50);
	line->setToPositionX(120);
	line->setToPositionY(250);
	gb_rect->setPosition(Vec2(100, 100));
	gb_rect->setSizeWidth(200);
	gb_rect->setSizeHeight(150);
	gb_rect->setSolid(D3DFILL_SOLID);
	gb_pa->setPosition(0, Vec2(50, 50));
	gb_pa->setPSize(0, 50);

	gbAlloc(circle);
	circle->setPosition(Vec2(300, 300));
	circle->setRadian(60);
	circle->setSolid(D3DFILL_SOLID);


	D3DXMatrixIdentity(&mMatrix);
//	D3DXMatrixTranslation(&mMatrix, 50, 150, 0);
	
	KeyListener* listener = nullptr;
	gbAlloc(listener);
	listener->OnKeyDown = [](Event* e) -> bool{
		switch(e->getKey()){
		case 'A':
			--xx;
			/*line->setPositionX(line->getPosition().x - 1.0f);*/
			break;
		case 'D':
			++xx;
			/*line->setPositionX(line->getPosition().x + 1.0f);*/
			break;
		case 'W':
			++yy;
			/*line->setPositionY(line->getPosition().y + 1.0f);*/
			break;
		case 'S':
			--yy;
			/*line->setPositionY(line->getPosition().y - 1.0f);*/
			break;
		default:
			break;
		}
		D3DXMatrixTranslation(&mMatrix, xx, yy, 0);
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

	dxLinkProgram(nullptr);
	setTransformMatrix(nullptr);
	gb_pa->assemble();
	gb_pa->draw();

	dxLinkProgram(nullptr);
	setTransformMatrix(&mMatrix);
	circle->assemble();
	circle->draw();
}