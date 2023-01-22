#pragma once

namespace Fussion
{
    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        static Ref<Framebuffer> WithSize(u32 width, u32 height);

        virtual void Resize(u32 width, u32 height) = 0;

        virtual void Bind() = 0;
        virtual void UnBind() = 0;

        virtual u32 GetRendererHandle() const = 0;
        virtual u32 GetColorAttachment() const = 0;
    };
} // namespace Fussion
