#pragma once
#include "Fussion/Rendering/RendererApi.h"

namespace Fussion
{
    class OpenGLRendererAPI final : public RendererAPI
    {
    public:
        ~OpenGLRendererAPI() override = default;

        void SetClearColor(Vector3 color) override;
        void Clear() override;
        void ResizeViewport(i32 x, i32 y, i32 width, i32 height) override;

        void DrawIndexed(const Ref<VertexArray> &array) override;
    };
} // namespace Fussion
