#ifndef GUI_H_
#define GUI_H_

#include <string>

namespace Heavenly::Window
{
struct WindowContext;
}

namespace Heavenly::GUI
{

void InitDevGui(const Window::WindowContext* ctx = nullptr);

void RegisterImGuiRenderFunction(void(*renderFunction)(const float));

void ShowDevGui(const float deltaTime = 0.f);

void Terminate();

}

#endif //GUI_H_
