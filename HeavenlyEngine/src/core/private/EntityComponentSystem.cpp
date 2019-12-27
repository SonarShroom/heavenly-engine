#include "../EntityComponentSystem.h"

#include <iostream>
#include <vector>
#include <string>

using namespace Heavenly;

struct Component
{
    // TODO: A component is a bundle of data, with a list of systems that will act upon it.
};

static void EmptySystemTickFunction(float timeDelta)
{
    std::cout << "Uninitialized tick function.";
}
struct System
{
    // TODO: A System acts upon various components of an Entity.
    EntityComponentSystem::SystemTickFunc Tick { *EmptySystemTickFunction };
};

struct Entity
{
    // TODO: An Entity is a collection of components. Each cycle they will all be ran against their systems.
};

static std::vector<System*>     w_systems;
static std::vector<Entity*>     w_entities;
static std::vector<Component*>  w_components;

unsigned int EntityComponentSystem::CreateEntity()
{
    return 0;
}

void EntityComponentSystem::RegisterSystemType(SystemTickFunc tick)
{
    System* addedSystem;
    addedSystem->Tick = *tick;
    w_systems.push_back(addedSystem);
}

template<typename Component_t>
void EntityComponentSystem::RegisterComponentType()
{

}

/* NOTE: As this runs Tick on all systems, it's required that when initializing a new system we check to see if the
 * order of systems does not cause any unexpected side effects (may change in the future for a more verbose way of
 * running said systems)*/
void EntityComponentSystem::Tick(float timeDelta)
{
    for(System* s : w_systems)
    {
        s->Tick(timeDelta);
    }
}