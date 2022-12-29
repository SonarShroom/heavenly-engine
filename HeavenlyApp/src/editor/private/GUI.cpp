#include "GUI.h"

#include <Heavenly.h>

#include <IconsFontAwesome6.h>

#include "app/Runtime.h"

namespace HeavenlyApp::Editor
{

GUI::GUI(App::Runtime& runtime) : runtime(runtime) { }

void GUI::DrawMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open Scene", "", false, false); // TODO: Implement when scene load and unload is possible.
			if (ImGui::MenuItem("Exit Heavenly"))
			{
				runtime.engine.SetShouldTerminate(true);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			for (auto& _scope : scopes)
			{
				ImGui::MenuItem(_scope->GetTitle().data(), nullptr, &_scope->isOpen);
			}
			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();
}

void GUI::DrawScopes()
{
	for (auto& _scope : scopes)
	{
		_scope->Draw();
	}
}

}