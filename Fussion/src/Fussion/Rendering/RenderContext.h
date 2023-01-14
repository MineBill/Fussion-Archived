#pragma once

namespace Fussion
{

    class RenderContext
    {
    public:
        virtual ~RenderContext() = default;

        virtual void Init() = 0;

        virtual void SwapBuffers() = 0;
    };

} // namespace Fussion