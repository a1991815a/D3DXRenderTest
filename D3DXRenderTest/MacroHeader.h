#ifndef __MACROHEADER__
#define __MACROHEADER__

//宏定义数据
#define WINNAME			"我的测试用窗口"
#define WND_WIDTH		800
#define WND_HEIGHT		600
#define DEFAULT_VSHADER "vShader.vshader"
#define DEFAULT_FSHADER "fShader.fshader"


/*
	宏定义操作
*/
#define SAFE_RELEASE_COM(com) do{if(com) com->Release(); com = nullptr;} while(0)
#define SAFE_DELETE(p) do{if(p) delete p; p = nullptr;} while(0)
#define SAFE_DELETE_ARRAY(p) do{if(p) delete[] p; p = nullptr;} while(0)




#endif