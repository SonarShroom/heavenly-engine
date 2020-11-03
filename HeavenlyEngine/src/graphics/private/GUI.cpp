#include "GUI.h"

#include <iostream>

#include "LogManager.h"

using namespace Heavenly::GUI;

void GUISystem::Tick(float time_delta)
{
    HV_LOG_INFO("GUI", "Ticking GUISystem with time_delta: {}", time_delta);
}