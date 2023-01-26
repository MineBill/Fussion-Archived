#include "Framebuffer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"
#include "Renderer.h"
#include "RendererApi.h"

namespace Fussion
{
    Ref<Framebuffer> Framebuffer::WithSize(u32 width, u32 height)
    {
        switch (Renderer::api()) {
        case RendererAPI::API::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
        case RendererAPI::API::OpenGL:
            return make_ref<OpenGLFrameBuffer>(width, height);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }
} // namespace Fussion
