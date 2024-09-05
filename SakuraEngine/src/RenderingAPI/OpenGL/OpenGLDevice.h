#pragma once

#include "Sakura/Render/RenderDevice.h"

namespace Sakura
{
	class OpenGLDevice : public RenderDevice
	{
	public:
		OpenGLDevice(const RawPointer<RenderInstance>& instance);
		OpenGLDevice(const Unique<RenderInstance>& instance);
		virtual ~OpenGLDevice() = default;
	};
}

