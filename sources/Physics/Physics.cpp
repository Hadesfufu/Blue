#include "Physics/Physics.h"
#include "System/SystemManager.h"
#include "Game/Position.h"

tSystemID CPhysicsSystem::id = -1;

SPhysicsBody::SPhysicsBody(const sf::FloatRect& rect)
: body(rect)
{

}

bool CPhysicsSystem::detectCollision(const SPhysicsBody& b1, const SPhysicsBody& b2)
{
	if(b1.body.intersects(b2.body))
		return true;
	else
		return false;
}

bool CPhysicsSystem::isColliding(tObjectID id)
{
	auto found = mComponents.find(id);

	if(found == mComponents.end())
		return false;

	for(auto it = mComponents.begin() ; it != mComponents.end() ; ++it)
	{
		if(detectCollision(*found->second, *it->second) && it != found)
			return true;
	}
	return false;
}

void CPhysicsSystem::onUpdate(const sf::Time dt)
{
	for(auto it = mComponents.begin() ; it != mComponents.end() ; ++it)
	{
		it->second->body = sf::FloatRect(CSystemManager::instance()->getSystem<CPositionSystem>()->getPosition(it->first), 
										 sf::Vector2f(it->second->body.width, it->second->body.height));
	}
}