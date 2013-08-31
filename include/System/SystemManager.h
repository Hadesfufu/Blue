#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <vector>
#include "System/System.h"

class CSystemManager
{
public:
	static CSystemManager* instance()
	{
		static CSystemManager instance;
		return &instance;
	}

public:
	~CSystemManager()
	{
		for(auto it = mSystems.begin() ; it != mSystems.end() ; ++it)
		{
			delete *it;
			*it = nullptr;
		}
	}

	template<typename T>
	void addSystem()
	{
		T::id = mSystems.size();
		mSystems.push_back(new T());
	}

	template<typename T>
	T* getSystem()
	{
		return static_cast<T*>(mSystems[T::id]);
	}

	void onUpdate(const sf::Time dt)
	{
		for(auto it = mSystems.begin() ; it != mSystems.end() ; ++it)
			(*it)->onUpdate(dt);
	}

private:
	std::vector<ISystem*> mSystems;
};

#endif