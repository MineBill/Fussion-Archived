#pragma once

#include "Fussion/Core/Types.h"
#include <filesystem>

namespace Fussion
{

    namespace fs = std::filesystem;

    class Texture
    {
    public:
        mustuse static Ptr<Texture> load_from_file(const fs::path &path);
        // Create texture from raw pixels.
        mustuse static Ptr<Texture> from_pixels(u8 *pixels, u32 width, u32 height, u32 channels);
        virtual ~Texture() = default;

        virtual void bind(u32 unit) const = 0;

        mustuse virtual i32 width() const = 0;
        mustuse virtual i32 height() const = 0;
        mustuse virtual u32 renderer_handle() const = 0;
    };

} // namespace Fussion
