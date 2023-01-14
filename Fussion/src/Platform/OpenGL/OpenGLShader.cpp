#include "Fussion/Rendering/Shader.h"
#include <fstream>
#include <glad/glad.h>
#include <iostream>

using namespace fussion;

class OpenGLShader final : public Shader
{
    u32 id { 0 };

public:
    OpenGLShader(const fs::path &vertex_path, const fs::path &fragment_path)
    {
        std::ifstream vertex_file(vertex_path);
        std::stringstream buffer;
        buffer << vertex_file.rdbuf();

        auto vertex = glCreateShader(GL_VERTEX_SHADER);
        auto str = buffer.str();
        auto c_str = str.c_str();
        glShaderSource(vertex, 1, &c_str, nullptr);
        glCompileShader(vertex);
        ReportCompilationError(vertex);

        std::ifstream fragment_file(fragment_path);
        std::stringstream new_buffer_because_cpp_is_shit;
        new_buffer_because_cpp_is_shit << fragment_file.rdbuf();

        str = new_buffer_because_cpp_is_shit.str();
        c_str = str.c_str();
        auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &c_str, nullptr);
        glCompileShader(fragment);
        ReportCompilationError(fragment);

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);


        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    OpenGLShader(const StringView &vertex_source, const StringView &fragment_source)
    {
        auto vertex = glCreateShader(GL_VERTEX_SHADER);
        auto c_str = vertex_source.data();
        glShaderSource(vertex, 1, &c_str, nullptr);
        glCompileShader(vertex);

        c_str = fragment_source.data();
        auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &c_str, nullptr);
        glCompileShader(fragment);

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        ReportCompilationError(id);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    ~OpenGLShader() override = default;

    void Use() const override
    {
        glUseProgram(id);
    }

    void SetUniform(const StringView &name, f32 value) override
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1f(*loc, value);
        }
    }

    void SetUniform(const StringView &name, f64 value) override
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1d(*loc, value);
        }
    }

    void SetUniform(const StringView &name, i32 value) override
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1i(*loc, value);
        }
    }

    void SetUniform(const StringView &name, u32 value) override
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform1ui(*loc, value);
        }
    }

    void SetUniform(const StringView &name, Vector3 value) override
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniform3f(*loc, value.x(), value.y(), value.z());
        }
    }

    void SetUniform(const StringView &name, Matrix4 value) override
    {
        if (auto loc = FindUniformLocation(name)) {
            glUniformMatrix4fv(*loc, 1, GL_FALSE, value.data.data());
        }
    }

    mustuse Optional<int> FindUniformLocation(const StringView &name) const
    {
        Use();
        if (auto loc = glGetUniformLocation(id, name.data()); loc != -1) {
            return loc;
        }
        return {};
    }

    void ReportCompilationError(u32 shader)
    {
        i32 status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_TRUE) return;

        char message[512];
        glGetShaderInfoLog(shader, 512, nullptr, message);
        std::cout << "SHADER ERROR: " << std::string(message) << std::endl;
    }
};

Ptr<Shader> Shader::Create(const fs::path &vertex_path, const fs::path &fragment_path)
{
    return std::make_unique<OpenGLShader>(vertex_path, fragment_path);
}

Ptr<Shader> Shader::FromStringLiterals(const StringView &vertex_path, const StringView &fragment_path)
{
    return std::make_unique<OpenGLShader>(vertex_path, fragment_path);
}
