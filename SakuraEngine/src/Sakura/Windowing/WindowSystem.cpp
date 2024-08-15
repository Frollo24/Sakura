#include "skrpch.h"
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

	Unique<Window> WindowSystem::Create(const WindowProps& props)
	{
		return CreateUnique<Window>(props);
	}

	void WindowSystem::Destroy(Unique<Window>& window)
	{
		window = nullptr;
	}
}