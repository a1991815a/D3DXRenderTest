#include "SpriteFrameManager.h"
#include "TextureManager.h"

SpriteFrameManager::SpriteFrameManager()
{

}

SpriteFrameManager::~SpriteFrameManager()
{

}

void SpriteFrameManager::insertSpriteFrame( const std::string& name, SpriteFrame* tex )
{
	m_frameList.insert(name, tex);
}

void SpriteFrameManager::deleteSpriteFrame( const std::string& texture_name )
{
	m_frameList.erase(texture_name);
}

SpriteFrame* SpriteFrameManager::getSpriteFrame( const std::string& texture_name )
{
	return m_frameList.at(texture_name);
}

SpriteFrame* SpriteFrameManager::loadSpriteFrameFromFile( const std::string& file_name )
{
	Texture2D* tex = _textureManager->loadTextureFromFile(file_name);
	SpriteFrame* sf = SpriteFrame::create(tex);
	m_frameList.insert(file_name, sf);
	return sf;
}
