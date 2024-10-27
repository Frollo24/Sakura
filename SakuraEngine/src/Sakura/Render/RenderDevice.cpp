#include "skrpch.h"
#include "RenderDevice.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLDevice.h"

namespace Sakura
{
	Ref<RenderDevice> RenderDevice::Create(const RawPointer<RenderInstance>& instance)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLDevice>(instance);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}

	Ref<Buffer> RenderDevice::CreateBuffer(const BufferDescription& bufferDescription) const
	{
		return Buffer::Create(bufferDescription);
	}

	void RenderDevice::DestroyBuffer(Ref<Buffer>& buffer) const
	{
		buffer = nullptr;
	}

	Ref<Texture> RenderDevice::CreateTexture(const TextureDescription& textureDescription) const
	{
		return Texture::Create(textureDescription);
	}

	void RenderDevice::DestroyTexture(Ref<Texture>& texture) const
	{
		texture = nullptr;
	}

	Ref<Pipeline> RenderDevice::CreatePipeline(const PipelineState& state, const Ref<Shader>& shader) const
	{
		return Pipeline::Create(state, shader);
	}

	void RenderDevice::DestroyPipeline(Ref<Pipeline>& pipeline) const
	{
		pipeline = nullptr;
	}

	Ref<Shader> RenderDevice::CreateShader(const std::vector<ShaderSpecs>& shaderFiles) const
	{
		return Shader::Create(shaderFiles);
	}

	void RenderDevice::DestroyShader(Ref<Shader>& shader) const
	{
		shader = nullptr;
	}

	Ref<RenderPass> RenderDevice::CreateRenderPass(const RenderPassDescription& renderPassDescription) const
	{
		return RenderPass::Create(renderPassDescription);
	}

	void RenderDevice::DestroyRenderPass(Ref<RenderPass>& renderPass) const
	{
		renderPass = nullptr;
	}

	Ref<Framebuffer> RenderDevice::CreateFramebuffer(const FramebufferDescription& framebufferDescription) const
	{
		return Framebuffer::Create(framebufferDescription);
	}

	void RenderDevice::DestroyFramebuffer(Ref<Framebuffer>& framebuffer) const
	{
		framebuffer = nullptr;
	}
}