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

	void Renderer::Init()
	{
		s_RendererData = CreateUnique<RendererData>();
		s_RendererData->Device = Application::Instance().GetWindow()->GetRenderInstance()->GetDevice();
		s_RendererData->Context = Application::Instance().GetWindow()->GetRenderInstance()->GetContext();

		float vertexBuffer[] = {
			 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f
		};

		BufferDescription vertexDescription = {};
		vertexDescription.Type = BufferType::Vertex;
		vertexDescription.Size = sizeof(vertexBuffer);
		vertexDescription.Data = vertexBuffer;
		sVertexBuffer = s_RendererData->Device->CreateBuffer(vertexDescription);

		sInputBinding = {
			{ShaderDataType::Float2, "aPosition"},
			{ShaderDataType::Float3, "aColor"},
		};
		sInputLayout = InputLayout::Create(std::vector<InputBinding>({ sInputBinding }));
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