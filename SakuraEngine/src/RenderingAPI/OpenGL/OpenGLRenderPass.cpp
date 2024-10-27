#include "skrpch.h"
#include "OpenGLRenderPass.h"

#include <glad/glad.h>

namespace Sakura
{
	OpenGLRenderPass::OpenGLRenderPass(const RenderPassDescription& desc)
		: RenderPass(desc)
	{
		if (m_RenderPassDesc.IsSwapchainTarget) 
			return;

		glCreateFramebuffers(1, &m_RendererID);

		bool depthAttachment = false;
		int colorAttachment = 0;
		for (int i = 0; i < m_RenderPassDesc.Attachments.size(); i++)
		{
			switch (m_RenderPassDesc.Attachments[i])
			{
				case AttachmentFormat::R8:
				case AttachmentFormat::RGBA8:
				case AttachmentFormat::RGBA16F:
					m_Attachments[i] = GL_COLOR_ATTACHMENT0 + colorAttachment;
					colorAttachment++;
					break;
				case AttachmentFormat::D24S8:
					if (!depthAttachment)
					{
						m_Attachments[i] = GL_DEPTH_STENCIL_ATTACHMENT;
						depthAttachment = true;
					}
					break;
				case AttachmentFormat::D32:
					if (!depthAttachment)
					{
						m_Attachments[i] = GL_DEPTH_ATTACHMENT;
						depthAttachment = true;
					}
					break;
				default:
					break;
			}
		}
	}

	OpenGLRenderPass::~OpenGLRenderPass()
	{
		if (!m_RenderPassDesc.IsSwapchainTarget)
			glDeleteFramebuffers(1, &m_RendererID);
	}
}