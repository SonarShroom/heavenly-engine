#include "GUIManager.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <IconsFontAwesome6.h>

#include "logging/LogManager.h"
#include "window_system/Window.h"

namespace Heavenly::Graphics
{

constexpr auto MAIN_DOCK_WINDOW_FLAGS =
	ImGuiWindowFlags_MenuBar | 
	ImGuiWindowFlags_NoDocking |
	ImGuiWindowFlags_NoTitleBar |
	ImGuiWindowFlags_NoCollapse |
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus |
	ImGuiWindowFlags_NoNavFocus |
	ImGuiWindowFlags_NoBackground;

GUIManager::GUIManager(const WindowSystem::Window& window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window.GetContext(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

	imGuiIO = &ImGui::GetIO();
	imGuiIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImFontConfig _defaultFontCfg;
	_defaultFontCfg.OversampleH = _defaultFontCfg.OversampleV = 1;
	_defaultFontCfg.PixelSnapH = true;
	_defaultFontCfg.SizePixels = DEFAULT_FONT_SIZE;
	imGuiIO->Fonts->AddFontDefault(&_defaultFontCfg);
}

GUIManager::~GUIManager()
{
	HV_LOG_INFO("Destroying ImGui Context...");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUIManager::MergeFont(const std::filesystem::path& path, const ImWchar* range, const float size)
{
	static ImFontConfig _fontAwesomeConfig;
	_fontAwesomeConfig.MergeMode = true;
	_fontAwesomeConfig.PixelSnapH = true;
	imGuiIO->Fonts->AddFontFromFileTTF(path.c_str(), size, &_fontAwesomeConfig, range);
}

void GUIManager::RegisterImGUIRenderFunction(const std::function<void(const float)>& renderFunction)
{
	imGuiRenderFunctions.push_back(renderFunction);
}

void GUIManager::RenderGUI(const float deltaTime)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const auto _mainViewport = ImGui::GetMainViewport();
	const auto _mainDockspaceID = ImGui::GetID("Root Dockspace");
	ImGui::SetNextWindowPos(_mainViewport->WorkPos);
	ImGui::SetNextWindowSize(_mainViewport->WorkSize);
	ImGui::SetNextWindowViewport(_mainViewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::Begin("##__root_dockspace", nullptr, MAIN_DOCK_WINDOW_FLAGS);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::DockSpace(_mainDockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

	for (auto& renderFunc : imGuiRenderFunctions)
	{
		renderFunc(deltaTime);
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::EndFrame();
}

}
