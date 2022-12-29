#pragma once

#include <array>
#include <functional>
#include <memory>
#include <string_view>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <Heavenly.h>

#include "EditorScope.hpp"
#include "EntityInspector.h"
#include "WorldExplorer.h"

namespace HeavenlyApp::App
{
class Runtime;
}

namespace HeavenlyApp::Editor
{

class GUI
{
public:
	GUI(App::Runtime& runtime);

	void DrawMenuBar();

	void DrawScopes();

private:
	App::Runtime& runtime;

	bool showSceneExplorer = true;
	Heavenly::World::Entity* selectedEntity = nullptr;
	
	EntityInspector entityInspector;
	WorldExplorer worldExplorer = WorldExplorer(runtime, entityInspector);
	std::array<IEditorScope*, 2> scopes = {&entityInspector, &worldExplorer};
};

}