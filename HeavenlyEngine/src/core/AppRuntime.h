#pragma once

namespace Heavenly::Core
{

class AppRuntime
{
public:
	AppRuntime() = default;
	virtual ~AppRuntime() = default;

	virtual void OnBoot(int argc, char** argv) = 0;
	virtual void OnUpdate(const float deltaTime) = 0;
	virtual void OnDrawImGui(const float deltaTime) = 0;
};

}
