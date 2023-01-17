#include "Buffers.h"
#include "Fussion/Core.h"
#include "Fussion/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
namespace Fussion
{

    Ref<VertexBuffer> VertexBuffer::Create(std::initializer_list<f32> vertices)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::WithSize(i32 size)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(std::initializer_list<u32> indices)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indices);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::WithSize(i32 count)
    {
        switch (Renderer::GetAPI()) {
        case RendererAPI::API::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(count);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

} // namespace Fussion
#pragma clang diagnostic pop