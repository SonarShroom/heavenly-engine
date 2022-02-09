#include "GUI.h"

#include <iostream>

#include "LogManager.h"

namespace Heavenly::GUI
{

void GUISystem::Tick(float time_delta)
{
	HV_LOG_INFO("Ticking GUISystem with time_delta: {}", time_delta);
}

}
