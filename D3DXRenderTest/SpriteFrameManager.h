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
	std::unordered_map<GString, Value> m_frameVMap;
public:
	void insertSpriteFrame(const GString& name, SpriteFrame* tex);
	void deleteSpriteFrame(const GString& texture_name);
	SpriteFrame* getSpriteFrame(const GString& texture_name);
	SpriteFrame* loadSpriteFrameFromFile(const GString& file_name);

	SpriteFrame* loadSpriteFrameFromFile(const GString& key, const GString& file_name);
	void loadSpriteFrameByXml(const GString& xml);
	SpriteFrame* loadSpriteFrameNotIns(const GString& file);

	SpriteFrame* getFrameByVMap(const char* key_1, ...);
	SpriteFrame* getFrameByVMap(va_list ap, const char* key_1);

	inline const char* const endTag() const{
		return end_tag;
	};

private:
	const char* const end_tag;
};
#endif