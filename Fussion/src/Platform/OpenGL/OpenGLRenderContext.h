#pragma once
#include "Fussion/Rendering/RenderContext.h"

struct GLFWwindow;

namespace Fussion
{
    class OpenGLRenderContext final : public RenderContext
    {
        GLFWwindow *m_windowHandle{};

    public:
        explicit OpenGLRenderContext(GLFWwindow *windowHandle);
        void Init() override;

        void SwapBuffers() override;
    };
} // namespace Fussion
