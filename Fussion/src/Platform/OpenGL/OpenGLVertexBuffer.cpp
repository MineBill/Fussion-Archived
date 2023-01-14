#include "OpenGLVertexBuffer.h"
#include <Fussion/Core.h>
#include <glad/glad.h>

namespace Fussion
{

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
            FSN_CORE_ASSERT(false, "Forgot to handle switch case");
        }
        return 0;
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<f32> &vertices, const std::vector<VertexType> &usage)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);

        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(vertices.size() * sizeof(f32)), vertices.data(),
                     GL_STATIC_DRAW);

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
                glVertexAttribPointer(index, static_cast<GLsizei>(elem_count), GL_UNSIGNED_BYTE, true,
                                      static_cast<GLsizei>(stride),
                                      reinterpret_cast<const void *>( // NOLINT(performance-no-int-to-ptr)
                                          previous_offset * sizeof(float)));
            } else {
                glVertexAttribPointer(index, static_cast<GLsizei>(elem_count), GL_FLOAT, false,
                                      static_cast<GLsizei>(stride),
                                      reinterpret_cast<const void *>( // NOLINT(performance-no-int-to-ptr)
                                          previous_offset * sizeof(float)));
            }
            glEnableVertexAttribArray(index);

            previous_offset += elem_count;
            index++;
        }
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(i32 size, const std::vector<VertexType> &usage)
    {
        glCreateBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);

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
                glVertexAttribPointer(index, static_cast<GLsizei>(elem_count), GL_UNSIGNED_BYTE, true,
                                      static_cast<GLsizei>(stride),
                                      reinterpret_cast<const void *>( // NOLINT(performance-no-int-to-ptr)
                                          previous_offset * sizeof(float)));
            } else {
                glVertexAttribPointer(index, static_cast<GLsizei>(elem_count), GL_FLOAT, false,
                                      static_cast<GLsizei>(stride),
                                      reinterpret_cast<const void *>( // NOLINT(performance-no-int-to-ptr)
                                          previous_offset * sizeof(float)));
            }
            glEnableVertexAttribArray(index);

            previous_offset += elem_count;
            index++;
        }
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

} // namespace Fussion