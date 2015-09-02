#include "GButton.h"
#include "MemoryPool\gbMemoryPool.h"
#include "MessageManager.h"
#include "CoordUtils.h"
#include "SpriteFrameManager.h"
#include "Director.h"

GButton::GButton()
	:onHit(nullptr), onMoveIn(nullptr), pointThis(false)
{
	listener = nullptr;
	gbAlloc(listener);
	listener->OnMouseDown = [this](Event* e) ->bool {
		const Vec2& location = e->getLocation();
		if(this->isEnable() && this->isVisiable() && HitTest(location))
		{
			if (onHit)
				onHit(e);
			return true;
		}
		return false;
	};
	listener->OnMouseMove = [this](Event* e) ->bool {
		const Vec2& location = e->getLocation();
		bool isHit = HitTest(location);
// 		if (this->isEnable() && this->isVisiable() && pointThis && !isHit) {
// 			setScaleX(getScale().x - 0.2f);
// 			setScaleY(getScale().y - 0.2f);
// 			if (this->onMoveIn)
// 				onMoveIn(e);
// 			pointThis = false;
// 		}
// 		else if (this->isEnable() && this->isVisiable() && !pointThis && isHit) {
// 			setScaleX(getScale().x + 0.2f);
// 			setScaleY(getScale().y + 0.2f);
// 			pointThis = true;
// 		}
		return false;
	};
	_dispatchMessage->addEventListener(listener);
}

GButton::~GButton()
{
	_dispatchMessage->removeEventListener(listener);
	if (listener)
		gbDealloc(listener);
}

GButton* GButton::create(const GString& image_path)
{
	GButton* ret = nullptr;
	gbAlloc(ret);
	ret->autorelease();
	ret->image = SpriteFrame::create(image_path);
	ret->setContentSize(ret->image->getSize());
	ret->image->initColorRect();
	
	

	return ret;
}

GButton* GButton::createFromSpriteFrame(const GString& _frame)
{
	GButton* ret = nullptr;
	gbAlloc(ret);
	ret->autorelease();
	ret->image = SpriteFrameManager::getInstance()->getSpriteFrame(_frame);
	ret->setContentSize(ret->image->getSize());
	ret->image->initColorRect();

	return ret;
}

GButton* GButton::createByKey(const char* key)
{
	SpriteFrameManager* sfm = SpriteFrameManager::getInstance();
	GButton* ret = nullptr;
	gbAlloc(ret);
	ret->autorelease();
	ret->image = sfm->getFrameByVMap("image", "button", key, sfm->endTag());
	ret->setContentSize(ret->image->getSize());
	ret->image->initColorRect();
	return ret;
}

void GButton::visit()
{
	image->setProgram(getProgram());
	image->setAnchontPoint(&getAnchontPoint());
	image->setContentSize(&getContentSize());
	image->setMatrix(getTransformMatrix());
	image->visit();
}

bool GButton::HitTest(const Vec2& point) const
{
	Vec2 location = WorldToNode(this, point);

	const Vec2& contentSize = getContentSize();

	location.x += getAnchontPoint().x * contentSize.x;
	location.y += getAnchontPoint().y * contentSize.y;

// 	location.x += getPosition().x / _director->getWindowSize().x * 15;
// 	location.y += getPosition().y / _director->getWindowSize().y * 30;
// 	GString text = "X: ";
// 	text += location.x;
// 	text += "  Y:";
// 	text += location.y;
// 	text += " \n";
// 	OutputDebugStringA(text.c_str());

	Color4f color = image->getColor(location);
	if (color.a == 0)
	 return false;
	
	return true;
}

Value GButton::serialization()
{
	Value val = Node::serialization();
	ValueMap& vm = val.asVMap();
	

}
