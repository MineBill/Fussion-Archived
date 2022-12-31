#pragma once
#include "Types.hpp"

namespace fussion {

struct WindowProps {
    i32 width { 0 }, height { 0 };
    std::string title { "" };
};

class Window {
public:
    virtual ~Window() = default;

    mustuse static Ptr<Window> Create(WindowProps const&);

    virtual void PollEvents() const = 0;
    virtual void SwapBuffers() const = 0;

    mustuse virtual bool ShouldClose() = 0;
};

}