#include "System/SystemManager.h"

#include "Game/Movement.h"
#include "Game/Position.h"

#include "Physics/Physics.h"

const float SMovable::MaxVelocity = 100.f;

tSystemID CMovementSystem::id = -1;

SMovable::SMovable(const sf::Vector2f& vel)
: velocity(vel)
{

}

void SMovable::limitVelocity()
{
	velocity.x = std::min(velocity.x, MaxVelocity);
	velocity.y = std::min(velocity.y, MaxVelocity);
}

void CMovementSystem::scaleVelocity(tObjectID id, const sf::Vector2f& vel)
{
	auto found = mComponents.find(id);
	found->second->velocity += vel;
}

void CMovementSystem::onUpdate(const sf::Time dt)
{
	for(auto it = mComponents.begin() ; it != mComponents.end() ; ++it)
	{
		sf::Vector2f tmp = CSystemManager::instance()->getSystem<CPositionSystem>()->getPosition(it->first);

		it->second->velocity.y += 9.81 * 2 * dt.asSeconds();
		it->second->limitVelocity();

		sf::Vector2f newPosition = tmp + it->second->velocity * dt.asSeconds();

		if(CSystemManager::instance()->getSystem<CPhysicsSystem>()->isColliding(it->first))
			it->second->velocity = sf::Vector2f(0.0f, 0.0f);
		else
			CSystemManager::instance()->getSystem<CPositionSystem>()->setComponent(it->first, newPosition);
	}
}