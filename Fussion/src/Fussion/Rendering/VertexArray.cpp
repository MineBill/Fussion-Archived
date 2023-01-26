#include "Fussion/Rendering/VertexArray.h"
#include "Fussion/Core/Core.h"
#include "Fussion/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fussion
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::api()) {
        case RendererAPI::API::None:
            FSN_CORE_ASSERT(false, "RenderAPI::None is not supported");
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }
} // namespace Fussion