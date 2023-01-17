#include "OpenGlRendererApi.h"
#include <glad/glad.h>

namespace Fussion
{
    void OpenGLRendererAPI::SetClearColor(Vector3 color)
    {
        glClearColor(color.x(), color.y(), color.z(), 1.0f);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::ResizeViewport(i32 x, i32 y, i32 width, i32 height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<Fussion::VertexArray> &array)
    {
        glDrawElements(GL_TRIANGLES, array->Count(), GL_UNSIGNED_INT, nullptr);
    }
} // namespace Fussion
