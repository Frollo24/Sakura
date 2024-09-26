#include "skrpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Sakura
{
	OpenGLBuffer::OpenGLBuffer(const BufferDescription& desc)
		: Buffer(desc)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, desc.Size, desc.Data, GL_STATIC_DRAW);
	}

	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLBuffer::SetData(uint32_t offset, uint32_t size, const void* data)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}
}