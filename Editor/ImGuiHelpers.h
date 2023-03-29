#pragma once
#include <imgui.h>

namespace ImGuiHelpers
{

    void BeginGroupPanel(const char *name, const ImVec2 &size = ImVec2(0, 0));
    void EndGroupPanel();
    void DragVec3(const char *id, glm::vec3 *value, f32 speed = 1.0f, f32 min = 0.0f, f32 max = 0.0f,
                  const char *format = "%.2f");
    bool ButtonCenteredOnLine(const char *label, float alignment = 0.5f);
} // namespace ImGuiHelpers
