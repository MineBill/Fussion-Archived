#include "Fussion/Core/Core.h"
#include "Fussion/Rendering/Texture.h"
#include "stb_image.h"
#include <filesystem>
#include <glad/glad.h>

namespace Fussion
{

    GLenum GetTextureFormatFromChannels(i32 channels)
    {
        switch (channels) {
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        default:
            return 0;
        }
        FSN_CORE_ASSERT(false, "Unsupported amount of channels: {}", channels)
        return 0;
    }

    GLenum GetInternalTextureFormatFromChannels(i32 channels)
    {
        switch (channels) {
        case 3:
            return GL_RGB8;
        case 4:
            return GL_RGBA8;
        default:
            return 0;
        }
        FSN_CORE_ASSERT(false, "Unsupported amount of channels: {}", channels)
        return 0;
    }

    class OpenGLTexture final : public Texture
    {
        u32 m_handle{};
        i32 m_width{};
        i32 m_height{};
        i32 m_channels{};

    public:
        explicit OpenGLTexture(const fs::path &path)
        {
            int num_channels;
            stbi_set_flip_vertically_on_load(1);
            const u8 *image = stbi_load(path.string().c_str(), &m_width, &m_height, &num_channels, 0);
            if (image == nullptr) {
                return;
            }
            m_channels = num_channels;

            LoadFromPixels(image);
        }

        explicit OpenGLTexture(const u8 *pixels, i32 width, i32 height) : m_width(width), m_height(height)
        {
            LoadFromPixels(pixels);
        }

        void LoadFromPixels(const u8 *pixels)
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
            glTextureStorage2D(m_handle, 1, GetInternalTextureFormatFromChannels(m_channels), m_width, m_height);

            glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, GetTextureFormatFromChannels(m_channels),
                                GL_UNSIGNED_BYTE, pixels);
            //            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void Use(u32 unit) const override { glBindTextureUnit(unit, m_handle); }

        mustuse u32 Handle() const override { return m_handle; }
        mustuse i32 Width() const override { return m_width; }
        mustuse i32 Height() const override { return m_height; }
    };

    Ptr<Texture> Texture::LoadFromFile(const fs::path &path)
    {
        return std::make_unique<OpenGLTexture>(path);
    }

    Ptr<Texture> Texture::FromPixels(u8 *pixels, i32 width, i32 height)
    {
        return std::make_unique<OpenGLTexture>(pixels, width, height);
    }

} // namespace Fussion