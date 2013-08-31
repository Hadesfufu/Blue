#include "System/SystemManager.h"

CSystemManager* CSystemManager::mInstance = 0;

CSystemManager* CSystemManager::instance()
{
	if(mInstance == 0)
		mInstance = new CSystemManager();
	return mInstance;
}

void CSystemManager::onUpdate(const sf::Time dt)
{
	for(auto it = mSystems.begin() ; it != mSystems.end() ; ++it)
		(*it)->onUpdate(dt);
}