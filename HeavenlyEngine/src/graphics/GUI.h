#ifndef GUI_H_
#define GUI_H_

#include <string>

namespace Heavenly::Rendering
{
struct RenderContext;
}

namespace Heavenly::GUI
{
void InitDevGui(Rendering::RenderContext* ctx);

void ShowDevGui();

void Terminate();
}

#endif //GUI_H_
