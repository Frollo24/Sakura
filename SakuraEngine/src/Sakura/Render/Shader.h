#pragma once

#include "Sakura/Core/Base.h"

#include <glm/glm.hpp>

typedef int GLint;

namespace Sakura
{
	enum class ShaderType
	{
		None = 0,
		Vertex,
		Fragment,
		Count
	};

	struct ShaderSpecs
	{
		std::string Filepath = "";
		ShaderType Type = ShaderType::None;
	};

	using ShaderStringMap = std::unordered_map<ShaderType, std::string>;

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void SetFloat4(const std::string& name, const glm::vec4& value) const = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) const = 0;

		static Ref<Shader> Create(const std::vector<ShaderSpecs>& shaderFiles);
	};
}

