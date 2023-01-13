#pragma once
#include "Fussion/Events/Event.hpp"
#include "Fussion/Types.hpp"

namespace fussion
{

class IComponent
{
public:
    virtual ~IComponent() = default;

    virtual void OnLoad() {}

    virtual void OnUpdate(f32) {}

    virtual void OnEvent(Ref<Event>) {}
};

}