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
		Ref<RenderPass> SwapchainPass;
		Ref<Texture> ScreenTexture;
		Ref<Pipeline> ScreenPipeline;
	};
	static Unique<RendererData> s_RendererData = nullptr;

	void Renderer::Init()
	{
		s_RendererData = CreateUnique<RendererData>();
		s_RendererData->Device = Application::Instance().GetWindow()->GetRenderInstance()->GetDevice();
		s_RendererData->Context = Application::Instance().GetWindow()->GetRenderInstance()->GetContext();

		ShaderSpecs vertexShader{};
		vertexShader.Filepath = "assets/shaders/DrawToScreen.vert";
		vertexShader.Type = ShaderType::Vertex;
		ShaderSpecs fragmentShader{};
		fragmentShader.Filepath = "assets/shaders/DrawToScreen.frag";
		fragmentShader.Type = ShaderType::Fragment;

		Ref<Shader> shader = s_RendererData->Device->CreateShader({vertexShader, fragmentShader});

		PipelineState pipelineState{};
		s_RendererData->ScreenPipeline = s_RendererData->Device->CreatePipeline(pipelineState, shader);

		RenderPassDescription swapchainPassDesc = {};
		swapchainPassDesc.ClearValues[0].Color = { 0.0f, 0.0f, 0.0f, 1.0f };
		swapchainPassDesc.ClearValues[0].Depth = 1.0f;
		swapchainPassDesc.ClearValues[0].ClearFlags = ClearFlags::All;
		swapchainPassDesc.Attachments[0] = AttachmentFormat::RGBA8;  // TODO: retrieve and store swapchain format for OpenGL
		swapchainPassDesc.IsSwapchainTarget = true;

		s_RendererData->SwapchainPass = s_RendererData->Device->CreateRenderPass(swapchainPassDesc);
	}

	void Renderer::Shutdown()
	{
		s_RendererData = nullptr;
	}

	const Ref<RenderDevice>& Renderer::GetDevice()
	{
		return s_RendererData->Device;
	}

	const Ref<RenderContext>& Renderer::GetContext()
	{
		return s_RendererData->Context;
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		// sFramebuffer->Resize(width, height);
	}

	void Renderer::BeginFrame()
	{
		s_RendererData->Context->BeginFrame();
	}

	void Renderer::EndFrame()
	{
		s_RendererData->Context->EndFrame();
	}

	void Renderer::SetScreenTexture(const Ref<Texture>& screenTexture)
	{
		s_RendererData->ScreenTexture = screenTexture;
	}

	void Renderer::DrawToScreen()
	{
		uint32_t width = Application::Instance().GetWindow()->GetWidth();
		uint32_t height = Application::Instance().GetWindow()->GetHeight();

		s_RendererData->Context->BeginRenderPass(s_RendererData->SwapchainPass);
		s_RendererData->Context->SetViewport(0, 0, width, height);
		s_RendererData->Context->BindPipeline(s_RendererData->ScreenPipeline);
		s_RendererData->Context->BindTexture(s_RendererData->ScreenTexture, 0);
		s_RendererData->Context->Draw(6, 1, 0, 0);
		s_RendererData->Context->EndRenderPass();
	}
}