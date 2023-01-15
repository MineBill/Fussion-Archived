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
        void DrawIndexed(const Ref<VertexArray> &array) override;
    };
} // namespace Fussion
