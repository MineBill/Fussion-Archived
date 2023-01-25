#pragma once
#include "Fussion/Core/Core.h"
#include "Fussion/Core/Types.h"
#include "Fussion/Debug/Profiling.h"
#include "Fussion/Input/Keys.h"
#include <concepts>
#include <functional>

#define FSN_BIND_FN(fn) [this](auto &&PH1) { return fn(std::forward<decltype(PH1)>(PH1)); }

#define EVENT(name)                 \
    static EventType StaticType()   \
    {                               \
        return EventType::name;     \
    }                               \
                                    \
    EventType Type() const override \
    {                               \
        return StaticType();        \
    }

#define EVENT_TOSTRING(name)         \
    String ToString() const override \
    {                                \
        return #name;                \
    }

namespace Fussion
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

    public:
        bool Handled{false};

        virtual ~Event() = default;

        mustuse virtual EventType Type() const = 0;
        mustuse virtual String ToString() const = 0;
    };

    class Dispatcher
    {
        Event &event;

    public:
        template<typename T>
        using EventFn = std::function<bool(T &)>;

        explicit Dispatcher(Event &e) : event(e)
        {
        }

        template<std::derived_from<Event> T>
        void Dispatch(EventFn<T> fn)
        {
            FSN_PROFILE_FUNCTION();
            if (event.Handled || event.Type() != T::StaticType())
                return;

            event.Handled = fn(dynamic_cast<T &>(event));
        }
    };

} // namespace Fussion
