#include "skrpch.h"
#include "Pipeline.h"
#include "RenderContext.h"

#include "RenderingAPI/OpenGL/OpenGLPipeline.h"

namespace Sakura
{
	Ref<Pipeline> Pipeline::Create(const PipelineState& pipelineState, const Ref<Shader>& shader)
	{
		switch (RenderContext::GetAPI())
		{
			case RenderAPI::None:      SKR_CORE_ASSERT(false, "RenderAPI::None is not supported!"); return nullptr;
			case RenderAPI::OpenGL:    return CreateRef<OpenGLPipeline>(pipelineState, shader);
		}

		SKR_CORE_ASSERT(false, "Unknown render API!"); return nullptr;
	}
}