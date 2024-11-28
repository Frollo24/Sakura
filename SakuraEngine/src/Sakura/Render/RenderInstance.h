#pragma once

#include "Sakura/Core/Base.h"

struct GLFWwindow;

namespace Sakura
{
	class RenderDevice;
	class RenderContext;

	class RenderInstance
	{
	public:
		virtual ~RenderInstance() = default;

		virtual void Init() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual void SwapBuffers() = 0;

		inline const Ref<RenderDevice>& GetDevice() { return m_Device; }
		inline const Ref<RenderContext>& GetContext() { return m_Context; }

		static Unique<RenderInstance> Create(GLFWwindow* windowHandle);

	protected:
		Ref<RenderDevice> m_Device = nullptr;
		Ref<RenderContext> m_Context = nullptr;
	};
}

