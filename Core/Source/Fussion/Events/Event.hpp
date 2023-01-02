#pragma once
#include "Fussion/Input/Keys.hpp"
#include "Fussion/Types.hpp"
#include <concepts>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#define EVENT(name)                          \
    static EventType static_type() {         \
        return EventType::name;              \
    }                                        \
                                             \
    EventType type() const override {        \
        return static_type();                \
    }                                        \
                                             \
    std::string to_string() const override { \
        return #name;                        \
    }

namespace fussion {

enum class EventType {
    OnKeyPressed = 0,
    OnKeyReleased,
    OnKeyDown,
    WindowClosed,
    WindowResized,
    WindowMoved,
    WindowMinimized,
    WindowMaximized,
    WindowGainedFocus,
    WindowLostFocus,
    MouseMoved,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseWheelMoved,
};

class Event {
    friend class Dispatcher;

public:
    virtual ~Event() = default;

    mustuse virtual EventType type() const = 0;
    mustuse virtual std::string to_string() const = 0;

protected:
    bool m_handled { false };
};

class Dispatcher {
    Ref<Event> m_event;

public:
    template<typename T>
    using EventFn = std::function<void(Ref<T>)>;

    explicit Dispatcher(Ref<Event> event)
        : m_event(std::move(event)) {
    }

    template<std::derived_from<Event> T>
    void dispatch(EventFn<T> fn) {
        if (m_event->m_handled || m_event->type() != T::static_typef()) return;

        fn(std::dynamic_pointer_cast<T>(m_event));
        m_event->m_handled = true;
    }

    template<std::derived_from<Event> T>
    void dispatch_no_consume(EventFn<T> fn) {
        if (m_event->m_handled || m_event->type() != T::static_type()) return;

        fn(std::dynamic_pointer_cast<T>(m_event));
    }
};

}
