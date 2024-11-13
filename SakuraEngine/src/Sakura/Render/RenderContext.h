#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Render/InputLayout.h"
#include "Sakura/Render/Buffer.h"
#include "Sakura/Render/Pipeline.h"
#include "Sakura/Render/Texture.h"
#include "Sakura/Render/RenderPass.h"

namespace Sakura
{
	enum class RenderAPI
	{
		None,
		OpenGL
	};

	class RenderContext
	{
	public:
		virtual ~RenderContext() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		virtual void BeginRenderPass(const Ref<RenderPass>& renderPass) = 0;
		virtual void EndRenderPass() = 0;

		virtual void BindPipeline(const Ref<Pipeline>& pipeline) = 0;
		virtual void SetInputLayout(const Ref<InputLayout>& layout) = 0;
		virtual void BindVertexBuffer(const Ref<Buffer>& vertexBuffer, const InputBinding& binding) = 0;
		virtual void BindIndexBuffer(const Ref<Buffer>& indexBuffer) = 0;

		// HACK: Should update all descriptors at the same time
		virtual void BindTexture(const Ref<Texture>& texture, uint32_t binding) = 0;

		virtual void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) = 0;
		virtual void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, uint32_t firstInstance, uint32_t vertexOffset) = 0;

		inline static RenderAPI GetAPI() { return s_API; }
		static Ref<RenderContext> Create();

	private:
		inline static RenderAPI s_API = RenderAPI::OpenGL;
	};
}

