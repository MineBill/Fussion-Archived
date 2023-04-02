#pragma once
#include "Event.h"
#include "Fussion/Core/Types.h"
#include <spdlog/fmt/bundled/core.h>

namespace Fussion
{

    class MouseMoved : public Event
    {
        f64 m_x{};
        f64 m_y{};

        f64 m_rel_x{};
        f64 m_rel_y{};

    public:
        EVENT(MouseMoved)
        MouseMoved(f64 x, f64 y, f64 rel_x, f64 rel_y) : m_x(x), m_y(y), m_rel_x(rel_x), m_rel_y(rel_y)
        {
        }

        mustuse f64 x() const
        {
            return m_x;
        }
        mustuse f64 y() const
        {
            return m_y;
        }

        mustuse f64 rel_x() const
        {
            return m_rel_x;
        }
        mustuse f64 rel_y() const
        {
            return m_rel_y;
        }

        mustuse String to_string() const override
        {
            return fmt::format("MouseMoved(x: {}, y: {})", m_x, m_y);
        }
    };

    enum class MouseButton {
        None,
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
        MouseButton m_button{};

    public:
        EVENT(MouseButtonPressed)
        explicit MouseButtonPressed(MouseButton button) : m_button(button)
        {
        }

        mustuse MouseButton button() const
        {
            return m_button;
        }

        mustuse String to_string() const override
        {
            return fmt::format("MouseButtonPressed({})", static_cast<i32>(m_button));
        }
    };

    class MouseButtonReleased : public Event
    {
        MouseButton m_button{};

    public:
        EVENT(MouseButtonReleased)
        explicit MouseButtonReleased(MouseButton b) : m_button(b)
        {
        }

        mustuse MouseButton button() const
        {
            return m_button;
        }

        mustuse String to_string() const override
        {
            return fmt::format("MouseButtonReleased({})", static_cast<i32>(m_button));
        }
    };

    class MouseButtonDown : public Event
    {
        MouseButton m_button{};

    public:
        EVENT(MouseButtonDown)
        explicit MouseButtonDown(MouseButton button) : m_button(button)
        {
        }

        mustuse MouseButton button() const
        {
            return m_button;
        }

        mustuse String to_string() const override
        {
            return fmt::format("MouseButtonDown({})", static_cast<i32>(m_button));
        }
    };

    class MouseWheelMoved : public Event
    {
        float m_x_offset{0.0f};
        float m_y_offset{0.0f};

    public:
        EVENT(MouseWheelMoved)
        explicit MouseWheelMoved(float x, float y) : m_x_offset(x), m_y_offset(y)
        {
        }

        mustuse glm::vec2 offset() const
        {
            return {m_x_offset, m_y_offset};
        }

        mustuse String to_string() const override
        {
            return fmt::format("MouseWheelMoved(x_offset: {}, y_offset: {})", m_x_offset, m_y_offset);
        }
    };

} // namespace Fussion
