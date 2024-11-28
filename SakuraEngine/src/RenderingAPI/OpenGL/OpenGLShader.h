#pragma once
#include "Sakura/Render/Shader.h"

namespace Sakura
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::vector<ShaderSpecs>& shaderFiles);
		virtual ~OpenGLShader();

		inline uint32_t GetRendererID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID = 0;
	};
}

