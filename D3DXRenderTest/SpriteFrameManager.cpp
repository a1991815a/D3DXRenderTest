#include "SpriteFrameManager.h"
#include "TextureManager.h"

SpriteFrameManager::SpriteFrameManager()
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
