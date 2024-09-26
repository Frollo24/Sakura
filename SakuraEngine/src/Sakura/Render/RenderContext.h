#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Render/InputLayout.h"
#include "Sakura/Render/Buffer.h"

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

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		virtual void SetInputLayout(const Ref<InputLayout>& layout) = 0;
		virtual void BindVertexBuffer(const Ref<Buffer>& vertexBuffer, const InputBinding& binding) = 0;
		virtual void BindIndexBuffer(const Ref<Buffer>& indexBuffer) = 0;

		virtual void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) = 0;

		inline static RenderAPI GetAPI() { return s_API; }
		static Ref<RenderContext> Create();

	private:
		inline static RenderAPI s_API = RenderAPI::OpenGL;
	};
}

