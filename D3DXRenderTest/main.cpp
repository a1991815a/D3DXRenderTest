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
	Application* application = new Application();

	_director->setRenderEngine(new D3DXRenderEngine());
	AppdeleGate::getInstance()->setCurrentApp(application);
	AppdeleGate::getInstance()->init();

	gbAlloc(line);
	
	
//	new(a)();
	/*line = new gbLine();*/
/*	gb_pa = new gbPointArray(5);*/
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
	
	

	D3DXIMAGE_INFO info;

	D3DXCreateTextureFromFileExA(
		dxGetDevice(),
		"../../assets/UnknownBrickOver.png",
		D3DX_FROM_FILE,
		D3DX_FROM_FILE,
		0,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x00000000,
		&info,
		nullptr,
		&texture
		);
	Texture2D* tex = Texture2D::create(texture, info.Width, info.Height);
	Scene* scene = Scene::create();
	sprite = Sprite::create();
	sprite_2 = Sprite::create();
	_director->TransformScene(scene);
	sprite->setFrame(tex);
	sprite_2->setFrame(tex);
	sprite->addChild(sprite_2);
	sprite->setTag(1);
	sprite_2->setTag(2);
	sprite_2->setPositionX(50);
	sprite_2->setPositionY(50);
	scene->addChild(sprite);
	

	UINT count = 0;
	texHandler = dxGetProgram()->getHandle("BaiscSampler", D3D_PIXEL_SHADER);
	dxGetProgram()->getTable(D3D_PIXEL_SHADER)->GetConstantDesc(
		texHandler, &desc, &count);


	KeyListener* listener = nullptr;
	gbAlloc(listener);
	listener->OnKeyDown = [](Event* e) -> bool {
		switch (e->getKey()) {
		case 'A':
			--xx;
			sprite->setPositionX(sprite->getPosition().x - 1);
			sprite_2->setPositionX(sprite_2->getPosition().x - 1);
			/*line->setPositionX(line->getPosition().x - 1.0f);*/
			break;
		case 'D':
			++xx;
			/*line->setPositionX(line->getPosition().x + 1.0f);*/
			sprite->setPositionX(sprite->getPosition().x + 1);
			sprite_2->setPositionX(sprite_2->getPosition().x + 1);
			break;
		case 'W':
			++yy;
			/*line->setPositionY(line->getPosition().y + 1.0f);*/
			sprite->setPositionY(sprite->getPosition().y + 1);
			break;
		case 'S':
			--yy;
			/*line->setPositionY(line->getPosition().y - 1.0f);*/
			sprite->setPositionY(sprite->getPosition().y - 1);
			break;
		default:
			break;
		}
		D3DXMatrixTranslation(&mMatrix, xx, yy, 0);
		return true;
	};
	_dispatchMessage->addEventListener(listener);

	return AppdeleGate::getInstance()->getCurrentApp()->run();
}



void GameDraw(IDirect3DDevice9* device, ID3DXSprite* sprite) {

	dxLinkProgram(nullptr);
//	setTransformMatrix(&mMatrix);
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
//	setTransformMatrix(&mMatrix);
	circle->assemble();
	circle->draw();
	
	dxLinkProgram(nullptr);
	dxGetProgram()->SetBool(D3D_PIXEL_SHADER, "isSprite", true);
	RECT rect = {0, 0, 48, 48 };
	sprite->Draw(texture, &rect, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(xx, yy, 0), 0xFFFFFFFF);
}

bool GameInit(HWND hWnd) {
	return _director->init(hWnd);
}