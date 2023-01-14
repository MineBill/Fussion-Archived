#pragma once
#include "Event.h"
#include <format>

namespace fussion
{

class OnKeyDown : public Event
{
    Key m_key {};

public:
    EVENT(OnKeyDown)

    explicit OnKeyDown(Key key) :
        m_key(key)
    {
    }

    mustuse Key GetKey() const { return m_key; }

    mustuse String ToString() const override
    {
        return std::format("OnKeyDown({})", static_cast<i32>(m_key));
    }
};

class OnKeyPressed : public Event
{
    Key m_key {};

public:
    EVENT(OnKeyPressed)

    explicit OnKeyPressed(Key key) :
        m_key(key)
    {
    }

    mustuse Key GetKey() const { return m_key; }

    mustuse String ToString() const override
    {
        return std::format("OnKeyPressed({})", static_cast<i32>(m_key));
    }
};

class OnKeyReleased : public Event
{
    Key m_key {};

public:
    EVENT(OnKeyReleased)

    explicit OnKeyReleased(Key key) :
        m_key(key)
    {
    }

    mustuse Key GetKey() const { return m_key; }

    mustuse String ToString() const override
    {
        return std::format("OnKeyReleased({})", static_cast<i32>(m_key));
    }
};

}
