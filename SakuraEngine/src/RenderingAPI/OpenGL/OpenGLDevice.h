#pragma once

#include "Sakura/Render/RenderDevice.h"

namespace Sakura
{
	class OpenGLDevice : public RenderDevice
	{
	public:
		OpenGLDevice(const RawPointer<RenderInstance>& instance);
		virtual ~OpenGLDevice() = default;
	};
}

