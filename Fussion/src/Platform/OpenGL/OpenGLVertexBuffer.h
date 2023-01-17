#pragma once
#include "Fussion/Rendering/Buffers.h"

namespace Fussion
{

    class OpenGLVertexBuffer : public VertexBuffer
    {
        u32 m_id{0};
        Optional<AttributeLayout> m_layout{};

    public:
        OpenGLVertexBuffer(std::initializer_list<f32> vertices);
        explicit OpenGLVertexBuffer(i32 size);
        ~OpenGLVertexBuffer() override;

        void Use() const override;
        void Resize(i32 new_size) override;
        void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) override;

        void SetLayout(const AttributeLayout &layout) override;
        mustuse const AttributeLayout &GetLayout() const override;
    };

} // namespace Fussion