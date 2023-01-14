#include "Buffers.h"
#include "Fussion/Rendering/Renderer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "Fussion/Core.h"

namespace Fussion
{

    Ptr<VertexBuffer> VertexBuffer::Create(const std::vector<float> &vertices, const std::vector<VertexType> &usage)
    {
        switch(Renderer::GetAPI())
        {
        case RenderAPI::None:
            FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_unique<OpenGLVertexBuffer>(vertices, usage);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ptr<VertexBuffer> VertexBuffer::WithSize(i32 size, const std::vector<VertexType> &usage)
    {
        switch(Renderer::GetAPI())
        {
        case RenderAPI::None:
        FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_unique<OpenGLVertexBuffer>(size, usage);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ptr<IndexBuffer> IndexBuffer::Create(std::vector<u32> const &indices)
    {
        switch(Renderer::GetAPI())
        {
        case RenderAPI::None:
        FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_unique<OpenGLIndexBuffer>(indices);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

    Ptr<IndexBuffer> IndexBuffer::WithSize(i32 size)
    {
        switch(Renderer::GetAPI())
        {
        case RenderAPI::None:
        FSN_CORE_ASSERT(false, "RenderAPI None is not supported");
            return nullptr;
        case RenderAPI::OpenGL:
            return std::make_unique<OpenGLIndexBuffer>(size);
        }

        FSN_CORE_ASSERT(false, "Reached unreachable(huh) code");
        return nullptr;
    }

} // namespace Fussion