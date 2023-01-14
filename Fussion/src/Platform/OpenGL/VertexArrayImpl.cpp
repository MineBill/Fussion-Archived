#include "Fussion/Rendering/IndexBuffer.hpp"
#include "Fussion/Rendering/VertexArray.hpp"
#include "Fussion/Rendering/VertexBuffer.hpp"
#include <glad/glad.h>

namespace fussion
{

class VertexArrayImpl : public VertexArray
{
    unsigned int id { 0 };
    Ptr<VertexBuffer> vertex_buffer {};
    Ptr<IndexBuffer> index_buffer {};

    void UpdateVertexBufferSubDataRaw(i32 offset, const void *data, i32 size) override
    {
        vertex_buffer->UpdateSubDataRawPtr(offset, data, size);
    }

    void UpdateIndexBufferSubDataRaw(i32 offset, const void *data, i32 size) override
    {
        index_buffer->UpdateSubDataRawPtr(offset, data, size);
    }

public:
    VertexArrayImpl(const std::vector<float> &vertices, const std::vector<VertexType> &usage)
    {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);

        vertex_buffer = VertexBuffer::Create(vertices, usage);
        index_buffer = IndexBuffer::Create({});
    }

    VertexArrayImpl(i32 vertex_size, i32 index_size, const std::vector<VertexType> &usage)
    {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);

        vertex_buffer = VertexBuffer::WithSize(vertex_size, usage);
        index_buffer = IndexBuffer::WithSize(index_size);
    }

    ~VertexArrayImpl() override = default;

    void Use() const override
    {
        glBindVertexArray(id);
        vertex_buffer->use();
        index_buffer->Use();
    }

    void ResizeVertexBuffer(i32 new_size) override
    {
        vertex_buffer->Resize(new_size);
    }

    void ResizeIndexBuffer(i32 new_size) override
    {
        index_buffer->Resize(new_size);
    }

    mustuse i32 Count() const override
    {
        return 36;
    }
};

Ptr<VertexArray> VertexArray::Create(const std::vector<float> &vertices, const std::vector<VertexType> &usage)
{
    return std::make_unique<VertexArrayImpl>(vertices, usage);
}

Ptr<VertexArray> VertexArray::WithSize(i32 vertex_size, i32 index_size, const std::vector<VertexType> &usage)
{
    return std::make_unique<VertexArrayImpl>(vertex_size, index_size, usage);
}

}
