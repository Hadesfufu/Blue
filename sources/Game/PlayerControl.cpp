#include "Game/PlayerControl.h"
#include "Game/Movement.h"
#include "System/SystemManager.h"

#include <SFML/Window/Keyboard.hpp>

tSystemID CPlayerControlSystem::id = -1;

void CPlayerControlSystem::setPlayerID(tObjectID id)
{
	mPlayerID = id;
}

void CPlayerControlSystem::onUpdate(const sf::Time dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		CSystemManager::instance()->getSystem<CMovementSystem>()->scaleVelocity(mPlayerID, sf::Vector2f(80.f, 0.0f));
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
		CSystemManager::instance()->getSystem<CMovementSystem>()->scaleVelocity(mPlayerID, sf::Vector2f(-80.f, 0.0f));
}