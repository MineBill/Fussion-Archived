#pragma once
#include "Event.hpp"
#include "Fussion/Types.hpp"

namespace fussion {

class WindowClosed : public Event {
public:
    EVENT(WindowClosed)
    WindowClosed() = default;
};

class WindowResized : public Event {
    i32 m_width, m_height;

public:
    EVENT(WindowResized)
    explicit WindowResized(i32 width, i32 height)
        : m_width(width)
        , m_height(height) {
    }

    mustuse i32 width() const { return m_width; }
    mustuse i32 height() const { return m_height; }
};

class WindowMoved : public Event {
    u32 m_x, m_y;

public:
    EVENT(WindowMoved)
    explicit WindowMoved(u32 new_x, u32 new_y)
        : m_x(new_x)
        , m_y(new_y) {
    }

    mustuse u32 x() const { return m_x; }
    mustuse u32 y() const { return m_y; }
};

class WindowMinimized : public Event {
public:
    EVENT(WindowMinimized)
    WindowMinimized() = default;
};

class WindowMaximized : public Event {
public:
    EVENT(WindowMaximized)
    WindowMaximized() = default;
};

class WindowGainedFocus : public Event {
public:
    EVENT(WindowGainedFocus)
    WindowGainedFocus() = default;
};

class WindowLostFocus : public Event {
public:
    EVENT(WindowLostFocus)
    WindowLostFocus() = default;
};

}
