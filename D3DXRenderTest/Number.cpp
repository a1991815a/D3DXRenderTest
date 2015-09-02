#include "Number.h"
#include "SpriteFrameManager.h"

Number* Number::create(NumTypes type, bool isLv)
{
	Number* ret = nullptr;
	gbAlloc(ret);
	ret->autorelease();
	ret->m_type = type;
	ret->m_isLv = isLv;
	Vector<SpriteFrame*>& vv = ret->m_frame;
	for (int i = 0; i <= 9; ++i)
		vv.push_back(ret->getNumFrame(i));
	if(isLv)
		vv.push_back(ret->getNumFrame(10));

	return ret;
}

void Number::setValue(int val)
{
	m_num = val;
	GString text = m_num;
	Vec2 cts = m_frame.front()->getSize();
	if(!m_isLv)
		cts.x = text.size() * (cts.x);
	else
		cts.x = (text.size() + 1) * (cts.x);
	setContentSize(cts);
}

SpriteFrame* Number::getNumFrame(int num)
{
	SpriteFrameManager* sfm = SpriteFrameManager::getInstance();
	GString key_1 = "image";
	GString key_2 = "number";
	GString key_3;
	GString key_4;
	switch (m_type)
	{
	case Number::WHITE:
		key_3 = "white";
		break;
	case Number::BLUE:
		key_3 = "blue";
		break;
	case Number::GREEN:
		key_3 = "green";
		break;
	case Number::YELLOW:
		key_3 = "yellow";
		break;
	case Number::WHITE_SM:
		key_3 = "white_sm";
		break;
	case Number::YELLOW_SM:
		key_3 = "yellow_sm";
		break;
	case Number::BLUE_SM:
		key_3 = "blue_sm";
		break;
	case Number::WHITE_LG:
		key_3 = "white_lg";
		break;
	case Number::RED_VLG:
		key_3 = "red_vlg";
		break;
	case Number::RED:
		key_3 = "red";
		break;
	default:
		break;
	}
	if(num != 10)
		key_4 += num;
	else
		key_4 += "lv";
	return sfm->getFrameByVMap(
		key_1.c_str(), key_2.c_str(), 
		key_3.c_str(), key_4.c_str(),
		sfm->endTag());
}

void Number::visit()
{
	GString display_text = "";
	if(m_isLv)
		display_text += 'a';
	display_text += m_num;
	float width = 0;
	
	for (int i = 0; i < display_text.size(); ++i)
	{
		GString gs = display_text.at(i);
		if(gs == "a")
			gs = "10";
		D3DXMATRIX transfromMatrix = *getTransformMatrix();
		D3DXMATRIX matrix;
		D3DXMatrixTranslation(&matrix, width, 0, 0);
		
		SpriteFrame* sf = m_frame.at(gs.toInt());
		sf->setProgram(getProgram());
		sf->setAnchontPoint(&getAnchontPoint());
		sf->setContentSize(&getContentSize());
		transfromMatrix = transfromMatrix * matrix;
		sf->setMatrix(&transfromMatrix);
		sf->visit();
		width += sf->getSize().x * 1.4;
	}

}
