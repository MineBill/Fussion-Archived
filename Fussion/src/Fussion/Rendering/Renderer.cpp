#include "Renderer.h"
#include "Shader.h"

namespace Fussion
{
    glm::mat4 Renderer::s_projection;
    bool Renderer::s_beganScene = false;

    void Renderer::BeginScene(const Camera2D &camera)
    {
        FSN_CORE_ASSERT(!s_beganScene, "Did you forget to call EndScene()?")

        s_projection = camera.GetProjection() * glm::inverse(camera.GetView());
        s_beganScene = true;
    }

    void Renderer::EndScene()
    {
        s_beganScene = false;
    }

    void Renderer::UseShader(const Ref<Shader> &shader)
    {
        shader->Use();

        // Set the per-scene data for the shader
        shader->SetUniform("u_ViewProjection", s_projection);
    }

    void Renderer::Submit(const Ref<VertexArray> &array)
    {
        array->Use();
        RenderCommand::DrawIndexed(array);
    }
} // namespace Fussion