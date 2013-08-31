#ifndef POSITION_H
#define POSITION_H

#include <SFML/System/Vector2.hpp>
#include "System/System.h"

class CPositionSystem : public TComponentSystem<sf::Vector2f>
{
public:
	static tSystemID id;

	sf::Vector2f& getPosition(tObjectID id) const;

	void onUpdate(const sf::Time dt);
};

#endif