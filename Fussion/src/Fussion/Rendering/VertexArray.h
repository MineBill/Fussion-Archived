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

        virtual void bind() const = 0;

        virtual void add_vertex_buffer(const Ref<VertexBuffer> &vertexBuffer) = 0;
        virtual void set_index_buffer(const Ref<IndexBuffer> &indexBuffer) = 0;

        mustuse virtual const std::vector<Ref<VertexBuffer>> &vertex_buffers() const = 0;
        mustuse virtual const Ref<IndexBuffer> &index_buffer() const = 0;
        mustuse virtual u32 count() const = 0;
    };

} // namespace Fussion
