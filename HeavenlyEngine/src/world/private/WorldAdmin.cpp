#include "WorldAdmin.h"

#include "world/Component.h"
#include "world/Entity.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

namespace Heavenly::World
{

WorldAdmin::WorldAdmin([[maybe_unused]] Core::Engine& engine)
{
	// RegisterSystem(&MaterialRendererSystem);
	// RegisterSystem(&RectRendererSystem);
}

/* NOTE: As this runs Tick on all systems, it's required that when initializing a new system we check to see if the
 * order of systems does not cause any unexpected side effects (may change in the future for a more verbose way of
 * running said systems) */
void WorldAdmin::Tick(const float deltaTime)
{
	for (const auto& system : systems)
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
	auto& _ent = entities.emplace_back(id);
	return _ent;
}

Entity* WorldAdmin::GetEntity(const std::string& id)
{
	for (auto& _ent: entities)
	{
		if (_ent.GetID() == id) return &_ent;
	}
	return nullptr;
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
		DestroyComponent(_entCompIt->get());
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

}