#include "../EntityComponentSystem.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "logging/LogManager.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

namespace Heavenly::World
{

std::vector<WorldAdmin*> _worlds;

WorldAdmin* CreateWorld()
{
	auto _worldInit = [](WorldAdmin* world)
	{
		RegisterSystem(world, &MaterialRendererSystem);
		RegisterSystem(world, &RectRendererSystem);
	};
	auto* _newWorld = new WorldAdmin();
	_worldInit(_newWorld);
	_worlds.emplace_back(new WorldAdmin());
	return _newWorld;
}

void DestroyWorld(WorldAdmin* world)
{
	for (auto* _ent : world->entities)
	{
		delete _ent;
	}

	for (auto* _comp : world->components)
	{
		delete _comp;
	}
	
	delete world;
}

/* NOTE: As this runs Tick on all systems, it's required that when initializing a new system we check to see if the
* order of systems does not cause any unexpected side effects (may change in the future for a more verbose way of
* running said systems)*/
void Tick(WorldAdmin* world, const float deltaTime)
{
	for(const auto& system : world->systems)
	{
		system(deltaTime);
	}
}

void Terminate()
{
	HV_LOG_INFO("Removing {} {}.", _worlds.size(), _worlds.size() == 1 ? "world" : "worlds");
	for (auto* _world : _worlds)
	{
		DestroyWorld(_world);
	}
}

Entity* CreateEntity(WorldAdmin* world, const std::string& id)
{
	auto* _newEntity = new Entity(world, id);
	world->entities.push_back(_newEntity);
	CreateComponent<TransformComponent>(_newEntity);
	return _newEntity;
}

void DestroyEntity(Entity* entity)
{
	auto* _world = const_cast<WorldAdmin*>(entity->world);
	std::erase(_world->entities, entity);
	for (const auto* _entityComp : entity->components)
	{
		std::erase(_world->components, _entityComp);
	}
	delete entity;
}

void DestroyComponent(Component* comp)
{
	auto* _entity = const_cast<Entity*>(comp->GetEntity());
	std::erase(_entity->components, comp);
	auto* _world = const_cast<WorldAdmin*>(_entity->world);
	std::erase(_world->components, comp);
	delete comp;
}

} // Heavenly::World
