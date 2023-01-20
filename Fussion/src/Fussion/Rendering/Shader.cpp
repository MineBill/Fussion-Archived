#include "Fussion/Rendering/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Fussion
{
    Ref<Shader> Shader::LoadFromFile(const fs::path &shaderPath)
    {
        return std::make_unique<OpenGLShader>(shaderPath);
    }

    Ref<Shader> Shader::FromStringLiterals(const StringView &vertexSource, const StringView &fragmentSource)
    {
        return std::make_unique<OpenGLShader>(vertexSource, fragmentSource);
    }
}
