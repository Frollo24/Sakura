#include "skrpch.h"
#include "Shader.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLShader.h"

namespace Sakura
{
	Ref<Shader> Shader::Create(const std::vector<ShaderSpecs>& shaderFiles)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLShader>(shaderFiles);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
}