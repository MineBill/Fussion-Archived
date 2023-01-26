#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Fussion
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &id);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &id);
    }

    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(id);
    }

    void OpenGLVertexArray::add_vertex_buffer(const Ref<VertexBuffer> &vertexBuffer)
    {
        FSN_CORE_ASSERT(!vertexBuffer->layout().attributes().empty(), "")

        glBindVertexArray(id);
        m_vertexBuffers.push_back(vertexBuffer);

        auto layout = vertexBuffer->layout();
        for (u32 i = 0; const auto &attribute : layout.attributes()) {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute.Count, GL_FLOAT, GL_FALSE, layout.stride(),
                                  reinterpret_cast<const void *>(static_cast<intptr_t>(attribute.Offset))); // NOLINT
            i++;
        }
    }

    void OpenGLVertexArray::set_index_buffer(const Ref<IndexBuffer> &indexBuffer)
    {
        m_indexBuffer = indexBuffer;
    }

    mustuse u32 OpenGLVertexArray::count() const
    {
        return m_indexBuffer->count();
    }
} // namespace Fussion
