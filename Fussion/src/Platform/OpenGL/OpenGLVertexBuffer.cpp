#include "OpenGLVertexBuffer.h"
#include <Fussion/Core/Core.h>
#include <glad/glad.h>

namespace Fussion
{
    GLenum VertexElementTypeGLEnum(VertexElementType type)
    {
        using enum VertexElementType;
        switch (type) {
        case Int:
        case Int2:
        case Int3:
        case Int4:
            return GL_INT;
        case Float:
        case Float2:
        case Float3:
        case Float4:
        case Mat4:
            return GL_FLOAT;
        default:
            FSN_CORE_ASSERT(false, "Unhandled case");
            return 0;
        }
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(std::initializer_list<f32> vertices)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);

        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(f32)), std::data(vertices),
                     GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(i32 size)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);

        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void OpenGLVertexBuffer::Use() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void OpenGLVertexBuffer::Resize(i32 new_size)
    {
        Use();
        glBufferData(GL_ARRAY_BUFFER, new_size, nullptr, GL_DYNAMIC_DRAW);
    }

    void OpenGLVertexBuffer::UpdateSubDataRawPtr(i32 offset, const void *data, i32 size)
    {
        Use();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void OpenGLVertexBuffer::SetLayout(const AttributeLayout &layout)
    {
        m_layout = layout;
    }

    const AttributeLayout &OpenGLVertexBuffer::GetLayout() const
    {
        FSN_CORE_ASSERT(m_layout.has_value(), "Layout is not set already");
        return *m_layout;
    }

} // namespace Fussion
