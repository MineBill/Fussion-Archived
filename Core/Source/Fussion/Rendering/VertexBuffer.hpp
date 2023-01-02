#pragma once
#include "Fussion/Types.hpp"
#include <vector>

namespace fussion {

enum class VertexType {
    Vector2,
    Vector3
};

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    static Ptr<VertexBuffer> create(std::vector<f32> const& vertices, std::vector<VertexType> const& usage);

    virtual void use() const = 0;
};

}