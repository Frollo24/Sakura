#pragma once

#include "Sakura/Core/Base.h"

struct GLFWwindow;

namespace Sakura
{
	class RenderInstance
	{
	public:
		virtual ~RenderInstance() = default;

		virtual void Init() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SwapBuffers() = 0;

		static Unique<RenderInstance> Create(GLFWwindow* windowHandle);
	};
}

