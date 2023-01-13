#pragma once
#include "Fussion/Types.hpp"

namespace fussion
{

class ImGuiImpl
{
public:
    virtual ~ImGuiImpl() = default;

    static Ptr<ImGuiImpl> Create(i32 width, i32 height);

    virtual void WindowResized(i32 width, i32 height) = 0;
    virtual void Render() = 0;
    virtual void NewFrame(f32 elapsed) = 0;
};

}
