#pragma once
#include "Event.hpp"
#include "Fussion/Types.hpp"

namespace fussion
{

class MouseMoved : public Event
{
    double x {};
    double y {};

public:
    EVENT(MouseMoved)
    MouseMoved(double x, double y) :
        x(x), y(y)
    {
    }

    mustuse double X() const { return x; }
    mustuse double Y() const { return y; }
};

enum class MouseButton {
    Left,
    Right,
    Middle,
    Button4,
    Button5,
    Button6,
    Button7,
    Button8,
};

class MouseButtonPressed : public Event
{
    MouseButton button {};

public:
    EVENT(MouseButtonPressed)
    explicit MouseButtonPressed(MouseButton button) :
        button(button)
    {
    }

    mustuse MouseButton Button() const { return button; }
};

class MouseButtonReleased : public Event
{
    MouseButton button {};

public:
    EVENT(MouseButtonReleased)
    explicit MouseButtonReleased(MouseButton b) :
        button(b)
    {
    }

    mustuse MouseButton Button() const { return button; }
};

class MouseWheelMoved : public Event
{
    float x_offset { 0.0f };
    float y_offset { 0.0f };

public:
    EVENT(MouseWheelMoved)
    explicit MouseWheelMoved(float x, float y) :
        x_offset(x), y_offset(y)
    {
    }

    mustuse std::pair<float, float> Offset() const { return { x_offset, y_offset }; }
};

}
