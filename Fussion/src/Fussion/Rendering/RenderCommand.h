#pragma once
#include "Fussion/Rendering/RendererApi.h"

namespace Fussion
{
    class RenderCommand
    {
        static RendererAPI *s_api;

    public:
        inline static void inti()
        {
            s_api->init();
        }
        inline static void set_clear_color(glm::vec3 color)
        {
            s_api->set_clear_color(color);
        }

        inline static void clear()
        {
            s_api->clear();
        }

        inline static void resize_viewport(i32 x, i32 y, i32 width, i32 height)
        {
            s_api->resize_viewport(x, y, width, height);
        }

        inline static void draw_indexed(const Ref<VertexArray> &array, u32 count = 0)
        {
            s_api->draw_indexed(array, count);
        }
    };
} // namespace Fussion
