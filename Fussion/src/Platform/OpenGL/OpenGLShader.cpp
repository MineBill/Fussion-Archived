#include "OpenGLShader.h"
#include "Fussion/Core/Core.h"
#include "Fussion/Core/Log.h"
#include "Fussion/Rendering/Shader.h"
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Fussion
{
    String OpenGLShader::ReadEntireFile(const fs::path &filePath)
    {
        std::ifstream file(filePath);
        FSN_CORE_ASSERT(file.is_open(), "Failed to open file: {}, CWD: {}", filePath.string(),
                        fs::current_path().string())
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }

    OpenGLShader::OpenGLShader(const fs::path &shaderPath)
    {
        String sourceCode = ReadEntireFile(shaderPath);
        auto sources = PreProcessPass(sourceCode);
        CompileFromSources(sources);
    }

    OpenGLShader::OpenGLShader(const StringView &vertex_source, const StringView &fragment_source)
    {
        std::unordered_map<GLenum, StringView> sources(2);
        sources[GL_VERTEX_SHADER] = vertex_source;
        sources[GL_FRAGMENT_SHADER] = fragment_source;
        CompileFromSources(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(id);
    }

    void OpenGLShader::CompileFromSources(const std::unordered_map<GLenum, StringView> &sources)
    {
        std::array<GLenum, 2> shadersToDelete{};

        id = glCreateProgram();
        std::size_t index = 0;
        for (const auto &[type, source] : sources) {
            String str{source};
            auto shader = glCreateShader(type);
            auto c_str = str.c_str();
            glShaderSource(shader, 1, &c_str, nullptr);
            glCompileShader(shader);
            ReportCompilationError(shader);
            glAttachShader(id, shader);
            shadersToDelete[index++] = shader;
        }
        glLinkProgram(id);
        ReportLinkingError(id);

        for (const auto shader : shadersToDelete) {
            glDeleteShader(shader);
        }
    }

    std::unordered_map<GLenum, StringView> OpenGLShader::PreProcessPass(StringView sourceCode)
    {
        const auto ShaderTypeFromString = [](StringView string) -> GLenum {
            if (string == "vertex")
                return GL_VERTEX_SHADER;
            else if (string == "fragment")
                return GL_FRAGMENT_SHADER;
            FSN_CORE_ASSERT(false, "Unknown shader type: {}", string)
        };
        constexpr const auto *tokenIdent = "#type";
        constexpr const auto tokenCount = 5;
        std::unordered_map<GLenum, StringView> sources;
        auto token = sourceCode.find(tokenIdent);
        while (token != StringView::npos) {
            auto lineEnd = sourceCode.find_first_of("\n\r", token);
            auto start = token + tokenCount + 1;
            auto type = sourceCode.substr(start, lineEnd - start);

            token = sourceCode.find(tokenIdent, lineEnd);

            auto end = token == StringView::npos ? sourceCode.size() : token - 1;

            sources[ShaderTypeFromString(type)] = sourceCode.substr(lineEnd + 1, end - lineEnd);
        }
        return sources;
    }

    void OpenGLShader::Use() const
    {
        glUseProgram(id);
    }

    void OpenGLShader::SetUniform(const StringView &name, f32 value)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1f(*loc, value);
        }
    }

    void OpenGLShader::SetUniform(const StringView &name, f64 value)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1d(*loc, value);
        }
    }

    void OpenGLShader::SetUniform(const StringView &name, i32 value)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1i(*loc, value);
        }
    }

    void OpenGLShader::SetUniform(const StringView &name, u32 value)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1ui(*loc, value);
        }
    }

    void OpenGLShader::SetUniform(const StringView &name, Vector3 value)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform3f(*loc, value.x(), value.y(), value.z());
        }
    }

    void OpenGLShader::SetUniform(const StringView &name, Matrix4 value)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniformMatrix4fv(*loc, 1, GL_FALSE, value.data.data());
        }
    }

    void OpenGLShader::SetUniform(const StringView &name, const glm::mat4 &value)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniformMatrix4fv(*loc, 1, GL_FALSE, glm::value_ptr(value));
        }
    }

    void OpenGLShader::SetUniform(const StringView &name, const glm::vec4 &value)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform4f(*loc, value.x, value.y, value.z, value.w);
        }
    }

    void OpenGLShader::SetArray(StringView name, i32 *array, i32 count)
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1iv(*loc, count, array);
        }
    }

    mustuse Optional<int> OpenGLShader::FindUniformLocation(const StringView &name) const
    {
        Use();
        if (auto loc = glGetUniformLocation(id, name.data()); loc != -1) {
            return loc;
        }
        FSN_CORE_WARN("Uniform '{}' does not exist.", name);
        return {};
    }

    void OpenGLShader::ReportCompilationError(u32 shader)
    {
        i32 status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_TRUE)
            return;

        char message[512];
        glGetShaderInfoLog(shader, 512, nullptr, message);
        FSN_CORE_ASSERT(false, "Shader compilation error: {}", message);
    }

    void OpenGLShader::ReportLinkingError(u32 shader)
    {
        i32 status;
        glGetProgramiv(shader, GL_LINK_STATUS, &status);
        if (status == GL_TRUE)
            return;

        char message[512];
        glGetProgramInfoLog(shader, 512, nullptr, message);
        FSN_CORE_ASSERT(false, "Shader linking error: {}", message);
    }

} // namespace Fussion
