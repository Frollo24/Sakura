#pragma once

#include "Sakura/Windowing/WindowSystem.h"

namespace Sakura
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		Window* m_Window = nullptr;
		bool m_Running = true;
	};

	// To be defined by client
	Application* CreateApplication();
}