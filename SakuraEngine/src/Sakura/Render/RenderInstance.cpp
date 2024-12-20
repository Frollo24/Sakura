#include "skrpch.h"
#include "RenderInstance.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLInstance.h"

namespace Sakura
{
	Unique<RenderInstance> RenderInstance::Create(GLFWwindow* windowHandle)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateUnique<OpenGLInstance>(windowHandle);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
}