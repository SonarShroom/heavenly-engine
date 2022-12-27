#include "core/Engine.h"

#include <chrono>

#include "core/AppRuntime.h"
#include "core/HeavenlyVersion.h"

#include "logging/LogManager.h"

#include "HeavenlyMath.h"

#include "world/Component.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

namespace Heavenly::Core
{

Engine::Engine(int argc, char** argv, std::unique_ptr<IAppRuntime>&& appRuntime) : runtime(std::move(appRuntime))
{
	Logging::Init();

	if (!WindowSystem::Init())
	{
		state = State::ErrorOnBoot;
		return;
	}
	
	using WindowModeT = WindowSystem::Window::Mode;
	mainWindow = std::make_unique<WindowSystem::Window>("Heavenly Game Engine", glm::vec2(1280.f, 720.f), WindowModeT::WINDOWED);
	if (!mainWindow->IsWindowCreated())
	{
		state = State::ErrorOnBoot;
		return;
	}

	guiManager = std::make_unique<Graphics::GUIManager>(*mainWindow);
	renderer = std::make_unique<Graphics::Renderer>(mainWindow->GetWindowSize());

	guiManager->RegisterImGUIRenderFunction([&](const float deltaTime) {runtime->OnDrawImGui(deltaTime);});

	HV_LOG_INFO("Heavenly Engine started. Version: {}", HEAVENLY_VERSION);
	
	runtime->OnBoot(argc, argv);
}

World::WorldAdmin& Engine::CreateWorld() {
	auto& _world = worlds.emplace_back();
	_world.RegisterObjectSystem(*renderer, &Graphics::Renderer::MaterialRendererSystem);
	_world.RegisterObjectSystem(*renderer, &Graphics::Renderer::RectRendererSystem);
	return _world;
}

Engine::~Engine()
{
	guiManager = nullptr;
	renderer = nullptr;
	mainWindow = nullptr;
	WindowSystem::Terminate();
	Logging::Terminate();
}

int Engine::Run()
{
	if (state == State::ErrorOnBoot) return -1;

	state = State::Running;

	auto end_frame_time = std::chrono::steady_clock::now();

	while (!mainWindow->ShouldClose())
	{
		auto deltaTime = static_cast<float>((std::chrono::steady_clock::now() - end_frame_time).count());
		for (auto& _world : worlds)
			_world.Tick(deltaTime);

		renderer->Tick(deltaTime);
		guiManager->RenderGUI(deltaTime);

		mainWindow->SwapBuffers();
		mainWindow->PollEvents();
		mainWindow->SetShouldClose(shouldTerminate || mainWindow->ShouldClose());

		end_frame_time = std::chrono::steady_clock::now();
	}

	HV_LOG_INFO("Heavenly Engine shutdown.");

	return 0;
}

}
