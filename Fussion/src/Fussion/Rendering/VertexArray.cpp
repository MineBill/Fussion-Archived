#include "Fussion/Rendering/VertexArray.h"
#include "Fussion/Core.h"
#include "Fussion/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Fussion
{
    Ptr<VertexArray> VertexArray::Create(const std::vector<float> &vertices, const std::vector<VertexType> &usage)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::None:
            FSN_CORE_ASSERT(false, "RenderAPI::None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_unique<OpenGLVertexArray>(vertices, usage);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ptr<VertexArray> VertexArray::Create(const std::vector<float> &vertices, const std::vector<u32> &indices,
                                         const std::vector<VertexType> &usage)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::None:
            FSN_CORE_ASSERT(false, "RenderAPI::None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_unique<OpenGLVertexArray>(vertices, indices, usage);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ptr<VertexArray> VertexArray::WithSize(i32 vertex_size, i32 index_size, const std::vector<VertexType> &usage)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::None:
            FSN_CORE_ASSERT(false, "RenderAPI::None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_unique<OpenGLVertexArray>(vertex_size, index_size, usage);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }
} // namespace Fussion