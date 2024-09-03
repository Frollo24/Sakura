#include "skrpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>

namespace Sakura
{
	static void OpenGLDebugCallback(GLenum source, GLenum type, unsigned id, GLenum severity, int length, const char* message, const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         SKR_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       SKR_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_LOW:          SKR_CORE_INFO(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: SKR_CORE_TRACE(message); return;
			default:
				SKR_CORE_ASSERT(false, "Unknown severity level!");
				break;
		}
	}

	void OpenGLContext::Init()
	{
#ifdef SKR_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLDebugCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif // SKR_DEBUG

		glEnable(GL_FRAMEBUFFER_SRGB);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void OpenGLContext::Shutdown()
	{
		// In OpenGL this does nothing
	}

	void OpenGLContext::BeginFrame()
	{
		glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLContext::EndFrame()
	{
		// Reset buffer writing to true for any buffer
		glDepthMask(GL_TRUE);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}
}