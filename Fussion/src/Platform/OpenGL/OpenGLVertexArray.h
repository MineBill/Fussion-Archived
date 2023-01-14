#include "Fussion/Rendering/Buffers.h"
#include "Fussion/Rendering/VertexArray.h"

namespace Fussion
{

    class OpenGLVertexArray : public VertexArray
    {
        unsigned int id{0};
        Ptr<VertexBuffer> vertex_buffer{};
        Ptr<IndexBuffer> index_buffer{};

    public:
        OpenGLVertexArray(const std::vector<f32> &vertices, const std::vector<VertexType> &usage);
        OpenGLVertexArray(const std::vector<f32> &vertices, const std::vector<u32> &indices,
                          const std::vector<VertexType> &usage);
        OpenGLVertexArray(i32 vertex_size, i32 index_size, const std::vector<VertexType> &usage);
        ~OpenGLVertexArray() override;

        void Use() const override;
        void ResizeVertexBuffer(i32 new_size) override;
        void ResizeIndexBuffer(i32 new_size) override;
        void UpdateVertexBufferSubDataRaw(i32 offset, const void *data, i32 size) override;
        void UpdateIndexBufferSubDataRaw(i32 offset, const void *data, i32 size) override;

        mustuse i32 Count() const override;
    };

} // namespace Fussion
