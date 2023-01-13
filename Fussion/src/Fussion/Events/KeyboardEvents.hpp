#pragma once
#include "Event.hpp"

namespace fussion {

class OnKeyDown : public Event {
    Key m_key {};

public:
    EVENT(OnKeyDown)

    explicit OnKeyDown(Key key)
        : m_key(key) {
    }

    mustuse Key GetKey() const { return m_key; }
};

class OnKeyPressed : public Event {
    Key m_key {};

public:
    EVENT(OnKeyPressed)

    explicit OnKeyPressed(Key key)
        : m_key(key) {
    }

    mustuse Key GetKey() const { return m_key; }
};

class OnKeyReleased : public Event {
    Key m_key {};

public:
    EVENT(OnKeyReleased)

    explicit OnKeyReleased(Key key)
        : m_key(key) {
    }

    mustuse Key GetKey() const { return m_key; }
};

}
