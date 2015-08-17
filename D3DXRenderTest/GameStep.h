#ifndef __GAMESTEP__
#define __GAMESTEP__

class GameStep{
public:
	virtual bool init() = 0;					//初始化
	virtual void loop() = 0;					//循环
	virtual void destroy() = 0;					//销毁
};
#endif