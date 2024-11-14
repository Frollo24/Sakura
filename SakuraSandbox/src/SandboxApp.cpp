#define SAKURA_ENTRY_POINT
#include <SakuraEngine.h>
using namespace Sakura;

class SandboxApp : public Sakura::Application
{
public:
	SandboxApp()
	{
		Ref<RenderDevice> device = Renderer::GetDevice();

		float vertexBuffer[] = {
			-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};

		BufferDescription vertexDescription = {};
		vertexDescription.Type = BufferType::Vertex;
		vertexDescription.Size = sizeof(vertexBuffer);
		vertexDescription.Data = vertexBuffer;
		m_VertexBuffer = device->CreateBuffer(vertexDescription);

		int indexBuffer[] = {
			0, 1, 2, 2, 3, 0
		};

		BufferDescription indexDescription = {};
		indexDescription.Type = BufferType::Index;
		indexDescription.Size = sizeof(indexBuffer);
		indexDescription.Data = indexBuffer;
		m_IndexBuffer = device->CreateBuffer(indexDescription);

		m_InputBinding = {
			{ShaderDataType::Float2, "aPosition"},
			{ShaderDataType::Float3, "aColor"},
			{ShaderDataType::Float2, "aTexCoord"},
		};
		m_InputLayout = InputLayout::Create(std::vector<InputBinding>({ m_InputBinding }));

		TextureDescription textureDesc = {};
		textureDesc.ImageExtent = { 16, 16, 1 };
		textureDesc.ImageFormat = ImageFormat::RGBA8;
		textureDesc.GenerateMipmaps = false;
		textureDesc.FilterMode = TextureFilterMode::Nearest;
		m_Texture = device->CreateTexture(textureDesc);

		const uint32_t gray = 0x88888888;
		const uint32_t white = 0xffffffff;
		std::array<uint32_t, 16 * 16 > checkerboardPixels = { 0 };
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				checkerboardPixels[size_t(x * 16 + y)] = ((x % 2) ^ (y % 2)) ? white : gray;
			}
		}
		m_Texture->SetData(checkerboardPixels.data());

		ShaderSpecs vertexShader{};
		vertexShader.Filepath = "assets/shaders/TestTriangle.vert";
		vertexShader.Type = ShaderType::Vertex;
		ShaderSpecs fragmentShader{};
		fragmentShader.Filepath = "assets/shaders/TestTriangle.frag";
		fragmentShader.Type = ShaderType::Fragment;

		Ref<Shader> shader = device->CreateShader({ vertexShader, fragmentShader });

		PipelineState pipelineState{};
		pipelineState.InputLayout = m_InputLayout;
		m_Pipeline = device->CreatePipeline(pipelineState, shader);

		RenderPassDescription renderPassDesc = {};
		renderPassDesc.ClearValues[0].Color = { 1.0f, 0.6f, 0.3f, 1.0f };
		renderPassDesc.ClearValues[0].ClearFlags = ClearFlags::Color;
		renderPassDesc.Attachments[0] = AttachmentFormat::RGBA8;
		renderPassDesc.ClearValues[1].Color = { 0.2f, 1.0f, 0.5f, 1.0f };
		renderPassDesc.ClearValues[1].ClearFlags = ClearFlags::Color;
		renderPassDesc.Attachments[1] = AttachmentFormat::RGBA8;
		renderPassDesc.ClearValues[2].Depth = 1.0f;
		renderPassDesc.ClearValues[2].ClearFlags = ClearFlags::DepthStencil;
		renderPassDesc.Attachments[2] = AttachmentFormat::D32;
		renderPassDesc.IsSwapchainTarget = false;

		m_RenderPass = device->CreateRenderPass(renderPassDesc);

		uint32_t width = Application::Instance().GetWindow()->GetWidth();
		uint32_t height = Application::Instance().GetWindow()->GetHeight();

		TextureDescription framebufferTextureDesc = {};
		framebufferTextureDesc.ImageExtent = { width, height, 1 };
		framebufferTextureDesc.ImageFormat = ImageFormat::RGBA8;
		framebufferTextureDesc.GenerateMipmaps = false;
		framebufferTextureDesc.FilterMode = TextureFilterMode::Linear;
		Ref<Texture> framebufferColorTexture1 = device->CreateTexture(framebufferTextureDesc);
		Ref<Texture> framebufferColorTexture2 = device->CreateTexture(framebufferTextureDesc);
		framebufferTextureDesc.ImageFormat = ImageFormat::D32;
		Ref<Texture> framebufferDepthTexture = device->CreateTexture(framebufferTextureDesc);

		FramebufferDescription framebufferDesc = {};
		framebufferDesc.Width = width;
		framebufferDesc.Height = height;
		framebufferDesc.RenderTargets[0] = framebufferColorTexture1;
		framebufferDesc.RenderTargets[1] = framebufferColorTexture2;
		framebufferDesc.RenderTargets[2] = framebufferDepthTexture;
		framebufferDesc.RenderPass = m_RenderPass;
		m_Framebuffer = device->CreateFramebuffer(framebufferDesc);

		Renderer::SetScreenTexture(framebufferColorTexture1);
	}
	virtual ~SandboxApp() = default;

	void OnRender() override
	{
		uint32_t fbWidth = m_Framebuffer->GetDescription().Width;
		uint32_t fbHeight = m_Framebuffer->GetDescription().Height;

		Ref<RenderContext> context = Renderer::GetContext();
		context->BeginRenderPass(m_RenderPass);
		context->SetViewport(0, 0, fbWidth, fbHeight);
		context->BindPipeline(m_Pipeline);
		context->BindTexture(m_Texture, 0);
		context->SetInputLayout(m_InputLayout);
		context->BindVertexBuffer(m_VertexBuffer, m_InputBinding);
		context->BindIndexBuffer(m_IndexBuffer);
		context->DrawIndexed(6, 1, 0, 0, 0);
		context->EndRenderPass();

		Renderer::DrawToScreen();
	}

	void OnResize(uint32_t width, uint32_t height) override
	{
		m_Framebuffer->Resize(width, height);
		Renderer::SetScreenTexture(m_Framebuffer->GetDescription().RenderTargets[0]);
	}

private:
	Ref<Buffer> m_VertexBuffer = nullptr;
	Ref<Buffer> m_IndexBuffer = nullptr;
	Ref<InputLayout> m_InputLayout = nullptr;
	InputBinding m_InputBinding = {};
	Ref<Texture> m_Texture = nullptr;
	Ref<Pipeline> m_Pipeline = nullptr;
	Ref<RenderPass> m_RenderPass = nullptr;
	Ref<Framebuffer> m_Framebuffer = nullptr;
};

Sakura::Application* Sakura::CreateApplication()
{
	return new SandboxApp();
}