#pragma once
#include "Fussion/Rendering/Camera.h"
#include "Fussion/Rendering/RenderCommand.h"
#include "Fussion/Rendering/VertexArray.h"
#include "Fussion/Rendering/Shader.h"

namespace Fussion
{
    class Renderer final
    {
        static Matrix4 s_projection;

    public:
        static void BeginScene(const Camera2D &camera);
        static void EndScene();

        static void UseShader(const Ref<Shader> &shader);
        static void Submit(const Ref<VertexArray> &array);

        inline static RendererAPI::API GetAPI()
        {
            return RendererAPI::GetAPI();
        }
    };
} // namespace Fussion
