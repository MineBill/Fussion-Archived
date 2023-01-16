#include "Renderer.h"
#include "Shader.h"

namespace Fussion
{
    Matrix4 Renderer::s_projection;

    void Renderer::BeginScene(const Camera2D &camera)
    {
        s_projection = camera.GetProjection() * camera.GetProjection();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::UseShader(const Ref<Shader> &shader)
    {
        shader->Use();

        // Set the per-scene data for the shader
        shader->SetUniform("u_Projection", s_projection);
    }

    void Renderer::Submit(const Ref<VertexArray> &array)
    {
        array->Use();
        RenderCommand::DrawIndexed(array);
    }
} // namespace Fussion