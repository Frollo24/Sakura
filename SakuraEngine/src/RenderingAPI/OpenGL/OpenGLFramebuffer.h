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

		virtual void Resize(uint32_t width, uint32_t height) override;

	private:
		void Recreate();

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_RenderTargetCount = 0;
	};
}