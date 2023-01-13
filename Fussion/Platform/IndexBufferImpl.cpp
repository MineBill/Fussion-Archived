#include "Fussion/Rendering/IndexBuffer.hpp"
#include <assert.hpp>
#include <glad/glad.h>

using namespace fussion;

class IndexBufferImpl : public IndexBuffer
{
    u32 id { 0 };

public:
    explicit IndexBufferImpl(const std::vector<i32> &indices)
    {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(i32)), indices.data(), GL_STATIC_DRAW);
    }

    explicit IndexBufferImpl(i32 size)
    {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    ~IndexBufferImpl() override = default;

    void Use() const override
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void Resize(i32 new_size) override
    {
        Use();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_size, nullptr, GL_DYNAMIC_DRAW);
    }

    void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) override
    {
        Use();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    }
};

Ptr<IndexBuffer> IndexBuffer::Create(const std::vector<i32> &indices)
{
    return std::make_unique<IndexBufferImpl>(indices);
}

Ptr<IndexBuffer> IndexBuffer::WithSize(i32 size)
{
    return std::make_unique<IndexBufferImpl>(size);
}
