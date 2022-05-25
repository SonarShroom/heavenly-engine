#include "GUI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "LogManager.h"
#include "Window.h"

namespace Heavenly::GUI
{

std::vector<std::function<void(const float)>> p_ImGuiRenderFunctions;

constexpr auto MAIN_DOCK_WINDOW_FLAGS =
	ImGuiWindowFlags_MenuBar | 
	ImGuiWindowFlags_NoDocking |
	ImGuiWindowFlags_NoTitleBar |
	ImGuiWindowFlags_NoCollapse |
	ImGuiWindowFlags_NoResize |
	ImGuiWindowFlags_NoMove |
	ImGuiWindowFlags_NoBringToFrontOnFocus |
	ImGuiWindowFlags_NoNavFocus;

void InitDevGui(const Window::WindowContext* ctx)
{
	if (!ctx)
	{
		return;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(ctx->window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGuiIO& _io = ImGui::GetIO();
	_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void RegisterImGuiRenderFunction(const std::function<void(const float)>& renderFunction)
{
	p_ImGuiRenderFunctions.push_back(renderFunction);
}

void ShowDevGui(const float deltaTime)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	const auto _mainViewport = ImGui::GetMainViewport();
	const auto _mainDockspaceID = ImGui::GetID("Root Dockspace");
	ImGui::SetNextWindowPos(_mainViewport->WorkPos);
	ImGui::SetNextWindowSize(_mainViewport->WorkSize);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::Begin("##__root_dockspace", nullptr, MAIN_DOCK_WINDOW_FLAGS);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::DockSpace(_mainDockspaceID);

	for (auto& renderFunc : p_ImGuiRenderFunctions)
	{
		renderFunc(deltaTime);
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::EndFrame();
}

void Terminate()
{
	HV_LOG_INFO("Destroying ImGui Context...");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

}
