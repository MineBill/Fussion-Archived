#pragma once
#include "Fussion/Rendering/2D/Camera.h"
#include "Fussion/Rendering/RenderCommand.h"
#include "Fussion/Rendering/Shader.h"
#include "Fussion/Rendering/VertexArray.h"

namespace Fussion
{
    class Renderer final
    {
        struct SceneData {
            glm::mat4 Projection{};
        };
        static Ptr<SceneData> s_scene_data;

        static bool s_began_scene;

    public:
        static void init();

        static void begin_scene(const Camera2D &camera);
        static void end_scene();

        static void submit(const Ref<VertexArray> &array, const Ref<Shader> &shader,
                           const glm::mat4 &matrix = glm::mat4(1.0f));

        inline static RendererAPI::API api()
        {
            return RendererAPI::api();
        }
    };
} // namespace Fussion
