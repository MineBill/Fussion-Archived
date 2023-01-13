#pragma once
#include "Fussion/Types.hpp"
#include <vector>

namespace fussion
{

enum class VertexType {
    Vector2,
    Vector3,
    Vector4,
};

class VertexBuffer
{
    friend class VertexArrayImpl;

    virtual void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) = 0;

public:
    virtual ~VertexBuffer() = default;

    static Ptr<VertexBuffer> Create(std::vector<float> const &vertices, std::vector<VertexType> const &usage);
    static Ptr<VertexBuffer> WithSize(i32 size, std::vector<VertexType> const &usage);

    virtual void use() const = 0;

    virtual void Resize(i32 new_size) = 0;
};

}
