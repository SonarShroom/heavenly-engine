#pragma once

#include <Heavenly.h>

#include "editor/GUI.h"

namespace HeavenlyApp::App
{

class Runtime : public Heavenly::Core::IAppRuntime
{
public:
	Runtime(Heavenly::Core::Engine& engine) : IAppRuntime(engine) {}

	void OnBoot(int argc, char** argv) override;
	void OnUpdate(const float deltaTime) override;
	void OnDrawImGui(const float deltaTime) override;

private:
	friend class Editor::WorldExplorer;

	Editor::GUI editor = Editor::GUI(*this);
	Heavenly::World::WorldAdmin* mainWorld = nullptr;
};

}