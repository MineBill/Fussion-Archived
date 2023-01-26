#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace Fussion
{

    OpenGLIndexBuffer::OpenGLIndexBuffer(std::initializer_list<u32> indices) : m_count(static_cast<u32>(indices.size()))
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(u32)), std::data(indices),
                     GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(std::span<u32> indices) : m_count(static_cast<u32>(indices.size()))
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indices.size() * sizeof(u32)), std::data(indices),
                     GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(u32 count) : m_count(count)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * static_cast<i32>(sizeof(u32)), nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    void OpenGLIndexBuffer::resize(i32 new_size)
    {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_size, nullptr, GL_DYNAMIC_DRAW);
    }

    void OpenGLIndexBuffer::update_sub_data(i32 offset, const void *data, i32 size)
    {
        bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
    }

    u32 OpenGLIndexBuffer::count() const
    {
        return m_count;
    }

} // namespace Fussion
