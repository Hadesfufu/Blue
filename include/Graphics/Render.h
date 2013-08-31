#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "System/System.h"

class CRenderSystem : public TComponentSystem<sf::Sprite>
{
public:
	static tSystemID id;

	sf::Sprite& getSprite(tObjectID id) const;

	void onUpdate(const sf::Time dt);
	void onDraw(sf::RenderWindow& window);
};

#endif