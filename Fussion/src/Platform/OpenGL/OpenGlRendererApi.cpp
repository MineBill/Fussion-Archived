#include "OpenGlRendererApi.h"
#include <glad/glad.h>

namespace Fussion
{
    void OpenGLRendererAPI::init()
    {
        //glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::set_clear_color(glm::vec3 color)
    {
        glClearColor(color.x, color.y, color.z, 1.0f);
    }

    void OpenGLRendererAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::resize_viewport(i32 x, i32 y, i32 width, i32 height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::draw_indexed(const Ref<Fussion::VertexArray> &array, u32 count)
    {
        count = count ? count : array->index_buffer()->count();
        glDrawElements(GL_TRIANGLES, static_cast<i32>(count), GL_UNSIGNED_INT, nullptr);
    }
} // namespace Fussion
