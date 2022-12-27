#pragma once

#include <functional>
#include <memory>
#include <string_view>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <Heavenly.h>

#include "ComponentInspector.h"

namespace HeavenlyApp::App
{
class Runtime;
}

namespace HeavenlyApp::Editor
{

class IAppWindow {
public:
	
	constexpr IAppWindow(const std::string_view& title) : title(title) {}

	virtual void Draw() = 0;
	
	const std::string_view& GetTitle() const {
		return title;
	}

	bool IsOpen() const {
		return isOpen;
	}

private:

	const std::string_view title;
	bool isOpen = true;
};

class IAppScope {
public:
	IAppScope();

private:

};

class GUI
{
public:
	GUI(App::Runtime& runtime) ;

	void ShowMainMenuBar();

	void ShowSceneExplorer();

	void ShowInspector();

	template <Heavenly::World::ComponentType C, InspectorType I>
	void RegisterInspector() {
		inspectorFactory[typeid(C&)] = [](Heavenly::World::Component& comp) {
			return std::unique_ptr<IComponentInspector>(new I(dynamic_cast<C&>(comp)));
		};
	}

private:
	App::Runtime& runtime;

	bool showSceneExplorer = true;
	Heavenly::World::Entity* selectedEntity = nullptr;
	std::vector<std::unique_ptr<IComponentInspector>> componentInspectors;
	std::unordered_map<
		std::type_index,
		std::function<std::unique_ptr<IComponentInspector>(Heavenly::World::Component&)>
	> inspectorFactory;
};

}