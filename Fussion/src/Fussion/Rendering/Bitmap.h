#pragma once
#include "Fussion/Rendering/Texture.h"

namespace Fussion
{
    class Bitmap final
    {
        // Data is RGBA
        u8 *m_dataPtr{};
        u32 m_width{}, m_height{};

    public:
        Bitmap(u32 width, u32 height);

        void Resize(u32 width, u32 height);
        void SetPixel(u32 x, u32 y, u32 value);

        mustuse Ref<Texture> ToTexture() const;

        mustuse u32 GetWidth() const
        {
            return m_width;
        }

        mustuse u32 GetHeight() const
        {
            return m_height;
        }
    };
} // namespace Fussion
