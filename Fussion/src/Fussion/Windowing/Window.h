#pragma once
#include "Fussion/Events/Event.h"
#include "Fussion/Core/Types.h"
#include "VideoMode.h"
#include <functional>

namespace Fussion
{

    struct WindowProps {
        int width{0};
        int height{0};
        std::string title;
    };

    class Window
    {
    public:
        using EventCallback = std::function<void(Ptr<Event>)>;
        virtual ~Window() = default;

        mustuse static Ptr<Window> Create(WindowProps const &);

        virtual void PollEvents() const = 0;
        virtual void SwapBuffers() const = 0;
        virtual void SetEventCallback(EventCallback const &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual void SetShouldClose(bool enabled) = 0;

        mustuse virtual std::vector<VideoMode> GetVideoModes() const = 0;
        mustuse virtual bool ShouldClose() = 0;
        mustuse virtual std::pair<i32, i32> GetSize() const = 0;
        mustuse virtual void *Raw() = 0;
    };

} // namespace Fussion
