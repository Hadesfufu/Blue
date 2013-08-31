#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class CTextureHolder : public sf::NonCopyable
{
public:
	~CTextureHolder();
	static sf::Texture* getTexture(const std::string& asName);
private:
	static std::map<std::string, sf::Texture*> m_mapTextures;
};

#endif