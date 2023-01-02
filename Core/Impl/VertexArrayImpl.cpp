#include "Fussion/Rendering/VertexArray.hpp"
#include <glad/glad.h>

namespace fussion {

class VertexArrayImpl : public VertexArray {
    u32 id { 0 };
    Ptr<VertexBuffer> vertex_buffer {};

public:
    VertexArrayImpl(const std::vector<f32>& vertices, const std::vector<VertexType>& usage) {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);

        vertex_buffer = VertexBuffer::create(vertices, usage);
    }

    ~VertexArrayImpl() override = default;

    void use() const override {
        glBindVertexArray(id);
        vertex_buffer->use();
    }
};

Ptr<VertexArray> VertexArray::create(const std::vector<f32>& vertices, const std::vector<VertexType>& usage) {
    return std::make_unique<VertexArrayImpl>(vertices, usage);
}

}
