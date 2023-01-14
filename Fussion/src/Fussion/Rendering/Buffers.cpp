#include "Buffers.h"
#include "Fussion/Core.h"
#include "Fussion/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Fussion
{

    Ref<VertexBuffer> VertexBuffer::Create(const std::vector<float> &vertices)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::WithSize(i32 size)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(std::vector<u32> const &indices)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indices);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::WithSize(i32 count)
    {
        switch (Renderer::GetAPI()) {
        case RenderAPI::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(count);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

} // namespace Fussion