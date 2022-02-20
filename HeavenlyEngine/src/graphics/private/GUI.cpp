#include "GUI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "LogManager.h"
#include "Window.h"

namespace Heavenly::GUI
{

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
	ImGui_ImplOpenGL3_Init("#version 130");
}

void ShowDevGui()
{
	static bool _showDemoWindow = true;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	if (_showDemoWindow)
	{
		ImGui::ShowDemoWindow(&_showDemoWindow);
	}

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
