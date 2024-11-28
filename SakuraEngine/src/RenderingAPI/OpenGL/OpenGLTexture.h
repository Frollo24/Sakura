#pragma once
#include "Sakura/Render/Texture.h"

namespace Sakura
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const TextureDescription& desc);
		~OpenGLTexture();

		inline uint32_t GetRendererID() const { return m_RendererID; }

		virtual void SetData(const void* data) override;

	private:
		uint32_t m_RendererID = 0;
	};
}
