#include "TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::insertTexture(const std::string& name, Texture2D* tex )
{
	m_textureList.insert(name, tex);
}

void TextureManager::deleteTexture( const std::string& texture_name )
{
	m_textureList.erase(texture_name);
}

Texture2D* TextureManager::getTexture( const std::string& texture_name )
{
	return m_textureList.at(texture_name);
}

Texture2D* TextureManager::loadTextureFromFile( const std::string& file_name )
{
	Texture2D* tex = Texture2D::create(file_name);
	insertTexture(tex->getName(), tex);
	return tex;
}
