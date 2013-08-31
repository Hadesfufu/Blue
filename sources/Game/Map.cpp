#include "Game/Map.h"
#include "System/Rapidxml.h"
#include "Physics/Physics.h"
#include "Game/Position.h"
#include "Graphics/Render.h"
#include "Graphics/TextureHolder.h"
#include <fstream>

CMap::CMap()
: mTileSize(70.f)
{

}

void CMap::loadMap(const std::string& filename)
{
	std::ifstream file(filename.c_str());

	if(!file) return;

	mXMLFile = filename;

	std::string xmlContents;

	std::string line;
	while(std::getline(file, line))
		xmlContents += line;

    std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
    xmlData.push_back('\0');

    rapidxml::xml_document<> document;
    document.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

    rapidxml::xml_node<>* root = document.first_node();

	rapidxml::xml_node<>* tile = root->first_node("Tile");

	while(tile)
	{
		std::string texturePath = tile->first_attribute("texture")->value();
		int x					= std::atoi(tile->first_attribute("x")->value());
		int y					= std::atoi(tile->first_attribute("y")->value());

		tObjectID tileid = CGameObjectManager::instance()->createObject();
		CSystemManager::instance()->getSystem<CPositionSystem>()->setComponent(tileid, sf::Vector2f((float)x * mTileSize, (float)y * mTileSize));
		CSystemManager::instance()->getSystem<CRenderSystem>()->setComponent(tileid, sf::Sprite(*CTextureHolder::getTexture(texturePath)));
		CSystemManager::instance()->getSystem<CPhysicsSystem>()->setComponent(tileid, SPhysicsBody(sf::FloatRect((float)x * mTileSize, (float)y * mTileSize, mTileSize, mTileSize)));

		mTilesIDs.emplace(std::pair<int,int>(x, y), tileid);
		tile = tile->next_sibling("Tile");
	}
}

void CMap::editMap(sf::RenderWindow& window)
{

	bool PathEntered = false;
	bool isEditing = true;
	std::string TexturePathEditor;
	sf::Event event;

	while(isEditing)
	{
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				isEditing = false;
			if(!PathEntered)
			{
				std::cout << "Please enter the tile's name: ";
				std::cin >> TexturePathEditor;
				TexturePathEditor.insert(0,"Data/Tiles/");
				TexturePathEditor += ".png";
				PathEntered = true;
			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && PathEntered && TexturePathEditor != "Data/Tiles/Erase.png")
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				std::pair<int, int> tileMapPos(mousePos.x / (int)mTileSize, mousePos.y / (int)mTileSize);

				tObjectID tileid;
				auto it = mTilesIDs.find(tileMapPos);

				if(it != mTilesIDs.end())
				{
					tileid = it->second; // If the tile already exists, get the id.
				}
				else
				{
					tileid = CGameObjectManager::instance()->createObject(); // If it doesn't create it.
					sf::Vector2f tilePos((float)tileMapPos.first * mTileSize, (float)tileMapPos.second * mTileSize);
					CSystemManager::instance()->getSystem<CPositionSystem>()->setComponent(tileid, tilePos);

					mTilesIDs.emplace(tileMapPos, tileid);
				}
				CSystemManager::instance()->getSystem<CRenderSystem>()->setComponent(tileid, sf::Sprite(*CTextureHolder::getTexture(TexturePathEditor)));
				writeTile(TexturePathEditor, tileMapPos.first, tileMapPos.second);
				window.clear(sf::Color(208,244,247));
				CSystemManager::instance()->getSystem<CRenderSystem>()->onDraw(window);
				window.display();
			}
			else if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && PathEntered && TexturePathEditor == "Data/Tiles/Erase.png")
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				std::pair<int, int> tileMapPos(mousePos.x / (int)mTileSize, mousePos.y / (int)mTileSize);

				tObjectID tileid;
				auto it = mTilesIDs.find(tileMapPos);

				if(it != mTilesIDs.end())
				{
					tileid = it->second; // If the tile already exists, get the id.
					CSystemManager::instance()->getSystem<CRenderSystem>()->removeComponent(tileid);
					mTilesIDs.erase(it);
					writeTile(TexturePathEditor, tileMapPos.first, tileMapPos.second);
				}
				window.clear(sf::Color(208,244,247));
				CSystemManager::instance()->getSystem<CRenderSystem>()->onDraw(window);
				window.display();
			}
		}
		
	}
}

char* getUnsigned(unsigned int i, rapidxml::xml_document<>& doc)
{
	char buff[50];
	sprintf_s(buff,"%i",i);
	return doc.allocate_string(buff);
	 
}

void CMap::writeTile(const std::string& texturepath, int tileX, int tileY)
{
	std::ifstream file(mXMLFile.c_str());

	if(!file) return;

	std::string xmlContents;

	std::string line;
	while(std::getline(file, line))
		xmlContents += line;

    std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
    xmlData.push_back('\0');

    rapidxml::xml_document<> document;
    document.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

    rapidxml::xml_node<>* root = document.first_node();

	rapidxml::xml_node<>* tile = root->first_node("Tile");

	rapidxml::xml_attribute<>* Buff;

	while(tile)
	{
		std::string texturePath = tile->first_attribute("texture")->value();
		int x					= std::atoi(tile->first_attribute("x")->value());
		int y					= std::atoi(tile->first_attribute("y")->value());

		if(tileX == x && tileY == y) 
		{
			if (texturepath != "Data/Tiles/Erase.png")
			{

			Buff = tile->first_attribute("texture");
			Buff->value(document.allocate_string(texturepath.c_str()));
			Buff = tile->first_attribute("x");
			Buff->value(getUnsigned(x, document));
			Buff = tile->first_attribute("y");
			Buff->value(getUnsigned(y, document));
			}
			else
			{
				root->remove_node(tile);
			}
			std::ofstream wfile;
			wfile.open(mXMLFile.c_str(), std::ofstream::trunc, std::ofstream::_Nocreate);
			if(!wfile) return;
			wfile << document;
			wfile.close();
			
			return;
		}
		tile = tile->next_sibling("Tile");
	}

	tile = document.allocate_node(rapidxml::node_element,"Tile");
	tile->append_attribute(document.allocate_attribute("texture", document.allocate_string(texturepath.c_str())));
	tile->append_attribute(document.allocate_attribute("x", getUnsigned(tileX, document)));
	tile->append_attribute(document.allocate_attribute("y", getUnsigned(tileY, document)));
	root->append_node(tile);

	std::ofstream wfile;
	wfile.open(mXMLFile.c_str(), std::ofstream::trunc, std::ofstream::_Nocreate);
    if(!wfile) return;
	wfile << document;
    wfile.close();
	document.clear();

	loadMap(mXMLFile);
}


