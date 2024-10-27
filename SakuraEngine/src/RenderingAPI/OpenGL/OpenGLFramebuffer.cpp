#include "skrpch.h"
#include "OpenGLFramebuffer.h"

#include "OpenGLRenderPass.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>

namespace Sakura
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferDescription& desc)
		: Framebuffer(desc)
	{
		m_RendererID = dynamic_cast<OpenGLRenderPass*>(desc.RenderPass.get())->GetRendererID();

		const auto& attachments = dynamic_cast<OpenGLRenderPass*>(desc.RenderPass.get())->GetOpenGLAttachments();
		for (size_t i = 0; i < attachments.size(); i++)
		{
			if (attachments[i] == GL_NONE)
				break;

			glNamedFramebufferTexture(m_RendererID, attachments[i], dynamic_cast<OpenGLTexture*>(desc.RenderTargets[i].get())->GetRendererID(), 0);
		}

		GLsizei drawbufferCount = 0;
		for (const GLenum attachment : attachments)
		{
			if (attachment == GL_NONE)
				break;

			if (attachment == GL_DEPTH_STENCIL_ATTACHMENT || attachment == GL_DEPTH_ATTACHMENT || attachment == GL_STENCIL_ATTACHMENT)
				continue;

			drawbufferCount++;
		}

		if (drawbufferCount)
		{
			std::array<GLenum, MAX_COLOR_ATTACHMENTS> drawbuffers = {
				GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
				GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7
			};
			glNamedFramebufferDrawBuffers(m_RendererID, drawbufferCount, drawbuffers.data());
		}
		else
		{
			glNamedFramebufferDrawBuffer(m_RendererID, GL_NONE);
		}

		SKR_CORE_ASSERT(glCheckNamedFramebufferStatus(m_RendererID, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		// TODO: Add extensive completeness status logging
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		m_RendererID = 0;
	}
}