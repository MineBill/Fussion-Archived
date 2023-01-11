#include "Fussion/Rendering/Texture.hpp"
#include "StbImage.hpp"
#include <filesystem>
#include <glad/glad.h>

using namespace fussion;

class OpenGLTexture final : public Texture
{
    u32 handle {};

public:
    explicit OpenGLTexture(const fs::path &path)
    {
        int width;
        int height;
        int num_channels;
        const u8 *image = stbi_load(path.string().c_str(), &width, &height, &num_channels, 0);
        if (image == nullptr) {
            return;
        }

        glGenTextures(1, &handle);
        glBindTexture(GL_TEXTURE_2D, handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Use(u32 unit) const override
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, handle);
    }

    mustuse u32 Handle() const override
    {
        return handle;
    }
};

Ptr<Texture> Texture::LoadFromFile(const fs::path &path)
{
    return std::make_unique<OpenGLTexture>(path);
}