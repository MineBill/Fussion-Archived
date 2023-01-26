#include "Bitmap.h"
#include "Fussion/Core/Core.h"

namespace Fussion
{
    Bitmap Bitmap::GridPattern(u32 width, u32 height, u32 gridSize, u32 firstColor, u32 secondColor)
    {
        Bitmap b(width, height);

        for (u32 x = 0; x < b.width(); x++) {
            for (u32 y = 0; y < b.height(); y++) {
                if ((x * gridSize / width) % 2 == (y * gridSize / height) % 2)
                    b.set_pixel(x, y, firstColor);
                else
                    b.set_pixel(x, y, secondColor);
            }
        }

        return b;
    }

    Bitmap::Bitmap(u32 width, u32 height)
    {
        resize(width, height);
    }

    void Bitmap::resize(u32 width, u32 height)
    {
        m_width = width;
        m_height = height;

        delete[] m_dataPtr;
        m_dataPtr = new u8[width * height * 4];
        std::memset(m_dataPtr, 0, width * height * 4);
    }

    void Bitmap::set_pixel(u32 x, u32 y, u32 value)
    {
        FSN_CORE_ASSERT(x < m_width, "x must be less than width");
        FSN_CORE_ASSERT(y < m_height, "y must be less than height");
        FSN_CORE_ASSERT(m_dataPtr != nullptr, "Data is null");

        m_dataPtr[x * 4 * m_height + y * 4 + 3] = static_cast<u8>(value & 0x00'00'00'FF);
        m_dataPtr[x * 4 * m_height + y * 4 + 2] = static_cast<u8>((value & 0x00'00'FF'00) >> 8);
        m_dataPtr[x * 4 * m_height + y * 4 + 1] = static_cast<u8>((value & 0x00'FF'00'00) >> 16);
        m_dataPtr[x * 4 * m_height + y * 4 + 0] = static_cast<u8>((value & 0xFF'00'00'00) >> 24);
    }

    Ref<Texture> Bitmap::to_texture() const
    {
        return Fussion::Texture::FromPixels(m_dataPtr, m_width, m_height, 4);
    }
} // namespace Fussion
