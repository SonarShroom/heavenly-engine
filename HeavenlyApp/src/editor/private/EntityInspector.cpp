#include "EntityInspector.h"

namespace HeavenlyApp::Editor
{

void EntityInspector::DrawContents()
{
	for (auto& _inspector : componentInspectors)
	{
		if (ImGui::CollapsingHeader(_inspector->GetInspectorTitle().data(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			_inspector->InspectComponent();
		}
	}
}

}