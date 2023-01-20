#include "OpenGlRendererApi.h"
#include <glad/glad.h>

namespace Fussion
{
    void OpenGLRendererAPI::Init()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::SetClearColor(glm::vec3 color)
    {
        glClearColor(color.x, color.y, color.z, 1.0f);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::ResizeViewport(i32 x, i32 y, i32 width, i32 height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<Fussion::VertexArray> &array, u32 count)
    {
        count = count ? count : array->GetIndexBuffer()->Count();
        glDrawElements(GL_TRIANGLES, static_cast<i32>(count), GL_UNSIGNED_INT, nullptr);
    }
} // namespace Fussion
