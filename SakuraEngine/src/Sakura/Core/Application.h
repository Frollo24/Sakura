#pragma once

#include "Sakura/Core/Log.h"
#include "Sakura/Core/Memory.h"
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

		virtual void OnRender() = 0;
		virtual void OnResize(uint32_t width, uint32_t height) {}

		inline const Unique<Window>& GetWindow() const { return m_Window; }
		inline static const Application& Instance() { return *s_Instance; }

	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		inline static Application* s_Instance = nullptr;
		Unique<Window> m_Window = nullptr;
		bool m_Running = true;
	};

	// To be defined by client
	Application* CreateApplication();
}