#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Render/RenderInstance.h"
#include "Sakura/Render/Buffer.h"

namespace Sakura
{
	class RenderDevice
	{
	public:
		virtual ~RenderDevice() = default;
		static Ref<RenderDevice> Create(const RawPointer<RenderInstance>& instance);

		Ref<Buffer> CreateBuffer(const BufferDescription& bufferDescription) const;
		void DestroyBuffer(Ref<Buffer>& buffer) const;
	};
}

