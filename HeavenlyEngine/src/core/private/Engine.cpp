#include "core/Engine.h"

#include <iostream>
#include <chrono>

#include "core/AppRuntime.h"
#include "core/HeavenlyVersion.h"
#include "graphics/GUI.h"
#include "logging/LogManager.h"
#include "graphics/Renderer.h"

#include "world/Component.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

namespace Heavenly::Core
{

Engine::Engine(int argc, char** argv, std::unique_ptr<Core::AppRuntime>&& appRuntime) : runtime(std::move(appRuntime))
{
	Logging::Init();

	if (!WindowSystem::Init())
	{
		state = State::ErrorOnBoot;
		return;
	}
	
	using WindowModeT = WindowSystem::Window::Mode;
	mainWindow = std::make_unique<WindowSystem::Window>("Heavenly Game Engine", Math::Vector2(1280, 720), WindowModeT::WINDOWED);
	if (!mainWindow->IsWindowCreated())
	{
		state = State::ErrorOnBoot;
		return;
	}

	renderer = std::make_unique<Graphics::Renderer>(mainWindow->GetWindowSize());
	GUI::InitDevGui(*mainWindow);

	GUI::RegisterImGuiRenderFunction([&](const float deltaTime) {runtime->OnDrawImGui(deltaTime);});

	HV_LOG_INFO("Heavenly Engine started. Version: {}", HEAVENLY_VERSION);
	
	runtime->OnBoot(argc, argv);
}

World::WorldAdmin& Engine::CreateWorld() {
	auto& _world = worlds.emplace_back(*this);
	_world.RegisterObjectSystem(*renderer, &Graphics::Renderer::MaterialRendererSystem);
	_world.RegisterObjectSystem(*renderer, &Graphics::Renderer::RectRendererSystem);
	return _world;
}

Engine::~Engine()
{
	WindowSystem::Terminate();
	GUI::Terminate();
	HV_LOG_INFO("Heavenly Engine shutdown.");
}

int Engine::Run()
{
	if (state == State::ErrorOnBoot) return 0;

	auto end_frame_time = std::chrono::steady_clock::now();

	while (!mainWindow->ShouldClose())
	{
		auto deltaTime = static_cast<float>((std::chrono::steady_clock::now() - end_frame_time).count());
		for (auto& _world : worlds)
			_world.Tick(deltaTime);

		renderer->Tick(deltaTime);
		//GUI::ShowDevGui(deltaTime);

		mainWindow->SwapBuffers();
		mainWindow->PollEvents();
		mainWindow->SetShouldClose(shouldTerminate || mainWindow->ShouldClose());

		end_frame_time = std::chrono::steady_clock::now();
	}

	return 0;
}

}
