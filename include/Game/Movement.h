#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SFML/System/Vector2.hpp>
#include "System/System.h"

struct SMovable
{
	static const float MaxVelocity;

	SMovable(const sf::Vector2f& vel);

	void limitVelocity();

	sf::Vector2f velocity;
};

class CMovementSystem : public TComponentSystem<SMovable>
{
public:
	static tSystemID id;

	void scaleVelocity(tObjectID id, const sf::Vector2f& vel);
	void onUpdate(const sf::Time dt);
};

#endif