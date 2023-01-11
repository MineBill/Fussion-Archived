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

    static Ptr<VertexBuffer> Create(std::vector<float> const& vertices, std::vector<VertexType> const& usage);

    virtual void use() const = 0;
};

}