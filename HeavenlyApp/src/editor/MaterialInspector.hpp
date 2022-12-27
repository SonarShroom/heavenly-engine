#pragma once

#include "ComponentInspector.h"

namespace HeavenlyApp::Editor
{

class MaterialInspector : public IComponentInspector
{
	using CompT = Heavenly::World::MaterialComponent&;
public:
	MaterialInspector(CompT comp) : inspectedComponent(comp) { }
	constexpr std::string_view GetInspectorIcon() { return ""; }
	constexpr std::string_view GetInspectorTitle() { return "Material"; }
	void InspectComponent()
	{
		if (inspectedComponent.shader)
		{
			ImGui::Text("Material program ID: %d", inspectedComponent.shader->GetProgramID());
		}
		else
		{
			ImGui::TextUnformatted("No shader in material");
		}
	}

private:
	CompT inspectedComponent;
};

}