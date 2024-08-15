#include "skrpch.h"
#include "Window.h"

#include <GLFW/glfw3.h>

#include "Sakura/Events/WindowEvent.h"
#include "Sakura/Events/KeyEvent.h"
#include "Sakura/Events/MouseEvent.h"

namespace Sakura
{
	Window::Window(const WindowProps& props)
		: m_Data(props)
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
		glfwSetWindowUserPointer(m_NativeWindow, &m_Data);

		m_RenderInstance = RenderInstance::Create(m_NativeWindow);
		m_RenderInstance->Init();

		// Set GFLW callbacks
		glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event(data.Title);
			data.EventCallback(event);
			});

		glfwSetKeyCallback(m_NativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			static int repeatCount = 1;

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event((KeyCode)key, 0);
				data.EventCallback(event);
				repeatCount = 1;
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event((KeyCode)key);
				data.EventCallback(event);
				repeatCount = 1;
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event((KeyCode)key, repeatCount);
				data.EventCallback(event);
				repeatCount++;
				break;
			}
			}
			});

		glfwSetMouseButtonCallback(m_NativeWindow, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event((MouseCode)button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event((MouseCode)button);
				data.EventCallback(event);
				break;
			}
			}
			});

		glfwSetScrollCallback(m_NativeWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_NativeWindow, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
			});
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
		m_Data.VSync = enabled;
		m_RenderInstance->SetVSync(enabled);
	}
}