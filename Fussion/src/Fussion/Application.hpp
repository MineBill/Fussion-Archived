#pragma once
#include "Fussion/Windowing/Window.hpp"

namespace fussion
{

class Application
{
    Ptr<Window> window {};
    bool running { true };

protected:
    virtual void OnLoad()
    {
        // Default implementation
    }

    virtual void OnUpdate(float)
    {
        // Default implementation
    }

    virtual void OnEvent(const Ref<Event> &)
    {
        // Default implementation
    }

    virtual void OnShutdown()
    {
        // Default implementation
    }

public:
    Application(const WindowProps &props);
    virtual ~Application() = default;

    void Run();
};

} // namespace fussion
