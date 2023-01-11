#pragma once
#include "Fussion/Events/Event.hpp"
#include "Fussion/Types.hpp"
#include "VideoMode.hpp"
#include <functional>

namespace fussion
{

struct WindowProps {
    int width { 0 };
    int height { 0 };
    std::string title;
};

class Window
{
public:
    using EventCallback = std::function<void(Ref<Event>)>;
    virtual ~Window() = default;

    mustuse static Ptr<Window> create(WindowProps const &);

    virtual void PollEvents() const = 0;
    virtual void SwapBuffers() const = 0;
    virtual void OnEvent(EventCallback const &callback) = 0;
    virtual void SetVSync(bool enabled) = 0;

    mustuse virtual std::vector<VideoMode> VideoModes() const = 0;

    mustuse virtual bool ShouldClose() = 0;
};

}