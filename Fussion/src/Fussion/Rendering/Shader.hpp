#pragma once
#include "Fussion/Math/Vector3.hpp"
#include "Fussion/Types.hpp"
#include "Texture.hpp"
#include <filesystem>

namespace fussion
{

namespace fs = std::filesystem;

class Shader
{
public:
    virtual ~Shader() = default;

    static Ptr<Shader> Create(const fs::path &vertex_path, const fs::path &fragment_path);

    virtual void SetUniform(const std::string &name, f32 value) = 0;
    virtual void SetUniform(const std::string &name, f64 value) = 0;
    virtual void SetUniform(const std::string &name, i32 value) = 0;
    virtual void SetUniform(const std::string &name, u32 value) = 0;
    virtual void SetUniform(const std::string &name, Vector3 value) = 0;
};

}