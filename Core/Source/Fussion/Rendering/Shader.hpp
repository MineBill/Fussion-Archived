#pragma once
#include "Fussion/Types.hpp"
#include <filesystem>

namespace fussion {

namespace {
namespace fs = std::filesystem;
}

class Shader {
public:
    virtual ~Shader() = default;

    static Ptr<Shader> create(const fs::path& vertex_path, const fs::path& fragment_path);

    virtual void set_uniform(std::string name, f32 value) = 0;
    virtual void set_uniform(std::string name, f64 value) = 0;
    virtual void set_uniform(std::string name, u32 value) = 0;
    virtual void set_uniform(std::string name, i32 value) = 0;
};

}