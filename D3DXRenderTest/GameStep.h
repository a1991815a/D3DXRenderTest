#ifndef __GAMESTEP__
#define __GAMESTEP__

class GameStep{
public:
	virtual bool init() = 0;					//��ʼ��
	virtual void loop() = 0;					//ѭ��
	virtual void destroy() = 0;					//����
};
#endif