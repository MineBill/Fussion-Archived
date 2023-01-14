#include "Fussion/Rendering/VertexBuffer.h"
#include <assert.hpp>
#include <glad/glad.h>

using namespace fussion;

unsigned VertexTypeCount(VertexType vt)
{
    using enum VertexType;
    switch (vt) {
    case Vector2:
        return 2;
    case Vector3:
        return 3;
    case Vector4:
        return 4;
    default:
        ASSERT(false, "Forgot to handle switch case", vt);
    }
    return 0;
}

class VertexBufferImpl : public VertexBuffer
{
    unsigned id { 0 };

public:
    VertexBufferImpl(const std::vector<f32> &vertices, const std::vector<VertexType> &usage)
    {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);

        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(f32)), vertices.data(), GL_STATIC_DRAW);

        auto stride = 0u;
        for (auto const &elem : usage) {
            stride += VertexTypeCount(elem);
        }
        stride *= sizeof(float);

        auto previous_offset = 0u;
        auto index = 0u;
        for (auto const &elem : usage) {
            auto elem_count = VertexTypeCount(elem);
            if (elem == VertexType::Vector4) {
                glVertexAttribPointer(
                    index, static_cast<GLsizei>(elem_count), GL_UNSIGNED_BYTE, true, static_cast<GLsizei>(stride), reinterpret_cast<const void *>(previous_offset * sizeof(float)));
            }else {
                glVertexAttribPointer(
                    index, static_cast<GLsizei>(elem_count), GL_FLOAT, false, static_cast<GLsizei>(stride), reinterpret_cast<const void *>(previous_offset * sizeof(float)));
            }
            glEnableVertexAttribArray(index);

            previous_offset += elem_count;
            index++;
        }
    }

    VertexBufferImpl(i32 size, const std::vector<VertexType> &usage)
    {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);

        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

        auto stride = 0u;
        for (auto const &elem : usage) {
            stride += VertexTypeCount(elem);
        }
        stride *= sizeof(float);

        auto previous_offset = 0u;
        auto index = 0u;
        for (auto const &elem : usage) {
            auto elem_count = VertexTypeCount(elem);
            if (elem == VertexType::Vector4) {
                glVertexAttribPointer(
                    index, static_cast<GLsizei>(elem_count), GL_UNSIGNED_BYTE, true, static_cast<GLsizei>(stride), reinterpret_cast<const void *>(previous_offset * sizeof(float)));
            }else {
                glVertexAttribPointer(
                    index, static_cast<GLsizei>(elem_count), GL_FLOAT, false, static_cast<GLsizei>(stride), reinterpret_cast<const void *>(previous_offset * sizeof(float)));
            }
            glEnableVertexAttribArray(index);

            previous_offset += elem_count;
            index++;
        }
    }

    ~VertexBufferImpl() override = default;

    void use() const override
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void Resize(i32 new_size) override
    {
        use();
        glBufferData(GL_ARRAY_BUFFER, new_size, nullptr, GL_DYNAMIC_DRAW);
    }

    void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) override
    {
        use();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }
};

Ptr<VertexBuffer> VertexBuffer::Create(const std::vector<float> &vertices, const std::vector<VertexType> &usage)
{
    return std::make_unique<VertexBufferImpl>(vertices, usage);
}

Ptr<VertexBuffer> VertexBuffer::WithSize(i32 size, const std::vector<VertexType> &usage)
{
    return std::make_unique<VertexBufferImpl>(size, usage);
}
