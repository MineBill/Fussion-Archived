#include "OpenGLRenderContext.h"
#include "Fussion/Core/Core.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#define TO_STRING_VIEW(data)                 \
    StringView                               \
    {                                        \
        reinterpret_cast<const char *>(data) \
    }

Fussion::OpenGLRenderContext::OpenGLRenderContext(GLFWwindow *windowHandle) : m_windowHandle(windowHandle) {}

void Fussion::OpenGLRenderContext::init()
{
    glfwMakeContextCurrent(m_windowHandle);
    auto status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    FSN_CORE_ASSERT(status, "Failed to load glad")

    FSN_CORE_LOG("Render Info:");
    FSN_CORE_LOG("   Vendor         : {}", TO_STRING_VIEW(glGetString(GL_VENDOR)));
    FSN_CORE_LOG("   Driver         : {}", TO_STRING_VIEW(glGetString(GL_RENDERER)));
    FSN_CORE_LOG("   OpenGL Version : {}", TO_STRING_VIEW(glGetString(GL_VERSION)));
}

void Fussion::OpenGLRenderContext::swap_buffers()
{
    glfwSwapBuffers(m_windowHandle);
}
