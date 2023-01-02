#include "Fussion/Rendering/VertexBuffer.hpp"
#include <glad/glad.h>

namespace fussion {

u32 vertex_type_count(VertexType vt) {
    switch (vt) {
    case VertexType::Vector2:
        return 2;
    case VertexType::Vector3:
        return 3;
    }
    return 0;
}

class VertexBufferImpl : public VertexBuffer {
    u32 id { 0 };

public:
    VertexBufferImpl(const std::vector<f32>& vertices, const std::vector<VertexType>& usage) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);

        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size()), vertices.data(), GL_STATIC_DRAW);

        auto stride = 0u;
        for (auto const& elem : usage) {
            stride += vertex_type_count(elem);
        }
        stride *= sizeof(f32);

        auto previous_offset = 0u;
        auto index = 0u;
        for (auto const& elem : usage) {
            auto elem_count = vertex_type_count(elem);
            glVertexAttribPointer(
                index, static_cast<GLsizei>(elem_count), GL_FLOAT, false, static_cast<GLsizei>(stride), reinterpret_cast<const void*>(previous_offset * sizeof(f32)));
            glEnableVertexAttribArray(index);

            previous_offset += elem_count;
            index++;
        }
    }

    ~VertexBufferImpl() override = default;

    void use() const override {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }
};

Ptr<VertexBuffer> VertexBuffer::create(const std::vector<f32>& vertices, const std::vector<VertexType>& usage) {
    return std::make_unique<VertexBufferImpl>(vertices, usage);
}

}
