#pragma once
#include "Fussion/Events/Event.hpp"
#include "Types.hpp"
#include <functional>

namespace fussion {

struct WindowProps {
    i32 width { 0 }, height { 0 };
    std::string title;
};

class Window {
public:
    using EventCallback = std::function<void(Ref<Event>)>;
    virtual ~Window() = default;

    mustuse static Ptr<Window> create(WindowProps const&);

    virtual void poll_events() const = 0;
    virtual void swap_buffers() const = 0;
    virtual void on_event(EventCallback const& callback) = 0;

    mustuse virtual bool should_close() = 0;
};

}