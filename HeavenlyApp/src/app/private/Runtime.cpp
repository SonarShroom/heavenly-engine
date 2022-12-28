#include "Runtime.h"

#include <IconsFontAwesome6.h>
#include <Heavenly.h>

namespace HeavenlyApp::App
{

void Runtime::OnBoot([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	static constexpr ImWchar _fontAwesomeRange[] = {ICON_MIN_FA, ICON_MAX_16_FA, 0};
	std::filesystem::path _fontAwesomeRegularPath =
		std::filesystem::current_path() / "assets" / "fonts" / FONT_ICON_FILE_NAME_FAR;
	std::filesystem::path _fontAwesomeSolidPath =
		std::filesystem::current_path() / "assets" / "fonts" / FONT_ICON_FILE_NAME_FAS;
	engine.GetGUIManager().MergeFont(_fontAwesomeRegularPath, _fontAwesomeRange);
	engine.GetGUIManager().MergeFont(_fontAwesomeSolidPath, _fontAwesomeRange);
	mainWorld = &(engine.CreateWorld());
	auto& _rectEntity = mainWorld->CreateEntity("rect");
	auto* _rectTransform = mainWorld->GetComponent<Heavenly::World::TransformComponent>(_rectEntity);
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
	auto* _shader = engine.GetResourceManager().CreateResource<Heavenly::Resources::Shader>(_vertexShader, _fragmentShader);
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