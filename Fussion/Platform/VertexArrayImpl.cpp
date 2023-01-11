#include "Fussion/Rendering/VertexArray.hpp"
#include <glad/glad.h>

namespace fussion {

class VertexArrayImpl : public VertexArray {
    unsigned int id { 0 };
    Ptr<VertexBuffer> vertex_buffer {};

public:
    VertexArrayImpl(const std::vector<float> &vertices, const std::vector<VertexType> &usage) {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);

        vertex_buffer = VertexBuffer::Create(vertices, usage);
    }

    ~VertexArrayImpl() override = default;

    void Use() const override {
        glBindVertexArray(id);
        vertex_buffer->use();
    }
};

Ptr<VertexArray> VertexArray::Create(const std::vector<float> &vertices, const std::vector<VertexType> &usage) {
    return std::make_unique<VertexArrayImpl>(vertices, usage);
}

}
