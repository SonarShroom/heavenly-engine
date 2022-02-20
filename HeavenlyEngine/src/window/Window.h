#pragma once

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "MathBaseTypes.h"

namespace Heavenly::Window
{

enum class WindowMode : int
{
	WINDOWED = 0,
	BORDERLESS_FULLSCREEN,
	FULLSCREEN
};

struct WindowContext
{
	GLFWwindow* window = nullptr;
	std::string name;
	Math::Vector2<int> size;
	WindowMode mode = WindowMode::WINDOWED;
};

bool Init();

void CreateWindow(
	const std::string& name = "Heavenly Game Engine",
	const Math::Vector2<int>& size = Math::Vector2(1280, 720),
	const WindowMode& mode = WindowMode::WINDOWED
);

const WindowContext* GetWindowContext();

void SetWindowErrorCallback(const std::function<void(int, const char*)>& errorCallback);

bool ShouldClose();

void SwapBuffers();

void PollEvents();

void Terminate();

}