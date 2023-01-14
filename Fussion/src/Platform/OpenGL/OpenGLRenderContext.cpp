#include "OpenGLRenderContext.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

Fussion::OpenGLRenderContext::OpenGLRenderContext(GLFWwindow *windowHandle) : m_windowHandle(windowHandle)
{
}

void Fussion::OpenGLRenderContext::Init()
{
    glfwMakeContextCurrent(m_windowHandle);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
}

void Fussion::OpenGLRenderContext::SwapBuffers()
{
    glfwSwapBuffers(m_windowHandle);
}
