#pragma once
#include "Fussion/Rendering/Buffers.h"

namespace Fussion
{

    class OpenGLIndexBuffer : public IndexBuffer
    {
        u32 m_id{0};
        i32 m_count{};

    public:
        explicit OpenGLIndexBuffer(const std::vector<u32> &indices);
        explicit OpenGLIndexBuffer(i32 size);
        ~OpenGLIndexBuffer() override;

        void Use() const override;
        void Resize(i32 new_size) override;
        void UpdateSubDataRawPtr(i32 offset, const void *data, i32 size) override;

        mustuse i32 Count() const override;
    };

} // namespace Fussion