#include "SpriteFrameManager.h"
#include "TextureManager.h"
#include "XmlParse\XmlParse.h"
#include <wchar.h>

SpriteFrameManager::SpriteFrameManager()
	:end_tag("The_End!")
{

}

SpriteFrameManager::~SpriteFrameManager()
{

}

void SpriteFrameManager::insertSpriteFrame( const GString& name, SpriteFrame* tex )
{
	m_frameList.insert(name, tex);
}

void SpriteFrameManager::deleteSpriteFrame( const GString& texture_name )
{
	m_frameList.erase(texture_name);
}

SpriteFrame* SpriteFrameManager::getSpriteFrame( const GString& texture_name )
{
	return m_frameList.at(texture_name);
}

SpriteFrame* SpriteFrameManager::loadSpriteFrameFromFile( const GString& file_name )
{
	Texture2D* tex = _textureManager->loadTextureFromFile(file_name);
	SpriteFrame* sf = SpriteFrame::create(tex);
	m_frameList.insert(file_name, sf);
	return sf;
}

SpriteFrame* SpriteFrameManager::loadSpriteFrameFromFile(const GString& key, const GString& file_name)
{
	Texture2D* tex = _textureManager->loadTextureFromFile(key, file_name);
	SpriteFrame* sf = SpriteFrame::create(tex);
	m_frameList.insert(key, sf);
	return sf;
}

void SpriteFrameManager::loadSpriteFrameByXml(const GString& xml)
{
	struct Node{
		GString key;
		Value* val;
	};

	Value val = XmlParse::getInstance()->parseFromFile(xml.c_str());
	Node node;
	node.val = &val;
	std::vector<Node> stack_val;
	stack_val.push_back(node);
	GString key;
	while(!stack_val.empty()){
		Node node = stack_val.back();
		stack_val.pop_back();
		switch(node.val->getType()){
		case Value::VMAP:
		{
			auto itor = node.val->asVMap().begin();
			for(; itor != node.val->asVMap().end(); ++itor)
			{
				Node node;
				node.key = itor->first;
				node.val = &itor->second;
				stack_val.push_back(node);
			}
		}
			break;
		case Value::VVECTOR:
		{
			auto itor = node.val->asVVector().begin();
			for (; itor != node.val->asVVector().end(); ++itor)
			{
				Node node;
				node.val = &(*itor);
				stack_val.push_back(node);
			}
		}
			break;
		case Value::STRING:
		{
			SpriteFrame* sf = loadSpriteFrameNotIns(node.val->asString());
			sf->setKey(node.key);
			sf->retain();
			*node.val = sf;
		}
			break;
		}
	}

	auto itor = val.asVMap().begin();

	m_frameVMap[itor->first] = std::move(itor->second);
}

SpriteFrame* SpriteFrameManager::loadSpriteFrameNotIns(const GString& file)
{
	Texture2D* tex = _textureManager->loadTextureFromFileNotIns(file);
	SpriteFrame* sf = SpriteFrame::create(tex);
	return sf;
}

SpriteFrame* SpriteFrameManager::getFrameByVMap(const char* key_1, ...)
{
	SpriteFrame* sf = nullptr;
	va_list ap;
	va_start(ap, key_1);
	sf = getFrameByVMap(ap, key_1);
	va_end(ap);
	return sf;
}

SpriteFrame* SpriteFrameManager::getFrameByVMap(va_list ap, const char* key_1)
{
	SpriteFrame* sf = nullptr;
	GString key = key_1;
	Value* val = &m_frameVMap.at(key);
	
	for( key = va_arg(ap, const char*)
		;key != end_tag; 
		key = va_arg(ap,  const char*)){
			val = &val->asVMap().at(key);
	}
	sf = (SpriteFrame*)val->asData();
	return sf;
}
