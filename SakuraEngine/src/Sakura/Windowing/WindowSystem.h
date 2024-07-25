#pragma once

#include "Window.h"

namespace Sakura
{
	class WindowSystem
	{
	public:
		static void Init();
		static void Shutdown();

		static Window* CreateWindow(const WindowProps& props = WindowProps{});
		static void DestroyWindow(Window* window);
	};

}

