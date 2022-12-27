#pragma once

#include "ComponentInspector.h"

namespace HeavenlyApp::Editor
{

class TransformInspector final : public IComponentInspector
{
	using CompT = Heavenly::World::TransformComponent&;
public:
	TransformInspector(CompT comp) : inspectedComponent(comp) { }
	constexpr std::string_view GetInspectorIcon() { return ""; }
	constexpr std::string_view GetInspectorTitle() final { return "Transform"; }
	void InspectComponent()
	{
		ImGui::TextUnformatted("Position: ");
		ImGui::SameLine();
		ImGui::DragFloat3("##comp_transform_position", glm::value_ptr(inspectedComponent.position));
		ImGui::TextUnformatted("Rotation: ");
		ImGui::SameLine();
		ImGui::DragFloat3("##comp_transform_rotation", glm::value_ptr(inspectedComponent.rotation));
		ImGui::TextUnformatted("Scale: ");
		ImGui::SameLine();
		ImGui::DragFloat2("##comp_transform_scale", glm::value_ptr(inspectedComponent.scale));
	}

private:
	CompT inspectedComponent;
};

}