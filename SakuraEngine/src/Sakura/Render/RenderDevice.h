#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Render/RenderInstance.h"
#include "Sakura/Render/Buffer.h"
#include "Sakura/Render/Texture.h"

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
	};
}

