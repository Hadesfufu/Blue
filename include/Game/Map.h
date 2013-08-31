#ifndef MAP_H
#define MAP_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Game/GameObject.h"
#include "System/SystemManager.h"

class CMap
{
public:
	CMap();
	void loadMap(const std::string& filename);
	void editMap(sf::RenderWindow& window);
	void writeTile(const std::string& texturepath, int tileX, int tileY);

private:
	std::map<std::pair<int, int>, tObjectID> mTilesIDs;
	float mTileSize;
	std::string mXMLFile;
};

#endif