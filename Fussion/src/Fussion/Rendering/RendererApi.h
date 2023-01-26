#pragma once
#include "Fussion/Math/Vector3.h"
#include "VertexArray.h"

namespace Fussion
{
    class RendererAPI
    {
    public:
        enum class API {
            None = 0,
            OpenGL
        };

    private:
        static API s_api;

    public:
        virtual ~RendererAPI() = default;

        virtual void init() = 0;
        virtual void set_clear_color(glm::vec3 color) = 0;
        virtual void clear() = 0;
        virtual void resize_viewport(i32 x, i32 y, i32 width, i32 height) = 0;

        virtual void draw_indexed(const Ref<VertexArray> &array, u32 count = 0) = 0;

        inline static API api()
        {
            return s_api;
        }
    };
} // namespace Fussion
