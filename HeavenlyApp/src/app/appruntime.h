#pragma once

namespace HeavenlyApp::App
{

void OnBoot(int argc, char** argv);

void OnUpdate(const float deltaTime);

void OnDrawImGui(const float deltaTime);

}