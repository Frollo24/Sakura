#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Render/RenderInstance.h"
#include "Sakura/Render/Buffer.h"
#include "Sakura/Render/Texture.h"
#include "Sakura/Render/Pipeline.h"

namespace Sakura
{
	class RenderDevice
	{
	public:
		virtual ~RenderDevice() = default;
		static Ref<RenderDevice> Create(const RawPointer<RenderInstance>& instance);

		Ref<Buffer> CreateBuffer(const BufferDescription& bufferDescription) const;
		void DestroyBuffer(Ref<Buffer>& buffer) const;

		Ref<Texture> CreateTexture(const TextureDescription& textureDescription) const;
		void DestroyTexture(Ref<Texture>& texture) const;

		Ref<Pipeline> CreatePipeline(const PipelineState& state, const Ref<Shader>& shader) const;
		void DestroyPipeline(Ref<Pipeline>& pipeline) const;

		Ref<Shader> CreateShader(const std::vector<ShaderSpecs>& shaderFiles) const;
		void DestroyShader(Ref<Shader>& shader) const;
	};
}

