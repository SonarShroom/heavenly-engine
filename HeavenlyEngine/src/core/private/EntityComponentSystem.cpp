#include "../EntityComponentSystem.h"

#include <string>

using namespace Heavenly;

struct Component
{
	// TODO: A component is a bundle of data, with a list of systems that will act upon it.
};

struct System
{
	// TODO: A System acts upon the various components of an Entity.
};

struct Entity
{
	// TODO: An Entity is a collection of components. Each cycle they will all be ran against their systems.
};

template<typename Entity_t, typename ...Component_t>
void EntityComponentSystem::RegisterEntityType(Entity_t newEntityType, Component_t ...componentsList)
{

}

template<typename Entity_t, typename Component_t>
static void RegisterEntityTypeImpl(Entity_t newEntityType, std::initializer_list<Component_t> componentsList)
{

}

template<typename System_t>
void EntityComponentSystem::RegisterSystemType(System_t newSystem)
{

}

template<typename Component_t>
void EntityComponentSystem::RegisterComponentType(Component_t newComponent)
{

}