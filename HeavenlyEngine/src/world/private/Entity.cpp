#include "Entity.h"

namespace Heavenly::World
{

void Entity::AddComponent(Component& comp)
{
	components.push_back(std::ref(comp));
}

void Entity::RemoveComponent(Component& comp)
{
	for (auto _compIt = components.begin(); _compIt != components.end(); _compIt++)
	{
		if (&(*_compIt).get() == &comp)
		{
			components.erase(_compIt);
			break;
		}
	}
}

}