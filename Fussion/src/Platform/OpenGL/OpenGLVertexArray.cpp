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

    void OpenGLVertexArray::Use() const
    {
        glBindVertexArray(id);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer)
    {
        FSN_CORE_ASSERT(!vertexBuffer->GetLayout().GetAttributes().empty(), "")

        glBindVertexArray(id);
        m_vertexBuffers.push_back(vertexBuffer);

        auto layout = vertexBuffer->GetLayout();
        for (u32 i = 0; const auto &attribute : layout.GetAttributes()) {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute.Count, GL_FLOAT, GL_FALSE, layout.GetString(),
                                  reinterpret_cast<const void *>(static_cast<intptr_t>(attribute.Offset)));
            i++;
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer)
    {
        m_indexBuffer = indexBuffer;
    }

    mustuse i32 OpenGLVertexArray::Count() const
    {
        return m_indexBuffer->Count();
    }
} // namespace Fussion
