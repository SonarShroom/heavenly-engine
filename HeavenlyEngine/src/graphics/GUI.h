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

void ShowDevGui();

void Terminate();
}

#endif //GUI_H_
