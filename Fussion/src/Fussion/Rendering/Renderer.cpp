#include "Renderer.h"

namespace Fussion
{
    void Renderer::BeginScene()
    {
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<VertexArray> &array)
    {
        array->Use();
        RenderCommand::DrawIndexed(array);
    }
} // namespace Fussion