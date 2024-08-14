#pragma once

#include "Sakura/Render/RenderInstance.h"

namespace Sakura
{
	class OpenGLInstance : public RenderInstance
	{
	public:
		OpenGLInstance(GLFWwindow* windowHandle);
		virtual ~OpenGLInstance();

		virtual void Init() override;
		virtual void SetVSync(bool enabled) override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle = nullptr;
	};
}

