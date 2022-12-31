#pragma once
#include "Window.hpp"

namespace fussion {

class Application {
    Ptr<Window> m_window {};
    bool m_running { true };

protected:
    virtual void OnInitialize() { }
    virtual void OnUpdate(f32) { }
    virtual void OnEvent() { }
    virtual void OnShutdown() { }

public:
    Application();
    virtual ~Application() = default;

    void Run();
};

} // namespace fussion
