#include "editorgui.h"

#include <Heavenly.h>

#include "appruntime.h"

namespace HeavenlyApp::App
{

void EditorGUI::ShowMainMenuBar()
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
			ImGui::MenuItem("Scene Tree", NULL, &showSceneExplorer); // TODO: Implement when scene load and unload is possible.
			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();
}

void EditorGUI::ShowSceneExplorer()
{
	if (ImGui::Begin("Scene Tree", &showSceneExplorer))
	{
		runtime.mainWorld.IterateWorldEntities([](Heavenly::World::Entity& e) {
			if (ImGui::TreeNode(e.GetID().data()))
			{
				ImGui::TreePop();
			}
		});
	}
	ImGui::End();
}

void EditorGUI::ShowInspector()
{

}

}