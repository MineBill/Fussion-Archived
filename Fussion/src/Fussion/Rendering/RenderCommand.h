#pragma once
#include "Fussion/Rendering/RendererApi.h"

namespace Fussion
{
    class RenderCommand
    {
        static RendererAPI *s_api;

    public:
        inline static void SetClearColor(Vector3 color)
        {
            s_api->SetClearColor(color);
        }

        inline static void Clear()
        {
            s_api->Clear();
        }

        inline static void ResizeViewport(i32 x, i32 y, i32 width, i32 height)
        {
            s_api->ResizeViewport(x, y, width, height);
        }

        inline static void DrawIndexed(const Ref<VertexArray> &array)
        {
            s_api->DrawIndexed(array);
        }
    };
} // namespace Fussion