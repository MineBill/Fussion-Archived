#include "Fussion/Rendering/Renderer.h"
#include "Fussion/Rendering/2D/Renderer2D.h"
#include "Fussion/Rendering/Shader.h"

namespace Fussion
{
    Ptr<Renderer::SceneData> Renderer::s_scene_data = std::make_unique<SceneData>();

    bool Renderer::s_began_scene = false;

    void Renderer::init()
    {
        RenderCommand::inti();
        Renderer2D::init();
    }

    void Renderer::begin_scene(const Camera2D &camera)
    {
        FSN_CORE_ASSERT(!s_began_scene, "Did you forget to call end_scene()?")

        s_scene_data->Projection = camera.projection() * camera.view();
        s_began_scene = true;
    }

    void Renderer::end_scene()
    {
        s_began_scene = false;
    }

    void Renderer::submit(const Ref<VertexArray> &array, const Ref<Shader> &shader, const glm::mat4 &matrix)
    {
        shader->bind();
        shader->set_uniform("u_ViewProjection", s_scene_data->Projection);
        shader->set_uniform("u_Model", matrix);

        array->bind();
        RenderCommand::draw_indexed(array);
    }
} // namespace Fussion
