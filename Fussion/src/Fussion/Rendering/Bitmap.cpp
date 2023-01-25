#include "Bitmap.h"
#include "Fussion/Core/Core.h"

namespace Fussion
{
    Bitmap::Bitmap(u32 width, u32 height)
    {
        Resize(width, height);
    }

    void Bitmap::Resize(u32 width, u32 height)
    {
        m_width = width;
        m_height = height;

        delete[] m_dataPtr;
        m_dataPtr = new u8[width * height * 4];
        std::memset(m_dataPtr, 0, width * height * 4);
    }

    void Bitmap::SetPixel(u32 x, u32 y, u32 color)
    {
        FSN_CORE_ASSERT(x < m_width, "x must be less than width");
        FSN_CORE_ASSERT(y < m_height, "y must be less than height");
        FSN_CORE_ASSERT(m_dataPtr != nullptr, "Data is null");

        m_dataPtr[x * 4 * m_height + y * 4 + 3] = static_cast<u8>(color & 0x00'00'00'FF);
        m_dataPtr[x * 4 * m_height + y * 4 + 2] = static_cast<u8>((color & 0x00'00'FF'00) >> 8);
        m_dataPtr[x * 4 * m_height + y * 4 + 1] = static_cast<u8>((color & 0x00'FF'00'00) >> 16);
        m_dataPtr[x * 4 * m_height + y * 4 + 0] = static_cast<u8>((color & 0xFF'00'00'00) >> 24);
    }

    Ref<Texture> Bitmap::ToTexture() const
    {
        return Fussion::Texture::FromPixels(m_dataPtr, m_width, m_height, 4);
    }
} // namespace Fussion
