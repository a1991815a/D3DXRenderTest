#include "Scene.h"

Scene* Scene::create()
{
	Scene* ret = nullptr;
	gbAlloc(ret);
	ret->setEnable(false);
	return ret;
}

void Scene::visit()
{
	
	
}
// 
// void Scene::pushQuadCommand()
// {
// 	Vector<Node*>& list = getChilds();
// 	auto itor = list.begin();
// 	for (; itor != list.end(); ++itor)
// 	{
// 		Node* node = *itor;
// 		if(node->getGlobal() == 0)
// 		{
// 			dxPushQuadCommand(node);
// 		}else{
// 			node->pushQuadCommand();
// 		}
// 	}
// 
// }
