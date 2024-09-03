#include "skrpch.h"
#include "RenderInstance.h"

#include "RenderingAPI/OpenGL/OpenGLInstance.h"

namespace Sakura
{
	Unique<RenderInstance> RenderInstance::Create(GLFWwindow* windowHandle)
	{
		return CreateUnique<OpenGLInstance>(windowHandle);
	}
}