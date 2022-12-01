#include "EntityComponentSystem.h"

#include <cassert>

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "logging/LogManager.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

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

WorldAdmin::WorldAdmin()
{
	RegisterSystem(&MaterialRendererSystem);
	RegisterSystem(&RectRendererSystem);
}

/* NOTE: As this runs Tick on all systems, it's required that when initializing a new system we check to see if the
* order of systems does not cause any unexpected side effects (may change in the future for a more verbose way of
* running said systems)*/
void WorldAdmin::Tick(const float deltaTime)
{
	for(const auto& system : systems)
	{
		system(deltaTime);
	}
}

void WorldAdmin::IterateWorldEntities(void(*visitor)(Entity&))
{
	for (auto& _ent : entities)
	{
		visitor(_ent);
	}
}

Entity& WorldAdmin::CreateEntity(const std::string& id)
{
	auto& _ent = entities.emplace_back(this, id);
	CreateComponent<TransformComponent>(_ent);
	return _ent;
}

void WorldAdmin::DestroyEntity(const std::string& id)
{
	auto _entityIt = entities.begin();
	for (const auto _entitiesEnd = entities.end(); _entityIt != _entitiesEnd; _entityIt++)
	{
		if (_entityIt->GetID() == id) break;
	}
	if (_entityIt == entities.end())
	{
		return;
	}
	auto _entityComponents = _entityIt->GetComponents();
	for (auto _entCompIt = _entityComponents.begin(); _entCompIt != _entityComponents.end(); _entCompIt++)
	{
		DestroyComponent(*_entCompIt);
	}
	entities.erase(_entityIt);
}

void WorldAdmin::DestroyComponent(Component& comp)
{
	auto& _entity = comp.GetEntity();
	_entity.RemoveComponent(comp);
	auto _compIt = components.begin();
	for (auto _compEnd = components.end(); _compIt < _compEnd; _compIt++)
	{
		if (_compIt->get() == &comp)
		{
			components.erase(_compIt);
		}
	}
}

} // Heavenly::World
