#include "skrpch.h"
#include "RenderPass.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLRenderPass.h"

namespace Sakura
{
	Ref<RenderPass> RenderPass::Create(const RenderPassDescription& desc)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLRenderPass>(desc);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
}