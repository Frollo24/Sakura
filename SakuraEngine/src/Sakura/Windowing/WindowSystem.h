#pragma once

#include "Window.h"

namespace Sakura
{
	class WindowSystem
	{
	public:
		static void Init();
		static void Shutdown();

		static Unique<Window> Create(const WindowProps& props = WindowProps{});
		static void Destroy(Unique<Window>& window);
	};

}

