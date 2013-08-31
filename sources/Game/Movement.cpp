#include "System/SystemManager.h"

#include "Game/Movement.h"
#include "Game/Position.h"

#include "Physics/Physics.h"

const float CMovementSystem::MaxVelocity = 5.0f;
const float CMovementSystem::Gravity = 0.75f;
const float CMovementSystem::SpeedFactor = 64.0f;

tSystemID CMovementSystem::id = -1;

bool CMovementSystem::jump( tObjectID id ) {
	if( mCanJump == false ) return false;

	auto found = mComponents.find( id );
	found->second->y = -MaxVelocity * 2.5f;

	return true;
}

void CMovementSystem::setVelocityX( tObjectID id, float velX ) {
	auto found = mComponents.find( id );
	found->second->x = std::min( velX, MaxVelocity );
}

void CMovementSystem::setVelocityY( tObjectID id, float velY ) {
	auto found = mComponents.find( id );
	found->second->y = std::min( velY, MaxVelocity );
}


void CMovementSystem::onMove( tObjectID id, const sf::Time& dt, float moveX, float moveY ) {
	if( moveX == 0 && moveY == 0 ) return;

	mCanJump = false;

	auto found = mComponents.find( id );
	sf::Vector2f& pos = CSystemManager::instance()->getSystem<CPositionSystem>()->getPosition( found->first );

	float newX = 0;
	float newY = 0;

	moveX *= dt.asSeconds() * SpeedFactor;
	moveY *= dt.asSeconds() * SpeedFactor;

	if( moveX != 0 ) {
		if( moveX >= 0 )	newX = dt.asSeconds() * SpeedFactor;
		else				newX = -dt.asSeconds() * SpeedFactor;
	}

	if( moveY != 0 ) {
		if( moveY >= 0 )	newY = dt.asSeconds() * SpeedFactor;
		else				newY = -dt.asSeconds() * SpeedFactor;
	}

	while( true ) {
		if( CSystemManager::instance()->getSystem<CPhysicsSystem>()->posValid( found->first, pos.x + newX, pos.y ) )
			pos.x += newX;
		else
			found->second->x = 0;

		if( CSystemManager::instance()->getSystem<CPhysicsSystem>()->posValid( found->first, pos.x, pos.y + newY ) )
			pos.y += newY;
		else {
			if( moveY > 0 ) mCanJump = true;
			found->second->y = 0;
		}

		moveX += -newX;
		moveY += -newY;

		if( newX > 0 && moveX <= 0 ) newX = 0;
		if( newX < 0 && moveX >= 0 ) newX = 0;

		if( newY > 0 && moveY <= 0 ) newY = 0;
		if( newY < 0 && moveY >= 0 ) newY = 0;
		
		if( moveX == 0 ) newX = 0;
		if( moveY == 0 ) newY = 0;

		if( moveX == 0 && moveY == 0 ) break;
		if( newX  == 0 && newY  == 0 ) break;
	}
}

void CMovementSystem::onUpdate( const sf::Time dt ) {
	for( auto it = mComponents.begin() ; it != mComponents.end() ; ++it ) {
		// apply gravity
		it->second->y += Gravity * dt.asSeconds() * SpeedFactor;

		// limit velocity
		it->second->x = std::min( it->second->x, MaxVelocity );
		it->second->y = std::min( it->second->y, MaxVelocity );

		onMove( it->first, dt, it->second->x, it->second->y );
	}
}