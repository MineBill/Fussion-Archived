#include "Renderer.h"
#include "Shader.h"

namespace Fussion
{
    Ptr<Renderer::SceneData> Renderer::s_sceneData = std::make_unique<SceneData>();

    bool Renderer::s_beganScene = false;

    void Renderer::BeginScene(const Camera2D &camera)
    {
        FSN_CORE_ASSERT(!s_beganScene, "Did you forget to call EndScene()?")

        s_sceneData->Projection = camera.GetProjection() * camera.GetView();
        s_beganScene = true;
    }

    void Renderer::EndScene()
    {
        s_beganScene = false;
    }

    void Renderer::Submit(const Ref<VertexArray> &array, const Ref<Shader> &shader)
    {
        shader->Use();
        shader->SetUniform("u_ViewProjection", s_sceneData->Projection);

        array->Use();
        RenderCommand::DrawIndexed(array);
    }
} // namespace Fussion