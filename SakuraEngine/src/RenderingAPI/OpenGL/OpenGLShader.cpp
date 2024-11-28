#include "skrpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Sakura
{
	static GLenum ShaderTypeToGLenum(ShaderType type)
	{
		switch (type)
		{
			using enum Sakura::ShaderType;
			case None:     return 0;
			case Vertex:   return GL_VERTEX_SHADER;
			case Fragment: return GL_FRAGMENT_SHADER;

			default:
				return 0;
		}
	}

	static std::string ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in); // ifstream closes itself due to RAII
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
			}
			else
			{
				SKR_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			SKR_CORE_ERROR("Could not open file '{0}'", filepath);
		}

		return result;
	}

	static GLuint Compile(const ShaderStringMap& shaderSources)
	{
		GLuint program = glCreateProgram();
		std::array<GLuint, (int)ShaderType::Count - 1> glShaderIDs{};  // ShaderType::None is also a shader type
		int shaderIndex = 0;
		for (const auto& [type, source] : shaderSources) {
			if (type == ShaderType::None) continue;

			GLenum shaderType = ShaderTypeToGLenum(type);

			GLuint shaderID = glCreateShader(shaderType);
			const char* c_source = source.c_str();
			glShaderSource(shaderID, 1, &c_source, 0);
			glCompileShader(shaderID);

			GLint isCompiled = 0;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shaderID, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shaderID);

				SKR_CORE_ERROR("{0}", infoLog.data());
				SKR_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shaderID);
			glShaderIDs[shaderIndex++] = shaderID;
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			for (const GLuint& id : glShaderIDs)
			{
				glDetachShader(program, id);
				glDeleteShader(id);
			}

			glDeleteProgram(program);
			program = 0;

			SKR_CORE_ERROR("{0}", infoLog.data());
			SKR_CORE_ASSERT(false, "Shader linking failure!");
		}

		for (const GLuint& id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		return program;
	}

	OpenGLShader::OpenGLShader(const std::vector<ShaderSpecs>& shaderFiles)
	{
		ShaderStringMap sources{};
		sources.reserve(shaderFiles.size());
		for (const auto& shader : shaderFiles)
		{
			std::string source = ReadFile(shader.Filepath);
			sources[shader.Type] = source;
		}
		m_RendererID = Compile(sources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}
}