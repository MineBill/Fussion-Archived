#pragma once
#include "Fussion/Types.h"
#include <vector>

namespace Fussion
{

    class IndexBuffer
    {
        friend class VertexArrayImpl;

        virtual void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) = 0;

    public:
        virtual ~IndexBuffer() = default;

        static Ptr<IndexBuffer> Create(std::vector<i32> const &indices);
        static Ptr<IndexBuffer> WithSize(i32 size);

        virtual void Use() const = 0;

        virtual void Resize(i32 new_size) = 0;
    };

} // namespace Fussion
