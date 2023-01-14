#pragma once
#include "Fussion/Events/Event.h"
#include "Fussion/Types.h"

namespace fussion {

class Layer {
public:
    virtual ~Layer() = default;

    virtual void OnLoad() {}

    virtual void OnUpdate(f32) {}

    virtual void OnEvent(const Ref<Event>&) {}
};

}
