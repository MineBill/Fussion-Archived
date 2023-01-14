#include "Fussion/Rendering/Texture.h"
#include "stb_image.h"
#include <filesystem>
#include <glad/glad.h>

namespace Fussion
{

    class OpenGLTexture final : public Texture
    {
        u32 m_handle{};
        i32 m_width{};
        i32 m_height{};

    public:
        explicit OpenGLTexture(const fs::path &path)
        {
            int num_channels;
            const u8 *image = stbi_load(path.string().c_str(), &m_width, &m_height, &num_channels, 0);
            if (image == nullptr) {
                return;
            }

            glGenTextures(1, &m_handle);
            glBindTexture(GL_TEXTURE_2D, m_handle);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        explicit OpenGLTexture(u8 *pixels, i32 width, i32 height) : m_width(width), m_height(height)
        {
            glGenTextures(1, &m_handle);
            glBindTexture(GL_TEXTURE_2D, m_handle);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void Use(u32 unit) const override
        {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, m_handle);
        }

        mustuse u32 Handle() const override
        {
            return m_handle;
        }
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