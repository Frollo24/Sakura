#include "skrpch.h"
#include "Application.h"

#include "Sakura/Render/Renderer.h"


namespace Sakura
{
	Application::Application()
	{
		s_Instance = this;
		WindowSystem::Init();
		m_Window = WindowSystem::Create();
		m_Window->SetEventCallback(SKR_BIND_EVENT_FN(OnEvent));

		Renderer::Init();
	}

	Application::~Application()
	{
		Renderer::Shutdown();

		WindowSystem::Destroy(m_Window);
		WindowSystem::Shutdown();
		s_Instance = nullptr;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			Renderer::BeginFrame();
			this->OnRender();
			Renderer::EndFrame();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		SKR_CORE_TRACE("{0}", e);

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
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		this->OnResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}