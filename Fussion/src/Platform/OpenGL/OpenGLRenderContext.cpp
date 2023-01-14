#include "OpenGLRenderContext.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <assert.hpp>
#include <spdlog/spdlog.h>
#include "Fussion/Log.h"

Fussion::OpenGLRenderContext::OpenGLRenderContext(GLFWwindow *windowHandle) : m_windowHandle(windowHandle)
{
}

#define CONSTCHAR(data) StringView{reinterpret_cast<const char*>(data)}

void Fussion::OpenGLRenderContext::Init()
{
    glfwMakeContextCurrent(m_windowHandle);
    auto status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    DEBUG_ASSERT(status, "Failed to load glad");

    FSN_CORE_LOG("Render Info:");
    FSN_CORE_LOG("   Vendor         : {}", CONSTCHAR(glGetString(GL_VENDOR)));
    FSN_CORE_LOG("   Driver         : {}", CONSTCHAR(glGetString(GL_RENDERER)));
    FSN_CORE_LOG("   OpenGL Version : {}", CONSTCHAR(glGetString(GL_VERSION)));
}

void Fussion::OpenGLRenderContext::SwapBuffers()
{
    glfwSwapBuffers(m_windowHandle);
}
