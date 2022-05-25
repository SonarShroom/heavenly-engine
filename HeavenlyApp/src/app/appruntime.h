#pragma once

#include "Heavenly.h"

namespace HeavenlyApp::App
{

class Runtime : public Heavenly::Core::AppRuntime
{
public:
	void OnBoot(int argc, char** argv) override;
	void OnUpdate(const float deltaTime) override;
	void OnDrawImGui(const float deltaTime) override;
};

}