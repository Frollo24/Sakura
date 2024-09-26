#include "skrpch.h"
#include "OpenGLContext.h"

#include "OpenGLInputLayout.h"
#include "OpenGLBuffer.h"

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

		// HACK: we should create a proper pipeline and a proper shader before drawing anything
		const GLchar* vsGLSL = R"(#version 450
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

layout(location = 0) out vec3 vColor;

void main(){
	gl_Position = vec4(aPosition, 0.0, 1.0);
	vColor = aColor;
}
)";
		const GLchar* fsGLSL = R"(#version 450
layout(location = 0) in vec3 vColor;

layout(location = 0) out vec4 oColor;

void main(){
	oColor = vec4(vColor, 1.0);
}
)";

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vsGLSL, nullptr);
		glCompileShader(vs);
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fsGLSL, nullptr);
		glCompileShader(fs);
		GLuint program = glCreateProgram();
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glUseProgram(program);
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

	void OpenGLContext::SetInputLayout(const Ref<InputLayout>& layout)
	{
		m_BoundVertexArray = dynamic_cast<OpenGLInputLayout*>(layout.get())->GetRendererID();
		glBindVertexArray(m_BoundVertexArray);
	}

	void OpenGLContext::BindVertexBuffer(const Ref<Buffer>& vertexBuffer, const InputBinding& binding)
	{
		GLintptr offset = 0;
		GLuint vertexBufferID = dynamic_cast<OpenGLBuffer*>(vertexBuffer.get())->GetRendererID();
		glVertexArrayVertexBuffer(m_BoundVertexArray, binding.GetBinding(), vertexBufferID, offset, binding.GetStride());
	}

	void OpenGLContext::BindIndexBuffer(const Ref<Buffer>& indexBuffer)
	{
		GLuint indexBufferID = dynamic_cast<OpenGLBuffer*>(indexBuffer.get())->GetRendererID();
		glVertexArrayElementBuffer(m_BoundVertexArray, indexBufferID);
	}

	void OpenGLContext::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
	{
		if (instanceCount > 1 && firstInstance == 0)
			glDrawArraysInstanced(GL_TRIANGLES, firstVertex, vertexCount, instanceCount);
		else if (instanceCount > 1)
			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, firstVertex, vertexCount, instanceCount, firstInstance);
		else
			glDrawArrays(GL_TRIANGLES, firstVertex, vertexCount);
	}
}