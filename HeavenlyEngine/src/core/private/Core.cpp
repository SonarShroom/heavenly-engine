#include "Core.h"

#include <iostream>
#include <chrono>

#include "AppRuntime.h"
#include "EntityComponentSystem.h"
#include "HeavenlyVersion.h"
#include "LogManager.h"
#include "Rendering.h"
#include "Window.h"

#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"

namespace Heavenly
{

void InitializeEngine()
{
	Logging::Init();

	if (!Window::Init())
	{
		HV_LOG_ERROR("Could not initialize window system.");
		return;
	}

	Window::CreateWindow();
	Rendering::Init(Window::GetWindowContext());

	HV_LOG_INFO("Heavenly Engine started. Version: {}", HEAVENLY_VERSION);
}

void Terminate()
{
	Rendering::Terminate();
	World::Terminate();
	HV_LOG_INFO("Heavenly Engine shutdown.");
}

int Run([[maybe_unused]] AppRuntime* app)
{
	InitializeEngine();

	auto* _world = World::CreateWorld();
	auto* _rectEntity = World::CreateEntity(_world, "rect");
	auto* _rectTransform = World::GetComponent<World::TransformComponent>(_rectEntity);
	_rectTransform->position = {-.1f, .1f, 0.f};

	auto* _rectComponent = World::CreateComponent<World::RectComponent>(_rectEntity);
	_rectComponent->size.x = .2f;
	_rectComponent->size.y = .2f;

	auto* _matComponent = World::CreateComponent<World::MaterialComponent>(_rectEntity);
	_matComponent->vertexShader = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		void main()
		{
		   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)";

	_matComponent->fragmentShader = R"(
		#version 330 core
		//layout (location = 1) in vec4 fColor
		out vec4 FragColor;
		void main()
		{
		   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)";

	auto end_frame_time = std::chrono::steady_clock::now();

	while (!Window::ShouldClose())
	{
		auto deltaTime = (std::chrono::steady_clock::now() - end_frame_time).count();
		World::Tick(_world, (float)deltaTime);
		Rendering::Tick();
		Window::PollEvents();

		end_frame_time = std::chrono::steady_clock::now();
	}

	Terminate();

	return 0;
}

}
