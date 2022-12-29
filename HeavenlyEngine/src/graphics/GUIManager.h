#pragma once

#include <filesystem>
#include <functional>
#include <vector>

#include <imgui.h>

namespace Heavenly::WindowSystem
{
	class Window;
}

namespace Heavenly::Graphics
{

class GUIManager
{
	constexpr static float DEFAULT_FONT_SIZE = 13.f;
public:
	explicit GUIManager(const WindowSystem::Window& window);
	~GUIManager();

	void MergeFont(const std::filesystem::path& path, const ImWchar* range, const float size = DEFAULT_FONT_SIZE);
	void RenderGUI(const float deltaTime = 0.0f);
	void RegisterImGUIRenderFunction(const std::function<void(const float)>& renderFunction);

private:
	ImGuiIO* imGuiIO = nullptr;
	std::vector<std::function<void(const float)>> imGuiRenderFunctions;
};

}
