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

        void Use() const override;

        void AddVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) override;
        void SetIndexBuffer(const Ref<IndexBuffer> &indexBuffer) override;

        mustuse const std::vector<Ref<VertexBuffer>> &GetVertexBuffer() const override
        {
            return m_vertexBuffers;
        }

        mustuse const Ref<IndexBuffer> &GetIndexBuffer() const override
        {
            return m_indexBuffer;
        }

        mustuse i32 Count() const override;
    };

} // namespace Fussion
