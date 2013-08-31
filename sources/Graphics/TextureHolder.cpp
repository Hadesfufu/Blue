#include "graphics/TextureHolder.h"

std::map<std::string, sf::Texture*> CTextureHolder::m_mapTextures;

CTextureHolder::~CTextureHolder()
{
	for(auto it = m_mapTextures.begin() ; it != m_mapTextures.end() ; ++it)
		delete it->second;

	m_mapTextures.clear();
}

sf::Texture* CTextureHolder::getTexture(const std::string& asName)
{
	if(m_mapTextures.find(asName) != m_mapTextures.end())
		return m_mapTextures[asName];

	sf::Texture* texture = new sf::Texture();

	if(texture->loadFromFile(asName))
	{
		m_mapTextures[asName] = texture;
		return m_mapTextures[asName];
	}
	else
	{
		delete texture;
		return nullptr;
	}
}