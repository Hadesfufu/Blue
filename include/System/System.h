#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <memory>
#include <iostream>
#include <SFML/System/Time.hpp>

typedef unsigned int tSystemID;
typedef unsigned int tObjectID;

class ISystem
{
public:
	virtual ~ISystem() { }
	virtual void onUpdate(const sf::Time dt) = 0;
};

template<typename T>
class TComponentSystem : public ISystem
{
public:
	virtual void onUpdate(const sf::Time dt) = 0;

	virtual void setComponent(tObjectID id, const T& component)
	{
		auto found = mComponents.find(id);

		if(found == mComponents.end())
			mComponents.emplace(id, std::unique_ptr<T>(new T(component)));
		else
			*found->second = component;
	}

	virtual void removeComponent(tObjectID id)
	{
		auto found = mComponents.find(id);
		mComponents.erase(found);
	}

protected:
	std::map<tObjectID, std::unique_ptr<T>> mComponents;
};

#endif