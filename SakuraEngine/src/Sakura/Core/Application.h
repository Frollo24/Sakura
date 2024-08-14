#pragma once

#include "Sakura/Core/Log.h"
#include "Sakura/Events/Event.h"
#include "Sakura/Events/WindowEvent.h"
#include "Sakura/Windowing/WindowSystem.h"

namespace Sakura
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		Window* m_Window = nullptr;
		bool m_Running = true;
	};

	// To be defined by client
	Application* CreateApplication();
}