#pragma once

#include "Fussion/Types.h"
#include <filesystem>

namespace fussion
{

namespace fs = std::filesystem;

class Texture
{
public:
    virtual ~Texture() = default;

    mustuse static Ptr<Texture> LoadFromFile(const fs::path &path);

    // Create texture from raw pixels.
    mustuse static Ptr<Texture> FromPixels(u8 *pixels, i32 width, i32 height);

    virtual void Use(u32 unit) const = 0;

    mustuse virtual u32 Handle() const = 0;
};

}