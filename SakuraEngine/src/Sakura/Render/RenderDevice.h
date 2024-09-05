#pragma once

#include "Sakura/Core/Base.h"
#include "Sakura/Render/RenderInstance.h"

namespace Sakura
{
	class RenderDevice
	{
	public:
		// virtual Ref<Buffer> CreateBuffer(const BufferDescription& bufferDescription) = 0;
		// virtual void DestroyBuffer(Ref<Buffer>& buffer) = 0;

		static Ref<RenderDevice> Create(const RawPointer<RenderInstance>& instance);
	};
}

