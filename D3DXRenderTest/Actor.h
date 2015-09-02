#ifndef __ACTOR__
#define __ACTOR__
#include "Sprite.h"
#include "LimitStateMachine.h"
#include "Animate.h"

#define DIRECTION_LEFT		0x0010
#define DIRECTION_RIGHT		0x0011

#define ATTACK_LEFT			0x0020
#define ATTACK_RIGHT		0x0021


class Actor: public Node, public LimitStateMachine{
public:
	Actor();
	virtual void visit() override;

	void Run(long direction, void* data = nullptr);
	void Attack(long direction, void* data = nullptr);


private:
	Sprite* m_body;
	Animate* m_runAnimate;
	Animate* m_attackAnimate;
};
#endif