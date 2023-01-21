#pragma once
#include "Fussion/Core/Types.h"
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Math/Vector3.h"
#include "Texture.h"
#include <filesystem>

namespace Fussion
{

    namespace fs = std::filesystem;

    class Shader
    {
    public:
        virtual ~Shader() = default;

        static Ref<Shader> LoadFromFile(const fs::path &shaderPath);
        static Ref<Shader> FromStringLiterals(const StringView &vertex_source, const StringView &fragment_source);

        virtual void Use() const = 0;

        virtual void SetUniform(const StringView &name, f32 value) = 0;
        virtual void SetUniform(const StringView &name, f64 value) = 0;
        virtual void SetUniform(const StringView &name, i32 value) = 0;
        virtual void SetUniform(const StringView &name, u32 value) = 0;
        virtual void SetUniform(const StringView &name, Vector3 value) = 0;
        virtual void SetUniform(const StringView &name, Matrix4 value) = 0;
        virtual void SetUniform(const StringView &name, const glm::mat4 &value) = 0;
        virtual void SetUniform(const StringView &name, const glm::vec4 &value) = 0;

        virtual void SetArray(StringView name, i32 *array, i32 count) = 0;
    };

} // namespace Fussion
