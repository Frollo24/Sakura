#pragma once
#include "Sakura/Render/RenderPass.h"

typedef unsigned int GLenum;

namespace Sakura
{
	class OpenGLRenderPass : public RenderPass
	{
	public:
		OpenGLRenderPass(const RenderPassDescription& desc);
		virtual ~OpenGLRenderPass();

		inline const std::array<GLenum, MAX_TOTAL_ATTACHMENTS>& GetOpenGLAttachments() const { return m_Attachments; }
		inline uint32_t GetRendererID() const { return m_RendererID; }

	private:
		std::array<GLenum, MAX_TOTAL_ATTACHMENTS> m_Attachments{};
		uint32_t m_RendererID = 0;
	};
}

