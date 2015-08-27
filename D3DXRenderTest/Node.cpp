#include "Node.h"
#include "Win32Utils.h"
#include "gbRect.h"

void Node::pushQuadCommand()
{
	if(!m_visiable || !m_enable)
		return;
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

void Node::debug()
{
	gbRect* rect = nullptr;
	gbAlloc(rect);
	this->m_debugRect = rect;
	rect->setPosition(getPosition());
	rect->gbSetSize(getContentSize());
	this->addChild(rect);
}

void Node::setScaleToScreen(float x, float y)
{
	float scale_x = x * Win32Utils::getInstance()->getWidth() / m_contentSize.x;
	float scale_y = y * Win32Utils::getInstance()->getHeight() / m_contentSize.y;
	setScaleX(scale_x);
	setScaleY(scale_y);
}

void Node::setScaleToScreenX(float x)
{
	float scale_x = x * Win32Utils::getInstance()->getWidth() / m_contentSize.x;
	setScaleX(scale_x);
}

void Node::setScaleToScreenY(float y)
{
	float scale_y = y * Win32Utils::getInstance()->getHeight() / m_contentSize.y;
	setScaleY(scale_y);
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

void Node::setTransfromMatrix(const D3DXMATRIX& matrix)
{
	this->mMatrix = matrix;
}
