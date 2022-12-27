#pragma once

#include "ComponentInspector.h"

namespace HeavenlyApp::Editor
{

class RectInspector final : public IComponentInspector
{
	using CompT = Heavenly::World::RectComponent&;
public:
	RectInspector(CompT comp) : inspectedComponent(comp) { }
	constexpr std::string_view GetInspectorIcon() { return ""; }
	constexpr std::string_view GetInspectorTitle() final { return "Rect Renderer"; }
	void InspectComponent()
	{
		ImGui::TextUnformatted("Size: ");
		ImGui::SameLine();
		if (ImGui::DragFloat2("##comp_rect_size", glm::value_ptr(inspectedComponent.size))) {
			inspectedComponent.drawDirty = true;
		}
		ImGui::TextUnformatted("Color: ");
		ImGui::SameLine();
		if (ImGui::ColorEdit4("##comp_rect_color", glm::value_ptr(inspectedComponent.color))) {
			inspectedComponent.drawDirty = true;
		}
	}

private:
	CompT inspectedComponent;
};

}