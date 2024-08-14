#include "WindowSystem.h"

#include <GLFW/glfw3.h>

namespace Sakura
{
	void WindowSystem::Init()
	{
		glfwInit();
	}

	void WindowSystem::Shutdown()
	{
		glfwTerminate();
	}

	Window* WindowSystem::Create(const WindowProps& props)
	{
		return new Window(props);
	}

	void WindowSystem::Destroy(Window* window)
	{
		delete window;
	}
}