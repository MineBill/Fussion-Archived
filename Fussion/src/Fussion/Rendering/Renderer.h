#pragma once

namespace Fussion
{

    enum class RenderAPI {
        None = 0,
        OpenGL,
    };

    class Renderer final
    {
        static RenderAPI s_renderApi;
    public:

        static RenderAPI GetAPI()
        {
            return s_renderApi;
        }
    };

} // namespace Fussion
