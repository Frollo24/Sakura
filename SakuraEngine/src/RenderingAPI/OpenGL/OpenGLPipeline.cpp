#include "skrpch.h"
#include "OpenGLPipeline.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Sakura
{
	OpenGLPipeline::OpenGLPipeline(const PipelineState& state, const Ref<Shader>& shader)
		: Pipeline(state, shader), m_RendererID(dynamic_cast<OpenGLShader*>(shader.get())->GetRendererID())
	{
		// TODO: research about using OpenGL program pipelines
	}

	OpenGLPipeline::~OpenGLPipeline()
	{
		m_RendererID = 0;
	}
}