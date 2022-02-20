#include "Core.h"

#include <iostream>
#include <chrono>

#include "AppRuntime.h"
#include "EntityComponentSystem.h"
#include "HeavenlyVersion.h"
#include "LogManager.h"
#include "Rendering.h"
#include "Window.h"

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
	HV_LOG_INFO("Heavenly Engine shutdown.");
}

int Run(AppRuntime* app)
{
	InitializeEngine();

	auto admin = new EntityComponentSystem::WorldAdmin();

	// TODO: This is not a good API to be honest... must rework asap after getting the rect on screen.
	const char* vertex_shader_source = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	int vertex_shader_id = 0;
	bool vert_success =  Rendering::RegisterNewVertexShader(vertex_shader_source, vertex_shader_id);

	const char* frag_shader_source = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";
	int frag_shader_id = 0;
	bool frag_success = Rendering::RegisterNewFragmentShader(frag_shader_source, frag_shader_id);

	if (!vert_success || !frag_success)
	{
		HV_LOG_ERROR("Creating rect without shader program...");
		Rendering::CreateRect();
	}
	else
	{
		int shader_program_id = 0;
		bool link_success = Rendering::RegisterNewShaderProgram(vertex_shader_id, frag_shader_id, shader_program_id);

		if (!link_success)
		{
			HV_LOG_ERROR("Creating rect without shader program (link went wrong)...");
			Rendering::CreateRect();
		}
		else
		{
			Rendering::CreateRect(shader_program_id);
		}
	}

	auto end_frame_time = std::chrono::steady_clock::now();

	while (!Window::ShouldClose())
	{
		auto time_delta = (std::chrono::steady_clock::now() - end_frame_time).count();
		admin->Tick(time_delta);
		Rendering::Tick(time_delta);

		end_frame_time = std::chrono::steady_clock::now();
	}

	Terminate();

	HV_LOG_INFO("Heavenly Engine Shutdown...");

	return 0;
}

}
