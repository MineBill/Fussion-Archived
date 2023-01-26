#include "Fussion/Rendering/Buffers.h"
#include "Fussion/Rendering/VertexArray.h"

namespace Fussion
{

    class OpenGLVertexArray : public VertexArray
    {
        unsigned int id{0};
        std::vector<Ref<VertexBuffer>> m_vertexBuffers{};
        Ref<IndexBuffer> m_indexBuffer{};

    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void bind() const override;

        void add_vertex_buffer(const Ref<VertexBuffer> &vertexBuffer) override;
        void set_index_buffer(const Ref<IndexBuffer> &indexBuffer) override;

        mustuse const std::vector<Ref<VertexBuffer>> &vertex_buffers() const override
        {
            return m_vertexBuffers;
        }

        mustuse const Ref<IndexBuffer> &index_buffer() const override
        {
            return m_indexBuffer;
        }

        mustuse u32 count() const override;
    };

} // namespace Fussion
