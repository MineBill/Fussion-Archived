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

        virtual void Init() = 0;
        virtual void SetClearColor(glm::vec3 color) = 0;
        virtual void Clear() = 0;
        virtual void ResizeViewport(i32 x, i32 y, i32 width, i32 height) = 0;

        virtual void DrawIndexed(const Ref<VertexArray> &array, u32 count = 0) = 0;

        inline static API GetAPI()
        {
            return s_api;
        }
    };
} // namespace Fussion
