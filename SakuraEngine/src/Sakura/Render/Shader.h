#pragma once

#include "Sakura/Core/Base.h"

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

		static Ref<Shader> Create(const std::vector<ShaderSpecs>& shaderFiles);
	};
}

