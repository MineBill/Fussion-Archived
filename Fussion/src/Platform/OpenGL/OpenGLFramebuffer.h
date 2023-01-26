#pragma once
#include "Fussion/Rendering/Framebuffer.h"

namespace Fussion
{
    class OpenGLFrameBuffer final : public Framebuffer
    {
        u32 m_id{0};
        u32 m_colorTextureId{0};
        u32 m_size{};
        u32 m_height{}, m_width{};

    public:
        OpenGLFrameBuffer(u32 width, u32 height);
        ~OpenGLFrameBuffer();

        void bind() override;
        void unbind() override;

        void resize(u32 width, u32 height) override;

        mustuse u32 renderer_handle() const override
        {
            return m_id;
        }

        mustuse u32 color_attachment() const override
        {
            return m_colorTextureId;
        }
    };
} // namespace Fussion
