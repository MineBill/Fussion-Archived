#pragma once
#include "Buffers.h"
#include "Fussion/Core/Types.h"
#include <vector>

namespace Fussion
{

    enum class VertexElementType;

    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        static Ref<VertexArray> Create();

        virtual void Use() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) = 0;

        mustuse virtual const std::vector<Ref<VertexBuffer>> &GetVertexBuffer() const = 0;
        mustuse virtual const Ref<IndexBuffer> &GetIndexBuffer() const = 0;
        mustuse virtual u32 Count() const = 0;
    };

} // namespace Fussion
