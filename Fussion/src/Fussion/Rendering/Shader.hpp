#pragma once
#include "Fussion/Math/Vector3.hpp"
#include "Fussion/Math/Matrix4.hpp"
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
    static Ptr<Shader> FromStringLiterals(const StringView &vertex_source, const StringView &fragment_source);

    virtual void Use() const = 0;

    virtual void SetUniform(const StringView &name, f32 value) = 0;
    virtual void SetUniform(const StringView &name, f64 value) = 0;
    virtual void SetUniform(const StringView &name, i32 value) = 0;
    virtual void SetUniform(const StringView &name, u32 value) = 0;
    virtual void SetUniform(const StringView &name, Vector3 value) = 0;
    virtual void SetUniform(const StringView &name, Matrix4 value) = 0;
};

}
