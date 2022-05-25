#ifndef GUI_H_
#define GUI_H_

#include <functional>
#include <string>

namespace Heavenly::Window
{
struct WindowContext;
}

namespace Heavenly::GUI
{

void InitDevGui(const Window::WindowContext* ctx = nullptr);

void RegisterImGuiRenderFunction(const std::function<void(const float)>& renderFunction);

void ShowDevGui(const float deltaTime = 0.f);

void Terminate();

}

#endif //GUI_H_
