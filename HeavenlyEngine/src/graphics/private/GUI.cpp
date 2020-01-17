#include "GUI.h"

#include <iostream>

using namespace Heavenly::GUI;

void GUISystem::Tick(float time_delta)
{
    std::cout << "Ticking GUISystem with time_delta: " << time_delta << std::endl;
}