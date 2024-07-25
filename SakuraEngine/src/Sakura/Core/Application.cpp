#include "Application.h"

namespace Sakura
{
	Application::Application()
	{
		WindowSystem::Init();
		m_Window = WindowSystem::CreateWindow();
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
			m_Running = !m_Window->ShouldClose();
		}
	}
}