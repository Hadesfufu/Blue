#include "Game/Position.h"

tSystemID CPositionSystem::id = -1;

sf::Vector2f& CPositionSystem::getPosition(tObjectID id) const
{
	return *mComponents.find(id)->second;
}

void CPositionSystem::onUpdate(const sf::Time dt)
{

}