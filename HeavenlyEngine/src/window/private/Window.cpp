#include "Window.h"

#include "logging/LogManager.h"

namespace Heavenly::Window
{

bool m_isSystemInit = false;

WindowContext* m_mainWindowCtx = nullptr;

std::function<void(int, const char*)> m_windowErrorCallback;

void m_WindowErrorCaller(const int errorCode, const char* description)
{
	m_windowErrorCallback(errorCode, description);
}

bool Init()
{
	if (m_isSystemInit)
	{
		return true; // Already intialized correctly.
	}

	if (!glfwInit())
	{
		HV_LOG_ERROR("Could not init glfw. Exiting.");
		m_isSystemInit = false;
		return m_isSystemInit;
	}

	glfwSetErrorCallback(m_WindowErrorCaller);

	m_isSystemInit = true;
	return m_isSystemInit;
}

void CreateWindow(const std::string& name, const Math::Vector2& size, const WindowMode& mode)
{
	if (!m_isSystemInit)
	{
		HV_LOG_ERROR("Cannot create window when window system is not initialized. Check the console.");
		return;
	}

	if (m_mainWindowCtx)
	{
		HV_LOG_ERROR("Main window is already created.");
		return;
	}
	
	if (!m_windowErrorCallback)
	{
		SetWindowErrorCallback([](const int errorCode, const char* description) {
			HV_LOG_ERROR("Window error {}: {}", errorCode, description);
		});
	}
	
	m_mainWindowCtx = new WindowContext();

	m_mainWindowCtx->name = name;
	m_mainWindowCtx->size = size;
	m_mainWindowCtx->mode = mode;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	switch (mode)
	{
		case WindowMode::WINDOWED:
		{
			m_mainWindowCtx->window = glfwCreateWindow(size.x, size.y, name.c_str(), nullptr, nullptr);
		} break;
		case WindowMode::BORDERLESS_FULLSCREEN:
		{
		} break;
		case WindowMode::FULLSCREEN:
		{
			auto* _primaryMonitor = glfwGetPrimaryMonitor();
			m_mainWindowCtx->window = glfwCreateWindow(size.x, size.y, name.c_str(), _primaryMonitor, nullptr);
		} break;
		default: break;
	}
	
	if (!m_mainWindowCtx->window)
	{
		HV_LOG_INFO("Could not create glfw window. Exiting.");
		glfwTerminate();
		delete m_mainWindowCtx;
		return;
	}
	
	glfwMakeContextCurrent(m_mainWindowCtx->window);

	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		HV_LOG_INFO("Could not initialize GLAD. Exiting.");
		glfwTerminate();
		delete m_mainWindowCtx;
		return;
	}

	HV_LOG_INFO("OpenGL initialized. Version: {}", glGetString(GL_VERSION));

	glViewport(0, 0, size.x, size.y);
}

const WindowContext* GetWindowContext()
{
	return m_mainWindowCtx;
}

void SetWindowErrorCallback(const std::function<void(int, const char*)>& errorCallback)
{
	if (!errorCallback)
	{
		HV_LOG_ERROR("Attempted to set window error callback with an empty function.");
		return;
	}
	m_windowErrorCallback = errorCallback;
}

void SetMainWindowShouldClose(const bool shouldClose)
{
	glfwSetWindowShouldClose(m_mainWindowCtx->window, shouldClose);
}

bool ShouldClose()
{
	return glfwWindowShouldClose(m_mainWindowCtx->window) == GLFW_TRUE;
}

void SwapBuffers()
{
	glfwSwapBuffers(m_mainWindowCtx->window);
}

void PollEvents()
{
	glfwPollEvents();
}

void Terminate()
{
	if (m_mainWindowCtx->window)
	{
		glfwDestroyWindow(m_mainWindowCtx->window);
	}

	glfwTerminate();
	
	delete m_mainWindowCtx;
	m_isSystemInit = false;
}

}