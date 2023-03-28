#include "PropertiesEditorPanel.h"
#include <Fussion/Scene/Components.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

using namespace Fussion;

void Editor::PropertiesEditorPanel::on_draw(Optional<Entity> selected, f32 delta)
{
    (void)delta;
    ImGui::Begin("Properties");
    if (selected.has_value()) {
        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Name"); ImGui::SameLine(); ImGui::InputText("##name", &selected->name().name);
        ImGui::Separator();

        if (ImGui::TreeNodeEx("##transform", ImGuiTreeNodeFlags_CollapsingHeader, "Transform")) {
        }
    }
    ImGui::End();
}
