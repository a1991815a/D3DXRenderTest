#include "GButton.h"
#include "MemoryPool\gbMemoryPool.h"
#include "MessageManager.h"
#include "CoordUtils.h"
#include "SpriteFrameManager.h"

GButton::GButton()
	:onHit(nullptr), onMoveIn(nullptr), pointThis(false)
{
	listener = nullptr;
	gbAlloc(listener);
	listener->OnMouseDown = [this](Event* e) ->bool {
		const Vec2& location = e->getLocation();
		if(HitTest(location))
		{
			OutputDebugStringA("Hit GButton! \n");
			return true;
		}
		return false;
	};
	listener->OnMouseMove = [this](Event* e) ->bool {
		const Vec2& location = e->getLocation();
		bool isHit = HitTest(location);
		if(pointThis && !isHit){
			setScaleX(getScale().x - 0.2f);
			setScaleY(getScale().y - 0.2f);
			pointThis = false;
		}else if(!pointThis && isHit){
			setScaleX(getScale().x + 0.2f);
			setScaleY(getScale().y + 0.2f);
			pointThis = true;
		}
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
//	ret->autorelease();
	ret->image = SpriteFrame::create(image_path);
	ret->setContentSize(ret->image->getSize());
	ret->image->initColorRect();
	
	

	return ret;
}

GButton* GButton::createFromSpriteFrame(const GString& _frame)
{
	GButton* ret = nullptr;
	gbAlloc(ret);
	ret->image = SpriteFrameManager::getInstance()->getSpriteFrame(_frame);
	ret->setContentSize(ret->image->getSize());
	ret->image->initColorRect();

	return ret;
}

void GButton::visit()
{
	image->setProgram(getProgram());
	image->setAnchontPoint(&getAnchontPoint());
	image->setMatrix(getTransformMatrix());
	image->visit();
}

bool GButton::HitTest(const Vec2& point) const
{
	Vec2 location = WorldToNode(this, point);

	Color4f color = image->getColor(location);
	if (color.a == 0)
	 return false;
	
	return true;
}
