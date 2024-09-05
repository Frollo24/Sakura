#include "skrpch.h"
#include "OpenGLInstance.h"

#include "Sakura/Render/RenderDevice.h"
#include "Sakura/Render/RenderContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sakura
{
    OpenGLInstance::OpenGLInstance(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        glfwMakeContextCurrent(m_WindowHandle);
    }

    OpenGLInstance::~OpenGLInstance()
    {
        glfwMakeContextCurrent(nullptr);

        m_Device = nullptr;
    }

    void OpenGLInstance::Init()
    {
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (status)
            SKR_CORE_INFO("OpenGL Extension Loading Status: OK");
        else
            SKR_CORE_CRITICAL("OpenGL Extension Loading Status: ERROR");

        SKR_CORE_DEBUG("OpenGL info:");
        SKR_CORE_DEBUG("  Vendor: {}", std::string_view((const char*)glGetString(GL_VENDOR)));
        SKR_CORE_DEBUG("  Renderer: {}", std::string_view((const char*)glGetString(GL_RENDERER)));
        SKR_CORE_DEBUG("  Version: {}", std::string_view((const char*)glGetString(GL_VERSION)));

        RawPointer<RenderInstance> instance = this;
        m_Device = RenderDevice::Create(instance);
        m_Context = RenderContext::Create();
        m_Context->Init();
    }

    void OpenGLInstance::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
    }

    void OpenGLInstance::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}