#include "Fussion/Rendering/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Fussion
{
    Ref<Shader> Shader::Create(const fs::path &vertexPath, const fs::path &fragmentPath)
    {
        return std::make_unique<OpenGLShader>(vertexPath, fragmentPath);
    }

    Ref<Shader> Shader::FromStringLiterals(const StringView &vertexSource, const StringView &fragmentSource)
    {
        return std::make_unique<OpenGLShader>(vertexSource, fragmentSource);
    }
}