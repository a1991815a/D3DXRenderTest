#include "Node.h"
#include "Win32Utils.h"
#include "gbRect.h"
#include "Action.h"
#include <stdarg.h>
#include "ActionManager.h"

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

void Node::debug(bool flag)
{
	if(flag && rect == nullptr)
	{
		gbAlloc(rect);
		rect->autorelease();
		this->m_debugRect = rect;
		resetDebugSize();
		resetDebugAp();
		this->addChild(rect);
	}else if(!flag && rect != nullptr){
		m_childs.erase(rect);
		rect = nullptr;
	}
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

void Node::setPositionToScreen(float x, float y)
{
	float pos_x = x * Win32Utils::getInstance()->getWidth();
	float pos_y = y * Win32Utils::getInstance()->getHeight();
	setPositionX(pos_x);
	setPositionY(pos_y);
}

void Node::setPositionToScreenX(float x)
{
	float pos_x = x * Win32Utils::getInstance()->getWidth();
	setPositionX(pos_x);
}

void Node::setPositionToScreenY(float y)
{
	float pos_y = y * Win32Utils::getInstance()->getHeight();
	setPositionY(pos_y);
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

	if (m_isClip)
	{
		D3DXMatrixIdentity(&matrix);
		matrix._11 = -1;
		mMatrix = mMatrix * matrix;
	}

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

void Node::resetDebugSize()
{
	if (m_debugRect)
		m_debugRect->gbSetSize(m_contentSize);
}

void Node::resetDebugAp()
{
	if (m_debugRect)
		m_debugRect->gbSetAnchontPoint(m_anchontPoint);
}

Value Node::serialization()
{
	Value val = ValueMap();
	ValueMap& vm = val.asVMap();
	vm["type"] = "node";
	vm["anchontPoint"] = m_anchontPoint.serialization();
	vm["position"] = m_position.serialization();
	vm["scale"] = m_scale.serialization();
	vm["rotate"] = m_scale.serialization();
	vm["contentSize"] = m_contentSize.serialization();
	vm["enable"] = Serialization::serialization(m_enable);
	vm["visiable"] = Serialization::serialization(m_visiable);
	vm["tag"] = GString(getTag());
	vm["name"] = getName();
	vm["local"] = GString(m_local);
	vm["global"] = GString(m_global);
	vm["isClip"] = Serialization::serialization(m_isClip);

	vm["child"] = ValueVector();
	ValueVector& vvector = vm.at("child").asVVector();
	auto itor = m_childs.begin();
	for (; itor != m_childs.end(); ++itor)
		vvector.push_back((*itor)->serialization().asVMap());
	return val;
}

void Node::runAction(Action* action_1, ...)
{
	ActionManager* action_manager = ActionManager::getInstance();
	va_list ap;
	va_start(ap, action_1);
	action_1->init(this);
	action_manager->pushAction(action_1);
	Action* action = nullptr;
	while ( (action = va_arg(ap, Action*)) != nullptr)
	{
		action->init(this);
		action_manager->pushAction(action);
	}
	va_end(ap);
}