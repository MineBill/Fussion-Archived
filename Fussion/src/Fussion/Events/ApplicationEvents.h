#pragma once
#include "Event.h"
#include "Fussion/Types.h"

namespace fussion
{

class WindowClosed : public Event
{
public:
    EVENT(WindowClosed)
    WindowClosed() = default;
};

class WindowResized : public Event
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
};

class WindowMinimized : public Event
{
public:
    EVENT(WindowMinimized)
    WindowMinimized() = default;
};

class WindowMaximized : public Event
{
public:
    EVENT(WindowMaximized)
    WindowMaximized() = default;
};

class WindowGainedFocus : public Event
{
public:
    EVENT(WindowGainedFocus)
    WindowGainedFocus() = default;
};

class WindowLostFocus : public Event
{
public:
    EVENT(WindowLostFocus)
    WindowLostFocus() = default;
};

}
