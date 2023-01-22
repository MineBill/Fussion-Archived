#pragma once
#include "Fussion/Rendering/Framebuffer.h"

namespace Fussion
{
    class OpenGLFrameBuffer final : public Framebuffer
    {
        u32 m_id{};
        u32 m_colorTextureId{};
        u32 m_size{};
        u32 m_height{}, m_width{};

    public:
        OpenGLFrameBuffer(u32 width, u32 height);
        ~OpenGLFrameBuffer();

        void Bind() override;
        void UnBind() override;

        void Resize(u32 width, u32 height) override;

        u32 GetRendererHandle() const override
        {
            return m_id;
        }

        u32 GetColorAttachment() const override
        {
            return m_colorTextureId;
        }
    };
} // namespace Fussion
