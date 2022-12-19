#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "math/MathBaseTypes.h"

namespace Heavenly::WindowSystem
{

bool Init();

void Terminate();

class Window
{
public:
	enum class Mode : int
	{
		WINDOWED = 0,
		BORDERLESS_FULLSCREEN,
		FULLSCREEN
	};

	Window(const std::string& name, const Math::Vector2& size, const Mode& mode);
	~Window();

	inline bool IsWindowCreated() { return window != nullptr; }

	inline GLFWwindow* GetContext() const { return window; }
	inline void SetAsCurrentContext() { glfwMakeContextCurrent(window); }

	inline const Math::Vector2& GetWindowSize() { return size; }

	void SetShouldClose(const bool shouldClose);
	bool ShouldClose();

	void SwapBuffers();
	void PollEvents();

private:
	std::string name = "Heavenly Game Engine";
	Math::Vector2 size = { 1280, 720 };
	Mode mode = Mode::WINDOWED;

	GLFWwindow* window = nullptr;
};

}