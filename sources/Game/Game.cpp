#include "Game/Game.h"

#include <iostream>

#include "System/SystemManager.h"
#include "Physics/Physics.h"
#include "Game/Position.h"
#include "Game/Movement.h"
#include "Game/PlayerControl.h"
#include "Graphics/Render.h"
#include "Graphics/TextureHolder.h"

const sf::Time CGame::TimePerFrame = sf::seconds(1.f/60.f);

CGame::CGame()
{
	mWindow.create(sf::VideoMode(70 * 12, 70 * 8), "SFML Application", sf::Style::Close);

	/* Add all the systems to our system manager. */
	CSystemManager::instance()->addSystem<CPositionSystem>();
	CSystemManager::instance()->addSystem<CRenderSystem>();
	CSystemManager::instance()->addSystem<CPhysicsSystem>();
	CSystemManager::instance()->addSystem<CMovementSystem>();
	CSystemManager::instance()->addSystem<CPlayerControlSystem>();

	mMap.loadMap("Data/Maps/Map001.xml");

	tObjectID player = CGameObjectManager::instance()->createObject();
	CSystemManager::instance()->getSystem<CPositionSystem>()->setComponent(player, sf::Vector2f(0.f, 0.f));
	CSystemManager::instance()->getSystem<CRenderSystem>()->setComponent(player, sf::Sprite(*CTextureHolder::getTexture("Data/Player/player_stand.png")));
	CSystemManager::instance()->getSystem<CMovementSystem>()->setComponent(player, SMovable(sf::Vector2f(0.0f, 0.0f)));
	CSystemManager::instance()->getSystem<CPhysicsSystem>()->setComponent(player, SPhysicsBody(sf::FloatRect(0.f, 0.f, 66.f, 92.f)));
	CSystemManager::instance()->getSystem<CPlayerControlSystem>()->setPlayerID(player);
}

void CGame::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while(mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while(timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			onUpdate(TimePerFrame);
		}
		onDraw();
	}
}

void CGame::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			mWindow.close();
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
			mMap.editMap(mWindow);
	}
}

void CGame::onUpdate(const sf::Time dt)
{
	CSystemManager::instance()->onUpdate(dt);
}

void CGame::onDraw()
{
	mWindow.clear(sf::Color(208,244,247));
	CSystemManager::instance()->getSystem<CRenderSystem>()->onDraw(mWindow);
	mWindow.display();
}