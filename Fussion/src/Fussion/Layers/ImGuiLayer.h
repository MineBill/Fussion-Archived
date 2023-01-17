#pragma once
#include "Layer.h"

namespace Fussion
{

    class ImGuiLayer : public Fussion::Layer
    {
    public:
        void OnLoad() override;

        void OnUpdate(f32 elapsed) override;

        bool OnEvent(Fussion::Event &event) override;

        static void BeginFrame(f32 elapsed);

        void EndFrame();
    };

} // namespace Fussion
