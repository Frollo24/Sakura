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
	};
}

