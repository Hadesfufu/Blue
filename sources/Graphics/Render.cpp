#include "System/SystemManager.h"
#include "Game/Position.h"
#include "Graphics/Render.h"

tSystemID CRenderSystem::id = -1;

sf::Sprite& CRenderSystem::getSprite(tObjectID id) const
{
	return *mComponents.find(id)->second;
}

void CRenderSystem::onUpdate(const sf::Time dt)
{
	for(auto it = mComponents.begin() ; it != mComponents.end() ; ++it)
		it->second->setPosition(CSystemManager::instance()->getSystem<CPositionSystem>()->getPosition(it->first));
}

void CRenderSystem::onDraw(sf::RenderWindow& window)
{
	for(auto it = mComponents.begin() ; it != mComponents.end() ; ++it)
		window.draw(*it->second);
}