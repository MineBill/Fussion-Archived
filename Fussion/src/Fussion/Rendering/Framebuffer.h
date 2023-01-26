#pragma once

namespace Fussion
{
    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        static Ref<Framebuffer> WithSize(u32 width, u32 height);

        virtual void resize(u32 width, u32 height) = 0;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        mustuse virtual u32 renderer_handle() const = 0;
        mustuse virtual u32 color_attachment() const = 0;
    };
} // namespace Fussion
