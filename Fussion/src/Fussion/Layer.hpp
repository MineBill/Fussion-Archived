#pragma once
#include "Fussion/Types.hpp"
#include "Fussion/Events/Event.hpp"

namespace fussion {

class Layer {
public:
    virtual ~Layer() = default;

    virtual void OnLoad() {}

    virtual void OnUpdate(f32) {}

    virtual void OnEvent(const Ref<Event>&) {}
};

}
