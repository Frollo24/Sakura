#include "skrpch.h"
#include "Framebuffer.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLFramebuffer.h"

namespace Sakura
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferDescription& desc)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLFramebuffer>(desc);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
}
