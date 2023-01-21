#include "Fussion/Core/Log.h"
#include "Fussion/Rendering/Shader.h"
#include <fstream>
#include <glad/glad.h>

namespace Fussion
{

    class OpenGLShader final : public Shader
    {
        u32 id{0};

        static String ReadEntireFile(const fs::path &filePath);
        std::unordered_map<GLenum, StringView> PreProcessPass(StringView sourceCode);
        void CompileFromSources(const std::unordered_map<GLenum, StringView> &sources);

    public:
        OpenGLShader(const fs::path &shaderPath);
        OpenGLShader(const StringView &vertex_source, const StringView &fragment_source);
        ~OpenGLShader() override;

        void Use() const override;

        void SetUniform(const StringView &name, f32 value) override;
        void SetUniform(const StringView &name, f64 value) override;
        void SetUniform(const StringView &name, i32 value) override;
        void SetUniform(const StringView &name, u32 value) override;
        void SetUniform(const StringView &name, Vector3 value) override;
        void SetUniform(const StringView &name, Matrix4 value) override;
        void SetUniform(const StringView &name, const glm::mat4 &value) override;
        void SetUniform(const StringView &name, const glm::vec4 &value) override;

        void SetArray(StringView name, i32 *array, i32 count) override;

        mustuse Optional<int> FindUniformLocation(const StringView &name) const;
        static void ReportCompilationError(u32 shader);
        static void ReportLinkingError(u32 shader);
    };

} // namespace Fussion
