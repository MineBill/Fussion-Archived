#pragma once
#include "Window.hpp"

namespace fussion {

class Application {
    Ptr<Window> m_window {};
    bool m_running { true };

protected:
    virtual void on_initialize() { }
    virtual void on_update(f32) { }
    virtual void on_event(Ref<Event>) { }
    virtual void OnShutdown() { }

public:
    Application();
    virtual ~Application() = default;

    void run();
};

} // namespace fussion
