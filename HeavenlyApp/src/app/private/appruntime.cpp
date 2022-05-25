#include "appruntime.h"

#include <Heavenly.h>

#include "editorgui.h"

namespace HeavenlyApp::App
{

void Runtime::OnBoot([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{

}

void Runtime::OnUpdate([[maybe_unused]] const float deltaTime)
{

}

void Runtime::OnDrawImGui([[maybe_unused]] const float deltaTime)
{
	// ImGui::ShowDemoWindow();
	ShowMainMenuBar();
	ShowSceneExplorer();
	ShowInspector();
}

}