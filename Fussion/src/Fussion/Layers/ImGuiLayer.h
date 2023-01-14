#pragma once
#include "Fussion/Layer.h"

namespace Fussion
{

    class ImGuiLayer : public Fussion::Layer
    {
    public:
        void OnLoad() override;

        void OnUpdate(f32 elapsed) override;

        void OnEvent(const Ref<Fussion::Event> &event) override;

        static void BeginFrame(f32 elapsed);

        void EndFrame();
    };

} // namespace Fussion
