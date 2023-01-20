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
        static Ptr<SceneData> s_sceneData;

        static bool s_beganScene;

    public:
        static void Init();

        static void BeginScene(const Camera2D &camera);
        static void EndScene();

        static void Submit(const Ref<VertexArray> &array, const Ref<Shader> &shader,
                           const glm::mat4 &matrix = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI()
        {
            return RendererAPI::GetAPI();
        }
    };
} // namespace Fussion
