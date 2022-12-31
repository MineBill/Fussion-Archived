#pragma once
#include "Event.hpp"

namespace fussion {

class MouseMoved : public Event {
public:
    EVENT(MouseMoved)
    MouseMoved(f64 x, f64 y)
        : m_x(x)
        , m_y(y) {
    }

    [[nodiscard]] f64 x() const { return m_x; }
    [[nodiscard]] f64 y() const { return m_y; }

private:
    f64 m_x, m_y;
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

class MouseButtonPressed : public Event {
public:
    EVENT(MouseButtonPressed)
    explicit MouseButtonPressed(MouseButton button)
        : m_button(button) {
    }

    [[nodiscard]] MouseButton button() const { return m_button; }

private:
    MouseButton m_button {};
};

class MouseButtonReleased : public Event {
public:
    EVENT(MouseButtonReleased)
    explicit MouseButtonReleased(MouseButton button)
        : m_button(button) {
    }

    [[nodiscard]] MouseButton button() const { return m_button; }

private:
    MouseButton m_button {};
};

class MouseWheelMoved : public Event {
public:
    EVENT(MouseWheelMoved)
    explicit MouseWheelMoved(f32 x, f32 y)
        : m_x_offset(x)
        , m_y_offset(y) {
    }

    [[nodiscard]] f32 x_offset() const { return m_x_offset; }
    [[nodiscard]] f32 y_offset() const { return m_y_offset; }

private:
    f32 m_x_offset { 0.0f }, m_y_offset { 0.0f };
};

}
