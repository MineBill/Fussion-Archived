#include "Fussion/Rendering/Shader.hpp"
#include <glad/glad.h>
#include <fstream>

namespace fussion {

class ShaderImpl final : public Shader {
    u32 id { 0 };

public:
    ShaderImpl(const fs::path &vertex_path, const fs::path &fragment_path) {
        std::ifstream vertex_file(vertex_path);
        //        id = glCreateProgram()
    }

    ~ShaderImpl() override = default;

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
}

}