#include "Fussion/Rendering/Shader.hpp"
#include <fstream>
#include <glad/glad.h>
#include <sstream>

namespace fussion {

enum class ShaderType {

};

class OpenGLShader final : public Shader {
    u32 id { 0 };

public:
    OpenGLShader(const fs::path &vertex_path, const fs::path &fragment_path) {
        std::ifstream vertex_file(vertex_path);
        std::stringstream buffer;
        buffer << vertex_file.rdbuf();

        auto vertex = glCreateShader(GL_VERTEX_SHADER);
        auto str = buffer.str();
        auto c_str = str.c_str();
        glShaderSource(vertex, 1, &c_str, nullptr);

        std::ifstream fragment_file(fragment_path);
        buffer << fragment_file.rdbuf();

        str = buffer.str();
        c_str = str.c_str();
        auto fragment = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(fragment, 1, &c_str, nullptr);

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    ~OpenGLShader() override = default;

    void set_uniform(std::string name, f32 value) override {
        if (auto loc = find_uniform_location(name)) {
            glUniform1f(*loc, value);
        }
    }

    void set_uniform(std::string name, f64 value) override {
        if (auto loc = find_uniform_location(name)) {
            glUniform1d(*loc, value);
        }
    }

    void set_uniform(std::string name, u32 value) override {
        if (auto loc = find_uniform_location(name)) {
            glUniform1ui(*loc, value);
        }
    }

    void set_uniform(std::string name, i32 value) override {
        if (auto loc = find_uniform_location(name)) {
            glUniform1i(*loc, value);
        }
    }

    mustuse Optional<i32> find_uniform_location(std::string const &name) const {
        if (auto loc = glGetUniformLocation(id, name.c_str()); loc != -1) {
            return loc;
        }
        return {};
    }
};

Ptr<Shader> Shader::create(const fs::path &vertex_path, const fs::path &fragment_path) {
    return std::make_unique<OpenGLShader>(vertex_path, fragment_path);
}

}