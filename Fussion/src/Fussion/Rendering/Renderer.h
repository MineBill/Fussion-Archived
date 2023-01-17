#pragma once
#include "Fussion/Rendering/Camera.h"
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
        static void BeginScene(const Camera2D &camera);
        static void EndScene();

        static void Submit(const Ref<VertexArray> &array, const Ref<Shader> &shader);

        inline static RendererAPI::API GetAPI()
        {
            return RendererAPI::GetAPI();
        }
    };
} // namespace Fussion
