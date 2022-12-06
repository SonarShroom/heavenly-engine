#include "core/Engine.h"

#include <iostream>
#include <chrono>

#include "core/AppRuntime.h"
#include "core/HeavenlyVersion.h"
#include "graphics/GUI.h"
#include "logging/LogManager.h"
#include "graphics/Rendering.h"
#include "window/Window.h"

#include "world/Component.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

namespace Heavenly::Core
{

Engine::Engine(int argc, char** argv, std::unique_ptr<Core::AppRuntime>&& appRuntime) : runtime(std::move(appRuntime))
{
	Logging::Init();

	if (!Window::Init())
	{
		HV_LOG_ERROR("Could not initialize window system.");
		return;
	}

	Window::CreateWindow();
	auto* _windowCtx = Window::GetWindowContext();
	Rendering::Init();
	GUI::InitDevGui(_windowCtx);

	GUI::RegisterImGuiRenderFunction([&](const float deltaTime) {runtime->OnDrawImGui(deltaTime);});

	HV_LOG_INFO("Heavenly Engine started. Version: {}", HEAVENLY_VERSION);
	
	runtime->OnBoot(argc, argv);
}

World::WorldAdmin& Engine::CreateWorld() {
	return worlds.emplace_back(*this);
}

void Terminate()
{
	Rendering::Terminate();
	GUI::Terminate();
	HV_LOG_INFO("Heavenly Engine shutdown.");
}

int Engine::Run()
{
	auto end_frame_time = std::chrono::steady_clock::now();

	while (!Window::ShouldClose())
	{
		auto deltaTime = static_cast<float>((std::chrono::steady_clock::now() - end_frame_time).count());
		for (auto& _world : worlds) _world.Tick(deltaTime);

		Rendering::Tick(deltaTime);
		GUI::ShowDevGui(deltaTime);

		Window::SwapBuffers();
		Window::PollEvents();

		end_frame_time = std::chrono::steady_clock::now();
	}

	Terminate();

	return 0;
}

}
