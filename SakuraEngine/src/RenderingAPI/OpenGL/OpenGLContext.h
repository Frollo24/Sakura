#pragma once
#include "Sakura/Render/RenderContext.h"

namespace Sakura
{
	class OpenGLContext : public RenderContext
	{
	public:
		OpenGLContext() = default;
		virtual ~OpenGLContext() = default;

		virtual void Init() override;
		virtual void Shutdown() override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void BeginRenderPass(const Ref<RenderPass>& renderPass) override;
		virtual void EndRenderPass() override;

		virtual void BindPipeline(const Ref<Pipeline>& pipeline) override;
		virtual void SetInputLayout(const Ref<InputLayout>& layout) override;
		virtual void BindVertexBuffer(const Ref<Buffer>& vertexBuffer, const InputBinding& binding) override;
		virtual void BindIndexBuffer(const Ref<Buffer>& indexBuffer) override;

		virtual void BindTexture(const Ref<Texture>& texture, uint32_t binding) override;

		virtual void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) override;
		virtual void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, uint32_t firstInstance, uint32_t vertexOffset) override;

	private:
		uint32_t m_BoundVertexArray = 0;
	};
}

