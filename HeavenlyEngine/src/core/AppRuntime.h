#pragma once

namespace Heavenly::Core
{

struct AppRuntime
{
	using BootFunc = void(*)(int argc, char** argv);
	using UpdateFunc = void(*)(const float deltaTime);
	using DrawImGuiFunc = void(*)(const float deltaTime);

	BootFunc bootFunction = nullptr;
	UpdateFunc updateFunction = nullptr;
	DrawImGuiFunc drawImGuiFunction = nullptr;
};

}
