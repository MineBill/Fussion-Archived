#include "Fussion/Rendering/VertexBuffer.hpp"
#include <glad/glad.h>

namespace fussion {

unsigned VertexTypeCount(VertexType vt) {
    using enum VertexType;
    switch (vt) {
    case Vector2:
        return 2;
    case Vector3:
        return 3;
    }
    return 0;
}

class VertexBufferImpl : public VertexBuffer {
    unsigned id { 0 };

public:
    VertexBufferImpl(const std::vector<float> &vertices, const std::vector<VertexType> &usage) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);

        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size()), vertices.data(), GL_STATIC_DRAW);

        auto stride = 0u;
        for (auto const &elem : usage) {
            stride += VertexTypeCount(elem);
        }
        stride *= sizeof(float);

        auto previous_offset = 0u;
        auto index = 0u;
        for (auto const &elem : usage) {
            auto elem_count = VertexTypeCount(elem);
            glVertexAttribPointer(
                index, static_cast<GLsizei>(elem_count), GL_FLOAT, false, static_cast<GLsizei>(stride), reinterpret_cast<const void *>(previous_offset * sizeof(float)));
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

Ptr<VertexBuffer> VertexBuffer::Create(const std::vector<float> &vertices, const std::vector<VertexType> &usage) {
    return std::make_unique<VertexBufferImpl>(vertices, usage);
}

}
