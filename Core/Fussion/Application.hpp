#pragma once
#include "Window.hpp"

namespace fussion {

class Application {
    Ptr<Window> m_window {};
    bool m_running { true };

protected:
    virtual void OnInitialize() { }
    virtual void OnUpdate() { }
    virtual void OnEvent() { }
    virtual void OnShutdown() { }

public:
    Application();

    void Run();
};

} // namespace fussion
