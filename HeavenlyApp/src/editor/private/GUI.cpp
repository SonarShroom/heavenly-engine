#include "GUI.h"

#include <Heavenly.h>

#include <IconsFontAwesome6.h>

#include "app/Runtime.h"

#include "MaterialInspector.hpp"
#include "TransformInspector.hpp"
#include "RenderPrimitiveInspector.hpp"

namespace HeavenlyApp::Editor
{

GUI::GUI(App::Runtime& runtime) : runtime(runtime)
{
	RegisterInspector<Heavenly::World::TransformComponent, TransformInspector>();
	RegisterInspector<Heavenly::World::RectComponent, RectInspector>();
	RegisterInspector<Heavenly::World::MaterialComponent, MaterialInspector>();
}

void GUI::ShowMainMenuBar()
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
			ImGui::MenuItem("Entity Inspector", "", false, false); // TODO: Implement when scene load and unload is possible.
			ImGui::MenuItem("Scene Tree", NULL, &showSceneExplorer); // TODO: Implement when scene load and unload is possible.
			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();
}

void GUI::ShowSceneExplorer()
{
	if (ImGui::Begin(ICON_FA_GLOBE " Scene Tree", &showSceneExplorer))
	{
		runtime.mainWorld->IterateWorldEntities([&](Heavenly::World::Entity& e) -> void {
			if (ImGui::TreeNode(e.GetID().data()))
			{
				selectedEntity = &e;
				componentInspectors.clear();
				for (auto& _comp : e.GetComponents())
				{
					auto& _compRef = _comp.get();
					std::type_index _type = typeid(_compRef);
					componentInspectors.push_back(inspectorFactory[_type](_compRef));
				}
				ImGui::TreePop();
			}
		});
	}
	ImGui::End();
}

void GUI::ShowInspector()
{
	if (ImGui::Begin(ICON_FA_MAGNIFYING_GLASS " Inspector"))
	{
		for (auto& _inspector : componentInspectors)
		{
			if (ImGui::CollapsingHeader(_inspector->GetInspectorTitle().data(), ImGuiTreeNodeFlags_DefaultOpen))
			{
				_inspector->InspectComponent();
			}
		}
	}
	ImGui::End();
}

}