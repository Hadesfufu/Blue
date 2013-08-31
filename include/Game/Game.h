#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Map.h"

class CGame
{
public:
	CGame();

	void run();

private:
	void processEvents();
	void onUpdate(const sf::Time dt);
	void onDraw();

private:

	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;

	CMap mMap;
};

#endif