#pragma once
#include "Fussion/Rendering/Buffers.h"

namespace Fussion
{

    class OpenGLIndexBuffer : public IndexBuffer
    {
        u32 m_id{0};
        u32 m_count{};

    public:
        explicit OpenGLIndexBuffer(std::initializer_list<u32> indices);
        explicit OpenGLIndexBuffer(std::span<u32> indices);
        explicit OpenGLIndexBuffer(u32 size);
        ~OpenGLIndexBuffer() override;

        void bind() const override;
        void resize(i32 new_size) override;
        void update_sub_data(i32 offset, const void *data, i32 size) override;

        mustuse u32 count() const override;
    };

} // namespace Fussion
