#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace Fussion
{

    OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<u32> &indices) : m_count(static_cast<i32>(indices.size()))
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(u32)), indices.data(),
                     GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(i32 count) : m_count(count)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * static_cast<i32>(sizeof(u32)), nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLIndexBuffer::Use() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void OpenGLIndexBuffer::Resize(i32 new_size)
    {
        Use();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_size, nullptr, GL_DYNAMIC_DRAW);
    }

    void OpenGLIndexBuffer::UpdateSubDataRawPtr(i32 offset, const void *data, i32 size)
    {
        Use();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    }

    i32 OpenGLIndexBuffer::Count() const
    {
        return m_count;
    }

} // namespace Fussion