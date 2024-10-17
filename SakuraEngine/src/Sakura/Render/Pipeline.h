#pragma once

#include "Sakura/Core/Base.h"
#include "PipelineState.h"
#include "InputLayout.h"
#include "Shader.h"

namespace Sakura
{
	struct PipelineState
	{
		PipelineDepthState PipelineDepthState{};
		PipelineBlendState PipelineBlendState{};
		PipelinePolygonState PipelinePolygonState{};
		
		Ref<InputLayout> InputLayout = nullptr;
	};

	class Pipeline
	{
	public:
		virtual ~Pipeline() = default;

		static Ref<Pipeline> Create(const PipelineState& pipelineState, const Ref<Shader>& shader);

		inline const PipelineState& GetPipelineState() const { return m_State; }
		inline const Ref<Shader>& GetShader() const { return m_Shader; }

	protected:
		Pipeline(const PipelineState& spec, const Ref<Shader>& shader) : m_State(spec), m_Shader(shader) {}

	protected:
		PipelineState m_State;
		Ref<Shader> m_Shader = nullptr;
	};
}
