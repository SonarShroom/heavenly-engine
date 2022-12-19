#include "appruntime.h"

#include <Heavenly.h>

#include "editorgui.h"

namespace HeavenlyApp::App
{

void Runtime::OnBoot([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	mainWorld = &(engine.CreateWorld());
	auto& _rectEntity = mainWorld->CreateEntity("rect");
	auto* _rectTransform = mainWorld->CreateComponent<Heavenly::World::TransformComponent>(_rectEntity);
	_rectTransform->position = { -.2f, .1f, 0.f };

	auto* _rectComponent = mainWorld->CreateComponent<Heavenly::World::RectComponent>(_rectEntity);
	_rectComponent->size.x = .2f;
	_rectComponent->size.y = .2f;
	_rectComponent->color = { 1.f, .5f, .2f, 1.0f };

	constexpr std::string_view _vertexShader = R"(
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
	constexpr std::string_view _fragmentShader = R"(
		#version 330 core
		in vec4 vCol;
		out vec4 FragColor;
		void main()
		{
		   FragColor = vCol;
		}
	)";
	auto* _shader = new Heavenly::Resources::Shader(_vertexShader, _fragmentShader);
	mainWorld->CreateComponent<Heavenly::World::MaterialComponent>(_rectEntity, *_shader);
}

void Runtime::OnUpdate([[maybe_unused]] const float deltaTime)
{

}

void Runtime::OnDrawImGui([[maybe_unused]] const float deltaTime)
{
	//ImGui::ShowDemoWindow();
	editor.ShowMainMenuBar();
	editor.ShowSceneExplorer();
	editor.ShowInspector();
}

}