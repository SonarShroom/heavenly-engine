#pragma once

#include <functional>
#include <vector>

namespace Heavenly::WindowSystem
{
	class Window;
}

namespace Heavenly::Graphics
{

class GUIManager
{
public:
	explicit GUIManager(const WindowSystem::Window& window);
	~GUIManager();

	void RenderGUI(const float deltaTime = 0.0f);
	void RegisterImGUIRenderFunction(const std::function<void(const float)>& renderFunction);

private:
	std::vector<std::function<void(const float)>> imGuiRenderFunctions;
};

}
