#pragma once

#include <memory>
#include <vector>

#include "graphics/GUIManager.h"
#include "graphics/Renderer.h"

#include "resources/Manager.h"

#include "window_system/Window.h"

#include "world/WorldAdmin.h"

namespace Heavenly::Core
{

class IAppRuntime;

class Engine
{
public:
	enum class State {
		Booting = 0,
		ErrorOnBoot,
		Running,
		SIZE
	};

	Engine() = delete;
	Engine(int argc, char** argv, std::unique_ptr<IAppRuntime>&& appRuntime);
	~Engine();

	[[nodiscard]]
	inline Graphics::Renderer& GetRenderer() const { return *renderer; }

	[[nodiscard]]
	inline Graphics::GUIManager& GetGUIManager() const { return *guiManager; }

	[[nodiscard]]
	inline Resources::Manager& GetResourceManager() { return manager; }

	World::WorldAdmin& CreateWorld();

	inline void SetShouldTerminate(const bool newShouldTerminate) { shouldTerminate = newShouldTerminate; }

	int Run();

private:
	// Internal engine use
	State state = State::Booting;
	bool shouldTerminate = false;

	std::unique_ptr<WindowSystem::Window> mainWindow;
	std::unique_ptr<Graphics::Renderer> renderer;
	std::unique_ptr<Graphics::GUIManager> guiManager;
	Resources::Manager manager;
	std::vector<World::WorldAdmin> worlds;

	// Runime related vars
	std::unique_ptr<IAppRuntime> runtime;
};

}
