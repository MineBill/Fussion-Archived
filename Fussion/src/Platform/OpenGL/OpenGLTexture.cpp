#include "Fussion/Core/Core.h"
#include "Fussion/Rendering/Texture.h"
#include "stb_image.h"
#include <filesystem>
#include <glad/glad.h>

namespace Fussion
{

    GLenum texture_format_from_channels(i32 channels)
    {
        switch (channels) {
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        default:
            FSN_CORE_ASSERT(false, "Unsupported amount of channels: {}", channels)
            return 0;
        }
    }

    GLenum internal_texture_format_from_channels(i32 channels)
    {
        switch (channels) {
        case 3:
            return GL_RGB8;
        case 4:
            return GL_RGBA8;
        default:
            FSN_CORE_ASSERT(false, "Unsupported amount of channels: {}", channels)
            return 0;
        }
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
                FSN_CORE_ERR("Failed to load texture, i should probably give you something default to indicate that "
                             "visually: path: {}",
                             path.string());
                return;
            }
            m_channels = num_channels;

            LoadFromPixels(image);
        }

        explicit OpenGLTexture(const u8 *pixels, i32 width, i32 height, i32 channels)
            : m_width(width), m_height(height), m_channels(channels)
        {
            LoadFromPixels(pixels);
        }

        void LoadFromPixels(const u8 *pixels)
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
            glTextureStorage2D(m_handle, 1, internal_texture_format_from_channels(m_channels), m_width, m_height);

            glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, texture_format_from_channels(m_channels),
                                GL_UNSIGNED_BYTE, pixels);
            //            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void bind(u32 unit) const override
        {
            FSN_CORE_ASSERT(m_handle != 0, "Texture handle is not valid. Possible not created at all.");
            glBindTextureUnit(unit, m_handle);
        }

        mustuse u32 renderer_handle() const override { return m_handle; }

        mustuse i32 width() const override { return m_width; }

        mustuse i32 height() const override { return m_height; }
    };

    Ptr<Texture> Texture::load_from_file(const fs::path &path)
    {
        return std::make_unique<OpenGLTexture>(path);
    }

    Ptr<Texture> Texture::from_pixels(u8 *pixels, u32 width, u32 height, u32 channels)
    {
        return std::make_unique<OpenGLTexture>(pixels, width, height, channels);
    }

} // namespace Fussion
