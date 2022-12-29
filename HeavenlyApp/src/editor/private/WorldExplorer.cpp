#include "WorldExplorer.h"

#include "app/Runtime.h"

#include "EntityInspector.h"

namespace HeavenlyApp::Editor
{

void WorldExplorer::DrawContents()
{
	if (runtime.mainWorld)
	{
		runtime.mainWorld->IterateWorldEntities([&](Heavenly::World::Entity& e) -> void {
			if (ImGui::TreeNode(e.GetID().data()))
			{
				selectedEntity = &e;
				inspector.Inspect(&e);
				ImGui::TreePop();
			}
		});
	}
	
}

}