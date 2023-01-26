#pragma once
#include "Event.h"
#include <spdlog/fmt/bundled/core.h>

namespace Fussion
{

    class OnKeyDown : public Event
    {
        Key m_key{};

    public:
        EVENT(OnKeyDown)

        explicit OnKeyDown(Key key) : m_key(key)
        {
        }

        mustuse Key key() const
        {
            return m_key;
        }

        mustuse String to_string() const override
        {
            return fmt::format("OnKeyDown({})", static_cast<i32>(m_key));
        }
    };

    class OnKeyPressed : public Event
    {
        Key m_key{};

    public:
        EVENT(OnKeyPressed)

        explicit OnKeyPressed(Key key) : m_key(key)
        {
        }

        mustuse Key key() const
        {
            return m_key;
        }

        mustuse String to_string() const override
        {
            return fmt::format("OnKeyPressed({})", static_cast<i32>(m_key));
        }
    };

    class OnKeyReleased : public Event
    {
        Key m_key{};

    public:
        EVENT(OnKeyReleased)

        explicit OnKeyReleased(Key key) : m_key(key)
        {
        }

        mustuse Key key() const
        {
            return m_key;
        }

        mustuse String to_string() const override
        {
            return fmt::format("OnKeyReleased({})", static_cast<i32>(m_key));
        }
    };

} // namespace Fussion
