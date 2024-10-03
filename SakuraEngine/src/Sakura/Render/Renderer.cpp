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

	// HACK: these should be created on client side
	static Ref<Buffer> sVertexBuffer = nullptr;
	static Ref<InputLayout> sInputLayout = nullptr;
	static InputBinding sInputBinding = {};
	static Ref<Texture> sTexture = nullptr;

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
		s_RendererData->Context->SetInputLayout(sInputLayout);
		s_RendererData->Context->BindVertexBuffer(sVertexBuffer, sInputBinding);
		s_RendererData->Context->Draw(3, 1, 0, 0);
	}
}