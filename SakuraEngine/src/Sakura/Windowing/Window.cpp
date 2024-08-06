#include "Window.h"

#include <GLFW/glfw3.h>

namespace Sakura
{
	Window::Window(const WindowProps& props)
		: m_WindowProps(props)
	{
#define OPENGL
#ifdef OPENGL
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif

		m_NativeWindow = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);

		m_RenderInstance = RenderInstance::Create(m_NativeWindow);
		m_RenderInstance->Init();
	}

	Window::~Window()
	{
		delete m_RenderInstance;
		m_RenderInstance = nullptr;
		glfwDestroyWindow(m_NativeWindow);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		m_RenderInstance->SwapBuffers();
	}

	void Window::SetVSync(bool enabled)
	{
		m_RenderInstance->SetVSync(enabled);
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_NativeWindow);
	}
}