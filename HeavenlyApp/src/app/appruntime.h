#pragma once

#include <Heavenly.h>

#include "editorgui.h"

namespace HeavenlyApp::App
{

class Runtime : public Heavenly::Core::AppRuntime
{
public:
	Runtime(Heavenly::Core::Engine& engine) : AppRuntime(engine) {}

	void OnBoot(int argc, char** argv) override;
	void OnUpdate(const float deltaTime) override;
	void OnDrawImGui(const float deltaTime) override;

private:
	friend EditorGUI;

	EditorGUI editor = EditorGUI(*this);
	Heavenly::World::WorldAdmin& mainWorld = engine.CreateWorld();
};

}