#pragma once

#include "Fussion/Types.hpp"
#include <filesystem>

namespace fussion
{

namespace fs = std::filesystem;

class Texture
{
public:
    virtual ~Texture() = default;

    mustuse static Ptr<Texture> LoadFromFile(const fs::path &path);

    virtual void Use(u32 unit) const = 0;

    mustuse virtual u32 Handle() const = 0;
};

}