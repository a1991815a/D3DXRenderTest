#ifndef __SCENE__
#define __SCENE__
#include "Node.h"

class Scene: public Node{
private:
	
public:
	CREATE_FUNC(Scene);
	bool init();

	virtual void visit() override;
};
#endif