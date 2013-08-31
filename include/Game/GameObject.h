#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>
#include "System/SystemManager.h"

typedef unsigned int tObjectID;

class CGameObject
{
public:
	tObjectID id;
};

class CGameObjectManager
{
public:
	static CGameObjectManager* instance()
	{
		static CGameObjectManager instance;
		return &instance;
	}

public:
	tObjectID createObject()
	{
		CGameObject object;
		object.id = mObjects.size() + 1;
		mObjects.push_back(object);

		return object.id;
	}

private:
	std::vector<CGameObject> mObjects;
};

#endif