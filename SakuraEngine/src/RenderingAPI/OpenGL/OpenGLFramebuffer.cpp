#include "skrpch.h"
#include "OpenGLFramebuffer.h"

#include "OpenGLRenderPass.h"
#include "OpenGLTexture.h"
#include "Sakura/Core/Application.h"
#include "Sakura/Render/RenderDevice.h"

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
			m_RenderTargetCount++;
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

		GLenum fbStatus = glCheckNamedFramebufferStatus(m_RendererID, GL_FRAMEBUFFER);

		switch (fbStatus)
		{
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				SKR_CORE_ERROR("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: One of the framebuffer attachment points has not been configured correctly");
				break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				SKR_CORE_ERROR("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: The framebuffer does not have any image attached to it");
				break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
				SKR_CORE_ERROR("GL_FRAMEBUFFER_UNSUPPORTED: Implementation-dependent error");
				break;
			case GL_FRAMEBUFFER_COMPLETE:
				SKR_CORE_DEBUG("Framebuffer is complete");
				break;
			default:
				SKR_CORE_ERROR("Unhandled error code!");
		}

		SKR_CORE_ASSERT(fbStatus == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		m_RendererID = 0;
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		m_FramebufferDesc.Width = width;
		m_FramebufferDesc.Height = height;

		Recreate();
	}

	void OpenGLFramebuffer::Recreate()
	{
		std::vector<TextureDescription> resizedDescs;
		resizedDescs.reserve(m_RenderTargetCount);

		for (int i = 0; i < m_RenderTargetCount; i++)
		{
			Ref<Texture>& renderTarget = m_FramebufferDesc.RenderTargets[i];
			if (!renderTarget)
				break;

			TextureDescription newTexDesc{};
			newTexDesc.ImageExtent = { m_FramebufferDesc.Width, m_FramebufferDesc.Height, 1 };
			newTexDesc.ImageFormat = renderTarget->GetDescription().ImageFormat;
			resizedDescs.push_back(newTexDesc);

			// HACK: Every render resource should have a reference to the device that created it
			Application::Instance().GetWindow()->GetRenderInstance()->GetDevice()->DestroyTexture(renderTarget);
		}

		const auto& attachments = dynamic_cast<OpenGLRenderPass*>(m_FramebufferDesc.RenderPass.get())->GetOpenGLAttachments();
		for (int i = 0; i < m_RenderTargetCount; i++)
		{
			if (attachments[i] == GL_NONE)
				break;

			m_FramebufferDesc.RenderTargets[i] = Application::Instance().GetWindow()->GetRenderInstance()->GetDevice()->CreateTexture(resizedDescs[i]);
			glNamedFramebufferTexture(m_RendererID, attachments[i], dynamic_cast<OpenGLTexture*>(m_FramebufferDesc.RenderTargets[i].get())->GetRendererID(), 0);
		}
	}
}