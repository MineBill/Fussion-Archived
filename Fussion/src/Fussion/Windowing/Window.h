#pragma once
#include "Fussion/Core/Types.h"
#include "Fussion/Events/Event.h"
#include "VideoMode.h"
#include <functional>

namespace Fussion
{

    struct WindowProps {
        int width{0};
        int height{0};
        std::string title;
    };

    class Window
    {
    public:
        using EventCallback = std::function<void(Ptr<Event>)>;
        virtual ~Window() = default;

        mustuse static Ptr<Window> Create(WindowProps const &);

        virtual void poll_events() const = 0;
        virtual void swap_buffers() const = 0;
        virtual void set_event_callback(EventCallback const &callback) = 0;
        virtual void set_vsync(bool enabled) = 0;
        virtual void set_should_close(bool enabled) = 0;

        mustuse virtual std::vector<VideoMode> video_modes() const = 0;
        mustuse virtual bool should_close() = 0;
        mustuse virtual std::pair<i32, i32> size() const = 0;
        mustuse virtual void *raw_ptr() = 0;
    };

} // namespace Fussion
