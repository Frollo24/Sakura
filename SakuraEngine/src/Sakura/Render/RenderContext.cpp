#include "skrpch.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLContext.h"

namespace Sakura
{
	Unique<RenderContext> RenderContext::Create()
	{
		switch (s_API)
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateUnique<OpenGLContext>();
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
}