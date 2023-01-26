#pragma once
#include "Fussion/Rendering/RendererApi.h"

namespace Fussion
{
    class OpenGLRendererAPI final : public RendererAPI
    {
    public:
        ~OpenGLRendererAPI() override = default;

        void init() override;
        void set_clear_color(glm::vec3 color) override;
        void clear() override;
        void resize_viewport(i32 x, i32 y, i32 width, i32 height) override;

        void draw_indexed(const Ref<VertexArray> &array, u32 count) override;
    };
} // namespace Fussion
