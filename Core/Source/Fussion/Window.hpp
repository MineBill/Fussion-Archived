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

    mustuse static Ptr<Window> Create(WindowProps const&);

    virtual void PollEvents() const = 0;
    virtual void SwapBuffers() const = 0;
    virtual void OnEvent(EventCallback const& callback) = 0;

    mustuse virtual bool ShouldClose() = 0;
};

}