#include "Node.h"

void Node::pushQuadCommand()
{
	Vector<Node*>& list = getChilds();
	auto itor = list.begin();
	for (; itor != list.end(); ++itor)
	{
		Node* node = *itor;
		if(node->getLocal() < 0)
			node->pushQuadCommand();
	}
	dxPushQuadCommand(this);
	itor = list.begin();
	for (; itor != list.end(); ++itor)
	{
		Node* node = *itor;
		if(node->getLocal() >= 0)
			node->pushQuadCommand();
	}
}

void Node::update()
{
	//如果无需更新矩阵
	if (!m_updateFlag)
	{
		auto itor = m_childs.begin();
		for (; itor != m_childs.end(); ++itor)
			(*itor)->update();
		return;
	}
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&mMatrix);
	D3DXMatrixRotationX(&matrix, m_rotate.x / 180.0f * D3DX_PI);
	mMatrix = mMatrix * matrix;
	D3DXMatrixRotationY(&matrix, m_rotate.y / 180.0f * D3DX_PI);
	mMatrix = mMatrix * matrix;
	D3DXMatrixRotationZ(&matrix, m_rotate.z / 180.0f * D3DX_PI);
	mMatrix = mMatrix * matrix;
	D3DXMatrixScaling(&matrix, m_scale.x, m_scale.y, 1);
	mMatrix = mMatrix * matrix;
	D3DXMatrixTranslation(&matrix, m_position.x, m_position.y, 0);
	mMatrix = mMatrix * matrix;
	if (m_parent)
		mMatrix = mMatrix * m_parent->mMatrix;
	setUpdate(false);
	auto itor = m_childs.begin();
	for (; itor != m_childs.end(); ++itor)
	{
		(*itor)->setUpdate(true);
		(*itor)->update();
	}
}
