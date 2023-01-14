#pragma once
#include "Fussion/Layer.h"

namespace fussion
{

class ImGuiLayer : public fussion::Layer
{
public:
    void OnLoad() override;

    void OnUpdate(f32 elapsed) override;

    void OnEvent(const Ref<fussion::Event> &event) override;

    static void BeginFrame(f32 elapsed);

    void EndFrame();
};

}
