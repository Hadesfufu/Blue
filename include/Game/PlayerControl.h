#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include "System/System.h"

class CPlayerControlSystem : public ISystem
{
public:
	static tSystemID id;

	void setPlayerID(tObjectID id);
	void onUpdate(const sf::Time dt);

private:
	tObjectID mPlayerID;
};

#endif