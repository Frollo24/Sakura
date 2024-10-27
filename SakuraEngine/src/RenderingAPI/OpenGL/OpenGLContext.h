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

		virtual void BeginRenderPass(const Ref<RenderPass>& renderPass) override;
		virtual void EndRenderPass() override;

		virtual void BindPipeline(const Ref<Pipeline>& pipeline) override;
		virtual void SetInputLayout(const Ref<InputLayout>& layout) override;
		virtual void BindVertexBuffer(const Ref<Buffer>& vertexBuffer, const InputBinding& binding) override;
		virtual void BindIndexBuffer(const Ref<Buffer>& indexBuffer) override;

		virtual void BindTexture(const Ref<Texture>& texture, uint32_t binding) override;

		virtual void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) override;

	private:
		uint32_t m_BoundVertexArray = 0;
	};
}

