#pragma once
#include "Sakura/Render/Buffer.h"

namespace Sakura
{
	class OpenGLBuffer : public Buffer
	{
	public:
		OpenGLBuffer(const BufferDescription& desc);
		~OpenGLBuffer();

		inline uint32_t GetRendererID() const { return m_RendererID; }

		virtual void SetData(uint32_t offset, uint32_t size, const void* data) override;

	private:
		uint32_t m_RendererID = 0;
	};
}
