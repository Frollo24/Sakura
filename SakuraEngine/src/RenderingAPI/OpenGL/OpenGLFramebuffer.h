#pragma once
#include "Sakura/Render/Framebuffer.h"

namespace Sakura
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferDescription& desc);
		~OpenGLFramebuffer();

		inline uint32_t GetRendererID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID = 0;
	};
}