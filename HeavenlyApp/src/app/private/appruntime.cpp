#include "appruntime.h"

#include <Heavenly.h>

#include "editorgui.h"

namespace HeavenlyApp::App
{

void OnBoot([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{

}

void OnUpdate([[maybe_unused]] const float deltaTime)
{

}

void OnDrawImGui([[maybe_unused]] const float deltaTime)
{
	ShowMainMenuBar();
	ShowSceneExplorer();
	ShowInspector();
}

}