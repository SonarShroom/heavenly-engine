#ifndef GUI_H_
#define GUI_H_

#include <functional>
#include <string>

namespace Heavenly::WindowSystem
{
	class Window;
}

namespace Heavenly::GUI
{

void InitDevGui(const WindowSystem::Window& window);

void RegisterImGuiRenderFunction(const std::function<void(const float)>& renderFunction);

void ShowDevGui(const float deltaTime = 0.f);

void Terminate();

}

#endif //GUI_H_
