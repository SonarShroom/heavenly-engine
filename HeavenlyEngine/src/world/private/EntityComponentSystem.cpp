#include "../EntityComponentSystem.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include "logging/LogManager.h"
#include "world/GUIComponents.h"

namespace Heavenly::World
{

std::vector<WorldAdmin*> _worlds;

WorldAdmin* CreateWorld()
{
	auto _worldInit = [](WorldAdmin* world) {
		RegisterSystem(world, &RectRendererSystem);
	};
	auto* _newWorld = new WorldAdmin();
	_worldInit(_newWorld);
	_worlds.emplace_back(new WorldAdmin());
	return _newWorld;
}

Entity* CreateEntity(WorldAdmin* world, const std::string& id)
{
	auto* _newEntity = new Entity(world, id);
	world->entities.push_back(_newEntity);
	return _newEntity;
}

/* NOTE: As this runs Tick on all systems, it's required that when initializing a new system we check to see if the
* order of systems does not cause any unexpected side effects (may change in the future for a more verbose way of
* running said systems)*/
void Tick(WorldAdmin* world, const float timeDelta)
{
	for(const auto& system : world->systems)
	{
		system(timeDelta);
	}
}

} // Heavenly::World
