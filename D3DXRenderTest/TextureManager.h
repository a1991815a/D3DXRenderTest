#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__
#include "SingleInstance.h"
#include "Map.h"
#include <string>
#include "Texture2D.h"

#define _textureManager TextureManager::getInstance()

class TextureManager: public SingleInstance<TextureManager>{
	DEFINE_PRIVATE_INSTANCE(TextureManager);
private:
	Map<std::string, Texture2D*> m_textureList;
public:
	void insertTexture(const std::string& name, Texture2D* tex);
	void deleteTexture(const std::string& texture_name);
	Texture2D* getTexture(const std::string& texture_name);
	Texture2D* loadTextureFromFile(const std::string& file_name);

};
#endif