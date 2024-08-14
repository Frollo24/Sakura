#include "RenderInstance.h"

#include "RenderingAPI/OpenGL/OpenGLInstance.h"

namespace Sakura
{
	RenderInstance* RenderInstance::Create(GLFWwindow* windowHandle)
	{
		return new OpenGLInstance(windowHandle);
	}
}