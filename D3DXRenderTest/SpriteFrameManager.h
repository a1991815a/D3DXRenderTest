#ifndef __SPRITEFRAMEMANAGER__
#define __SPRITEFRAMEMANAGER__
#include "Map.h"
#include <string>
#include "SpriteFrame.h"
#include "SingleInstance.h"

class SpriteFrameManager: public SingleInstance<SpriteFrameManager>{
	DEFINE_PRIVATE_INSTANCE(SpriteFrameManager);
private:
	Map<std::string, SpriteFrame*> m_frameList;
public:
	void insertSpriteFrame(const std::string& name, SpriteFrame* tex);
	void deleteSpriteFrame(const std::string& texture_name);
	SpriteFrame* getSpriteFrame(const std::string& texture_name);
	SpriteFrame* loadSpriteFrameFromFile(const std::string& file_name);
};
#endif