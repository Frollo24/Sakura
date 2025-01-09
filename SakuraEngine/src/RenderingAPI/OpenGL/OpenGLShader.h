#pragma once
#include "Sakura/Render/Shader.h"

namespace Sakura
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::vector<ShaderSpecs>& shaderFiles);
		virtual ~OpenGLShader();

		virtual void SetFloat4(const std::string& name, const glm::vec4& value) const override;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) const override;

		inline uint32_t GetRendererID() const { return m_RendererID; }

	private:
		GLint GetUniformLocation(const std::string& name) const;

	private:
		mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
		uint32_t m_RendererID = 0;
	};
}

