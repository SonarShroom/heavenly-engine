#pragma once

#include "EditorScope.hpp"

#include <typeinfo>
#include <typeindex>

#include <Heavenly.h>

#include <IconsFontAwesome6.h>

#include "ComponentInspector.h"
#include "private/MaterialInspector.hpp"
#include "private/TransformInspector.hpp"
#include "private/RenderPrimitiveInspector.hpp"

namespace HeavenlyApp::Editor
{

class EntityInspector final : public IEditorScope
{
public:
	explicit EntityInspector()
	{
		RegisterInspector<Heavenly::World::TransformComponent, TransformInspector>();
		RegisterInspector<Heavenly::World::RectComponent, RectInspector>();
		RegisterInspector<Heavenly::World::MaterialComponent, MaterialInspector>();
	}

	inline constexpr std::string_view GetTitle() const final { return ICON_FA_MAGNIFYING_GLASS " Inspector"; }

	template <Heavenly::World::ComponentType C, InspectorType I>
	void RegisterInspector() {
		inspectorFactory[typeid(C&)] = [](Heavenly::World::Component& comp) {
			return std::unique_ptr<IComponentInspector>(new I(dynamic_cast<C&>(comp)));
		};
	}

	void Inspect(Heavenly::World::Entity* entity)
	{
		componentInspectors.clear();
		if (entity)
		{
			for (auto& _comp : entity->GetComponents())
			{
				auto& _compRef = _comp.get();
				std::type_index _type = typeid(_compRef);
				componentInspectors.push_back(inspectorFactory[_type](_compRef));
			}
		}
	}

protected:
	void DrawContents() final;

private:
	std::vector<std::unique_ptr<IComponentInspector>> componentInspectors;
	std::unordered_map<
		std::type_index,
		std::function<std::unique_ptr<IComponentInspector>(Heavenly::World::Component&)>
	> inspectorFactory;
};

}