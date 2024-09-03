#include "skrpch.h"
#include "Application.h"

#include "Sakura/Render/RenderContext.h"


namespace Sakura
{
	// TODO: abstract into renderer
	static Unique<RenderContext> s_RenderContext = nullptr;

	Application::Application()
	{
		WindowSystem::Init();
		m_Window = WindowSystem::Create();
		m_Window->SetEventCallback(SKR_BIND_EVENT_FN(OnEvent));

		s_RenderContext = RenderContext::Create();
		s_RenderContext->Init();
	}

	Application::~Application()
	{
		WindowSystem::Destroy(m_Window);
		WindowSystem::Shutdown();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			s_RenderContext->BeginFrame();
			// Render code...
			s_RenderContext->EndFrame();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		//SKR_CORE_TRACE("{0}", e);
		Log::GetCoreLogger()->trace("{0}", e);

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