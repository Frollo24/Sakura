#include "OpenGLInstance.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

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
    }

    void OpenGLInstance::Init()
    {
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        std::cout << status << std::endl;  // TODO: replace with logger
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