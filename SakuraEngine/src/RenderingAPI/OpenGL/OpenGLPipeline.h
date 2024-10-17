#pragma once
#include "Sakura/Render/Pipeline.h"

namespace Sakura
{
	class OpenGLPipeline : public Pipeline
	{
	public:
		OpenGLPipeline(const PipelineState& state, const Ref<Shader>& shader);
		virtual ~OpenGLPipeline();

		inline uint32_t GetRendererID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID = 0;
	};
}

