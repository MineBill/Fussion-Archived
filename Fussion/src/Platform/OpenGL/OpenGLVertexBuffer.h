#pragma once
#include "Fussion/Rendering/Buffers.h"

namespace Fussion
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
        u32 m_id{0};

    public:
        OpenGLVertexBuffer(const std::vector<f32> &vertices, const std::vector<VertexType> &usage);
        OpenGLVertexBuffer(i32 size, const std::vector<VertexType> &usage);
        ~OpenGLVertexBuffer() override;

        void Use() const override;
        void Resize(i32 new_size) override;
        void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) override;
    };

} // namespace Fussion