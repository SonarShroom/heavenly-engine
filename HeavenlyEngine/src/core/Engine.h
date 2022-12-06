#pragma once

#include <memory>
#include <vector>

#include "world/WorldAdmin.h"
#include "graphics/Rendering.h"

namespace Heavenly::Core
{

class AppRuntime;

class Engine
{
public:
	Engine(int argc, char** argv, std::unique_ptr<Core::AppRuntime>&& appRuntime);
		
	World::WorldAdmin& CreateWorld();

	int Run();

private:
	std::unique_ptr<Core::AppRuntime> runtime;
	std::vector<World::WorldAdmin> worlds;
};

}
