#pragma once
#include "Fussion/Rendering/RenderCommand.h"
#include "Fussion/Rendering/VertexArray.h"

namespace Fussion
{

    class Renderer final
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const Ref<VertexArray> &array);

        inline static RendererAPI::API GetAPI()
        {
            return RendererAPI::GetAPI();
        }
    };

} // namespace Fussion
