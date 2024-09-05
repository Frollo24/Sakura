#include "skrpch.h"
#include "Renderer.h"

#include "Sakura/Core/Application.h"
#include "Sakura/Render/RenderInstance.h"
#include "Sakura/Render/RenderDevice.h"
#include "Sakura/Render/RenderContext.h"

namespace Sakura
{
	struct RendererData
	{
		Ref<RenderDevice> Device;
		Ref<RenderContext> Context;
	};
	static Unique<RendererData> s_RendererData = nullptr;

	void Renderer::Init()
	{
		s_RendererData = CreateUnique<RendererData>();
		s_RendererData->Device = Application::Instance().GetWindow()->GetRenderInstance()->GetDevice();
		s_RendererData->Context = Application::Instance().GetWindow()->GetRenderInstance()->GetContext();
	}

	void Renderer::Shutdown()
	{
		s_RendererData = nullptr;
	}

	void Renderer::BeginFrame()
	{
		s_RendererData->Context->BeginFrame();
	}

	void Renderer::EndFrame()
	{
		s_RendererData->Context->EndFrame();
	}
}