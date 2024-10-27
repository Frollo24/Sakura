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
	};
	static Unique<RendererData> s_RendererData = nullptr;

	// HACK: these should be created on client side
	static Ref<Buffer> sVertexBuffer = nullptr;
	static Ref<InputLayout> sInputLayout = nullptr;
	static InputBinding sInputBinding = {};
	static Ref<Texture> sTexture = nullptr;
	static Ref<Pipeline> sPipeline = nullptr;
	static Ref<RenderPass> sRenderPass = nullptr;
	static Ref<Framebuffer> sFramebuffer = nullptr;

	void Renderer::Init()
	{
		s_RendererData = CreateUnique<RendererData>();
		s_RendererData->Device = Application::Instance().GetWindow()->GetRenderInstance()->GetDevice();
		s_RendererData->Context = Application::Instance().GetWindow()->GetRenderInstance()->GetContext();

		float vertexBuffer[] = {
			 0.0f,  0.5f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		};

		BufferDescription vertexDescription = {};
		vertexDescription.Type = BufferType::Vertex;
		vertexDescription.Size = sizeof(vertexBuffer);
		vertexDescription.Data = vertexBuffer;
		sVertexBuffer = s_RendererData->Device->CreateBuffer(vertexDescription);

		sInputBinding = {
			{ShaderDataType::Float2, "aPosition"},
			{ShaderDataType::Float3, "aColor"},
			{ShaderDataType::Float2, "aTexCoord"},
		};
		sInputLayout = InputLayout::Create(std::vector<InputBinding>({ sInputBinding }));

		TextureDescription textureDesc = {};
		textureDesc.ImageExtent = { 16, 16, 1 };
		textureDesc.ImageFormat = ImageFormat::RGBA8;
		textureDesc.GenerateMipmaps = false;
		textureDesc.FilterMode = TextureFilterMode::Nearest;
		sTexture = s_RendererData->Device->CreateTexture(textureDesc);

		const uint32_t gray = 0x88888888;
		const uint32_t white = 0xffffffff;
		std::array<uint32_t, 16 * 16 > checkerboardPixels = { 0 };
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				checkerboardPixels[size_t(x * 16 + y)] = ((x % 2) ^ (y % 2)) ? white : gray;
			}
		}
		sTexture->SetData(checkerboardPixels.data());

		ShaderSpecs vertexShader{};
		vertexShader.Filepath = "assets/shaders/TestTriangle.vert";
		vertexShader.Type = ShaderType::Vertex;
		ShaderSpecs fragmentShader{};
		fragmentShader.Filepath = "assets/shaders/TestTriangle.frag";
		fragmentShader.Type = ShaderType::Fragment;

		Ref<Shader> shader = s_RendererData->Device->CreateShader({vertexShader, fragmentShader});

		PipelineState pipelineState{};
		pipelineState.InputLayout = sInputLayout;
		sPipeline = s_RendererData->Device->CreatePipeline(pipelineState, shader);

		RenderPassDescription renderPassDesc = {};
		renderPassDesc.ClearValues[0].Color = {1.0f, 0.6f, 0.3f, 1.0f};
		renderPassDesc.ClearValues[0].ClearFlags = ClearFlags::Color;
		renderPassDesc.Attachments[0] = AttachmentFormat::RGBA8;
		renderPassDesc.ClearValues[1].Color = { 0.2f, 1.0f, 0.5f, 1.0f };
		renderPassDesc.ClearValues[1].ClearFlags = ClearFlags::Color;
		renderPassDesc.Attachments[1] = AttachmentFormat::RGBA8;
		renderPassDesc.ClearValues[2].Depth = 1.0f;
		renderPassDesc.ClearValues[2].ClearFlags = ClearFlags::DepthStencil;
		renderPassDesc.Attachments[2] = AttachmentFormat::D32;
		renderPassDesc.IsSwapchainTarget = false;

		sRenderPass = s_RendererData->Device->CreateRenderPass(renderPassDesc);

		TextureDescription framebufferTextureDesc = {};
		framebufferTextureDesc.ImageExtent = { 800, 600, 1 };
		framebufferTextureDesc.ImageFormat = ImageFormat::RGBA8;
		framebufferTextureDesc.GenerateMipmaps = false;
		framebufferTextureDesc.FilterMode = TextureFilterMode::Linear;
		Ref<Texture> framebufferColorTexture1 = s_RendererData->Device->CreateTexture(framebufferTextureDesc);
		Ref<Texture> framebufferColorTexture2 = s_RendererData->Device->CreateTexture(framebufferTextureDesc);
		framebufferTextureDesc.ImageFormat = ImageFormat::D32;
		Ref<Texture> framebufferDepthTexture = s_RendererData->Device->CreateTexture(framebufferTextureDesc);
		
		FramebufferDescription framebufferDesc = {};
		framebufferDesc.Width = 800;
		framebufferDesc.Height = 600;
		framebufferDesc.RenderTargets[0] = framebufferColorTexture1;
		framebufferDesc.RenderTargets[1] = framebufferColorTexture2;
		framebufferDesc.RenderTargets[2] = framebufferDepthTexture;
		framebufferDesc.RenderPass = sRenderPass;
		sFramebuffer = s_RendererData->Device->CreateFramebuffer(framebufferDesc);

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

	void Renderer::BeginFrame()
	{
		s_RendererData->Context->BeginFrame();
	}

	void Renderer::EndFrame()
	{
		s_RendererData->Context->EndFrame();
	}

	void Renderer::DrawTriangle()
	{
		s_RendererData->Context->BeginRenderPass(sRenderPass);
		s_RendererData->Context->BindPipeline(sPipeline);
		s_RendererData->Context->BindTexture(sTexture, 0);
		s_RendererData->Context->SetInputLayout(sInputLayout);
		s_RendererData->Context->BindVertexBuffer(sVertexBuffer, sInputBinding);
		s_RendererData->Context->Draw(3, 1, 0, 0);
		s_RendererData->Context->EndRenderPass();

		s_RendererData->Context->BeginRenderPass(s_RendererData->SwapchainPass);
		s_RendererData->Context->BindPipeline(sPipeline);
		s_RendererData->Context->BindTexture(sTexture, 0);
		s_RendererData->Context->SetInputLayout(sInputLayout);
		s_RendererData->Context->BindVertexBuffer(sVertexBuffer, sInputBinding);
		s_RendererData->Context->Draw(3, 1, 0, 0);
		s_RendererData->Context->EndRenderPass();
	}
}