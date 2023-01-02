#pragma once
#include "VertexBuffer.hpp"

namespace fussion {

class VertexArray {
public:
    virtual ~VertexArray() = default;

    static Ptr<VertexArray> create(std::vector<f32> const& vertices, std::vector<VertexType> const& usage);

    virtual void use() const = 0;
};

}