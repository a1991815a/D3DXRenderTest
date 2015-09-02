#include "TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::insertTexture(const GString& name, Texture2D* tex )
{
	m_textureList.insert(name, tex);
}

void TextureManager::deleteTexture( const GString& texture_name )
{
	m_textureList.erase(texture_name);
}

Texture2D* TextureManager::getTexture( const GString& texture_name )
{
	return m_textureList.at(texture_name);
}

Texture2D* TextureManager::loadTextureFromFile( const GString& file_name )
{
	Texture2D* tex = Texture2D::create(file_name);
	insertTexture(tex->getName(), tex);
	return tex;
}

Texture2D* TextureManager::loadTextureFromFile(const GString& key, const GString& file_name)
{
	Texture2D* tex = Texture2D::create(file_name);
	tex->setName(key);
	insertTexture(key, tex);
	return tex;
}

Texture2D* TextureManager::loadTextureFromFileNotIns(const GString& file_name)
{
	Texture2D* tex = Texture2D::create(file_name);
	return tex;
}
