#include "core/Engine.h"

#include <iostream>
#include <chrono>

#include "core/AppRuntime.h"
#include "core/HeavenlyVersion.h"
#include "graphics/GUI.h"
#include "logging/LogManager.h"
#include "graphics/Rendering.h"
#include "window/Window.h"
#include "world/EntityComponentSystem.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

namespace Heavenly
{

Core::AppRuntime* p_app = nullptr;

void InitializeEngine(int argc, char** argv)
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

	GUI::RegisterImGuiRenderFunction([](const float deltaTime) {p_app->OnDrawImGui(deltaTime);});

	HV_LOG_INFO("Heavenly Engine started. Version: {}", HEAVENLY_VERSION);
	
	p_app->OnBoot(argc, argv);
}

void Terminate()
{
	Rendering::Terminate();
	World::Terminate();
	GUI::Terminate();
	HV_LOG_INFO("Heavenly Engine shutdown.");
}

int Run(int argc, char** argv, Core::AppRuntime* app)
{
	p_app = app;

	InitializeEngine(argc, argv);

	auto* _world = World::CreateWorld();
	auto* _rectEntity = World::CreateEntity(_world, "rect");
	auto* _rectTransform = World::GetComponent<World::TransformComponent>(_rectEntity);
	_rectTransform->position = {-.2f, .1f, 0.f};

	auto* _rectComponent = World::CreateComponent<World::RectComponent>(_rectEntity);
	_rectComponent->size.x = .2f;
	_rectComponent->size.y = .2f;
	_rectComponent->color = {1.f, .5f, .2f, 1.0f};

	auto* _matComponent = World::CreateComponent<World::MaterialComponent>(_rectEntity);
	_matComponent->vertexShader = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec4 aCol;
		out vec4 vCol;
		void main()
		{
			vCol = aCol;
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	_matComponent->fragmentShader = R"(
		#version 330 core
		in vec4 vCol;
		out vec4 FragColor;
		void main()
		{
		   FragColor = vCol;
		}
	)";

	auto end_frame_time = std::chrono::steady_clock::now();

	while (!Window::ShouldClose())
	{
		auto deltaTime = static_cast<float>((std::chrono::steady_clock::now() - end_frame_time).count());
		World::Tick(_world, deltaTime);

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
