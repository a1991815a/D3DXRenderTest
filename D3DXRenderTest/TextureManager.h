#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__
#include "SingleInstance.h"
#include "Map.h"
#include "UtilsHeader.h"
#include "Texture2D.h"

#define _textureManager TextureManager::getInstance()

class TextureManager: public SingleInstance<TextureManager>{
	DEFINE_PRIVATE_INSTANCE(TextureManager);
private:
	Map<GString, Texture2D*> m_textureList;
public:
	void insertTexture(const GString& name, Texture2D* tex);
	void deleteTexture(const GString& texture_name);
	Texture2D* getTexture(const GString& texture_name);
	Texture2D* loadTextureFromFile(const GString& file_name);

};
#endif