#include "Window.h"

#include "logging/LogManager.h"

namespace Heavenly::WindowSystem
{

bool p_isGLFWInitialized = false;

void p_windowErrorCaller(const int errorCode, const char* description)
{
	HV_LOG_ERROR("Window error {}: {}", errorCode, description);
}

bool Init()
{
	if (p_isGLFWInitialized)
	{
		return true; // Already intialized correctly.
	}

	if (!glfwInit())
	{
		HV_LOG_ERROR("Could not init glfw. Exiting.");
		p_isGLFWInitialized = false;
		return p_isGLFWInitialized;
	}

	glfwSetErrorCallback(p_windowErrorCaller);

	p_isGLFWInitialized = true;
	return p_isGLFWInitialized;
}

void Terminate()
{
	glfwTerminate();

	p_isGLFWInitialized = false;
}

Window::Window(const std::string& name, const glm::vec2& size, const Mode& mode) : name(name), size(size), mode(mode)
{
	if (!p_isGLFWInitialized)
	{
		HV_LOG_ERROR("Cannot create window when window system is not initialized. Check the console.");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	switch (mode)
	{
		case Mode::WINDOWED:
		{
			window = glfwCreateWindow((int)size.x, (int)size.y, name.c_str(), nullptr, nullptr);
		} break;
		case Mode::BORDERLESS_FULLSCREEN:
		{
		} break;
		case Mode::FULLSCREEN:
		{
			auto* _primaryMonitor = glfwGetPrimaryMonitor();
			window = glfwCreateWindow((int)size.x, (int)size.y, name.c_str(), _primaryMonitor, nullptr);
		} break;
		default: break;
	}
	
	if (!window)
	{
		HV_LOG_INFO("Could not create glfw window. Exiting.");
		return;
	}
	
	if (!glfwGetCurrentContext())
	{
		SetAsCurrentContext();
	}
}

Window::~Window()
{
	if (window)
	{
		glfwDestroyWindow(window);
	}
}

void Window::SetShouldClose(const bool shouldClose)
{
	glfwSetWindowShouldClose(window, shouldClose);
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(window) == GLFW_TRUE;
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

}