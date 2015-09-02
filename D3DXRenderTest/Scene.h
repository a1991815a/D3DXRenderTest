#ifndef __SCENE__
#define __SCENE__
#include "Node.h"

class Scene: public Node{
private:
	
public:
	static Scene* create();

	virtual void visit() override;
};
#endif