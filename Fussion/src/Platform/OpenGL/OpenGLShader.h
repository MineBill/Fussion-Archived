#include "Fussion/Log.h"
#include "Fussion/Rendering/Shader.h"
#include <fstream>
#include <glad/glad.h>

namespace Fussion
{

    class OpenGLShader final : public Shader
    {
        u32 id{0};

    public:
        OpenGLShader(const fs::path &vertex_path, const fs::path &fragment_path);
        OpenGLShader(const StringView &vertex_source, const StringView &fragment_source);
        ~OpenGLShader() override;

        void Use() const override;

        void SetUniform(const StringView &name, f32 value) override;
        void SetUniform(const StringView &name, f64 value) override;
        void SetUniform(const StringView &name, i32 value) override;
        void SetUniform(const StringView &name, u32 value) override;
        void SetUniform(const StringView &name, Vector3 value) override;
        void SetUniform(const StringView &name, Matrix4 value) override;

        mustuse Optional<int> FindUniformLocation(const StringView &name) const;
        static void ReportCompilationError(u32 shader);
        static void ReportLinkingError(u32 shader);
    };

} // namespace Fussion