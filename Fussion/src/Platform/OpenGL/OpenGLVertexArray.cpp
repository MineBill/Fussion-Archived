#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Fussion
{

    void OpenGLVertexArray::UpdateVertexBufferSubDataRaw(i32 offset, const void *data, i32 size)
    {
        vertex_buffer->UpdateSubDataRawPtr(offset, data, size);
    }

    void OpenGLVertexArray::UpdateIndexBufferSubDataRaw(i32 offset, const void *data, i32 size)
    {
        index_buffer->UpdateSubDataRawPtr(offset, data, size);
    }

    OpenGLVertexArray::OpenGLVertexArray(const std::vector<f32> &vertices, const std::vector<VertexType> &usage)
    {
        glCreateVertexArrays(1, &id);
        glBindVertexArray(id);

        vertex_buffer = VertexBuffer::Create(vertices, usage);
        index_buffer = IndexBuffer::Create({});
    }

    OpenGLVertexArray::OpenGLVertexArray(const std::vector<f32> &vertices, const std::vector<u32> &indices,
                                         const std::vector<VertexType> &usage)
    {
        glCreateVertexArrays(1, &id);
        glBindVertexArray(id);

        vertex_buffer = VertexBuffer::Create(vertices, usage);
        index_buffer = IndexBuffer::Create(indices);
    }

    OpenGLVertexArray::OpenGLVertexArray(i32 vertex_size, i32 index_size, const std::vector<VertexType> &usage)
    {
        glCreateVertexArrays(1, &id);
        glBindVertexArray(id);

        vertex_buffer = VertexBuffer::WithSize(vertex_size, usage);
        index_buffer = IndexBuffer::WithSize(index_size);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &id);
    }

    void OpenGLVertexArray::Use() const
    {
        glBindVertexArray(id);
        vertex_buffer->Use();
        index_buffer->Use();
    }

    void OpenGLVertexArray::ResizeVertexBuffer(i32 new_size)
    {
        vertex_buffer->Resize(new_size);
    }

    void OpenGLVertexArray::ResizeIndexBuffer(i32 new_size)
    {
        index_buffer->Resize(new_size);
    }

    mustuse i32 OpenGLVertexArray::Count() const
    {
        return 36;
    }

} // namespace Fussion
