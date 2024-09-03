#include "skrpch.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLContext.h"

namespace Sakura
{
	Unique<RenderContext> RenderContext::Create()
	{
		switch (s_API)
		{
			case RenderAPI::None:      SKR_CORE_ERROR("RenderAPI::None is not supported!"); return nullptr;  // TODO: change to assert
			case RenderAPI::OpenGL:    return CreateUnique<OpenGLContext>();
		}

		SKR_CORE_ERROR("Unknown render API!"); return nullptr;  // TODO: change to assert
	}
}