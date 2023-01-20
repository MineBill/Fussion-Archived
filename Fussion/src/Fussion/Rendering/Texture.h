#pragma once

#include "Fussion/Core/Types.h"
#include <filesystem>

namespace Fussion
{

    namespace fs = std::filesystem;

    class Texture
    {
    public:
        mustuse static Ptr<Texture> LoadFromFile(const fs::path &path);
        // Create texture from raw pixels.
        mustuse static Ptr<Texture> FromPixels(u8 *pixels, i32 width, i32 height);
        virtual ~Texture() = default;

        virtual void Use(u32 unit) const = 0;

        mustuse virtual i32 Width() const = 0;
        mustuse virtual i32 Height() const = 0;
        mustuse virtual u32 Handle() const = 0;
    };

} // namespace Fussion
