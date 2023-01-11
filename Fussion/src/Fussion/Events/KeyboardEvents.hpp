#pragma once
#include "Event.hpp"

namespace fussion {

class OnKeyRepeated : public Event {
    Key key {};

public:
    EVENT(OnKeyDown)

    explicit OnKeyRepeated(Key key)
        : key(key) {
    }

    mustuse Key Key() const { return key; }
};

class OnKeyPressed : public Event {
    Key key {};

public:
    EVENT(OnKeyPressed)

    explicit OnKeyPressed(Key key)
        : key(key) {
    }

    mustuse Key Key() const { return key; }
};

class OnKeyReleased : public Event {
    Key key {};

public:
    EVENT(OnKeyReleased)

    explicit OnKeyReleased(Key key)
        : key(key) {
    }

    mustuse Key Key() const { return key; }
};

}
