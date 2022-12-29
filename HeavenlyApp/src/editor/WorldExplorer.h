#pragma once

#include "EditorScope.hpp"

#include <Heavenly.h>

#include <IconsFontAwesome6.h>

namespace HeavenlyApp::App
{
class Runtime;
}

namespace HeavenlyApp::Editor
{

class EntityInspector;

class WorldExplorer final : public IEditorScope
{
public:
	WorldExplorer(App::Runtime& runtime, EntityInspector& inspector) : runtime(runtime), inspector(inspector) { }

	inline constexpr std::string_view GetTitle() const final { return ICON_FA_GLOBE " World Explorer"; }

protected:
	void DrawContents() final;

private:
	App::Runtime& runtime;
	EntityInspector& inspector;

	Heavenly::World::Entity* selectedEntity = nullptr;
};

}