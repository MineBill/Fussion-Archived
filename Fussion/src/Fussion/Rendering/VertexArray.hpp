#pragma once
#include "VertexBuffer.hpp"

namespace fussion
{

class VertexArray
{
public:
    virtual ~VertexArray() = default;

    static Ptr<VertexArray> Create(std::vector<float> const &vertices, std::vector<VertexType> const &usage);

    virtual void Use() const = 0;
};

}