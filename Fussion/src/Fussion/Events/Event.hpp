#pragma once
#include "Fussion/Input/Keys.hpp"
#include "Fussion/Types.hpp"
#include <concepts>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#define EVENT(name)                       \
    static EventType StaticType()         \
    {                                     \
        return EventType::name;           \
    }                                     \
                                          \
    EventType Type() const override       \
    {                                     \
        return StaticType();              \
    }                                     \
                                          \
    std::string ToString() const override \
    {                                     \
        return #name;                     \
    }

namespace fussion
{

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
    MouseButtonDown,
    MouseWheelMoved,
};

class Event
{
    friend class Dispatcher;

protected:
    bool handled { false };

public:
    virtual ~Event() = default;

    mustuse virtual EventType Type() const = 0;
    mustuse virtual std::string ToString() const = 0;
};

class Dispatcher
{
    Ref<Event> event;

public:
    template<typename T>
    using EventFn = std::function<void(Ref<T>)>;

    explicit Dispatcher(Ref<Event> e) :
        event(std::move(e))
    {
    }

    template<std::derived_from<Event> T>
    void Dispatch(EventFn<T> fn)
    {
        if (event->handled || event->Type() != T::StaticType())
            return;

        fn(std::dynamic_pointer_cast<T>(event));
        event->handled = true;
    }

    template<std::derived_from<Event> T>
    void DispatchNoConsume(EventFn<T> fn)
    {
        if (event->handled || event->Type() != T::StaticType())
            return;

        fn(std::dynamic_pointer_cast<T>(event));
    }
};

}
