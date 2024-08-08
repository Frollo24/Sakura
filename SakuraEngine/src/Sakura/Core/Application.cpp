#include "Application.h"

#include <iostream>

namespace Sakura
{
	Application::Application()
	{
		WindowSystem::Init();
		m_Window = WindowSystem::CreateWindow();
		m_Window->SetEventCallback(SKR_BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
		WindowSystem::DestroyWindow(m_Window);
		WindowSystem::Shutdown();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		std::cout << e.ToString() << std::endl;

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(SKR_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(SKR_BIND_EVENT_FN(OnWindowResize));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Window->SetMinimized(true);
			return false;
		}

		m_Window->SetMinimized(false);
		return false;
	}
}