#pragma once

namespace Heavenly::Core
{

class Engine;

class IAppRuntime
{
public:
	IAppRuntime(Engine& engine) : engine(engine) { }
	virtual ~IAppRuntime() = default;

	virtual void OnBoot(int argc, char** argv) = 0;
	virtual void OnUpdate(const float deltaTime) = 0;
	virtual void OnDrawImGui(const float deltaTime) = 0;

	Engine& engine;
};

}
