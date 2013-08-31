#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include "System/System.h"

struct SPhysicsBody
{
	SPhysicsBody(const sf::FloatRect& rect);

	sf::FloatRect body;
};

class CPhysicsSystem : public TComponentSystem<SPhysicsBody>
{
public:
	static tSystemID id;

	void onUpdate(const sf::Time dt);

	bool detectCollision(const SPhysicsBody& b1, const SPhysicsBody& b2);
	bool isColliding(tObjectID id);
};

#endif