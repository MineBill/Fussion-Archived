#pragma once

namespace Fussion
{

    class RenderContext
    {
    public:
        virtual ~RenderContext() = default;

        virtual void init() = 0;

        virtual void swap_buffers() = 0;
    };

} // namespace Fussion