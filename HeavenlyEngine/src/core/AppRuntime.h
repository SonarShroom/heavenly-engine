#pragma once

namespace Heavenly::Core
{

class Engine;

class AppRuntime
{
public:
	AppRuntime(Engine& engine) : engine(engine) { }
	virtual ~AppRuntime() = default;

	virtual void OnBoot(int argc, char** argv) = 0;
	virtual void OnUpdate(const float deltaTime) = 0;
	virtual void OnDrawImGui(const float deltaTime) = 0;

	Engine& engine;
};

}
