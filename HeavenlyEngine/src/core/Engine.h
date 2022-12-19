#pragma once

#include <memory>
#include <vector>

#include "window_system/Window.h"
#include "world/WorldAdmin.h"
#include "graphics/Renderer.h"

namespace Heavenly::Core
{

class AppRuntime;

class Engine
{
public:
	enum class State {
		Booting = 0,
		ErrorOnBoot,
		Running,
		SIZE
	};

	Engine(int argc, char** argv, std::unique_ptr<Core::AppRuntime>&& appRuntime);
	~Engine();

	inline Graphics::Renderer& GetRenderer() { return *renderer; }
	
	World::WorldAdmin& CreateWorld();

	inline void SetShouldTerminate(const bool newShouldTerminate) { shouldTerminate = newShouldTerminate; }

	int Run();

private:
	// Internal engine use
	State state = State::Booting;
	bool shouldTerminate = false;

	std::unique_ptr<WindowSystem::Window> mainWindow;
	std::unique_ptr<Graphics::Renderer> renderer;
	std::vector<World::WorldAdmin> worlds;

	// Runime related vars
	std::unique_ptr<Core::AppRuntime> runtime;
};

}
