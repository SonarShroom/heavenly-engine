#include "editorgui.h"

#include <Heavenly.h>

namespace HeavenlyApp::App
{

bool p_showSceneExplorer = true;

void ShowMainMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open Scene", "", false, false); // TODO: Implement when scene load and unload is possible.
			if (ImGui::MenuItem("Exit Heavenly"))
			{
				Heavenly::Window::SetMainWindowShouldClose(true);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			ImGui::MenuItem("Entity Inspector", "", false, false); // TODO: Implement when scene load and unload is possible.
			ImGui::MenuItem("Scene Tree", NULL, &p_showSceneExplorer); // TODO: Implement when scene load and unload is possible.
			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();
}

void ShowSceneExplorer()
{
	if (ImGui::Begin("Scene Tree", &p_showSceneExplorer))
	{
		Heavenly::World::IterateWorldEntities(0, [](Heavenly::World::Entity* e) {
			if (ImGui::TreeNode(e->id.c_str()))
			{
				ImGui::TreePop();
			}	
		});
	}
	ImGui::End();
}

void ShowInspector()
{

}

}