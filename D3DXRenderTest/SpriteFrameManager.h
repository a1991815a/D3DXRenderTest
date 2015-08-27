#ifndef __SPRITEFRAMEMANAGER__
#define __SPRITEFRAMEMANAGER__
#include "Map.h"
#include "UtilsHeader.h"
#include "SpriteFrame.h"
#include "SingleInstance.h"

class SpriteFrameManager: public SingleInstance<SpriteFrameManager>{
	DEFINE_PRIVATE_INSTANCE(SpriteFrameManager);
private:
	Map<GString, SpriteFrame*> m_frameList;
public:
	void insertSpriteFrame(const GString& name, SpriteFrame* tex);
	void deleteSpriteFrame(const GString& texture_name);
	SpriteFrame* getSpriteFrame(const GString& texture_name);
	SpriteFrame* loadSpriteFrameFromFile(const GString& file_name);
};
#endif