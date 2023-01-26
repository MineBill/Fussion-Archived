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
        static Bitmap GridPattern(u32 width, u32 height, u32 gridSize = 10, u32 firstColor = 0x000000FF,
                                  u32 secondColor = 0xFFFFFFFF);
        Bitmap(u32 width, u32 height);

        void resize(u32 width, u32 height);
        void set_pixel(u32 x, u32 y, u32 value);

        mustuse Ref<Texture> to_texture() const;

        mustuse u32 width() const
        {
            return m_width;
        }

        mustuse u32 height() const
        {
            return m_height;
        }
    };
} // namespace Fussion
