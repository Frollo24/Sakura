#include "Window.h"

#include <GLFW/glfw3.h>

namespace Sakura
{
	Window::Window(const WindowProps& props)
		: m_WindowProps(props)
	{
		m_NativeWindow = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_NativeWindow);
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_NativeWindow);
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_NativeWindow);
	}
}