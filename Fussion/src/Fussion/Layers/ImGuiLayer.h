#pragma once
#include "Layer.h"

namespace Fussion
{

    class ImGuiLayer : public Fussion::Layer
    {
    public:
        void on_load() override;

        void on_update(f32 elapsed) override;

        bool on_event(Fussion::Event &event) override;

        static void begin_frame(f32 elapsed);

        void end_frame();
    };

} // namespace Fussion
