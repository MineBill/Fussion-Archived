#pragma once
#include "Event.h"
#include "Fussion/Types.h"
#include <format>

namespace fussion
{

class WindowClosed : public Event
{
public:
    EVENT(WindowClosed)
    WindowClosed() = default;
};

class WindowResized final : public Event
{
    int width {};
    int height {};

public:
    EVENT(WindowResized)
    explicit WindowResized(int w, int h) :
        width(w), height(h)
    {
    }

    mustuse int Width() const { return width; }
    mustuse int Height() const { return height; }

    mustuse String ToString() const override
    {
        return std::format("WindowResized(width: {}, height: {})", width, height);
    }
};

class WindowMoved : public Event
{
    unsigned x {};
    unsigned y {};

public:
    EVENT(WindowMoved)
    explicit WindowMoved(unsigned new_x, unsigned new_y) :
        x(new_x), y(new_y)
    {
    }

    mustuse unsigned X() const { return x; }
    mustuse unsigned Y() const { return y; }

    mustuse String ToString() const override
    {
        return std::format("WindowMoved({}, {})", x, y);
    }
};

class WindowMinimized : public Event
{
public:
    EVENT(WindowMinimized)
    EVENT_TOSTRING(WindowMinimized)
    WindowMinimized() = default;
};

class WindowMaximized : public Event
{
public:
    EVENT(WindowMaximized)
    EVENT_TOSTRING(WindowMaximized)
    WindowMaximized() = default;
};

class WindowGainedFocus : public Event
{
public:
    EVENT(WindowGainedFocus)
    EVENT_TOSTRING(WindowGainedFocus)
    WindowGainedFocus() = default;
};

class WindowLostFocus : public Event
{
public:
    EVENT(WindowLostFocus)
    EVENT_TOSTRING(WindowLostFocus)
    WindowLostFocus() = default;
};

}
