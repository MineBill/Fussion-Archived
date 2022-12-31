#pragma once
#include "Event.hpp"

namespace fussion {

class OnKeyRepeated : public Event {
public:
    EVENT(OnKeyDown)

    explicit OnKeyRepeated(Key key)
        : m_key(key) {
    }

    mustuse Key key() const { return m_key; }

private:
    Key m_key {};
};

class OnKeyPressed : public Event {
public:
    EVENT(OnKeyPressed)

    explicit OnKeyPressed(Key key)
        : m_key(key) {
    }

    mustuse Key key() const { return m_key; }

private:
    Key m_key {};
};

class OnKeyReleased : public Event {
public:
    EVENT(OnKeyReleased)

    explicit OnKeyReleased(Key key)
        : m_key(key) {
    }

    mustuse Key key() const { return m_key; }

private:
    Key m_key {};
};

}
