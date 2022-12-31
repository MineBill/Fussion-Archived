#pragma once
#include "Fussion/Input/Keys.hpp"
#include "Fussion/Types.hpp"
#include <functional>
#include <string>
#include <utility>
#include <vector>

#define EVENT(name)                         \
    static EventType StaticType() {         \
        return EventType::name;             \
    }                                       \
                                            \
    EventType Type() const override {       \
        return StaticType();                \
    }                                       \
                                            \
    std::string ToString() const override { \
        return #name;                       \
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

    mustuse virtual EventType Type() const = 0;
    mustuse virtual std::string ToString() const = 0;

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
    template<typename T>
    void Dispatch(EventFn<T> fn) {
        if (m_event->Type() == T::StaticType()) {
            fn(std::dynamic_pointer_cast<T>(m_event));
            m_event->m_handled = true;
        }
    }

    template<typename T>
    void DispatchNoConsume(EventFn<T> fn) {
        if (m_event->Type() == T::StaticType()) {
            fn(std::dynamic_pointer_cast<T>(m_event));
        }
    }
};

}
