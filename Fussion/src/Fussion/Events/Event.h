#pragma once
#include "Fussion/Core/Core.h"
#include "Fussion/Core/Types.h"
#include "Fussion/Debug/Profiling.h"
#include "Fussion/Input/Keys.h"
#include <concepts>
#include <functional>

#define FSN_BIND_FN(fn) [this](auto &&PH1) { return fn(std::forward<decltype(PH1)>(PH1)); }

#define EVENT(name)                 \
    static EventType static_type()  \
    {                               \
        return EventType::name;     \
    }                               \
                                    \
    EventType type() const override \
    {                               \
        return static_type();       \
    }

#define EVENT_TOSTRING(name)          \
    String to_string() const override \
    {                                 \
        return #name;                 \
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

        mustuse virtual EventType type() const = 0;
        mustuse virtual String to_string() const = 0;
    };

    class Dispatcher
    {
        Event &m_event;

    public:
        template<std::derived_from<Event> T>
        using EventFn = std::function<bool(T &)>;

        explicit Dispatcher(Event &e) : m_event(e)
        {
        }

        template<std::derived_from<Event> T>
        void dispatch(EventFn<T> fn)
        {
            FSN_PROFILE_FUNCTION();
            if (m_event.Handled || m_event.type() != T::static_type())
                return;

            m_event.Handled = fn(dynamic_cast<T &>(m_event));
        }
    };

} // namespace Fussion
