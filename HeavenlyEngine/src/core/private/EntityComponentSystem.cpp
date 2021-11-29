#include "../EntityComponentSystem.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "Rendering.h"

namespace Heavenly
{

namespace EntityComponentSystem
{

Entity::Entity(unsigned int id) : entity_id(id) { }

Entity::Entity(unsigned int id, std::initializer_list<unsigned int> component_list) :
    entity_id(id),
    component_id_list(component_list) { }

unsigned int WorldAdmin::CreateEntity()
{
    Entity* new_entity = new Entity(next_entity_id);
    world_entities.insert({ next_entity_id, new_entity });
    return next_entity_id++;
}

/* NOTE: As this runs Tick on all systems, it's required that when initializing a new system we check to see if the
* order of systems does not cause any unexpected side effects (may change in the future for a more verbose way of
* running said systems)*/
void WorldAdmin::Tick(float time_delta)
{
    for(const auto& s : world_systems)
    {
        s(time_delta);
    }
}

}

}
