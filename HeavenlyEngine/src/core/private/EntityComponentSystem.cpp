#include "../EntityComponentSystem.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace Heavenly::EntityComponentSystem;

Entity::Entity(unsigned int id) : entityID(id)
{

}

Entity::Entity(unsigned int id, std::initializer_list<Component*> component_list) :
    entityID(id),
    components(component_list)
{
    
}

Entity::~Entity()
{
    for(Component* c : components)
    {
        // TODO: For each component remove it from any admins they are registered to and delete the data.
    }
}

unsigned int WorldAdmin::CreateEntity()
{
    Entity* new_entity = new Entity(next_entity_id);
    world_entities.insert({ next_entity_id, new_entity });
    return next_entity_id++;
}

void WorldAdmin::RegisterComponent(Component* component)
{
    world_components.push_back(component);
}

void WorldAdmin::RegisterSystem(System* system) {
    world_systems.push_back(system);
}

/* NOTE: As this runs Tick on all systems, it's required that when initializing a new system we check to see if the
* order of systems does not cause any unexpected side effects (may change in the future for a more verbose way of
* running said systems)*/
void WorldAdmin::Tick(float time_delta)
{
    for(System* s : world_systems)
    {
        s->Tick(time_delta);
    }
}