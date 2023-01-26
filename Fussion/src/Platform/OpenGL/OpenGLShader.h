#include "Fussion/Core/Log.h"
#include "Fussion/Rendering/Shader.h"
#include <fstream>
#include <glad/glad.h>

namespace Fussion
{

    class OpenGLShader final : public Shader
    {
        u32 id{0};

        static String read_entire_file(const fs::path &filePath);
        std::unordered_map<GLenum, StringView> pre_process_pass(StringView sourceCode);
        void compile_from_sources(const std::unordered_map<GLenum, StringView> &sources);

    public:
        OpenGLShader(const fs::path &shaderPath);
        OpenGLShader(const StringView &vertex_source, const StringView &fragment_source);
        ~OpenGLShader() override;

        void bind() const override;

        void set_uniform(const StringView &name, f32 value) override;
        void set_uniform(const StringView &name, f64 value) override;
        void set_uniform(const StringView &name, i32 value) override;
        void set_uniform(const StringView &name, u32 value) override;
        void set_uniform(const StringView &name, Vector3 value) override;
        void set_uniform(const StringView &name, Matrix4 value) override;
        void set_uniform(const StringView &name, const glm::mat4 &value) override;
        void set_uniform(const StringView &name, const glm::vec4 &value) override;

        void set_array(StringView name, i32 *array, i32 count) override;

        mustuse Optional<int> find_uniform_location(const StringView &name) const;
        static void report_compilation_error(u32 shader);
        static void report_linking_error(u32 shader);
    };

} // namespace Fussion
