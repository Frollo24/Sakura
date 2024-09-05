#pragma once

#include "Sakura/Core/Base.h"

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
		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void BeginFrame() = 0;
		virtual void EndFrame() = 0;

		inline static RenderAPI GetAPI() { return s_API; }
		static Ref<RenderContext> Create();

	private:
		inline static RenderAPI s_API = RenderAPI::OpenGL;
	};
}

